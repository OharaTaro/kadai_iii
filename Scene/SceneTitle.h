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
	// フェードインorアウト中
	bool isFading() const;
private:
	// テキスト点滅用フレームカウント
	int m_textBlinkFrame;

	int m_fadeBright;
	int m_fadeSpeed;
};