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

	int elapsed_ = 0; //���Ԍv���p

};