#pragma once
#include "gm_scene_base.h"
#include "../../dxlib_ext/dxlib_ext.h"
class GmCamera;
class AnimSprite3D;
class SpriteBase;
class ModelBase;

class SceneField : public SceneBase {
public:
	SceneField() {}
	~SceneField();

	void initialzie() override;
	void update(float delta_time) override;
	void render() override;

	// =========== �֐� ==========

	void moveCamera(); //�J��������
	void updateSprites(float delta_time); //�X�v���C�g����
	void updateModels(float delta_time); //���f������

	void setField1(); //�t�B�[���h1�Ԃ𐶐�

	// ========== ��{�X�e�[�^�X ==========

	GmCamera* camera_ = nullptr; //�J����
	SpriteBase* player_ = nullptr; //�v���C���[
	std::list<SpriteBase*> sprites_; //�X�v���C�g���X�g
	std::list<ModelBase*> models_; //3D���f�����X�g

	int img_back_ = 0; //�w�i�摜
	dxe::Mesh* field_ = nullptr; //��

	const float CAM_ROT_SPEED_ = 1.0f; //�J������]���x
	const float CAM_ROT_MAX_ = 60.0f; //�J������]���
	const float CAM_ROT_MIN_ = 10.0f; //�J������]����
	const float CAM_ZOOM_SPEED_ = 5.0f; //�J�����Y�[�����x
	const float CAM_ZOOM_MAX_ = 400.0f; //�J�����Y�[������
	const float CAM_ZOOM_MIN_ = 200.0f; //�J�����Y�[�����

	const float FIELD_H_ = -15.0f; //�n�ʂ̍������W
	const int FIELD_R_ = 800; //�t�B�[���h�̔��a

};