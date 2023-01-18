#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "gm_object_actor.h"
class ScenePlay;

class BossEnemy : public Actor {
public:
	BossEnemy(ScenePlay* scene);
	~BossEnemy() {}
	void update(float delta_time) override;

	// =========== 関数 ==========


	// ========== 基本ステータス ==========

	const float POS_Z_ = 300.0f; //Z座標

	void getImage() override {
		// ====================================
		//  ここにアニメーションの画像を並べる
		// ====================================
		images_.emplace_back("graphics/chara/enemy/dragon.png");
		it = images_.begin();
	}
};