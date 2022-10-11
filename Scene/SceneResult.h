#pragma once
#include "SceneBase.h"

class SceneResult : public SceneBase
{
public:
	SceneResult()
	{
		m_isSuccess = false;
		m_destroyNum = 0;
		m_textBlinkFrame = 0;
		m_fadeBright = 0;
		m_fadeSpeed = 0;
	}
	virtual ~SceneResult() {}


	virtual void init() override;
	virtual void end() override;

	virtual SceneBase* update() override;
	virtual void draw() override;

	void setResult(bool isWin, int destroyNum);

private:
	// �t�F�[�h�C��or�A�E�g��
	bool isFading() const;
private:
	// �Q�[������
	bool m_isSuccess;
	int m_destroyNum;

	// �e�L�X�g�_�ŗp�t���[���J�E���g
	int m_textBlinkFrame;

	int m_fadeBright;
	int m_fadeSpeed;
};