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

	// プレイヤーのショット生成
	void addPlayerShot( Vec2 pos );
	// 敵のショット生成
	void addEnemyShot( Vec2 pos );

	// 敵のショット撃っていいか	射線上に他の敵がいる場合は撃たない
	bool isEnemyShotEnable(Vec2 shotStartPos);

	// プレイヤーいるか	ColType::kPlayerをチェックする
	bool isExistPlayer() const;
	// 敵の数取得	ColType::kEnemyをチェックする
	int getEnemyNum() const;

	// パーティクル生成
	void createParticle(Vec2 pos, int color, int num);

private:
	// list<ObjectBase*>への各処理
	void updateObject(std::list<ObjectBase*>& obj);
	void drawObject(std::list<ObjectBase*>& obj);
	void endObject(std::list<ObjectBase*>& obj);

private:
	// グラフィックハンドル
	std::vector<int>	m_graphicHandle;
//	int m_hPlayer;
//	int m_hEnemy;
//	int m_hBg;

	// ゲーム中に登場する物体
	std::list<ObjectBase*>	m_object;
	// 背景のスクロール
	float m_bgScroll;
	// ゲーム終了後のフレーム待ち
	int m_endCount;
};