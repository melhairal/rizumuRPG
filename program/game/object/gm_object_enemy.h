#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "gm_object_actor.h"
class ScenePlay;

class EnemyBase : public Actor {
public:
	EnemyBase() {};
	virtual ~EnemyBase() {}
	virtual void update(float delta_time) {}

	// =========== �֐� ==========

	void Initialize(ScenePlay* scene, int lane, int atk, int exp); //���b�V���̏�����

	void flow(float speed); //����Ă���
	void shot(Actor* bullet); //�e���΂��Ă���
	void shift(); //���[����ς���

	bool checkLane(); //���[���̊m�F
	void checkJudge(); //����̊m�F

	void notesEnemy(); //�G����
	bool notesEnemyKey(); //�L�[����

	void notesBullet(); //�U������
	bool notesBulletKey(); //�L�[����

	// ========== ��{�X�e�[�^�X ==========

	enum {
		perfect,
		good,
		miss
	};

	bool isBullet = false; //�e���ǂ���
	bool isShift = false; //�V�t�g�������ǂ���
	int shift_r_ = 0; //�V�t�g�p����
	float shift_dis_ = 0; //�V�t�g����
	const int SHIFT_SPEED_ = 30; //�V�t�g�ɂ����鎞��

	const float POS_Z_ = 300.0f; //����Z���W
	const float DEAD_Z_ = -160.0f; //����Z���W
	const float SPEED_ = 4.0f; //�����X�s�[�h(��)

	const float JUDGE_Z_ = -95.0f; //����Z���W
	const float RANGE_PERFECT_ = 10.0f; //�p�[�t�F�N�g����͈̔�
	const float RANGE_GOOD_ = 30.0f; //�O�b�h����͈̔�
	bool perfect_ = false; //�p�[�t�F�N�g����
	bool good_ = false; //�O�b�h����
	const float MISS_Z_ = JUDGE_Z_ - RANGE_GOOD_; //���s����Z���W
	const float RANGE_MISS_ = 20.0f;
	bool miss_ = false; //���s����

	int elapsed_ = 0; //���Ԍv���p

	int atk_ = 0; //�U����
	int exp_ = 0; //�X�R�A�A�o���l
};

class EnemyPig : public EnemyBase {
public:
	EnemyPig(ScenePlay* scene, int lane);
	~EnemyPig() {}
	void update(float delta_time) override;

	// =========== �֐� ==========

	// ========== ��{�X�e�[�^�X ==========

	const int ATK_ = 20;
	const int EXP_ = 100;

	void getImage() override {
		// ====================================
		//  �����ɃA�j���[�V�����̉摜����ׂ�
		// ====================================
		images_.emplace_back("graphics/chara/enemy/pig.png");
		it = images_.begin();
	}
};

class EnemyRizard : public EnemyBase {
public:
	EnemyRizard(ScenePlay* scene, int lane);
	~EnemyRizard() {}
	void update(float delta_time) override;

	// =========== �֐� ==========

	// ========== ��{�X�e�[�^�X ==========
	
	const float SHOT_Z_ = 200.0f; //�e�𔭎˂���Z���W
	const int TIME_SHOT_ = 40; //�e���΂��܂ł̎���
	const int TIME_STOP_ = 80; //��~����

	const int ATK_ = 10;
	const int EXP_ = 200;

	void getImage() override {
		// ====================================
		//  �����ɃA�j���[�V�����̉摜����ׂ�
		// ====================================
		images_.emplace_back("graphics/chara/enemy/rizard.png");
		it = images_.begin();
	}
};

class EnemyRizardBullet : public EnemyBase {
public:
	EnemyRizardBullet(ScenePlay* scene, int lane);
	~EnemyRizardBullet() {}
	void update(float delta_time) override;

	// =========== �֐� ==========

	// ========== ��{�X�e�[�^�X ==========

	const int ATK_ = 30;
	const int EXP_ = 10;

	void getImage() override {
		// ====================================
		//  �����ɃA�j���[�V�����̉摜����ׂ�
		// ====================================
		images_.emplace_back("graphics/effect/fireball.png");
		it = images_.begin();
	}
};

class EnemyMash : public EnemyBase {
public:
	EnemyMash(ScenePlay* scene, int lane);
	~EnemyMash() {}
	void update(float delta_time) override;

	// =========== �֐� ==========

	// ========== ��{�X�e�[�^�X ==========

	const float SHIFT_Z_ = 150.0f; //���[�����ړ�����Z���W

	const int ATK_ = 15;
	const int EXP_ = 200;

	void getImage() override {
		// ====================================
		//  �����ɃA�j���[�V�����̉摜����ׂ�
		// ====================================
		images_.emplace_back("graphics/chara/enemy/mash.png");
		it = images_.begin();
	}
};