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

	// �����ʒu�̐ݒ�
	void setStart(Vec2 pos);
//	// �_���[�W���󂯂�(�v���C���[�̒e�ɓ�������)
//	void damage();
	// �v���C���[�̂��܂ɂԂ���ꂽ���̏���
	virtual void beHit();

	virtual ColType getColType() const override { return ColType::kEnemy; }
	virtual ColType getTargetColType() const override { return ColType::kPlayer; }

private:
	
};