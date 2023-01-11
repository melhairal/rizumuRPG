#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
class ScenePlay;

class ObjectBase {
public:
	ScenePlay* scene_ = nullptr; //�V�[���̕ϐ����擾���邽�߂̃|�C���^
	ObjectBase() {};
	virtual ~ObjectBase();
	virtual void update(float delta_time) {}

	// =========== �֐� ==========


	// ========== ��{�X�e�[�^�X ==========

	dxe::Mesh* mesh_ = nullptr; //����
	float mesh_w_ = 0; //���b�V���̉���
	float mesh_h_ = 0; //���b�V���̉���

	bool move_ = true; //����t���O
	bool alive_ = true; //�����t���O
};
