#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "gm_object_actor.h"
#include <unordered_map>
#include <functional>
#include <memory>

class ScenePlay;

class AttackNotes : public Actor {
public:
	AttackNotes(ScenePlay* scene, int lane);
	~AttackNotes() {}
	void update(float delta_time);

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

	bool set_enemy_pos_ = false;

	void getImage() override {
		// ====================================
		//  ここにアニメーションの画像を並べる
		// ====================================
		images_.emplace_back("graphics/effect/lockon.png");
		it = images_.begin();
	}
};

class SkillBase {
public:
	SkillBase() {};
	virtual ~SkillBase() {}
	virtual void update(float delta_time) {}

	// =========== 関数 ==========

	void damage(); //ダメージ計算

	void randomPop(); //ランダムなレーンに生成
	void checkJudge(); //判定を確認

	virtual void notesPerfect(){} //パーフェクト判定
	virtual void notesGood(){} //グッド判定

	// ========== 基本ステータス ==========

	ScenePlay* scene_ = nullptr; //シーンポインタ
	int num_ = 0; //何個目のノーツか
	bool finish_ = false; //処理が終わったかどうか

	Actor* attacks_[6] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr }; //アタックノーツリスト
	int judges_[6] = { -1,-1,-1,-1,-1,-1 }; //判定リスト

	int elapsed_ = 0; //時間計測用
	const int SKILL_INTERVAL_ = 150; //スキルとスキルの間隔

	int damage_good_ = 0;
	int damage_perfect_ = 0;
};

class SkillNormalA : public SkillBase {
public:
	SkillNormalA(ScenePlay* scene);
	~SkillNormalA() {}
	void update(float delta_time);

	// =========== 関数 ==========

	void notesPerfect(); //パーフェクト判定
	void notesGood(); //グッド判定

	// ========== 基本ステータス ==========

	const int MAX_NUM_ = 2; //ノード数
	const int INTERVAL_ = 24; //ノード生成間隔

};

class SkillNormalB : public SkillBase {
public:
	SkillNormalB(ScenePlay* scene);
	~SkillNormalB() {}
	void update(float delta_time);

	// =========== 関数 ==========

	void notesPerfect(); //パーフェクト判定
	void notesGood(); //グッド判定

	// ========== 基本ステータス ==========

	const int MAX_NUM_ = 3; //ノード数
	const int INTERVAL_ = 24; //ノード生成間隔

};

class SkillComboA : public SkillBase {
public:
	SkillComboA(ScenePlay* scene);
	~SkillComboA() {}
	void update(float delta_time);

	// =========== 関数 ==========

	void notesPerfect(); //パーフェクト判定
	void notesGood(); //グッド判定

	// ========== 基本ステータス ==========

	const int MAX_NUM_ = 3; //ノード数
	const int INTERVAL_ = 18; //ノード生成間隔

};

class SkillComboB : public SkillBase {
public:
	SkillComboB(ScenePlay* scene);
	~SkillComboB() {}
	void update(float delta_time);

	// =========== 関数 ==========

	void notesPerfect(); //パーフェクト判定
	void notesGood(); //グッド判定

	// ========== 基本ステータス ==========

	const int MAX_NUM_ = 5; //ノード数
	const int INTERVAL_ = 18; //ノード生成間隔

};

class SkillComboC : public SkillBase {
public:
	SkillComboC(ScenePlay* scene);
	~SkillComboC() {}
	void update(float delta_time);

	// =========== 関数 ==========

	void notesPerfect(); //パーフェクト判定
	void notesGood(); //グッド判定

	// ========== 基本ステータス ==========

	const int MAX_NUM_ = 4; //ノード数
	const int INTERVAL_ = 24; //ノード生成間隔

};

class SkillComboD : public SkillBase {
public:
	SkillComboD(ScenePlay* scene);
	~SkillComboD() {}
	void update(float delta_time);

	// =========== 関数 ==========

	void notesPerfect(); //パーフェクト判定
	void notesGood(); //グッド判定

	// ========== 基本ステータス ==========

	const int MAX_NUM_ = 6; //ノード数
	const int INTERVAL_ = 18; //ノード生成間隔

};

class SkillPowerA : public SkillBase {
public:
	SkillPowerA(ScenePlay* scene);
	~SkillPowerA() {}
	void update(float delta_time);

	// =========== 関数 ==========

	void notesPerfect(); //パーフェクト判定
	void notesGood(); //グッド判定

	// ========== 基本ステータス ==========

	const int MAX_NUM_ = 1; //ノード数
	const int INTERVAL_ = 24; //ノード生成間隔

};

class SkillPowerB : public SkillBase {
public:
	SkillPowerB(ScenePlay* scene);
	~SkillPowerB() {}
	void update(float delta_time);

	// =========== 関数 ==========

	void notesPerfect(); //パーフェクト判定
	void notesGood(); //グッド判定

	// ========== 基本ステータス ==========

	const int MAX_NUM_ = 2; //ノード数
	const int INTERVAL_ = 18; //ノード生成間隔

};

class SkillPowerC : public SkillBase {
public:
	SkillPowerC(ScenePlay* scene);
	~SkillPowerC() {}
	void update(float delta_time);

	// =========== 関数 ==========

	void notesPerfect(); //パーフェクト判定
	void notesGood(); //グッド判定

	// ========== 基本ステータス ==========

	const int MAX_NUM_ = 1; //ノード数
	const int INTERVAL_ = 24; //ノード生成間隔

};

class SkillOtherA : public SkillBase {
public:
	SkillOtherA(ScenePlay* scene);
	~SkillOtherA() {}
	void update(float delta_time);

	// =========== 関数 ==========

	void notesPerfect(); //パーフェクト判定
	void notesGood(); //グッド判定

	// ========== 基本ステータス ==========

	const int MAX_NUM_ = 3; //ノード数
	const int INTERVAL_ = 24; //ノード生成間隔

};


class SkillList {
public:
	SkillList() {}
	~SkillList() {}
	std::string name_ = "-"; //名前
	std::string class_name_ = "class -"; //クラス名
	std::string exp1_ = "-"; //説明文
	std::string exp2_ = "-"; //説明文
	std::string exp3_ = "-"; //説明文
	int mp_ = 0; //消費MP
};