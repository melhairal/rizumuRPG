#pragma once
#include "gm_scene_base.h"
#include "../../dxlib_ext/dxlib_ext.h"
class GmCamera;
class AnimSprite3D;
class SpriteBase;
class ModelBase;
class FieldUi;
class SkillList;
class ItemList;

class SceneField : public SceneBase {
public:
	SceneField() {}
	~SceneField();

	void initialzie() override;
	void update(float delta_time) override;
	void render() override;

	// =========== �֐� ==========
	
	void getStatus(); //�X�e�[�^�X���擾
	void getSkill(); //�X�L�������擾
	void getItem(); //�A�C�e�������擾
	void setItem(); //�A�C�e������o�^

	void moveCamera(); //�J��������
	void updateSprites(float delta_time); //�X�v���C�g����
	void updateModels(float delta_time); //���f������
	void playSe(); //SE����

	void outField(); //�t�B�[���h����o�鏈��

	void setField1(); //�t�B�[���h1�Ԃ𐶐�

	void finishGame(); //�Q�[���I��

	// ========== ��{�X�e�[�^�X ==========

	GmCamera* camera_ = nullptr; //�J����
	SpriteBase* player_ = nullptr; //�v���C���[
	std::list<SpriteBase*> sprites_; //�X�v���C�g���X�g
	std::list<ModelBase*> models_; //3D���f�����X�g
	FieldUi* ui_ = nullptr; //UI

	int img_back_ = 0; //�w�i�摜
	dxe::Mesh* field_ = nullptr; //��
	dxe::Mesh* load_ = nullptr; //��

	int bgm_ = 0; //BGM
	int se_select_ = 0; //�I����
	int se_esc_ = 0; //�L�����Z����

	//�v���C���[�X�e�[�^�X
	int player_lv_ = 0;
	int player_hp_ = 0;
	int player_atk_ = 0;
	int player_exp_ = 0;
	int player_monney_ = 0;
	int player_skills_ = 4;

	std::vector<std::vector<std::string>> csv_skill_; //�X�L�����csv
	SkillList* skill_[10] = { nullptr }; //�X�L�����X�g

	std::vector<std::vector<std::string>> csv_item_; //�X�L�����csv
	ItemList* item_[5] = { nullptr }; //�A�C�e�����X�g
	int items_[8] = { -1,-1,-1,-1,-1,-1,-1,-1 };

	//�o���l�e�[�u��
	const int UP_EXP_[10] = {
		1000,
		2000,
		3000,
		5000,
		10000,
		20000,
		30000,
		40000,
		50000,
		0
	};

	const float CAM_ROT_SPEED_ = 1.0f; //�J������]���x
	const float CAM_ROT_MAX_ = 60.0f; //�J������]���
	const float CAM_ROT_MIN_ = 10.0f; //�J������]����
	const float CAM_ZOOM_SPEED_ = 5.0f; //�J�����Y�[�����x
	const float CAM_ZOOM_MAX_ = 400.0f; //�J�����Y�[������
	const float CAM_ZOOM_MIN_ = 200.0f; //�J�����Y�[�����

	const float FIELD_H_ = -15.0f; //�n�ʂ̍������W
	const int FIELD_R_ = 800; //�t�B�[���h�̔��a

	bool isMenu_ = false; //���j���[�t���O
	bool isShop_ = false; //�V���b�v�t���O

};