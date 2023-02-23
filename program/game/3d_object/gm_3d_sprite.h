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

	// =========== 関数 ==========

	void hitPlayer(tnl::Vector3 size); //プレイヤーとの衝突判定

	// =========== 基本ステータス ==========

	SceneField* scene_ = nullptr; //シーン情報を取得

	AnimSprite3D* sprite_ = nullptr; //スプライト情報
	tnl::Vector3 pos_ = { 0,0,0 }; //座標
	tnl::Vector3 prev_pos_ = { 0,0,0 }; //座標

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


	// =========== 基本ステータス ==========

	float speed_ = 2.0f; //移動速度
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