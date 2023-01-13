#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "gm_object_actor.h"
class ScenePlay;

class EnemyBase : public Actor {
public:
	EnemyBase() {};
	virtual ~EnemyBase() {}
	virtual void update(float delta_time) {}

	// =========== 関数 ==========

	void Initialize(ScenePlay* scene, int lane); //メッシュの初期化

	void flow(float speed); //流れてくる
	void shot(Actor* bullet); //弾を飛ばしてくる
	void shift(); //レーンを変える

	bool checkLane(); //レーンの確認
	void notesEnemy(); //敵判定
	void notesBullet(); //攻撃判定

	// ========== 基本ステータス ==========

	bool onPlayerLane = false; //プレイヤーと同じレーンかどうか

	const float POS_Z_ = 300.0f; //初期Z座標
	const float DEAD_Z_ = -200.0f; //消滅Z座標
	const float SPEED_ = 5.0f; //流れるスピード(仮)
};

class EnemyPig : public EnemyBase {
public:
	EnemyPig(ScenePlay* scene, int lane);
	~EnemyPig() {}
	void update(float delta_time) override;

	// =========== 関数 ==========

	// ========== 基本ステータス ==========


	void getImage() override {
		// ====================================
		//  ここにアニメーションの画像を並べる
		// ====================================
		images_.emplace_back("graphics/chara/enemy/pig_a.png");
		it = images_.begin();
	}
};