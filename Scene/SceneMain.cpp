#include "DxLib.h"
#include "game.h"
#include "SceneMain.h"
#include "SceneTitle.h"
#include "SceneResult.h"
#include "Pad.h"

#include "Enemy.h"
#include "Shot.h"
#include "Particle.h"

namespace
{
	// グラフィックファイル名
	const char* const kPlayerFileName		= "Data/player.png";
	const char* const kEnemyFileName		= "Data/enemy00.png";
	const char* const kPlayerShotFileName	= "Data/playerShot.png";
	const char* const kEnemyShotFileName	= "Data/enemyShot.png";
	const char* const kBgFileName			= "Data/bg.png";
	// ファイル名リスト
	typedef enum GraphicFileData
	{
		kGraphicFileData_Player,
		kGraphicFileData_Enemy,
		kGraphicFileData_PlayerShot,
		kGraphicFileData_EnemyShot,
		kGraphicFileData_Bg,

		kGraphicFileData_Num
	}GraphicFileData;
	const char* const kGraphicFileNameList[kGraphicFileData_Num] =
	{
		kPlayerFileName,
		kEnemyFileName,
		kPlayerShotFileName,
		kEnemyShotFileName,
		kBgFileName,
	};

	// 背景色
	const int kBgColor = GetColor(160, 216, 239);

	// プレイヤー死亡or敵全滅後、タイトルに戻るまでのフレーム数
	constexpr int kGameEndWaitFrame = 150;
	constexpr int kGameEndFadeOutStartFrame = 120;
	// 敵の数
	constexpr int kEnemyNum = 24;
}

// ===============================================

void SceneMain::init()
{
	for (auto& fileName : kGraphicFileNameList)
	{
		int handle = LoadGraph(fileName);
		m_graphicHandle.push_back(handle);
	}

	{
		Player* pPlayer = new Player;
		pPlayer->init();
		pPlayer->setMain(this);
		pPlayer->setGraph(m_graphicHandle[kGraphicFileData_Player]);
		m_object.push_back(pPlayer);
	}
	for (int i = 0; i < kEnemyNum; i++)
	{
		Enemy* pEnemy = new Enemy;

		pEnemy->init();
		pEnemy->setMain(this);
		pEnemy->setGraph(m_graphicHandle[kGraphicFileData_Enemy]);
		Vec2 pos;
		pos.x = static_cast<float>( (i % 8) * 64 + 90 );
		pos.y = static_cast<float>( (i / 8) * 64 + 60 );
		pEnemy->setStart(pos);
		m_object.push_back(pEnemy);
	}

	m_bgScroll = 0.0f;
	m_endCount = 0;
}

void SceneMain::end()
{
	endObject(m_object);
	for (auto& handle : m_graphicHandle)
	{
		DeleteGraph(handle);
		handle = -1;
	}
	m_graphicHandle.clear();
}

SceneBase* SceneMain::update()
{
	SceneBase::updateFade();
	if (isFading())	return this;	// フェードイン、アウト中は動かない
	// 背景のスクロール
	m_bgScroll += 1.0f;
	if (m_bgScroll > Game::kScreenHeight)
	{
		m_bgScroll -= Game::kScreenHeight;
	}

	// 各オブジェクトの処理
	updateObject(m_object);

	// 当たり判定
	for (auto& hitObj : m_object)
	{
		for (auto& beHitObj : m_object)
		{
			if (hitObj->isCol(*beHitObj))
			{
				hitObj->hit();
				beHitObj->beHit();
			}
		}
	}

	// 敵が全滅orプレイヤーが死んだらタイトルに戻る
	if (!isExistPlayer() || (getEnemyNum() == 0))
	{
		m_endCount++;
		if( (!isFading()) && (m_endCount >= kGameEndFadeOutStartFrame) )
		{
			startFadeOut();
		}
		if (m_endCount >= kGameEndWaitFrame)
		{
			// 結果表示画面へ	ゲーム結果もここで渡しておく
			SceneResult* pResult = new SceneResult;
			pResult->setResult(isExistPlayer(), kEnemyNum - getEnemyNum());
			return pResult;
		}
	}
	return this;
}

void SceneMain::draw()
{
	// 背景色
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, kBgColor, true);

	// 背景
	DrawGraphF(0, m_bgScroll, m_graphicHandle[kGraphicFileData_Bg], true);
	DrawGraphF(0, m_bgScroll - Game::kScreenHeight , m_graphicHandle[kGraphicFileData_Bg], true);

	drawObject(m_object);

	DrawFormatString(0, 16, GetColor(255, 255, 255), "敵の数:%d", getEnemyNum());
	DrawFormatString(0, 32, GetColor(255, 255, 255), "オブジェクトの数:%d", m_object.size());

	SceneBase::drawFade();
}

void SceneMain::addPlayerShot(Vec2 pos)
{
	Shot* pShot = new Shot;
	pShot->init();
	pShot->setMain(this);
	pShot->setGraph(m_graphicHandle[kGraphicFileData_PlayerShot]);
	pShot->startPlayer(pos);
	m_object.push_back(pShot);
}

void SceneMain::addEnemyShot(Vec2 pos)
{
	Shot* pShot = new Shot;
	pShot->init();
	pShot->setMain(this);
	pShot->setGraph(m_graphicHandle[kGraphicFileData_EnemyShot]);
	pShot->startEnemy(pos);
	m_object.push_back(pShot);
}

bool SceneMain::isEnemyShotEnable(Vec2 shotStartPos)
{
	for (const auto& pObj : m_object)
	{
		if (pObj->getColType() == ObjectBase::ColType::kEnemy)
		{
			// 発射位置よりも上にいる敵は気にしない
			if (shotStartPos.y > pObj->getTop())	continue;
			// 左右位置がずれている敵は気にしない
			if (shotStartPos.x > pObj->getRight())	continue;
			if (shotStartPos.x < pObj->getLeft())	continue;
			// それ以外は弾の射線上にいるので撃たない
			return false;
		}
	}
	return true;
}

bool SceneMain::isExistPlayer() const
{
	for (const auto& pObj : m_object)
	{
		if (pObj->getColType() == ObjectBase::ColType::kPlayer)
		{
			return true;
		}
	}
	return false;
}

int SceneMain::getEnemyNum() const
{
	int result = 0;
	for (const auto& pObj : m_object)
	{
		if (pObj->getColType() == ObjectBase::ColType::kEnemy)
		{
			result++;
		}
	}
	return result;
}

void SceneMain::createParticle(Vec2 pos, int color, int num)
{
	for (int i = 0; i < num; i++)
	{
		Particle* pPart = new Particle;
		pPart->init();
		pPart->setMain(this);
		pPart->start(pos, color);
		m_object.push_back(pPart);
	}
}

void SceneMain::updateObject(std::list<ObjectBase*>& obj)
{
	std::list<ObjectBase*>::iterator it = obj.begin();
	while (it != obj.end())
	{
		auto pObj = (*it);
		pObj->update();
		if (!pObj->isExist())
		{
			delete pObj;
			it = obj.erase(it);
		}
		else
		{
			it++;
		}
	}
}
void SceneMain::drawObject(std::list<ObjectBase*>& obj)
{
	for (auto& pObj : obj)
	{
		pObj->draw();
	}
}
void SceneMain::endObject(std::list<ObjectBase*>& obj)
{
	for (auto& pObj : obj)
	{
		pObj->end();
		delete pObj;
	}
	obj.clear();
}