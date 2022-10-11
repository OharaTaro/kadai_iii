#pragma once

#include "ObjectBase.h"
class Enemy;

class Shot : public ObjectBase
{
public:
	Shot();
	virtual ~Shot();

	virtual void init() override;
	virtual void end() override;

	virtual void update() override;
	virtual void draw() override;

	// 発射開始
	void start(Vec2 pos);
//	// 敵と当たった時の処理
//	void col(Enemy& target);

	// 敵にぶつかったときの処理
	virtual void hit() { m_isExist = false; };

	virtual ColType getColType() const override { return ColType::kPlayerShot; }
	virtual ColType getTargetColType() const override { return ColType::kEnemy; }

private:
	Vec2	m_vec;
};