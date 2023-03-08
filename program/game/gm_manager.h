#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class SceneBase;
class GameManager {
private:
	GameManager();
	~GameManager();

	int img_black_ = 0;

	static GameManager* instance_;

	// ��ʑJ�ډ��o�̎���
	const float SCENE_TRANSITION_FIX_TIME = 0.5f;
	float scene_transition_time_ = 0;
	float scene_transition_alpha_ = 1.0f;

	tnl::Sequence<GameManager> sequence_ =
		tnl::Sequence<GameManager>(this, &GameManager::seqSceneInTransition);

	// ��ʑJ��( �t�F�[�h�C���v���Z�X )
	bool seqSceneInTransition(const float delta_time);

	// �Q�[���v���Z�X
	bool seqGameProcess(const float delta_time);

	// ��ʑJ��( �t�F�[�h�A�E�g�v���Z�X )
	bool seqSceneOutTransition(const float delta_time);

	// ���݂̃V�[��
	SceneBase* scene_now_ = nullptr;
	// �\��V�[��
	SceneBase* scene_next_ = nullptr;

public:

	// �C���X�^���X�̎擾
	static GameManager* GetInstance();

	// �j��
	static void Destroy();

	// �X�V
	void update(float delta_time);

	// �V�[���̕ύX
	// arg1... SceneBase ���p�������N���X�C���X�^���X
	void chengeScene(SceneBase* next);

public:

	// �Q�[���S�̂ŎQ�Ƃ������ϐ��͂����ŗp��

	//�v���C���[�X�e�[�^�X
	int player_lv_ = 1; //�f�t�H���g1
	int player_atk_ = 10; //�f�t�H���g10
	int player_hp_ = 1000; //�f�t�H���g1000
	int player_mp_ = 0;
	int player_exp_ = 0;
	int player_monney_ = 500; //�f�t�H���g500
	int player_skills_ = 8; //�f�t�H���g�l��2s
	int have_items_[8] = { 0,3,-1,-1,-1,-1,-1,-1 }; //�����Ă�A�C�e��(id)

	//���U���g��ʗp
	bool result_judge_ = true;
	int result_score_ = 0;
	int result_max_combo_ = 0;
	int result_perfect_ = 0;
	int result_good_ = 0;
	int result_miss_ = 0;

	int now_stage_ = 0; //�I�񂾃X�e�[�W

	//�i�s�t���O(�N���A�t���O)
	int flag_stage_ = 6;
	int max_score_[6] = { 0,0,0,0,0,0 };

	//�n�C�X�R�A
	int best_score_[6] = { 0,0,0,0,0,0 };
};