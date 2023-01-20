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

	enum {
		LL, //��ԍ�
		L, //������2�Ԗ�
		R, //�E����2�Ԗ�
		RR //��ԉE
	};

	int lane_ = 0; //���[��

	const float POS_X_[4] = { -110.0f,-35.0f,35.0f,110.0f }; //4�̃��[���̍��W
	const float POS_Y_ = 20.0f; //Y���W

	const float MESH_W_ = 50.0f; //���b�V���̉���
	const float MESH_H_ = 50.0f; //���b�V���̗���

	int elapsed_ = 0; //�A�j���[�V�����v���p
	int frame_ = 0; //�A�j���[�V�����̌��݂̃t���[��
	std::list<std::string> images_; //�A�j���[�V�������X�g
	std::list<std::string>::iterator it; //�A�j���[�V�������X�g�p�C�e���[�^

	int judge_ = -1; //�A�^�b�N�m�[�c�p����
};