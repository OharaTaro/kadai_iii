#include "Enemy.h"
#include "../game.h"
#include "DxLib.h"
#include "Pad.h"

#include "SceneMain.h"

namespace
{
	constexpr int kSize = 32;
	const int kColor = GetColor(255,0,0);

	// アニメーション情報
	constexpr int kAnimNum = 4;		// アニメのコマ数
	constexpr int kAnimNo[kAnimNum] = { 0, 1, 2,1 };
	constexpr int kAnimFrame = 8;	// １コマ当たりのフレーム数
}

Enemy::Enemy()
{
	m_hGraph = -1;
	m_animFrameCount = 0;
	m_shotInterval = 0;
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
	// アニメーション
	m_animFrameCount++;
	if (m_animFrameCount >= kAnimNum * kAnimFrame)
	{
		m_animFrameCount = 0;
	}
	// 一定間隔でショットを撃つ
	m_shotInterval--;
	if (m_shotInterval <= 0)
	{
		if (m_pMain->isEnemyShotEnable(getShotStartPos()))
		{
			m_pMain->addEnemyShot(getShotStartPos());
		}
		m_shotInterval = 120;
	}
}

void Enemy::draw()
{
	if (!m_isExist)	return;

	int animIndex = m_animFrameCount / kAnimFrame;
	int animNo = kAnimNo[animIndex];
	DrawRectGraph(m_pos.x, m_pos.y,
		animNo * kSize, 0, kSize, kSize,
		m_hGraph, true, false);

	// 当たり判定表示
//	DrawBoxAA(m_pos.x, m_pos.y, m_pos.x + m_colSize.x, m_pos.y + m_colSize.y, kColor, false);
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