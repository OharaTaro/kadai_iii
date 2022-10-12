#pragma once
#include "SceneBase.h"

class SceneTitle : public SceneBase
{
public:
	SceneTitle() 
	{
		m_textBlinkFrame = 0;
	}
	virtual ~SceneTitle() {}


	virtual void init() override;
	virtual void end() override;

	virtual SceneBase* update() override;
	virtual void draw() override;
private:
	// �e�L�X�g�_�ŗp�t���[���J�E���g
	int m_textBlinkFrame;
};