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
	{
		Player* pPlayer = new Player;
		pPlayer->init();
		pPlayer->setMain(this);
		m_object.push_back(pPlayer);
	}
	for (int i = 0; i < 24; i++)
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
	// �e�I�u�W�F�N�g�̏���
	updateObject(m_object);

	// �����蔻��
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

	// �v���C���[�����񂾂�^�C�g���ɖ߂�
	if (!isExistPlayer())
	{
		m_endCount++;
		if (m_endCount >= 180)
		{
			return (new SceneTitle);
		}
	}
	return this;
}

void SceneMain::draw()
{
	drawObject(m_object);

	// �f�o�b�O�\��
//	DrawFormatString(0,  0, GetColor(255, 255, 255), "�e�̐�:%d", m_shot.size());
//	DrawFormatString(0, 16, GetColor(255, 255, 255), "�G�̐�:%d", m_enemy.size());
//	DrawFormatString(0, 32, GetColor(255, 255, 255), "�G�t�F�N�g�̐�:%d", m_particle.size());

	DrawFormatString(0, 32, GetColor(255, 255, 255), "�I�u�W�F�N�g�̐�:%d", m_object.size());
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

bool SceneMain::isExistPlayer() const
{
	for (auto& pObj : m_object)
	{
		if (pObj->getColType() == ObjectBase::ColType::kPlayer)
		{
			return true;
		}
	}
	return false;
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