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

	// プレイヤーいるか	ColType::kPlayerをチェックする
	bool isExistPlayer() const;

	// パーティクル生成
	void createParticle(Vec2 pos, int color, int num);

private:
	// list<ObjectBase*>への各処理
	void updateObject(std::list<ObjectBase*>& obj);
	void drawObject(std::list<ObjectBase*>& obj);
	void endObject(std::list<ObjectBase*>& obj);

	

private:
	std::list<ObjectBase*>	m_object;

	int m_endCount;
};