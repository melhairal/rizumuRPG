#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
class SceneField;
class AnimSprite3D;

class SpriteBase {
public:
	SpriteBase() {}
	virtual ~SpriteBase() {
		delete sprite_;
	}
	virtual void update(float delta_time) {}
	virtual void render() {}
	virtual void getComment() {} //セリフセット

	// =========== 関数 ==========

	void getSurface(tnl::Vector3 size); //カメラに対する面を取得
	virtual void eventAction() {} //イベント
	void hitPlayer(tnl::Vector3 size); //プレイヤーとの衝突判定

	// =========== 基本ステータス ==========

	SceneField* scene_ = nullptr; //シーン情報を取得

	AnimSprite3D* sprite_ = nullptr; //スプライト情報
	tnl::Vector3 pos_ = { 0,0,0 }; //座標
	tnl::Vector3 prev_pos_ = { 0,0,0 }; //座標
	tnl::Vector3 look_ = { 0,0,0 }; //見ている方向ベクトル

	std::list<const char*> comment_; //セリフリスト
	std::list<const char*>::iterator it; //セリフリスト用イテレータ

	bool isComment_ = false; //セリフ中フラグ
	bool isEvent_ = false; //イベント中フラグ
	bool move_ = true; //動作フラグ
	bool alive_ = true; //生存フラグ
};

class SpritePlayer : public SpriteBase {
public:
	SpritePlayer(SceneField* scene);
	~SpritePlayer() {}
	void update(float delta_time);
	void render();

	// =========== 関数 ==========

	void movePlayer(); //移動制御
	void getEvent(); //イベント制御(エンターキーでイベントを起こす)

	// =========== 基本ステータス ==========

	float speed_ = 2.0f; //移動速度

	tnl::Vector3 size_ = { 32,32,32 }; //当たり判定用サイズ

	
};

class SpriteTree : public SpriteBase {
public:
	SpriteTree(SceneField* scene, tnl::Vector3 pos);
	~SpriteTree() {}
	void update(float delta_time);
	void render();

	// =========== 関数 ==========

	// =========== 基本ステータス ==========

	tnl::Vector3 size_ = { 50,50,50 }; //当たり判定用サイズ

};

class SpriteNpc : public SpriteBase {
public:
	SpriteNpc() {}
	virtual ~SpriteNpc() {}
	virtual void update(float delta_time) {}
	virtual void render() {}
	virtual void getComment() {} //セリフセット

	// =========== 関数 ==========

	virtual void eventAction() {} //イベント
	void randomWalk(int range, int speed); //ランダムで歩く

	// =========== 基本ステータス ==========

	tnl::Vector3 dir_[4] = {
		{0,0,1}, //上
		{1,0,0}, //右
		{0,0,-1}, //下
		{-1,0,0} //左
	};

	bool isWalk_ = false; //移動中フラグ
	float next_x_ = 0; //移動先のX座標
	float next_z_ = 0; //移動先のZ座標

	bool isWait_ = false; //待機中フラグ
	int elapsed_ = 0; //時間計測
	int wait_time_ = 0; //待機時間
};

class SpriteMurabito : public SpriteNpc {
public:
	SpriteMurabito(SceneField* scene, tnl::Vector3 pos);
	~SpriteMurabito() {}
	void update(float delta_time);
	void render();

	// =========== 関数 ==========
	
	void eventAction(); //イベント

	// =========== 基本ステータス ==========

	tnl::Vector3 size_ = { 32,32,32 }; //当たり判定用サイズ
	int range_ = 120; //移動範囲
	int speed_ = 2; //移動速度

	void getComment() override {
		// ====================================
		//  ここにセリフを並べる
		// ====================================
		comment_.emplace_back("...");
		comment_.emplace_back("ここは始まりの村");
		comment_.emplace_back("雑貨屋や装備屋があるよ");
		it = comment_.begin();
	}
};

class SpriteMurabitoF : public SpriteNpc {
public:
	SpriteMurabitoF(SceneField* scene, tnl::Vector3 pos);
	~SpriteMurabitoF() {}
	void update(float delta_time);
	void render();

	// =========== 関数 ==========

	void eventAction(); //イベント

	// =========== 基本ステータス ==========

	tnl::Vector3 size_ = { 32,32,32 }; //当たり判定用サイズ
	int range_ = 100; //移動範囲
	int speed_ = 2; //移動速度

	void getComment() override {
		// ====================================
		//  ここにセリフを並べる
		// ====================================
		comment_.emplace_back("...");
		comment_.emplace_back("知ってる？");
		comment_.emplace_back("モンスターの攻撃をタイミング良く避けると、");
		comment_.emplace_back("スコアとコンボがボーナスで加算されるんだって！");
		it = comment_.begin();
	}
};

class SpriteHeisi : public SpriteNpc {
public:
	SpriteHeisi(SceneField* scene, tnl::Vector3 pos, int look);
	~SpriteHeisi() {}
	void update(float delta_time);
	void render();

	// =========== 関数 ==========

	void eventAction(); //イベント

	// =========== 基本ステータス ==========

	tnl::Vector3 size_ = { 32,32,32 }; //当たり判定用サイズ
	int look_ = 0; //向いてる向き

	void getComment() override {
		// ====================================
		//  ここにセリフを並べる
		// ====================================
		comment_.emplace_back("...");
		comment_.emplace_back("外に出るとモンスターがいるぞ");
		comment_.emplace_back("しっかり準備してから行くんだ");
		it = comment_.begin();
	}
};

class SpriteKazi : public SpriteNpc {
public:
	SpriteKazi(SceneField* scene, tnl::Vector3 pos, int look);
	~SpriteKazi() {}
	void update(float delta_time);
	void render();

	// =========== 関数 ==========

	void eventAction(); //イベント

	// =========== 基本ステータス ==========

	tnl::Vector3 size_ = { 32,32,32 }; //当たり判定用サイズ
	int look_ = 0; //向いてる向き

	void getComment() override {
		// ====================================
		//  ここにセリフを並べる
		// ====================================
		comment_.emplace_back("...");
		comment_.emplace_back("ここは装備屋だ");
		comment_.emplace_back("武器や防具を着けると強くなるぞ");
		it = comment_.begin();
	}
};

class SpriteShop : public SpriteNpc {
public:
	SpriteShop(SceneField* scene, tnl::Vector3 pos, int look);
	~SpriteShop() {}
	void update(float delta_time);
	void render();

	// =========== 関数 ==========

	void eventAction(); //イベント

	// =========== 基本ステータス ==========

	tnl::Vector3 size_ = { 32,32,32 }; //当たり判定用サイズ
	int look_ = 0; //向いてる向き

	void getComment() override {
		// ====================================
		//  ここにセリフを並べる
		// ====================================
		comment_.emplace_back("...");
		comment_.emplace_back("ここは雑貨屋よ");
		comment_.emplace_back("旅のお供に回復アイテムはいかが？");
		it = comment_.begin();
	}
};