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

	// ���ˊJ�n
	void startPlayer(Vec2 pos);	// �v���C���[�̃V���b�g
	void startEnemy(Vec2 pos);	// �G�̃V���b�g

	// �G�ɂԂ������Ƃ��̏���
	virtual void hit() { m_isExist = false; };

	virtual ColType getColType() const override { return m_myType; }
	virtual ColType getTargetColType() const override { return m_targetType; }

private:
	Vec2	m_vec;

	// �G�ɓ�����e���v���C���[�ɓ�����e����ݒ肷��
	ColType	m_myType;
	ColType	m_targetType;
};