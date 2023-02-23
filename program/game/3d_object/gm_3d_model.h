#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
class SceneField;

class ModelBase {
public:
	ModelBase() {}
	virtual ~ModelBase() {}
	virtual void update(float delta_time) {}
	virtual void render() {}

	// =========== 関数 ==========

	void hitPlayer(tnl::Vector3 size); //プレイヤーとの衝突判定

	// =========== 基本ステータス ==========

	SceneField* scene_ = nullptr; //シーン情報を取得

	int mv1_ = 0; //モデルハンドル
	tnl::Vector3 pos_ = { 0,0,0 }; //座標

	bool render_ = true; //描画フラグ
	bool alive_ = true; //生存フラグ
};

class ModelHouse : public ModelBase {
public:
	ModelHouse(SceneField* scene, tnl::Vector3 pos, tnl::Vector3 rot);
	~ModelHouse() {}
	void update(float delta_time);
	void render();

	// =========== 関数 ==========

	// =========== 基本ステータス ==========

	tnl::Vector3 size_ = { 200,200,200 }; //衝突判定用大きさ
};