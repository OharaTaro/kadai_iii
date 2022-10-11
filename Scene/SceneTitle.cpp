#include "DxLib.h"
#include "game.h"
#include "SceneTitle.h"
#include "SceneMain.h"
#include "Pad.h"


namespace
{
	// �t�F�[�h�C���A�E�g���x
	constexpr int kFadeSpeed = 8;

	// �\�����镶����
	const char* const kTitleText = "�C���x�[�_�[���Q�[��";
	const char* const kGuideText = "1�{�^���������Ă�������";
	// ������_��
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
				// Main�ɐ؂�ւ�
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
	// �e�L�X�g�̓_��
	m_textBlinkFrame++;
	if (m_textBlinkFrame >= kTextDispFrame + kTextHideFrame)
	{
		m_textBlinkFrame = 0;
	}
	if (!isFading())
	{
		if (Pad::isTrigger(PAD_INPUT_1))
		{
			// �t�F�[�h�A�E�g�J�n
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