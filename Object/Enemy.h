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
	// �O���t�B�b�N�f�[�^�ݒ�
	void setGraph(int handle) { m_hGraph = handle; }

	// �v���C���[�̂��܂ɂԂ���ꂽ���̏���
	virtual void beHit();

	virtual ColType getColType() const override { return ColType::kEnemy; }
	virtual ColType getTargetColType() const override { return ColType::kPlayer; }


	// �e���ˈʒu�̎擾
	Vec2 getShotStartPos() const;

private:
	// �O���t�B�b�N�n���h��
	int		m_hGraph;
	// �A�j���[�V����
	int		m_animFrameCount;

	int m_shotInterval;
};