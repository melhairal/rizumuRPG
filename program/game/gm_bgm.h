#pragma once
#include "../dxlib_ext/dxlib_ext.h"
class ScenePlay;

class Bgm {
public:
	Bgm(ScenePlay* scene);
	~Bgm(){}
	void update(float delta_time);

	// =========== �֐� ==========


	// ========== ��{�X�e�[�^�X ==========

	ScenePlay* scene_ = nullptr; //�V�[���̕ϐ����擾���邽�߂̃|�C���^
	int se_notes_ = 0; //�m�[�c��
	int se_perfect_ = 0; //�p�[�t�F�N�g��

	bool perfect_ = false; //�p�[�t�F�N�g���肩�ǂ���


};