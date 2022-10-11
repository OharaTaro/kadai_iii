#include "DxLib.h"
#include "game.h"
#include "SceneTitle.h"
#include "SceneMain.h"
#include "Pad.h"


namespace
{
	// フェードインアウト速度
	constexpr int kFadeSpeed = 8;

	// 表示する文字列
	const char* const kTitleText = "インベーダー風ゲーム";
	const char* const kGuideText = "1ボタンを押してください";
	// 文字列点滅
	constexpr int kTextDispFrame = 45;
	constexpr int kTextHideFrame = 15;
}

void SceneTitle::init()
{
	m_textBlinkFrame = 0;
	m_fadeBright = 0;
	m_fadeSpeed = kFadeSpeed;
}

void SceneTitle::end()
{
	SetDrawBright(255, 255, 255);
}

SceneBase* SceneTitle::update()
{
	if( isFading() )
	{
		m_fadeBright += m_fadeSpeed;
		if (m_fadeBright <= 0)
		{
			if (m_fadeSpeed < 0)
			{
				// Mainに切り替え
				return (new SceneMain);
			}
			m_fadeBright = 0;
			m_fadeSpeed = 0;
		}
		if (m_fadeBright >= 255)
		{
			m_fadeBright = 255;
			m_fadeSpeed = 0;
		}
	}
	// テキストの点滅
	m_textBlinkFrame++;
	if (m_textBlinkFrame >= kTextDispFrame + kTextHideFrame)
	{
		m_textBlinkFrame = 0;
	}
	if (!isFading())
	{
		if (Pad::isTrigger(PAD_INPUT_1))
		{
			// フェードアウト開始
			m_fadeSpeed = -kFadeSpeed;
		}
	}
	return this;
}

void SceneTitle::draw()
{
	SetDrawBright(m_fadeBright, m_fadeBright, m_fadeBright);

	int width = GetDrawStringWidth(kTitleText, strlen(kTitleText));
	DrawString(Game::kScreenWidth/2 - width/2, 180, kTitleText,GetColor(255,255,255));

	if (m_textBlinkFrame < kTextDispFrame)
	{
		width = GetDrawStringWidth(kGuideText, strlen(kGuideText));
		DrawString(Game::kScreenWidth / 2 - width / 2, 300, kGuideText, GetColor(255, 255, 255));
	}
}

bool SceneTitle::isFading() const
{
	return (m_fadeSpeed != 0);
}