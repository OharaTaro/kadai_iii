#pragma once
#include "SceneBase.h"

class SceneTitle : public SceneBase
{
public:
	SceneTitle() 
	{
		m_textBlinkFrame = 0;
		m_fadeBright = 0;
		m_fadeSpeed = 0;
	}
	virtual ~SceneTitle() {}


	virtual void init() override;
	virtual void end() override;

	virtual SceneBase* update() override;
	virtual void draw() override;
private:
	// �t�F�[�h�C��or�A�E�g��
	bool isFading() const;
private:
	// �e�L�X�g�_�ŗp�t���[���J�E���g
	int m_textBlinkFrame;

	int m_fadeBright;
	int m_fadeSpeed;
};