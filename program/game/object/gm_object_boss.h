#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "gm_object_actor.h"
class ScenePlay;

class BossEnemy : public Actor {
public:
	BossEnemy() {}
	virtual ~BossEnemy() {}
	virtual void update(float delta_time) {}

	// =========== 関数 ==========

	void initialize(ScenePlay* scene); //初期化
	virtual void attackMeleeA(){} //近接攻撃1
	virtual void attackMeleeB(){} //近接攻撃2
	virtual void attackRangeA(){} //全体攻撃1
	virtual void attackRangeB(){} //全体攻撃2
	virtual void attackBulletA(){} //遠隔攻撃1
	virtual void attackBulletB(){} //遠隔攻撃2

	// ========== 基本ステータス ==========

	const float POS_Z_ = 300.0f; //Z座標
	const float MELEE_POS_Z_ = 50.0f; //接近Z座標
	const float BULLET_POS_Z_ = 150.0f; //遠隔Z座標

};

class BossDragon : public BossEnemy {
public:
	BossDragon(ScenePlay* scene);
	~BossDragon() {}
	void update(float delta_time);

	// =========== 関数 ==========


	// ========== 基本ステータス ==========





	void getImage() override {
		// ====================================
		//  ここにアニメーションの画像を並べる
		// ====================================
		images_.emplace_back("graphics/chara/enemy/dragon.png");
		it = images_.begin();
	}
};

class BossNotes : public Actor {
public:
	BossNotes() {}
	virtual ~BossNotes() {}
	virtual void update(float delta_time) {}

	// =========== 関数 ==========

	void flow(float speed); //流れてくる

	void judge(); //判定
	bool judgeKey(); //キー判定

	// ========== 基本ステータス ==========

	enum {
		none = -1,
		perfect,
		good,
		miss
	};

	const float POS_Z_ = 300.0f; //初期Z座標
	const float DEAD_Z_ = -160.0f; //消滅Z座標

	const float JUDGE_Z_ = -96.0f; //判定Z座標
	const float RANGE_PERFECT_ = 10.0f; //パーフェクト判定の範囲
	const float RANGE_GOOD_ = 30.0f; //グッド判定の範囲
	const float MISS_Z_ = JUDGE_Z_ - RANGE_GOOD_; //失敗判定Z座標
	const float RANGE_MISS_ = 15.0f;
};

class NotesWarning : public BossNotes {
public:
	NotesWarning(ScenePlay* scene, int lane);
	~NotesWarning() {}
	void update(float delta_time) override;

	// =========== 関数 ==========

	// ========== 基本ステータス ==========

	void getImage() override {
		// ====================================
		//  ここにアニメーションの画像を並べる
		// ====================================
		images_.emplace_back("graphics/effect/warning.png");
		it = images_.begin();
	}
};