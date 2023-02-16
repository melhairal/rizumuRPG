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
	void switchAction(); //アクションの切り替え
	void setMove(float x, float z); //移動用数値セットアップ
	void move(float x, float z); //メッシュの移動
	virtual void attackMeleeA(){} //近接攻撃1
	virtual void attackMeleeB(){} //近接攻撃2
	virtual void attackRangeA(){} //全体攻撃1
	virtual void attackRangeB(){} //全体攻撃2
	virtual void attackBulletA(){} //遠隔攻撃1
	virtual void attackBulletB(){} //遠隔攻撃2

	// ========== 基本ステータス ==========

	const float POS_Z_ = 300.0f; //Z座標
	const float MELEE_POS_Z_ = 0.0f; //接近Z座標
	const float BULLET_POS_Z_ = 100.0f; //遠隔Z座標

	const int FLOW_INTERVAL_ = 99; //ノーツが流れてきてから判定ラインに到達するまでのラグ
	const int BULLET_INTERVAL_ = 49; //遠距離攻撃が流れてきてから判定ラインに到達するまでのラグ
	const int MOVE_SPEED_ = 18; //移動にかかる時間
	const int ATTACK_INTERVAL_FAST_ = 18; //攻撃間隔(短)
	const int ATTACK_INTERVAL_SLOW_ = 36; //攻撃間隔(遅)

	int r_[20] = { 0 }; //攻撃レーン乱数保存用
	float dir_x_ = 0; //移動量を保存
	float dir_z_ = 0; //移動量を保存

	int move_flame_ = 0; //移動量計測用
	int elapsed_ = 0; //時間計測
};

class BossGorem : public BossEnemy {
public:
	BossGorem(ScenePlay* scene);
	~BossGorem() {}
	void update(float delta_time);

	// =========== 関数 ==========

	void attackMeleeA(); //近接攻撃1
	void attackMeleeB(); //近接攻撃2
	void attackRangeA(); //全体攻撃1
	void attackRangeB(); //全体攻撃2
	void attackBulletA(); //遠隔攻撃1
	void attackBulletB(); //遠隔攻撃2
	

	// ========== 基本ステータス ==========

	const int ATK_MELEE_ = 40;
	const int ATK_RANGE_ = 20;
	const int ATK_BULLET_ = 0;

	void getImage() override {
		// ====================================
		//  ここにアニメーションの画像を並べる
		// ====================================
		images_.emplace_back("graphics/chara/enemy/gorem.png");
		it = images_.begin();
	}
};

class BossDragon : public BossEnemy {
public:
	BossDragon(ScenePlay* scene);
	~BossDragon() {}
	void update(float delta_time);

	// =========== 関数 ==========

	void attackMeleeA(); //近接攻撃1
	void attackMeleeB(); //近接攻撃2
	void attackRangeA(); //全体攻撃1
	void attackRangeB(); //全体攻撃2
	void attackBulletA(); //遠隔攻撃1
	void attackBulletB(); //遠隔攻撃2


	// ========== 基本ステータス ==========

	const int ATK_MELEE_ = 50;
	const int ATK_RANGE_ = 40;
	const int ATK_BULLET_ = 70;

	void getImage() override {
		// ====================================
		//  ここにアニメーションの画像を並べる
		// ====================================
		images_.emplace_back("graphics/chara/enemy/dragon.png");
		it = images_.begin();
	}
};

class BossKeruberos : public BossEnemy {
public:
	BossKeruberos(ScenePlay* scene);
	~BossKeruberos() {}
	void update(float delta_time);

	// =========== 関数 ==========

	void attackMeleeA(); //近接攻撃1
	void attackMeleeB(); //近接攻撃2
	void attackRangeA(); //全体攻撃1
	void attackRangeB(); //全体攻撃2
	void attackBulletA(); //遠隔攻撃1
	void attackBulletB(); //遠隔攻撃2


	// ========== 基本ステータス ==========

	const int ATK_MELEE_ = 90;
	const int ATK_RANGE_ = 40;
	const int ATK_BULLET_ = 50;

	void getImage() override {
		// ====================================
		//  ここにアニメーションの画像を並べる
		// ====================================
		images_.emplace_back("graphics/chara/enemy/keruberos.png");
		it = images_.begin();
	}
};

class BossNotes : public Actor {
public:
	BossNotes() {}
	virtual ~BossNotes() {}
	virtual void update(float delta_time) {}

	// =========== 関数 ==========

	void initialize(ScenePlay* scene, int damage, int lane);
	void flow(float speed); //流れてくる

	void judge(); //判定
	bool judgeKey(); //キー判定

	void judgeAll(); //全体攻撃の判定

	// ========== 基本ステータス ==========

	enum {
		none = -1,
		perfect,
		good,
		miss
	};

	const float POS_Z_ = 300.0f; //初期Z座標
	const float BULLET_POS_Z_ = 100.0f; //遠隔Z座標
	const float DEAD_Z_ = -160.0f; //消滅Z座標

	const float JUDGE_Z_ = -96.0f; //判定Z座標
	const float RANGE_PERFECT_ = 10.0f; //パーフェクト判定の範囲
	const float RANGE_GOOD_ = 30.0f; //グッド判定の範囲
	const float MISS_Z_ = JUDGE_Z_ - RANGE_GOOD_; //失敗判定Z座標
	const float RANGE_MISS_ = 15.0f; //失敗判定の範囲

	int damage_ = 0;
};

class NotesWarning : public BossNotes {
public:
	NotesWarning(ScenePlay* scene, int damage, int lane);
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

class NotesWarningAll : public BossNotes {
public:
	NotesWarningAll(ScenePlay* scene, int damage, int lane);
	~NotesWarningAll() {}
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

class NotesDragonBless : public BossNotes {
public:
	NotesDragonBless(ScenePlay* scene, int damage, int lane);
	~NotesDragonBless() {}
	void update(float delta_time) override;

	// =========== 関数 ==========

	// ========== 基本ステータス ==========

	void getImage() override {
		// ====================================
		//  ここにアニメーションの画像を並べる
		// ====================================
		images_.emplace_back("graphics/effect/fireball.png");
		it = images_.begin();
	}
};

class NotesKeruberosBless : public BossNotes {
public:
	NotesKeruberosBless(ScenePlay* scene, int damage, int lane);
	~NotesKeruberosBless() {}
	void update(float delta_time) override;

	// =========== 関数 ==========

	// ========== 基本ステータス ==========

	void getImage() override {
		// ====================================
		//  ここにアニメーションの画像を並べる
		// ====================================
		images_.emplace_back("graphics/effect/blackball1.png");
		it = images_.begin();
	}
};