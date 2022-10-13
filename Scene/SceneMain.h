#pragma once
#include "SceneBase.h"
#include "Vec2.h"
#include <vector>
#include <list>
#include "Player.h"

class SceneMain : public SceneBase
{
public:
	SceneMain()
	{
		m_bgScroll = 0.0f;
		m_endCount = 0;
	}
	virtual ~SceneMain() {}


	virtual void init() override;
	virtual void end()  override;

	virtual SceneBase* update() override;
	virtual void draw() override;

	// �v���C���[�̃V���b�g����
	void addPlayerShot( Vec2 pos );
	// �G�̃V���b�g����
	void addEnemyShot( Vec2 pos );

	// �G�̃V���b�g�����Ă�����	�ː���ɑ��̓G������ꍇ�͌����Ȃ�
	bool isEnemyShotEnable(Vec2 shotStartPos);

	// �v���C���[���邩	ColType::kPlayer���`�F�b�N����
	bool isExistPlayer() const;
	// �G�̐��擾	ColType::kEnemy���`�F�b�N����
	int getEnemyNum() const;

	// �p�[�e�B�N������
	void createParticle(Vec2 pos, int color, int num);

private:
	// list<ObjectBase*>�ւ̊e����
	void updateObject(std::list<ObjectBase*>& obj);
	void drawObject(std::list<ObjectBase*>& obj);
	void endObject(std::list<ObjectBase*>& obj);

private:
	// �O���t�B�b�N�n���h��
	std::vector<int>	m_graphicHandle;
//	int m_hPlayer;
//	int m_hEnemy;
//	int m_hBg;

	// �Q�[�����ɓo�ꂷ�镨��
	std::list<ObjectBase*>	m_object;
	// �w�i�̃X�N���[��
	float m_bgScroll;
	// �Q�[���I����̃t���[���҂�
	int m_endCount;
};