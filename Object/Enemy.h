#pragma once

#include "ObjectBase.h"

class Enemy : public ObjectBase
{
public:
	Enemy();
	virtual ~Enemy();

	virtual void init() override;
	virtual void end() override;

	virtual void update() override;
	virtual void draw() override;

	// 初期位置の設定
	void setStart(Vec2 pos);
	// プレイヤーのたまにぶつかられた時の処理
	virtual void beHit();

	virtual ColType getColType() const override { return ColType::kEnemy; }
	virtual ColType getTargetColType() const override { return ColType::kPlayer; }

private:
	int m_shotInterval;
};