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
	int se_hit_ = 0; //��e��
	int se_heal_ = 0; //�񕜉�

	int se_select_ = 0; //�R�}���h�I����
	int se_esc_ = 0; //�L�����Z����
	int sound_warning_ = 0; //�x����
	int sound_clear_ = 0; //������
	int sound_failed_ = 0; //���s��

	int bgm_stage_ = 0; //BGM
	int bgm_boss_ = 0; //�{�XBGM

	bool perfect_ = false; //�p�[�t�F�N�g���肩�ǂ���

	int prev_hp_ = 0; //HP�������Ă��邩�ǂ����̊m�F


};