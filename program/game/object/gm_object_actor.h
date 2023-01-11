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

	const float X_LL_ = -110.0f; //一番左のX座標
	const float X_L_ = -35.0f; //左から2番目のX座標
	const float X_R_ = 35.0f; //右から2番目のX座標
	const float X_RR_ = 110.0f; //一番右のX座標

	int elapsed_ = 0; //アニメーション計測用
	int frame_ = 0; //アニメーションの現在のフレーム
	std::list<std::string> images_; //アニメーションリスト
	std::list<std::string>::iterator it; //アニメーションリスト用イテレータ
};


class Player : public Actor {
public:
	Player(ScenePlay* scene);
	~Player() {}
	void update(float delta_time) override;

	// =========== 関数 ==========


	// ========== 基本ステータス ==========

	const float MESH_W_ = 50.0f; //メッシュの横幅
	const float MESH_H_ = 50.0f; //メッシュの立幅
	const float POS_Y_ = 20.0f; //Y座標
	const float POS_Z_ = -100.0f; //Z座標
	const int FRAME_ = 10; //アニメーション更新フレーム


	void getImage() override {
		// ====================================
		//  ここにアニメーションの画像を並べる
		// ====================================
		images_.emplace_back("graphics/chara/player/1.png");
		images_.emplace_back("graphics/chara/player/2.png");
		images_.emplace_back("graphics/chara/player/3.png");
		it = images_.begin();
	}
};