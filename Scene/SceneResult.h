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
	// フェードインorアウト中
	bool isFading() const;
private:
	// ゲーム結果
	bool m_isSuccess;
	int m_destroyNum;

	// テキスト点滅用フレームカウント
	int m_textBlinkFrame;

	int m_fadeBright;
	int m_fadeSpeed;
};