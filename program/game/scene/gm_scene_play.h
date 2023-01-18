#pragma once
#include "gm_scene_base.h"

class GmCamera;
class ObjectBase;
class Actor;
class Ui;
class SubUiJudge;
class Bgm;
class Sheet;
class MakeSheet;
class Boss;

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
	void updateSubUi(float delta_time); //�T�uUi����

	void Debug(); //�f�o�b�O

	// ========== ��{�X�e�[�^�X ==========

	GmCamera* camera_ = nullptr;
	Ui* ui_ = nullptr; //���C��UI
	Bgm* bgm_ = nullptr; //BGM,SE
	dxe::Mesh* frame_ = nullptr; //���̐�
	std::list<ObjectBase*> objects_; //�I�u�W�F�N�g���X�g
	std::list<Actor*> actors_; //�A�N�^�[���X�g
	std::list<SubUiJudge*> subUis_; //�T�uUI���X�g
	Actor* player_ = nullptr; //�v���C���[�|�C���^
	Sheet* sheet_ = nullptr; //���ʃ|�C���^
	MakeSheet* make_ = nullptr; //���ʍ쐬�p�N���X�|�C���^
	Boss* boss_ = nullptr; //�{�X��N���X�p�|�C���^

	const float FIELD_H_ = 450.0f; //���̏c��
	const float FIELD_W_ = 300.0f; //���̉���
	const float BACK_W_ = 700.0f; //�w�i�̉���
	const float FIELD_Z1_ = 75.0f; //���摜1���ڂ̏���Z���W
	const float FIELD_Z2_ = 525.0f; //���摜2���ڂ̏���Z���W
	std::string road_img = "graphics/base/road.png"; //���摜�p�X
	std::string back_img = "graphics/base/ground.png"; //�w�i�摜�p�X

	std::string stage_2_csv_ = "csv/stage_2.csv"; //csv�p�X

	const int NOTES_SPEED_ = 4; //�m�[�c�̗���鑬�x

	// ========== �Q�[�����X�e�[�^�X ==========

	const int COMBO_MAX_ = 999; //�ő�R���{��
	int combo_ = 0; //�R���{

	int score_ = 0; //�X�R�A

	int hp_max_ = 1000; //�v���C���[�ő�HP
	int hp_ = hp_max_; //�v���C���[HP

	int mp_max_ = 1000; //�v���C���[�ő�MP
	int mp_ = 0; //�v���C���[MP
};

