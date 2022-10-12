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

	// “G‚Ì’e‚ª“–‚½‚Á‚½‚Æ‚«‚Ìˆ—
	virtual void beHit() override;
	// ’e”­ËˆÊ’u‚Ìæ“¾
	Vec2 getShotStartPos() const;

private:
	int		m_shotInterval;
};