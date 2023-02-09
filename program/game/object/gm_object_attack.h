#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "gm_object_actor.h"
#include <unordered_map>
#include <functional>
#include <memory>

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

	bool set_enemy_pos_ = false;

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

	void damage(); //�_���[�W�v�Z

	void randomPop(); //�����_���ȃ��[���ɐ���
	void checkJudge(); //������m�F

	virtual void notesPerfect(){} //�p�[�t�F�N�g����
	virtual void notesGood(){} //�O�b�h����

	// ========== ��{�X�e�[�^�X ==========

	ScenePlay* scene_ = nullptr; //�V�[���|�C���^
	int num_ = 0; //���ڂ̃m�[�c��
	bool finish_ = false; //�������I��������ǂ���

	Actor* attacks_[6] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr }; //�A�^�b�N�m�[�c���X�g
	int judges_[6] = { -1,-1,-1,-1,-1,-1 }; //���胊�X�g

	int elapsed_ = 0; //���Ԍv���p
	const int SKILL_INTERVAL_ = 150; //�X�L���ƃX�L���̊Ԋu

	int damage_good_ = 0;
	int damage_perfect_ = 0;
};

class SkillNormalA : public SkillBase {
public:
	SkillNormalA(ScenePlay* scene);
	~SkillNormalA() {}
	void update(float delta_time);

	// =========== �֐� ==========

	void notesPerfect(); //�p�[�t�F�N�g����
	void notesGood(); //�O�b�h����

	// ========== ��{�X�e�[�^�X ==========

	const int MAX_NUM_ = 2; //�m�[�h��
	const int INTERVAL_ = 24; //�m�[�h�����Ԋu

};

class SkillNormalB : public SkillBase {
public:
	SkillNormalB(ScenePlay* scene);
	~SkillNormalB() {}
	void update(float delta_time);

	// =========== �֐� ==========

	void notesPerfect(); //�p�[�t�F�N�g����
	void notesGood(); //�O�b�h����

	// ========== ��{�X�e�[�^�X ==========

	const int MAX_NUM_ = 3; //�m�[�h��
	const int INTERVAL_ = 24; //�m�[�h�����Ԋu

};

class SkillComboA : public SkillBase {
public:
	SkillComboA(ScenePlay* scene);
	~SkillComboA() {}
	void update(float delta_time);

	// =========== �֐� ==========

	void notesPerfect(); //�p�[�t�F�N�g����
	void notesGood(); //�O�b�h����

	// ========== ��{�X�e�[�^�X ==========

	const int MAX_NUM_ = 3; //�m�[�h��
	const int INTERVAL_ = 18; //�m�[�h�����Ԋu

};

class SkillComboB : public SkillBase {
public:
	SkillComboB(ScenePlay* scene);
	~SkillComboB() {}
	void update(float delta_time);

	// =========== �֐� ==========

	void notesPerfect(); //�p�[�t�F�N�g����
	void notesGood(); //�O�b�h����

	// ========== ��{�X�e�[�^�X ==========

	const int MAX_NUM_ = 5; //�m�[�h��
	const int INTERVAL_ = 18; //�m�[�h�����Ԋu

};

class SkillComboC : public SkillBase {
public:
	SkillComboC(ScenePlay* scene);
	~SkillComboC() {}
	void update(float delta_time);

	// =========== �֐� ==========

	void notesPerfect(); //�p�[�t�F�N�g����
	void notesGood(); //�O�b�h����

	// ========== ��{�X�e�[�^�X ==========

	const int MAX_NUM_ = 4; //�m�[�h��
	const int INTERVAL_ = 24; //�m�[�h�����Ԋu

};

class SkillComboD : public SkillBase {
public:
	SkillComboD(ScenePlay* scene);
	~SkillComboD() {}
	void update(float delta_time);

	// =========== �֐� ==========

	void notesPerfect(); //�p�[�t�F�N�g����
	void notesGood(); //�O�b�h����

	// ========== ��{�X�e�[�^�X ==========

	const int MAX_NUM_ = 6; //�m�[�h��
	const int INTERVAL_ = 18; //�m�[�h�����Ԋu

};

class SkillPowerA : public SkillBase {
public:
	SkillPowerA(ScenePlay* scene);
	~SkillPowerA() {}
	void update(float delta_time);

	// =========== �֐� ==========

	void notesPerfect(); //�p�[�t�F�N�g����
	void notesGood(); //�O�b�h����

	// ========== ��{�X�e�[�^�X ==========

	const int MAX_NUM_ = 1; //�m�[�h��
	const int INTERVAL_ = 24; //�m�[�h�����Ԋu

};

class SkillPowerB : public SkillBase {
public:
	SkillPowerB(ScenePlay* scene);
	~SkillPowerB() {}
	void update(float delta_time);

	// =========== �֐� ==========

	void notesPerfect(); //�p�[�t�F�N�g����
	void notesGood(); //�O�b�h����

	// ========== ��{�X�e�[�^�X ==========

	const int MAX_NUM_ = 2; //�m�[�h��
	const int INTERVAL_ = 18; //�m�[�h�����Ԋu

};

class SkillPowerC : public SkillBase {
public:
	SkillPowerC(ScenePlay* scene);
	~SkillPowerC() {}
	void update(float delta_time);

	// =========== �֐� ==========

	void notesPerfect(); //�p�[�t�F�N�g����
	void notesGood(); //�O�b�h����

	// ========== ��{�X�e�[�^�X ==========

	const int MAX_NUM_ = 1; //�m�[�h��
	const int INTERVAL_ = 24; //�m�[�h�����Ԋu

};

class SkillOtherA : public SkillBase {
public:
	SkillOtherA(ScenePlay* scene);
	~SkillOtherA() {}
	void update(float delta_time);

	// =========== �֐� ==========

	void notesPerfect(); //�p�[�t�F�N�g����
	void notesGood(); //�O�b�h����

	// ========== ��{�X�e�[�^�X ==========

	const int MAX_NUM_ = 3; //�m�[�h��
	const int INTERVAL_ = 24; //�m�[�h�����Ԋu

};


class SkillList {
public:
	SkillList() {}
	~SkillList() {}
	std::string name_ = "-"; //���O
	std::string class_name_ = "class -"; //�N���X��
	std::string exp1_ = "-"; //������
	std::string exp2_ = "-"; //������
	std::string exp3_ = "-"; //������
	int mp_ = 0; //����MP
};