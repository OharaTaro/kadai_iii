#include "DxLib.h"
#include "game.h"
#include "SceneTitle.h"
#include "SceneMain.h"
#include "Pad.h"


namespace
{
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
}

void SceneTitle::end()
{
	
}

SceneBase* SceneTitle::update()
{
	if(isFading())
	{
		bool isOut = isFadingOut();
		SceneBase::updateFade();
		// �t�F�[�h�A�E�g�I�����ɃV�[���؂�ւ�
		if (!isFading() && isOut)
		{
			return (new SceneMain);
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
			startFadeOut();
		}
	}
	return this;
}

void SceneTitle::draw()
{
	int width = GetDrawStringWidth(kTitleText, static_cast<int>(strlen(kTitleText)));
	DrawString(Game::kScreenWidth/2 - width/2, 180, kTitleText,GetColor(255,255,255));

	if (m_textBlinkFrame < kTextDispFrame)
	{
		width = GetDrawStringWidth(kGuideText, static_cast<int>(strlen(kGuideText)));
		DrawString(Game::kScreenWidth / 2 - width / 2, 300, kGuideText, GetColor(255, 255, 255));
	}

	SceneBase::drawFade();
}