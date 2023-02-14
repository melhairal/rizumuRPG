#pragma once
#include "../dxlib_ext/dxlib_ext.h"
class ScenePlay;
class Actor;
class SkillBase;

class Boss {
public:
	Boss(ScenePlay* scene);
	~Boss();
	void update(float delta_time);
	void render();

	// =========== �֐� ==========

	void initialize(); //�����J��
	void changeAngleCommand(); //�R�}���h�I���̃J�����A���O���ɑJ��
	void changeAngleBattle(); //�o�g���̃J�����A���O���ɑJ��
	void command(); //�R�}���h�I������
	void progress(); //�i�s���o����
	void battle(); //�퓬�J�n(�m�[�c������n�߂�)
	void nextTurn(); //�^�[���i�s���o
	void win(); //��������
	void lose(); //�s�k����

	// ========== ��{�X�e�[�^�X ==========

	ScenePlay* scene_ = nullptr; //�V�[���̕ϐ����擾���邽�߂̃|�C���^
	Actor* enemy_ = nullptr; //�{�X
	dxe::Mesh* field_l1_ = nullptr; //���⊮�p(����)
	dxe::Mesh* field_r1_ = nullptr; //���⊮�p(�E��)
	dxe::Mesh* field_l2_ = nullptr; //���⊮�p(����)
	dxe::Mesh* field_r2_ = nullptr; //���⊮�p(�E��)
	dxe::Mesh* road_ = nullptr; //���⊮�p(��)
	std::shared_ptr<SkillBase> skills_ = nullptr; //�X�L���|�C���^

	const float LEFT_X_ = -300.0f; //�⊮���pX���W
	const float RIGHT_X_ = 300.0f; //�⊮���pX���W
	const float ROAD_Z_ = -375.0f; //�⊮���pZ���W

	int back_ = 0; //�w�i

	bool init_ = false; //�������t���O
	int elapsed_ = 0; //���Ԍv���p

	const int ANGLE_TIMER_ = 120; //�J�����A���O�����ς��̂ɂ����鎞��
	const int INIT_TIMER_ = 75; //�������ɂ����鎞��
	bool is_changing_angle_ = true; //�J�����A���O���ύX�t���O
	bool is_command_angle_ = false; //�R�}���h��ʃA���O��
	bool is_battle_angle_ = true; //�o�g����ʃA���O��

	int hp_max_ = 10; //�{�XHP
	int hp_ = hp_max_;

	bool command_ = false; //�R�}���h�t���O
	bool battle_ = false; //�o�g���J�n�t���O
	bool progress_ = false; //�i�s���o�t���O
	bool next_turn_ = false;
	int action_num_ = -1; //�A�N�V������
	int player_action_[3] = { -1,-1,-1 }; //�v���C���[�̍s����\��
	int enemy_action_[3] = { -1,-1,-1 }; //�G�l�~�[�̍s����\��

	const int INDEX_MAX_ = 3; //�C���f�b�N�X�ő吔
	int index_main_ = 0; //���C���R�}���h�I��p�C���f�b�N�X
	int index_sub_ = 0; //�T�u�R�}���h�I��p�C���f�b�N�X
	int index_sub_list_ = 0; //�T�u�R�}���h���X�g�ʒu�p�C���f�b�N�X
	bool main_command_ = true; //���C���R�}���h���ǂ���
	int select_num_ = 0; //�I�������s����

	bool init_progress_ = false; //���o��������

	bool win_ = false; //�����t���O
	bool lose_ = false; //�����t���O

	bool init_win_ = false; //�������o�̏�������
	bool win_result_ = false; //���U���g��ʂ֑J�ڂ���t���O

	bool init_lose_ = false; //�������o�̏�������
	bool lose_result_ = false; //���U���g��ʂ֑J�ڂ���t���O
};