#pragma once
#include "../dxlib_ext/dxlib_ext.h"
class ScenePlay;
class Actor;

class Boss {
public:
	Boss(ScenePlay* scene);
	~Boss() {}
	void update(float delta_time);
	void render();

	// =========== �֐� ==========

	void initialize(); //�����J��
	void changeAngleCommand(); //�R�}���h�I���̃J�����A���O���ɑJ��
	void changeAngleBattle(); //�o�g���̃J�����A���O���ɑJ��

	// ========== ��{�X�e�[�^�X ==========

	ScenePlay* scene_ = nullptr; //�V�[���̕ϐ����擾���邽�߂̃|�C���^
	Actor* enemy_ = nullptr; //�{�X
	dxe::Mesh* field_l1_ = nullptr; //���⊮�p(����)
	dxe::Mesh* field_r1_ = nullptr; //���⊮�p(�E��)
	dxe::Mesh* field_l2_ = nullptr; //���⊮�p(����)
	dxe::Mesh* field_r2_ = nullptr; //���⊮�p(�E��)
	dxe::Mesh* road_ = nullptr; //���⊮�p(��)

	const float LEFT_X_ = -300.0f; //�⊮���pX���W
	const float RIGHT_X_ = 300.0f; //�⊮���pX���W
	const float ROAD_Z_ = -375.0f; //�⊮���pZ���W

	int back_ = 0; //�w�i

	bool init_ = false; //�������t���O
	int elapsed_ = 0; //���Ԍv���p

	const int ANGLE_TIMER_ = 120; //�J�����A���O�����ς��̂ɂ����鎞��
	const int INIT_TIMER_ = 75; //�������ɂ����鎞��
	bool is_changing_angle_ = true; //�J�����A���O���ύX�t���O
	bool is_command_angle_ = false; //�R�}���h��ʃA���O��
	bool is_battle_angle_ = true; //�o�g����ʃA���O��

	int hp_max_ = 1000; //�{�XHP
	int hp_ = hp_max_;
};