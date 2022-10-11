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
	// list<ObjectBase*>への各処理
	void updateObject(std::list<ObjectBase*>& obj);
	void drawObject(std::list<ObjectBase*>& obj);
	void endObject(std::list<ObjectBase*>& obj);

private:
	std::list<ObjectBase*>	m_object;
};