#include "DxLib.h"
#include "SceneTitle.h"
#include "SceneMain.h"
//#include "SceneTest.h"
#include "Pad.h"

void SceneTitle::init()
{
	m_textPosY = 0;
	m_textVecY = 4;
}

SceneBase* SceneTitle::update()
{
	// 文字の移動
	m_textPosY += m_textVecY;
	if (m_textPosY < 0)
	{
		m_textPosY = 0;
		m_textVecY = 4;
	}
	if (m_textPosY > 200)
	{
		m_textPosY = 200;
		m_textVecY = -4;
	}

	if (Pad::isTrigger(PAD_INPUT_1))
	{
		// Mainに切り替え
		return (new SceneMain);
	}

	return this;
}

void SceneTitle::draw()
{
	DrawString(0, m_textPosY,"タイトル画面",GetColor(255,255,255));
}