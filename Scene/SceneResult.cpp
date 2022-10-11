#include "DxLib.h"
#include "game.h"
#include "SceneResult.h"
#include "SceneTitle.h"
#include "Pad.h"


namespace
{
	// �t�F�[�h�C���A�E�g���x
	constexpr int kFadeSpeed = 8;

	// �\�����镶����
	const char* const kSuccessText = "��퐬��";
	const char* const kFailText = "��편�s";
	const char* const kScoreText = "���j��:%d";
	const char* const kGuideText = "1�{�^���������Ă�������";
	// ������_��
	constexpr int kTextDispFrame = 45;
	constexpr int kTextHideFrame = 15;
}

void SceneResult::init()
{
	m_textBlinkFrame = 0;
	m_fadeBright = 0;
	m_fadeSpeed = kFadeSpeed;
}

void SceneResult::end()
{
	SetDrawBright(255, 255, 255);
}

SceneBase* SceneResult::update()
{
	if( isFading() )
	{
		m_fadeBright += m_fadeSpeed;
		if (m_fadeBright <= 0)
		{
			if (m_fadeSpeed < 0)
			{
				// Main�ɐ؂�ւ�
				return (new SceneTitle);
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

void SceneResult::draw()
{
	SetDrawBright(m_fadeBright, m_fadeBright, m_fadeBright);

	if (m_isSuccess)
	{
		int width = GetDrawStringWidth(kSuccessText, strlen(kSuccessText));
		DrawString(Game::kScreenWidth / 2 - width / 2, 180, kSuccessText, GetColor(255, 255, 255));
	}
	else
	{
		int width = GetDrawStringWidth(kFailText, strlen(kFailText));
		DrawString(Game::kScreenWidth / 2 - width / 2, 180, kFailText, GetColor(255, 255, 255));

		DrawFormatString(Game::kScreenWidth / 2 - width / 2, 196, GetColor(255, 255, 255), kScoreText, m_destroyNum);
	}
	

	if (m_textBlinkFrame < kTextDispFrame)
	{
		int width = GetDrawStringWidth(kGuideText, strlen(kGuideText));
		DrawString(Game::kScreenWidth / 2 - width / 2, 300, kGuideText, GetColor(255, 255, 255));
	}
}

void SceneResult::setResult(bool isWin, int destroyNum)
{
	m_isSuccess = isWin;
	m_destroyNum = destroyNum;
}

bool SceneResult::isFading() const
{
	return (m_fadeSpeed != 0);
}