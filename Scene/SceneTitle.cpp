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
	// •¶š‚ÌˆÚ“®
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
		// Main‚ÉØ‚è‘Ö‚¦
		return (new SceneMain);
	}

	return this;
}

void SceneTitle::draw()
{
	DrawString(0, m_textPosY,"ƒ^ƒCƒgƒ‹‰æ–Ê",GetColor(255,255,255));
}