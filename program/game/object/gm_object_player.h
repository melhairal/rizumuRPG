#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "gm_object_actor.h"
class ScenePlay;

class Player : public Actor {
public:
	Player(ScenePlay* scene);
	~Player() {}
	void update(float delta_time) override;

	// =========== 関数 ==========


	// ========== 基本ステータス ==========

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
