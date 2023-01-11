#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "gm_object_base.h"

class Actor : public ObjectBase {
public:
	Actor() {};
	virtual ~Actor() {}
	virtual void update(float delta_time) {}

	// =========== �֐� ==========

	virtual void getImage() {} //�A�j���[�V�����摜�Z�b�g
	void animation(int frame); //�A�j���[�V�����̍X�V

	// ========== ��{�X�e�[�^�X ==========

	const float X_LL_ = -110.0f; //��ԍ���X���W
	const float X_L_ = -35.0f; //������2�Ԗڂ�X���W
	const float X_R_ = 35.0f; //�E����2�Ԗڂ�X���W
	const float X_RR_ = 110.0f; //��ԉE��X���W

	int elapsed_ = 0; //�A�j���[�V�����v���p
	int frame_ = 0; //�A�j���[�V�����̌��݂̃t���[��
	std::list<std::string> images_; //�A�j���[�V�������X�g
	std::list<std::string>::iterator it; //�A�j���[�V�������X�g�p�C�e���[�^
};


class Player : public Actor {
public:
	Player(ScenePlay* scene);
	~Player() {}
	void update(float delta_time) override;

	// =========== �֐� ==========


	// ========== ��{�X�e�[�^�X ==========

	const float MESH_W_ = 50.0f; //���b�V���̉���
	const float MESH_H_ = 50.0f; //���b�V���̗���
	const float POS_Y_ = 20.0f; //Y���W
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