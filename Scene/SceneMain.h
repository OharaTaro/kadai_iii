#pragma once
#include "SceneBase.h"
#include "Vec2.h"
//#include <vector>
#include <list>
#include "Player.h"

class SceneMain : public SceneBase
{
public:
	SceneMain()
	{
		m_endCount = 0;
	}
	virtual ~SceneMain() {}


	virtual void init() override;
	virtual void end()  override;

	virtual SceneBase* update() override;
	virtual void draw() override;

	void addPlayerShot( Vec2 pos );
	void addEnemyShot(Vec2 pos);

	// �v���C���[���邩	ColType::kPlayer���`�F�b�N����
	bool isExistPlayer() const;

	// �p�[�e�B�N������
	void createParticle(Vec2 pos, int color, int num);

private:
	// list<ObjectBase*>�ւ̊e����
	void updateObject(std::list<ObjectBase*>& obj);
	void drawObject(std::list<ObjectBase*>& obj);
	void endObject(std::list<ObjectBase*>& obj);

	

private:
	std::list<ObjectBase*>	m_object;

	int m_endCount;
};