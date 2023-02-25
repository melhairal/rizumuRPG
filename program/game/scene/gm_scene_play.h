#pragma once
#include "gm_scene_base.h"

class GmCamera;
class ObjectBase;
class Actor;
class Ui;
class SubUiBase;
class Bgm;
class Sheet;
class MakeSheet;
class Boss;
class SkillList;
class ItemList;

class ScenePlay : public SceneBase {
public :
	ScenePlay(){}
	~ScenePlay();

	void initialzie() override;
	void update(float delta_time) override;
	void render() override;

	// =========== �֐� ==========

	void getStatus(); //�X�e�[�^�X�擾
	void getSkill(); //�X�L�����擾
	void setScore(); //�X�R�A�����L�^
	void getItem();
	void getSheet(); //�X�e�[�W���擾

	void updateObject(float delta_time); //�I�u�W�F�N�g����
	void updateActor(float delta_time); //�A�N�^�[����
	void updateSubUi(float delta_time); //�T�uUi����
	void deleteList(); //�f���[�g����

	void Debug(float delta_time); //�f�o�b�O

	// ========== ��{�X�e�[�^�X ==========

	GmCamera* camera_ = nullptr;
	Ui* ui_ = nullptr; //���C��UI
	Bgm* bgm_ = nullptr; //BGM,SE
	dxe::Mesh* frame_ = nullptr; //���̐�
	dxe::Mesh* back_black1_ = nullptr; //�w�i�p���n�̍��摜
	dxe::Mesh* back_black2_ = nullptr; //�w�i�p���n�̍��摜
	std::list<ObjectBase*> objects_; //�I�u�W�F�N�g���X�g
	std::list<Actor*> actors_; //�A�N�^�[���X�g
	std::list<SubUiBase*> subUis_; //�T�uUI���X�g
	Actor* player_ = nullptr; //�v���C���[�|�C���^
	Sheet* sheet_ = nullptr; //���ʃ|�C���^
	MakeSheet* make_ = nullptr; //���ʍ쐬�p�N���X�|�C���^
	Boss* boss_ = nullptr; //�{�X��N���X�p�|�C���^
	std::vector<std::vector<std::string>> csv_skill_; //�X�L�����csv
	SkillList* skill_[10] = { nullptr }; //�X�L�����X�g
	std::vector<std::vector<std::string>> csv_item_; //�A�C�e�����csv
	ItemList* item_[10] = { nullptr }; //�A�C�e�����X�g

	int have_item_[8] = { -1,-1,-1,-1,-1,-1,-1,-1 }; //�����Ă�A�C�e��
	int item_num_ = 0; //�����Ă�A�C�e���̐�

	const float FIELD_H_ = 450.0f; //���̏c��
	const float FIELD_W_ = 300.0f; //���̉���
	const float BACK_W_ = 700.0f; //�w�i�̉���
	const float FIELD_Z1_ = 75.0f; //���摜1���ڂ̏���Z���W
	const float FIELD_Z2_ = 525.0f; //���摜2���ڂ̏���Z���W

	std::string road_img_[6] = {
		"graphics/base/road.png",
		"graphics/base/road.png",
		"graphics/base/road.png",
		"graphics/base/road.png",
		"graphics/base/road.png",
		"graphics/base/road.png"
	}; //���摜�p�X
	std::string back_img_[6] = {
		"graphics/base/ground.png",
		"graphics/base/ground.png",
		"graphics/base/cave_wall.jpeg",
		"graphics/base/cave_wall.jpeg",
		"graphics/base/sea.jpg",
		"graphics/base/kuraimori4.jpg"
	}; //�w�i�摜�p�X

	std::string stage_csv_[6] = {
		"csv/stage_1.csv",
		"csv/stage_2.csv",
		"csv/stage_3.csv",
		"csv/stage_4.csv",
		"csv/stage_5.csv",
		"csv/stage_6.csv"
	};

	const int NOTES_SPEED_ = 4; //�m�[�c�̗���鑬�x

	// ========== �Q�[�����X�e�[�^�X ==========

	bool isPause_ = false; //�ꎞ��~

	int stage_ = 1; //�X�e�[�W

	const int COMBO_MAX_ = 999; //�ő�R���{��
	const int mp_max_ = 1000; //�v���C���[�ő�MP
	int combo_ = 0; //�R���{
	int score_ = 0; //�X�R�A
	int hp_max_ = 0; //�v���C���[�ő�HP
	int hp_ = 0; //�v���C���[HP
	int mp_ = 0; //�v���C���[MP
	int atk_ = 0; //�v���C���[�U����
	int player_skills_ = 2; //�o���Ă�X�L���̐�

	bool score_judge_ = true; //���������ǂ���
	int score_perfect_ = 0; //�p�[�t�F�N�g��
	int score_good_ = 0; //�O�b�h��
	int score_miss_ = 0; //�~�X��
	int score_max_combo_ = 0; //�ő�R���{��
};