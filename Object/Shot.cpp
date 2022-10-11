#include "Shot.h"
#include "../game.h"
#include "DxLib.h"
#include "Pad.h"

#include "Enemy.h"

namespace
{
	// サイズ
	constexpr int kSize = 8;
	// 移動速度
	constexpr float kSpeed = -4.0f;
}

namespace
{
	
}

Shot::Shot()
{
	
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
	if (m_pos.y < 0.0f - 4.0f)
	{
		m_isExist = false;
	}
}

void Shot::draw()
{
	if (!m_isExist)	return;
	DrawBoxAA(m_pos.x, m_pos.y, m_pos.x + m_colSize.x, m_pos.y + m_colSize.y, GetColor(0, 0, 255), true);
}

void Shot::start(Vec2 pos)
{
	m_isExist = true;
	m_pos = pos;

	m_colSize.x = kSize;
	m_colSize.y = kSize;

	m_vec.x = 0.0f;
	m_vec.y = kSpeed;
}
#if false
void Shot::col(Enemy& target)
{
	if (isCol(target))
	{
		m_isExist = false;
		target.damage();
	}
}
#endif