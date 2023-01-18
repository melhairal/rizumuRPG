#pragma once
#include "../dxlib_ext/dxlib_ext.h"
class ScenePlay;

class Sheet {
public:
	Sheet(ScenePlay* scene);
	~Sheet(){}
	void update(float delta_time);

	// =========== �֐� ==========


	// ========== ��{�X�e�[�^�X ==========

	ScenePlay* scene_ = nullptr; //�V�[���̕ϐ����擾���邽�߂̃|�C���^
	std::vector<std::vector<std::string>> csv_; //����csv
	int bgm_ = 0; //bgm
	int bpm_ = 10; //�m�[�c���x(���C���ƃ��C���̊Ԃɂ���m�[�c�̐�)

	int elapsed_ = 0; //���Ԍv���p
	const int INTERVAL_LINE_ = 120; //���C��������Ă���Ԋu

	int bgm_timer_ = 0; //BGM���O�v���p
	const int START_INTERVAL_ = 99; //�ŏ��̃��C�������胉�C���ɓ��B����܂ł̃��O

	int csv_y_ = 1;

	int save_ = 0;
};