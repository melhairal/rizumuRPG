#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
class SceneField;

class ModelBase {
public:
	ModelBase() {}
	virtual ~ModelBase() {}
	virtual void update(float delta_time) {}
	virtual void render() {}

	// =========== �֐� ==========

	void hitPlayer(tnl::Vector3 size); //�v���C���[�Ƃ̏Փ˔���

	// =========== ��{�X�e�[�^�X ==========

	SceneField* scene_ = nullptr; //�V�[�������擾

	int mv1_ = 0; //���f���n���h��
	tnl::Vector3 pos_ = { 0,0,0 }; //���W

	bool render_ = true; //�`��t���O
	bool alive_ = true; //�����t���O
};

class ModelHouse : public ModelBase {
public:
	ModelHouse(SceneField* scene, tnl::Vector3 pos, tnl::Vector3 rot);
	~ModelHouse() {}
	void update(float delta_time);
	void render();

	// =========== �֐� ==========

	// =========== ��{�X�e�[�^�X ==========

	tnl::Vector3 size_ = { 200,200,200 }; //�Փ˔���p�傫��
};