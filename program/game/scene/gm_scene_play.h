#pragma once
#include "gm_scene_base.h"

class GmCamera;
class ObjectBase;
class Actor;

class ScenePlay : public SceneBase {
public :
	ScenePlay(){}
	~ScenePlay();

	void initialzie() override;
	void update(float delta_time) override;
	void render() override;

	// =========== �֐� ==========

	void updateObject(float delta_time); //�I�u�W�F�N�g����
	void updateActor(float delta_time); //�A�N�^�[����

	// ========== ��{�X�e�[�^�X ==========

	GmCamera* camera_ = nullptr;
	dxe::Mesh* frame_ = nullptr;
	std::list<ObjectBase*> objects_; //�I�u�W�F�N�g���X�g
	std::list<Actor*> actors_; //�A�N�^�[���X�g
	Actor* player_ = nullptr; //�v���C���[�|�C���^

	const float FIELD_H_ = 450.0f; //���̏c��
	const float FIELD_W_ = 300.0f; //���̉���
	const float BACK_W_ = 700.0f; //�w�i�̉���
	const float FIELD_Z1_ = 75.0f; //���摜1���ڂ̏���Z���W
	const float FIELD_Z2_ = 525.0f; //���摜2���ڂ̏���Z���W
	std::string road_img = "graphics/base/road.png"; //���摜�p�X
	std::string back_img = "graphics/base/ground.png"; //�w�i�摜�p�X
};

