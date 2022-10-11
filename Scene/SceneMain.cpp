#include "DxLib.h"
#include "SceneMain.h"
#include "SceneTitle.h"
#include "Pad.h"

#include "Enemy.h"
#include "Shot.h"
#include "Particle.h"

// ===============================================

void SceneMain::init()
{
	m_player.init();
	m_player.setMain(this);
	for (int i = 0; i < 24; i++)
	{
		Enemy* pEnemy = new Enemy;

		pEnemy->init();
		pEnemy->setMain(this);
		Vec2 pos;
		pos.x = static_cast<float>( (i % 8) * 64 + 90 );
		pos.y = static_cast<float>( (i / 8) * 64 + 60 );
		pEnemy->setStart(pos);
		m_enemy.push_back(pEnemy);
	}
}

void SceneMain::end()
{
	m_player.end();
	endObject(m_enemy);
	endObject(m_shot);
	endObject(m_particle);
}

SceneBase* SceneMain::update()
{
	// 各オブジェクトの処理
	m_player.update();
	updateObject(m_enemy);
	updateObject(m_shot);
	updateObject(m_particle);

	// 当たり判定
	for (auto& shot : m_shot)
	{
		for (auto& enemy : m_enemy)
		{
			if (shot->isCol(*enemy))
			{
				shot->hit();
				enemy->beHit();
			}
		}
	}

#if false
	if (Pad::isTrigger(PAD_INPUT_2))
	{
		return (new SceneTitle);
	}
#endif
	return this;
}

void SceneMain::draw()
{
	m_player.draw();
	drawObject(m_particle);
	drawObject(m_shot);
	drawObject(m_enemy);

	// デバッグ表示
	DrawFormatString(0,  0, GetColor(255, 255, 255), "弾の数:%d", m_shot.size());
	DrawFormatString(0, 16, GetColor(255, 255, 255), "敵の数:%d", m_enemy.size());
	DrawFormatString(0, 32, GetColor(255, 255, 255), "エフェクトの数:%d", m_particle.size());
}

void SceneMain::addShot(Vec2 pos)
{
	Shot* pShot = new Shot;
	pShot->init();
	pShot->setMain(this);
	pShot->start(pos);
	m_shot.push_back(pShot);
}

void SceneMain::createParticle(Vec2 pos, int color, int num)
{
	for (int i = 0; i < num; i++)
	{
		Particle* pPart = new Particle;
		pPart->init();
		pPart->setMain(this);
		pPart->start(pos, color);
		m_particle.push_back(pPart);
	}
}

void SceneMain::updateObject(std::vector<ObjectBase*>& obj)
{
	std::vector<ObjectBase*>::iterator it = obj.begin();
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
void SceneMain::drawObject(std::vector<ObjectBase*>& obj)
{
	for (auto& pObj : obj)
	{
		pObj->draw();
	}
}
void SceneMain::endObject(std::vector<ObjectBase*>& obj)
{
	for (auto& pObj : obj)
	{
		pObj->end();
		delete pObj;
	}
	obj.clear();
}