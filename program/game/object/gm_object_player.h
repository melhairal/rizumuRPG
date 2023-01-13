#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "gm_object_actor.h"
class ScenePlay;

class Player : public Actor {
public:
	Player(ScenePlay* scene);
	~Player() {}
	void update(float delta_time) override;

	// =========== �֐� ==========


	// ========== ��{�X�e�[�^�X ==========

	const float POS_Z_ = -100.0f; //Z���W
	const int FRAME_ = 10; //�A�j���[�V�����X�V�t���[��


	void getImage() override {
		// ====================================
		//  �����ɃA�j���[�V�����̉摜����ׂ�
		// ====================================
		images_.emplace_back("graphics/chara/player/1.png");
		images_.emplace_back("graphics/chara/player/2.png");
		images_.emplace_back("graphics/chara/player/3.png");
		it = images_.begin();
	}
};
