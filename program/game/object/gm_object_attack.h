#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "gm_object_actor.h"
class ScenePlay;

class AttackNotes : public Actor {
public:
	AttackNotes(ScenePlay* scene, int lane);
	~AttackNotes() {}
	void update(float delta_time);

	// =========== �֐� ==========

	void flow(float speed); //����Ă���

	void judge(); //����
	bool judgeKey(); //�L�[����

	// ========== ��{�X�e�[�^�X ==========

	enum {
		none = -1,
		perfect,
		good,
		miss
	};

	const float POS_Z_ = 300.0f; //����Z���W
	const float DEAD_Z_ = -160.0f; //����Z���W

	const float JUDGE_Z_ = -96.0f; //����Z���W
	const float RANGE_PERFECT_ = 10.0f; //�p�[�t�F�N�g����͈̔�
	const float RANGE_GOOD_ = 30.0f; //�O�b�h����͈̔�
	const float MISS_Z_ = JUDGE_Z_ - RANGE_GOOD_; //���s����Z���W
	const float RANGE_MISS_ = 15.0f;

	void getImage() override {
		// ====================================
		//  �����ɃA�j���[�V�����̉摜����ׂ�
		// ====================================
		images_.emplace_back("graphics/effect/lockon.png");
		it = images_.begin();
	}
};

class SkillBase {
public:
	SkillBase() {};
	virtual ~SkillBase() {}
	virtual void update(float delta_time) {}

	// =========== �֐� ==========

	void randomPop(); //�����_���ȃ��[���ɐ���
	void checkJudge(); //������m�F

	virtual void notesPerfect(){} //�p�[�t�F�N�g����
	virtual void notesGood(){} //�O�b�h����

	// ========== ��{�X�e�[�^�X ==========

	ScenePlay* scene_ = nullptr; //�V�[���|�C���^
	std::string name_ = "-"; //�Z�̖��O
	int mp_ = 0; //����MP
	int num_ = 0; //���ڂ̃m�[�c��
	bool finish_ = false; //�������I��������ǂ���

	Actor* attacks_[6] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr }; //�A�^�b�N�m�[�c���X�g
	int judges_[6] = { -1,-1,-1,-1,-1,-1 }; //���胊�X�g

	int elapsed_ = 0; //���Ԍv���p
	const int SKILL_INTERVAL_ = 36; //�X�L���ƃX�L���̊Ԋu
};

class SkillNormalA : public SkillBase {
public:
public:
	SkillNormalA(ScenePlay* scene);
	~SkillNormalA() {}
	void update(float delta_time);

	// =========== �֐� ==========

	void notesPerfect(); //�p�[�t�F�N�g����
	void notesGood(); //�O�b�h����

	// ========== ��{�X�e�[�^�X ==========

	const std::string NAME_ = "�A���a��"; //�Z�̖��O
	const int MP_ = 5; //����MP
	const int MAX_NUM_ = 2; //�m�[�h��
	const int INTERVAL_ = 24; //�m�[�h�����Ԋu

};

class SkillNormalB : public SkillBase {
public:
public:
	SkillNormalB(ScenePlay* scene);
	~SkillNormalB() {}
	void update(float delta_time);

	// =========== �֐� ==========

	void notesPerfect(); //�p�[�t�F�N�g����
	void notesGood(); //�O�b�h����

	// ========== ��{�X�e�[�^�X ==========

	const std::string NAME_ = "�O�A�a��"; //�Z�̖��O
	const int MP_ = 10; //����MP
	const int MAX_NUM_ = 3; //�m�[�h��
	const int INTERVAL_ = 24; //�m�[�h�����Ԋu

};

class SkillComboA : public SkillBase {
public:
public:
	SkillComboA(ScenePlay* scene);
	~SkillComboA() {}
	void update(float delta_time);

	// =========== �֐� ==========

	void notesPerfect(); //�p�[�t�F�N�g����
	void notesGood(); //�O�b�h����

	// ========== ��{�X�e�[�^�X ==========

	const std::string NAME_ = "���a��"; //�Z�̖��O
	const int MP_ = 20; //����MP
	const int MAX_NUM_ = 3; //�m�[�h��
	const int INTERVAL_ = 18; //�m�[�h�����Ԋu

};

class SkillComboB : public SkillBase {
public:
public:
	SkillComboB(ScenePlay* scene);
	~SkillComboB() {}
	void update(float delta_time);

	// =========== �֐� ==========

	void notesPerfect(); //�p�[�t�F�N�g����
	void notesGood(); //�O�b�h����

	// ========== ��{�X�e�[�^�X ==========

	const std::string NAME_ = "�_���a��"; //�Z�̖��O
	const int MP_ = 30; //����MP
	const int MAX_NUM_ = 5; //�m�[�h��
	const int INTERVAL_ = 18; //�m�[�h�����Ԋu

};

class SkillComboC : public SkillBase {
public:
public:
	SkillComboC(ScenePlay* scene);
	~SkillComboC() {}
	void update(float delta_time);

	// =========== �֐� ==========

	void notesPerfect(); //�p�[�t�F�N�g����
	void notesGood(); //�O�b�h����

	// ========== ��{�X�e�[�^�X ==========

	const std::string NAME_ = "�_�u���A�b�v"; //�Z�̖��O
	const int MP_ = 50; //����MP
	const int MAX_NUM_ = 4; //�m�[�h��
	const int INTERVAL_ = 24; //�m�[�h�����Ԋu

};

class SkillComboD : public SkillBase {
public:
public:
	SkillComboD(ScenePlay* scene);
	~SkillComboD() {}
	void update(float delta_time);

	// =========== �֐� ==========

	void notesPerfect(); //�p�[�t�F�N�g����
	void notesGood(); //�O�b�h����

	// ========== ��{�X�e�[�^�X ==========

	const std::string NAME_ = "�g���v���A�b�v"; //�Z�̖��O
	const int MP_ = 60; //����MP
	const int MAX_NUM_ = 6; //�m�[�h��
	const int INTERVAL_ = 18; //�m�[�h�����Ԋu

};