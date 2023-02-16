#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "gm_object_actor.h"
class ScenePlay;

class EffectHit : public Actor {
public:
	EffectHit(ScenePlay* scene, int lane);
	~EffectHit() {}
	void update(float delta_time) override;

	// =========== 関数 ==========


	// ========== 基本ステータス ==========

	const float POS_Z_ = -100.0f; //Z座標
	const int FRAME_ = 3; //アニメーション更新フレーム

	void getImage() override {
		// ====================================
		//  ここにアニメーションの画像を並べる
		// ====================================
		images_.emplace_back("graphics/effect/hit/hit_001.png");
		images_.emplace_back("graphics/effect/hit/hit_002.png");
		images_.emplace_back("graphics/effect/hit/hit_003.png");
		images_.emplace_back("graphics/effect/hit/hit_004.png");
		images_.emplace_back("graphics/effect/hit/hit_005.png");
		it = images_.begin();
	}
};

class EffectGood : public Actor {
public:
	EffectGood(ScenePlay* scene, int lane);
	~EffectGood() {}
	void update(float delta_time) override;

	// =========== 関数 ==========


	// ========== 基本ステータス ==========

	const float POS_Z_ = -100.0f; //Z座標
	const int FRAME_ = 3; //アニメーション更新フレーム

	void getImage() override {
		// ====================================
		//  ここにアニメーションの画像を並べる
		// ====================================
		images_.emplace_back("graphics/effect/good/good_001.png");
		images_.emplace_back("graphics/effect/good/good_002.png");
		images_.emplace_back("graphics/effect/good/good_003.png");
		images_.emplace_back("graphics/effect/good/good_004.png");
		images_.emplace_back("graphics/effect/good/good_005.png");
		images_.emplace_back("graphics/effect/good/good_006.png");
		images_.emplace_back("graphics/effect/good/good_007.png");
		images_.emplace_back("graphics/effect/good/good_008.png");
		images_.emplace_back("graphics/effect/good/good_009.png");
		it = images_.begin();
	}
};

class EffectPerfect : public Actor {
public:
	EffectPerfect(ScenePlay* scene, int lane);
	~EffectPerfect() {}
	void update(float delta_time) override;

	// =========== 関数 ==========


	// ========== 基本ステータス ==========

	const float POS_Z_ = -100.0f; //Z座標
	const int FRAME_ = 3; //アニメーション更新フレーム

	void getImage() override {
		// ====================================
		//  ここにアニメーションの画像を並べる
		// ====================================
		images_.emplace_back("graphics/effect/perfect/perfect_001.png");
		images_.emplace_back("graphics/effect/perfect/perfect_002.png");
		images_.emplace_back("graphics/effect/perfect/perfect_003.png");
		images_.emplace_back("graphics/effect/perfect/perfect_004.png");
		images_.emplace_back("graphics/effect/perfect/perfect_005.png");
		images_.emplace_back("graphics/effect/perfect/perfect_006.png");
		images_.emplace_back("graphics/effect/perfect/perfect_007.png");
		images_.emplace_back("graphics/effect/perfect/perfect_008.png");
		images_.emplace_back("graphics/effect/perfect/perfect_009.png");
		it = images_.begin();
	}
};

class EffectSkillGood : public Actor {
public:
	EffectSkillGood(ScenePlay* scene, int lane);
	~EffectSkillGood() {}
	void update(float delta_time) override;

	// =========== 関数 ==========


	// ========== 基本ステータス ==========

	const float POS_Z_ = -40.0f; //Z座標
	const int FRAME_ = 3; //アニメーション更新フレーム

	void getImage() override {
		// ====================================
		//  ここにアニメーションの画像を並べる
		// ====================================
		images_.emplace_back("graphics/effect/good/good_001.png");
		images_.emplace_back("graphics/effect/good/good_002.png");
		images_.emplace_back("graphics/effect/good/good_003.png");
		images_.emplace_back("graphics/effect/good/good_004.png");
		images_.emplace_back("graphics/effect/good/good_005.png");
		images_.emplace_back("graphics/effect/good/good_006.png");
		images_.emplace_back("graphics/effect/good/good_007.png");
		images_.emplace_back("graphics/effect/good/good_008.png");
		images_.emplace_back("graphics/effect/good/good_009.png");
		it = images_.begin();
	}
};

class EffectSkillPerfect : public Actor {
public:
	EffectSkillPerfect(ScenePlay* scene, int lane);
	~EffectSkillPerfect() {}
	void update(float delta_time) override;

	// =========== 関数 ==========


	// ========== 基本ステータス ==========

	const float POS_Z_ = -40.0f; //Z座標
	const int FRAME_ = 3; //アニメーション更新フレーム

	void getImage() override {
		// ====================================
		//  ここにアニメーションの画像を並べる
		// ====================================
		images_.emplace_back("graphics/effect/perfect/perfect_001.png");
		images_.emplace_back("graphics/effect/perfect/perfect_002.png");
		images_.emplace_back("graphics/effect/perfect/perfect_003.png");
		images_.emplace_back("graphics/effect/perfect/perfect_004.png");
		images_.emplace_back("graphics/effect/perfect/perfect_005.png");
		images_.emplace_back("graphics/effect/perfect/perfect_006.png");
		images_.emplace_back("graphics/effect/perfect/perfect_007.png");
		images_.emplace_back("graphics/effect/perfect/perfect_008.png");
		images_.emplace_back("graphics/effect/perfect/perfect_009.png");
		it = images_.begin();
	}
};

class EffectCrow : public Actor {
public:
	EffectCrow(ScenePlay* scene, int lane);
	~EffectCrow() {}
	void update(float delta_time) override;

	// =========== 関数 ==========


	// ========== 基本ステータス ==========

	const float POS_Z_ = -90.0f; //Z座標
	const int FRAME_ = 3; //アニメーション更新フレーム

	void getImage() override {
		// ====================================
		//  ここにアニメーションの画像を並べる
		// ====================================
		images_.emplace_back("graphics/effect/crow/crow_001.png");
		images_.emplace_back("graphics/effect/crow/crow_002.png");
		images_.emplace_back("graphics/effect/crow/crow_003.png");
		images_.emplace_back("graphics/effect/crow/crow_004.png");
		images_.emplace_back("graphics/effect/crow/crow_005.png");
		images_.emplace_back("graphics/effect/crow/crow_006.png");
		images_.emplace_back("graphics/effect/crow/crow_007.png");
		images_.emplace_back("graphics/effect/crow/crow_008.png");
		it = images_.begin();
	}
};

class EffectTail : public Actor {
public:
	EffectTail(ScenePlay* scene);
	~EffectTail() {}
	void update(float delta_time) override;

	// =========== 関数 ==========


	// ========== 基本ステータス ==========

	const float POS_Z_ = -90.0f; //Z座標
	const int FRAME_ = 3; //アニメーション更新フレーム

	void getImage() override {
		// ====================================
		//  ここにアニメーションの画像を並べる
		// ====================================
		images_.emplace_back("graphics/effect/tail/tail_001.png");
		images_.emplace_back("graphics/effect/tail/tail_002.png");
		images_.emplace_back("graphics/effect/tail/tail_003.png");
		images_.emplace_back("graphics/effect/tail/tail_004.png");
		images_.emplace_back("graphics/effect/tail/tail_005.png");
		images_.emplace_back("graphics/effect/tail/tail_006.png");
		images_.emplace_back("graphics/effect/tail/tail_007.png");
		images_.emplace_back("graphics/effect/tail/tail_008.png");
		images_.emplace_back("graphics/effect/tail/tail_009.png");
		images_.emplace_back("graphics/effect/tail/tail_010.png");
		it = images_.begin();
	}
};

class EffectBite : public Actor {
public:
	EffectBite(ScenePlay* scene, int lane);
	~EffectBite() {}
	void update(float delta_time) override;

	// =========== 関数 ==========


	// ========== 基本ステータス ==========

	const float POS_Z_ = -90.0f; //Z座標
	const int FRAME_ = 3; //アニメーション更新フレーム

	void getImage() override {
		// ====================================
		//  ここにアニメーションの画像を並べる
		// ====================================
		images_.emplace_back("graphics/effect/bite/bite_001.png");
		images_.emplace_back("graphics/effect/bite/bite_002.png");
		images_.emplace_back("graphics/effect/bite/bite_003.png");
		images_.emplace_back("graphics/effect/bite/bite_004.png");
		images_.emplace_back("graphics/effect/bite/bite_005.png");
		images_.emplace_back("graphics/effect/bite/bite_006.png");
		images_.emplace_back("graphics/effect/bite/bite_007.png");
		images_.emplace_back("graphics/effect/bite/bite_008.png");
		it = images_.begin();
	}
};

class EffectMaho : public Actor {
public:
	EffectMaho(ScenePlay* scene, int loop);
	~EffectMaho() {}
	void update(float delta_time) override;

	// =========== 関数 ==========


	// ========== 基本ステータス ==========

	const float POS_Z_ = 70.0f; //Z座標
	const int FRAME_ = 5; //アニメーション更新フレーム
	int loop_num_ = 1; //アニメーションを何回ループさせるか
	int loop_count_ = 0; //ループ回数カウント

	void getImage() override {
		// ====================================
		//  ここにアニメーションの画像を並べる
		// ====================================
		images_.emplace_back("graphics/effect/maho/maho_001.png");
		images_.emplace_back("graphics/effect/maho/maho_002.png");
		images_.emplace_back("graphics/effect/maho/maho_003.png");
		images_.emplace_back("graphics/effect/maho/maho_004.png");
		images_.emplace_back("graphics/effect/maho/maho_005.png");
		images_.emplace_back("graphics/effect/maho/maho_006.png");
		images_.emplace_back("graphics/effect/maho/maho_007.png");
		images_.emplace_back("graphics/effect/maho/maho_008.png");
		images_.emplace_back("graphics/effect/maho/maho_009.png");
		images_.emplace_back("graphics/effect/maho/maho_010.png");
		images_.emplace_back("graphics/effect/maho/maho_011.png");
		images_.emplace_back("graphics/effect/maho/maho_012.png");
		images_.emplace_back("graphics/effect/maho/maho_013.png");
		images_.emplace_back("graphics/effect/maho/maho_014.png");
		images_.emplace_back("graphics/effect/maho/maho_015.png");
		it = images_.begin();
	}
};

class EffectGard : public Actor {
public:
	EffectGard(ScenePlay* scene, int lane);
	~EffectGard() {}
	void update(float delta_time) override;

	// =========== 関数 ==========


	// ========== 基本ステータス ==========

	const float POS_Z_ = -110.0f; //Z座標
	const int FRAME_ = 3; //アニメーション更新フレーム

	void getImage() override {
		// ====================================
		//  ここにアニメーションの画像を並べる
		// ====================================
		images_.emplace_back("graphics/effect/gard/gard_001.png");
		images_.emplace_back("graphics/effect/gard/gard_002.png");
		images_.emplace_back("graphics/effect/gard/gard_003.png");
		images_.emplace_back("graphics/effect/gard/gard_004.png");
		images_.emplace_back("graphics/effect/gard/gard_005.png");
		images_.emplace_back("graphics/effect/gard/gard_006.png");
		images_.emplace_back("graphics/effect/gard/gard_007.png");
		images_.emplace_back("graphics/effect/gard/gard_008.png");
		images_.emplace_back("graphics/effect/gard/gard_009.png");
		images_.emplace_back("graphics/effect/gard/gard_010.png");
		it = images_.begin();
	}
};

class EffectClear : public Actor {
public:
	EffectClear(ScenePlay* scene);
	~EffectClear() {}
	void update(float delta_time) override;

	// =========== 関数 ==========


	// ========== 基本ステータス ==========

	const int FRAME_ = 5; //アニメーション更新フレーム

	void getImage() override {
		// ====================================
		//  ここにアニメーションの画像を並べる
		// ====================================
		images_.emplace_back("graphics/effect/pikapika/pika_001.png");
		images_.emplace_back("graphics/effect/pikapika/pika_002.png");
		images_.emplace_back("graphics/effect/pikapika/pika_003.png");
		images_.emplace_back("graphics/effect/pikapika/pika_004.png");
		images_.emplace_back("graphics/effect/pikapika/pika_005.png");
		images_.emplace_back("graphics/effect/pikapika/pika_006.png");
		images_.emplace_back("graphics/effect/pikapika/pika_007.png");
		images_.emplace_back("graphics/effect/pikapika/pika_008.png");
		images_.emplace_back("graphics/effect/pikapika/pika_009.png");
		images_.emplace_back("graphics/effect/pikapika/pika_010.png");
		images_.emplace_back("graphics/effect/pikapika/pika_011.png");
		images_.emplace_back("graphics/effect/pikapika/pika_012.png");
		images_.emplace_back("graphics/effect/pikapika/pika_013.png");
		images_.emplace_back("graphics/effect/pikapika/pika_014.png");
		images_.emplace_back("graphics/effect/pikapika/pika_015.png");
		it = images_.begin();
	}
};