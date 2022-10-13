#include "Shot.h"
#include "../game.h"
#include "DxLib.h"
#include "Pad.h"

#include "Enemy.h"

namespace
{
	// サイズ
	constexpr int kSize = 16;
	// 移動速度
	constexpr float kSpeed = -4.0f;
}

namespace
{
	
}

Shot::Shot()
{
	m_hGraph = 0;
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
	DrawRectGraph(m_pos.x, m_pos.y,
		0, 0, kSize, kSize,
		m_hGraph, true, false);

	// 当たり判定の表示
//	DrawBoxAA(m_pos.x, m_pos.y, m_pos.x + m_colSize.x, m_pos.y + m_colSize.y, GetColor(0, 0, 255), false);
}

void Shot::startPlayer(Vec2 centerPos)
{
	m_isExist = true;
	m_pos = centerPos;

	m_colSize.x = kSize;
	m_colSize.y = kSize;

	m_pos -= m_colSize / 2;

	m_vec.x = 0.0f;
	m_vec.y = kSpeed;

	m_myType = ColType::kPlayerShot;
	m_targetType = ColType::kEnemy;
}

void Shot::startEnemy(Vec2 centerPos)
{
	m_isExist = true;
	m_pos = centerPos;

	m_colSize.x = kSize;
	m_colSize.y = kSize;

	m_pos -= m_colSize / 2;

	m_vec.x = 0.0f;
	m_vec.y = -kSpeed;

	m_myType = ColType::kEnemyShot;
	m_targetType = ColType::kPlayer;
}
