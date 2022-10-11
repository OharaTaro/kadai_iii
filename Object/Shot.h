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

	// ”­ËŠJn
	void start(Vec2 pos);
//	// “G‚Æ“–‚½‚Á‚½‚Ìˆ—
//	void col(Enemy& target);

	// “G‚É‚Ô‚Â‚©‚Á‚½‚Æ‚«‚Ìˆ—
	virtual void hit() { m_isExist = false; };

	virtual ColType getColType() const override { return ColType::kPlayerShot; }
	virtual ColType getTargetColType() const override { return ColType::kEnemy; }

private:
	Vec2	m_vec;
};