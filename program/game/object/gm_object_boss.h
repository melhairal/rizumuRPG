#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "gm_object_actor.h"
class ScenePlay;

class BossEnemy : public Actor {
public:
	BossEnemy() {}
	virtual ~BossEnemy() {}
	virtual void update(float delta_time) {}

	// =========== �֐� ==========

	void initialize(ScenePlay* scene); //������
	void switchAction(); //�A�N�V�����̐؂�ւ�
	void setMove(float x, float z); //�ړ��p���l�Z�b�g�A�b�v
	void move(float x, float z); //���b�V���̈ړ�
	virtual void attackMeleeA(){} //�ߐڍU��1
	virtual void attackMeleeB(){} //�ߐڍU��2
	virtual void attackRangeA(){} //�S�̍U��1
	virtual void attackRangeB(){} //�S�̍U��2
	virtual void attackBulletA(){} //���u�U��1
	virtual void attackBulletB(){} //���u�U��2

	// ========== ��{�X�e�[�^�X ==========

	const float POS_Z_ = 300.0f; //Z���W
	const float MELEE_POS_Z_ = 0.0f; //�ڋ�Z���W
	const float BULLET_POS_Z_ = 100.0f; //���uZ���W

	const int FLOW_INTERVAL_ = 99; //�m�[�c������Ă��Ă��画�胉�C���ɓ��B����܂ł̃��O
	const int BULLET_INTERVAL_ = 49; //�������U��������Ă��Ă��画�胉�C���ɓ��B����܂ł̃��O
	const int MOVE_SPEED_ = 18; //�ړ��ɂ����鎞��
	const int ATTACK_INTERVAL_FAST_ = 18; //�U���Ԋu(�Z)
	const int ATTACK_INTERVAL_SLOW_ = 36; //�U���Ԋu(�x)

	int r_[20] = { 0 }; //�U�����[�������ۑ��p
	float dir_x_ = 0; //�ړ��ʂ�ۑ�
	float dir_z_ = 0; //�ړ��ʂ�ۑ�

	int move_flame_ = 0; //�ړ��ʌv���p
	int elapsed_ = 0; //���Ԍv��
};

class BossGorem : public BossEnemy {
public:
	BossGorem(ScenePlay* scene);
	~BossGorem() {}
	void update(float delta_time);

	// =========== �֐� ==========

	void attackMeleeA(); //�ߐڍU��1
	void attackMeleeB(); //�ߐڍU��2
	void attackRangeA(); //�S�̍U��1
	void attackRangeB(); //�S�̍U��2
	void attackBulletA(); //���u�U��1
	void attackBulletB(); //���u�U��2
	

	// ========== ��{�X�e�[�^�X ==========

	const int ATK_MELEE_ = 40;
	const int ATK_RANGE_ = 20;
	const int ATK_BULLET_ = 0;

	void getImage() override {
		// ====================================
		//  �����ɃA�j���[�V�����̉摜����ׂ�
		// ====================================
		images_.emplace_back("graphics/chara/enemy/gorem.png");
		it = images_.begin();
	}
};

class BossDragon : public BossEnemy {
public:
	BossDragon(ScenePlay* scene);
	~BossDragon() {}
	void update(float delta_time);

	// =========== �֐� ==========

	void attackMeleeA(); //�ߐڍU��1
	void attackMeleeB(); //�ߐڍU��2
	void attackRangeA(); //�S�̍U��1
	void attackRangeB(); //�S�̍U��2
	void attackBulletA(); //���u�U��1
	void attackBulletB(); //���u�U��2


	// ========== ��{�X�e�[�^�X ==========

	const int ATK_MELEE_ = 50;
	const int ATK_RANGE_ = 40;
	const int ATK_BULLET_ = 70;

	void getImage() override {
		// ====================================
		//  �����ɃA�j���[�V�����̉摜����ׂ�
		// ====================================
		images_.emplace_back("graphics/chara/enemy/dragon.png");
		it = images_.begin();
	}
};

class BossKeruberos : public BossEnemy {
public:
	BossKeruberos(ScenePlay* scene);
	~BossKeruberos() {}
	void update(float delta_time);

	// =========== �֐� ==========

	void attackMeleeA(); //�ߐڍU��1
	void attackMeleeB(); //�ߐڍU��2
	void attackRangeA(); //�S�̍U��1
	void attackRangeB(); //�S�̍U��2
	void attackBulletA(); //���u�U��1
	void attackBulletB(); //���u�U��2


	// ========== ��{�X�e�[�^�X ==========

	const int ATK_MELEE_ = 90;
	const int ATK_RANGE_ = 40;
	const int ATK_BULLET_ = 50;

	void getImage() override {
		// ====================================
		//  �����ɃA�j���[�V�����̉摜����ׂ�
		// ====================================
		images_.emplace_back("graphics/chara/enemy/keruberos.png");
		it = images_.begin();
	}
};

class BossNotes : public Actor {
public:
	BossNotes() {}
	virtual ~BossNotes() {}
	virtual void update(float delta_time) {}

	// =========== �֐� ==========

	void initialize(ScenePlay* scene, int damage, int lane);
	void flow(float speed); //����Ă���

	void judge(); //����
	bool judgeKey(); //�L�[����

	void judgeAll(); //�S�̍U���̔���

	// ========== ��{�X�e�[�^�X ==========

	enum {
		none = -1,
		perfect,
		good,
		miss
	};

	const float POS_Z_ = 300.0f; //����Z���W
	const float BULLET_POS_Z_ = 100.0f; //���uZ���W
	const float DEAD_Z_ = -160.0f; //����Z���W

	const float JUDGE_Z_ = -96.0f; //����Z���W
	const float RANGE_PERFECT_ = 10.0f; //�p�[�t�F�N�g����͈̔�
	const float RANGE_GOOD_ = 30.0f; //�O�b�h����͈̔�
	const float MISS_Z_ = JUDGE_Z_ - RANGE_GOOD_; //���s����Z���W
	const float RANGE_MISS_ = 15.0f; //���s����͈̔�

	int damage_ = 0;
};

class NotesWarning : public BossNotes {
public:
	NotesWarning(ScenePlay* scene, int damage, int lane);
	~NotesWarning() {}
	void update(float delta_time) override;

	// =========== �֐� ==========

	// ========== ��{�X�e�[�^�X ==========

	void getImage() override {
		// ====================================
		//  �����ɃA�j���[�V�����̉摜����ׂ�
		// ====================================
		images_.emplace_back("graphics/effect/warning.png");
		it = images_.begin();
	}
};

class NotesWarningAll : public BossNotes {
public:
	NotesWarningAll(ScenePlay* scene, int damage, int lane);
	~NotesWarningAll() {}
	void update(float delta_time) override;

	// =========== �֐� ==========

	// ========== ��{�X�e�[�^�X ==========

	void getImage() override {
		// ====================================
		//  �����ɃA�j���[�V�����̉摜����ׂ�
		// ====================================
		images_.emplace_back("graphics/effect/warning.png");
		it = images_.begin();
	}
};

class NotesDragonBless : public BossNotes {
public:
	NotesDragonBless(ScenePlay* scene, int damage, int lane);
	~NotesDragonBless() {}
	void update(float delta_time) override;

	// =========== �֐� ==========

	// ========== ��{�X�e�[�^�X ==========

	void getImage() override {
		// ====================================
		//  �����ɃA�j���[�V�����̉摜����ׂ�
		// ====================================
		images_.emplace_back("graphics/effect/fireball.png");
		it = images_.begin();
	}
};

class NotesKeruberosBless : public BossNotes {
public:
	NotesKeruberosBless(ScenePlay* scene, int damage, int lane);
	~NotesKeruberosBless() {}
	void update(float delta_time) override;

	// =========== �֐� ==========

	// ========== ��{�X�e�[�^�X ==========

	void getImage() override {
		// ====================================
		//  �����ɃA�j���[�V�����̉摜����ׂ�
		// ====================================
		images_.emplace_back("graphics/effect/blackball1.png");
		it = images_.begin();
	}
};