#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "gm_object_base.h"

class Actor : public ObjectBase {
public:
	Actor() {};
	virtual ~Actor() {}
	virtual void update(float delta_time) {}

	// =========== 関数 ==========

	virtual void getImage() {} //アニメーション画像セット
	void animation(int frame); //アニメーションの更新

	// ========== 基本ステータス ==========

	enum {
		LL, //一番左
		L, //左から2番目
		R, //右から2番目
		RR //一番右
	};

	int lane_ = 0; //レーン

	const float POS_X_[4] = { -110.0f,-35.0f,35.0f,110.0f }; //4つのレーンの座標
	const float POS_Y_ = 20.0f; //Y座標

	const float MESH_W_ = 50.0f; //メッシュの横幅
	const float MESH_H_ = 50.0f; //メッシュの立幅

	int elapsed_ = 0; //アニメーション計測用
	int frame_ = 0; //アニメーションの現在のフレーム
	std::list<std::string> images_; //アニメーションリスト
	std::list<std::string>::iterator it; //アニメーションリスト用イテレータ

	int judge_ = -1; //アタックノーツ用判定
};