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

	void Initialize(ScenePlay* scene, int lane, int atk, int exp); //メッシュの初期化

	void flow(float speed); //流れてくる
	void shot(Actor* bullet); //弾を飛ばしてくる
	void shift(); //レーンを変える

	bool checkLane(); //レーンの確認
	void checkJudge(); //判定の確認

	void notesEnemy(); //敵判定
	bool notesEnemyKey(); //キー判定

	void notesBullet(); //攻撃判定
	bool notesBulletKey(); //キー判定

	// ========== 基本ステータス ==========

	enum {
		perfect,
		good,
		miss
	};

	bool isBullet = false; //弾かどうか
	bool isShift = false; //シフトしたかどうか
	int shift_r_ = 0; //シフト用乱数
	float shift_dis_ = 0; //シフト距離
	const int SHIFT_SPEED_ = 30; //シフトにかかる時間

	const float POS_Z_ = 300.0f; //初期Z座標
	const float DEAD_Z_ = -160.0f; //消滅Z座標
	const float SPEED_ = 4.0f; //流れるスピード(仮)

	const float JUDGE_Z_ = -95.0f; //判定Z座標
	const float RANGE_PERFECT_ = 10.0f; //パーフェクト判定の範囲
	const float RANGE_GOOD_ = 30.0f; //グッド判定の範囲
	bool perfect_ = false; //パーフェクト判定
	bool good_ = false; //グッド判定
	const float MISS_Z_ = JUDGE_Z_ - RANGE_GOOD_; //失敗判定Z座標
	const float RANGE_MISS_ = 20.0f;
	bool miss_ = false; //失敗判定

	int elapsed_ = 0; //時間計測用

	int atk_ = 0; //攻撃力
	int exp_ = 0; //スコア、経験値
};

class EnemyPig : public EnemyBase {
public:
	EnemyPig(ScenePlay* scene, int lane);
	~EnemyPig() {}
	void update(float delta_time) override;

	// =========== 関数 ==========

	// ========== 基本ステータス ==========

	const int ATK_ = 20;
	const int EXP_ = 100;

	void getImage() override {
		// ====================================
		//  ここにアニメーションの画像を並べる
		// ====================================
		images_.emplace_back("graphics/chara/enemy/pig.png");
		it = images_.begin();
	}
};

class EnemyRizard : public EnemyBase {
public:
	EnemyRizard(ScenePlay* scene, int lane);
	~EnemyRizard() {}
	void update(float delta_time) override;

	// =========== 関数 ==========

	// ========== 基本ステータス ==========
	
	const float SHOT_Z_ = 200.0f; //弾を発射するZ座標
	const int TIME_SHOT_ = 40; //弾を飛ばすまでの時間
	const int TIME_STOP_ = 80; //停止時間

	const int ATK_ = 10;
	const int EXP_ = 200;

	void getImage() override {
		// ====================================
		//  ここにアニメーションの画像を並べる
		// ====================================
		images_.emplace_back("graphics/chara/enemy/rizard.png");
		it = images_.begin();
	}
};

class EnemyRizardBullet : public EnemyBase {
public:
	EnemyRizardBullet(ScenePlay* scene, int lane);
	~EnemyRizardBullet() {}
	void update(float delta_time) override;

	// =========== 関数 ==========

	// ========== 基本ステータス ==========

	const int ATK_ = 30;
	const int EXP_ = 10;

	void getImage() override {
		// ====================================
		//  ここにアニメーションの画像を並べる
		// ====================================
		images_.emplace_back("graphics/effect/fireball.png");
		it = images_.begin();
	}
};

class EnemyMash : public EnemyBase {
public:
	EnemyMash(ScenePlay* scene, int lane);
	~EnemyMash() {}
	void update(float delta_time) override;

	// =========== 関数 ==========

	// ========== 基本ステータス ==========

	const float SHIFT_Z_ = 150.0f; //レーンを移動するZ座標

	const int ATK_ = 15;
	const int EXP_ = 200;

	void getImage() override {
		// ====================================
		//  ここにアニメーションの画像を並べる
		// ====================================
		images_.emplace_back("graphics/chara/enemy/mash.png");
		it = images_.begin();
	}
};