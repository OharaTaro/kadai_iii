#include "DxLib.h"
#include "SceneMain.h"
#include "SceneTitle.h"
#include "SceneResult.h"
#include "Pad.h"

#include "Enemy.h"
#include "Shot.h"
#include "Particle.h"

namespace
{
	// プレイヤー死亡or敵全滅後、タイトルに戻るまでのフレーム数
	constexpr int kGameEndWaitFrame = 150;
	constexpr int kGameEndFadeOutStartFrame = 120;
	// 敵の数
	constexpr int kEnemyNum = 24;
}

// ===============================================

void SceneMain::init()
{
	{
		Player* pPlayer = new Player;
		pPlayer->init();
		pPlayer->setMain(this);
		m_object.push_back(pPlayer);
	}
	for (int i = 0; i < kEnemyNum; i++)
	{
		Enemy* pEnemy = new Enemy;

		pEnemy->init();
		pEnemy->setMain(this);
		Vec2 pos;
		pos.x = static_cast<float>( (i % 8) * 64 + 90 );
		pos.y = static_cast<float>( (i / 8) * 64 + 60 );
		pEnemy->setStart(pos);
		m_object.push_back(pEnemy);
	}

	m_endCount = 0;
}

void SceneMain::end()
{
	endObject(m_object);
}

SceneBase* SceneMain::update()
{
	SceneBase::updateFade();
	if (isFading())	return this;	// フェードイン、アウト中は動かない

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
	pShot->startPlayer(pos);
	m_object.push_back(pShot);
}

void SceneMain::addEnemyShot(Vec2 pos)
{
	Shot* pShot = new Shot;
	pShot->init();
	pShot->setMain(this);
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