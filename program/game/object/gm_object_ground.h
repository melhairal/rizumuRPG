#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "gm_object_base.h"

class Ground : public ObjectBase {
public:
	Ground(ScenePlay* scene, float w, float h, float z, const std::string img);
	~Ground() {}
	void update(float delta_time) override;

	// =========== �֐� ==========


	// ========== ��{�X�e�[�^�X ==========

	const int SPEED_ = 3;
	const int MIN_ = -375;
	const int MAX_ = 525;
};

class Line : public ObjectBase {
public:
	Line(ScenePlay* scene);
	~Line() {}
	void update(float delta_time) override;

	// =========== �֐� ==========


	// ========== ��{�X�e�[�^�X ==========

	const float MESH_W_ = 300.0f; //���b�V���̉���
	const float MESH_H_ = 5.0f; //���b�V���̗���
	const float POS_Z_ = 300.0f; //����Z���W
	const float DEAD_Z_ = -180.0f; //����Z���W

};