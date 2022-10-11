#include "Player.h"
#include "game.h"
#include "DxLib.h"
#include "Pad.h"
#include "SceneMain.h"

namespace
{
	// サイズ
	constexpr int kSize = 32;

	// 移動速度
	constexpr float kSpeed = 4.0f;
	// 弾の発射間隔(フレーム)
	constexpr int kShotInterval = 16;
}

Player::Player()
{
	m_shotInterval = 0;
}
Player::~Player()
{

}

void Player::init()
{
	m_isExist = true;

	m_pos.x = Game::kScreenWidth / 2;
	m_pos.y = Game::kScreenHeight - 80.0f;

	m_colSize.x = kSize;
	m_colSize.x = kSize;
}

void Player::end()
{

}

void Player::update()
{
	m_shotInterval++;
	if( (Pad::isPress(PAD_INPUT_1)) &&
		(m_shotInterval >= kShotInterval) )
	{
		m_pMain->addShot(m_pos);
		m_shotInterval = 0;
	}

	if (Pad::isPress(PAD_INPUT_LEFT))
	{
		m_pos.x -= kSpeed;
	}
	if (Pad::isPress(PAD_INPUT_RIGHT))
	{
		m_pos.x += kSpeed;
	}
	if (m_pos.x < 0.0f)
	{
		m_pos.x = 0.0f;
	}
	if (m_pos.x > Game::kScreenWidth)
	{
		m_pos.x = Game::kScreenWidth;
	}
}

void Player::draw()
{
	DrawCircleAA(m_pos.x, m_pos.y, m_colSize.x/2, 32, GetColor(255, 255, 255), true);
}