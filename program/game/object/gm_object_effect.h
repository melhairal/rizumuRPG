#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "gm_object_actor.h"
class ScenePlay;

class EffectHit : public Actor {
public:
	EffectHit(ScenePlay* scene, int lane);
	~EffectHit() {}
	void update(float delta_time) override;

	// =========== �֐� ==========


	// ========== ��{�X�e�[�^�X ==========

	const float POS_Z_ = -100.0f; //Z���W
	const int FRAME_ = 3
		; //�A�j���[�V�����X�V�t���[��

	void getImage() override {
		// ====================================
		//  �����ɃA�j���[�V�����̉摜����ׂ�
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

	// =========== �֐� ==========


	// ========== ��{�X�e�[�^�X ==========

	const float POS_Z_ = -100.0f; //Z���W
	const int FRAME_ = 3
		; //�A�j���[�V�����X�V�t���[��

	void getImage() override {
		// ====================================
		//  �����ɃA�j���[�V�����̉摜����ׂ�
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

	// =========== �֐� ==========


	// ========== ��{�X�e�[�^�X ==========

	const float POS_Z_ = -100.0f; //Z���W
	const int FRAME_ = 3
		; //�A�j���[�V�����X�V�t���[��

	void getImage() override {
		// ====================================
		//  �����ɃA�j���[�V�����̉摜����ׂ�
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

	// =========== �֐� ==========


	// ========== ��{�X�e�[�^�X ==========

	const float POS_Z_ = -90.0f; //Z���W
	const int FRAME_ = 3
		; //�A�j���[�V�����X�V�t���[��

	void getImage() override {
		// ====================================
		//  �����ɃA�j���[�V�����̉摜����ׂ�
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