#pragma once
#include "SceneBase.h"
#include "Vec2.h"
#include <vector>
#include "Player.h"

class SceneMain : public SceneBase
{
public:
	SceneMain()
	{
		
	}
	virtual ~SceneMain() {}


	virtual void init() override;
	virtual void end()  override;

	virtual SceneBase* update() override;
	virtual void draw() override;

	void addShot( Vec2 pos );

	// パーティクル生成
	void createParticle(Vec2 pos, int color, int num);

private:
	// vector<ObjectBase*>への各処理
	void updateObject(std::vector<ObjectBase*>& obj);
	void drawObject(std::vector<ObjectBase*>& obj);
	void endObject(std::vector<ObjectBase*>& obj);
private:
	Player	m_player;
	std::vector<ObjectBase*>	m_enemy;
	std::vector<ObjectBase*>	m_shot;
	std::vector<ObjectBase*>	m_particle;
};