#include "Enemy.h"
#include "../game.h"
#include "DxLib.h"
#include "Pad.h"

#include "SceneMain.h"

namespace
{
	constexpr int kSize = 32;
	const int kColor = GetColor(255,0,0);
}

Enemy::Enemy()
{
	m_shotInterval = 0;;
}
Enemy::~Enemy()
{

}

void Enemy::init()
{
	
}

void Enemy::end()
{

}

void Enemy::update()
{
	if (!m_isExist)	return;
	m_shotInterval--;
	if (m_shotInterval <= 0)
	{
		m_pMain->addEnemyShot(getShotStartPos());
		m_shotInterval = 120;
	}
}

void Enemy::draw()
{
	if (!m_isExist)	return;
	DrawBoxAA(m_pos.x, m_pos.y, m_pos.x + m_colSize.x, m_pos.y + m_colSize.y, kColor, true);
}

void Enemy::setStart(Vec2 pos)
{
	m_isExist = true;
	m_pos = pos;

	m_colSize.x = kSize;
	m_colSize.y = kSize;

	m_shotInterval = 120;
}

void Enemy::beHit()
{
	m_isExist = false;
	Vec2 pos = m_pos;
	pos.x += m_colSize.x / 2;
	pos.y += m_colSize.y / 2;
	m_pMain->createParticle(pos, kColor, 32);
}

Vec2 Enemy::getShotStartPos() const
{
	Vec2 result = m_pos;
	result.x += m_colSize.x / 2.0f;
	result.y += m_colSize.y;
	return result;
}