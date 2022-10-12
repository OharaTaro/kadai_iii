#include "Shot.h"
#include "../game.h"
#include "DxLib.h"
#include "Pad.h"

#include "Enemy.h"

namespace
{
	// �T�C�Y
	constexpr int kSize = 8;
	// �ړ����x
	constexpr float kSpeed = -4.0f;
}

namespace
{
	
}

Shot::Shot()
{
	m_myType = ColType::kPlayerShot;
	m_targetType = ColType::kEnemy;
}
Shot::~Shot()
{

}

void Shot::init()
{
	
}

void Shot::end()
{

}

void Shot::update()
{
	if (!m_isExist)	return;
	m_pos += m_vec;
	if ((m_vec.y < 0) &&
		(m_pos.y < 0.0f - kSize) )
	{
		m_isExist = false;
	}
	if ((m_vec.y > 0) &&
		(m_pos.y > Game::kScreenHeight))
	{
		m_isExist = false;
	}
}

void Shot::draw()
{
	if (!m_isExist)	return;
	DrawBoxAA(m_pos.x, m_pos.y, m_pos.x + m_colSize.x, m_pos.y + m_colSize.y, GetColor(0, 0, 255), true);
}

void Shot::startPlayer(Vec2 pos)
{
	m_isExist = true;
	m_pos = pos;

	m_colSize.x = kSize;
	m_colSize.y = kSize;

	m_vec.x = 0.0f;
	m_vec.y = kSpeed;

	m_myType = ColType::kPlayerShot;
	m_targetType = ColType::kEnemy;
}

void Shot::startEnemy(Vec2 pos)
{
	m_isExist = true;
	m_pos = pos;

	m_colSize.x = kSize;
	m_colSize.y = kSize;

	m_vec.x = 0.0f;
	m_vec.y = -kSpeed;

	m_myType = ColType::kEnemyShot;
	m_targetType = ColType::kPlayer;
}