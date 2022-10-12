#pragma once

#include "ObjectBase.h"

class Player : public ObjectBase
{
public:
	Player();
	virtual ~Player();

	virtual void init() override;
	virtual void end() override;

	virtual void update() override;
	virtual void draw() override;

	virtual ColType getColType() const override { return ColType::kPlayer; }
	virtual ColType getTargetColType() const override { return ColType::kNone; }

	// 敵の弾が当たったときの処理
	virtual void beHit() override;
	// 弾発射位置の取得
	Vec2 getShotStartPos() const;

private:
	int		m_shotInterval;
};