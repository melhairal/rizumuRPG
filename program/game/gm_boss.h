#pragma once
#include "../dxlib_ext/dxlib_ext.h"
class ScenePlay;

class Boss {
public:
	Boss(ScenePlay* scene);
	~Boss() {}
	void update(float delta_time);

	// =========== �֐� ==========


	// ========== ��{�X�e�[�^�X ==========

	ScenePlay* scene_ = nullptr; //�V�[���̕ϐ����擾���邽�߂̃|�C���^

	int elapsed_ = 0; //���Ԍv���p

};