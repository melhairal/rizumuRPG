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

	bool isBullet_ = false; //�e���ǂ���
	bool isShift_ = false; //�V�t�g�������ǂ���
	bool initElapsed_ = false; //�V�t�g�֐���elapsed�����������邽�߂̃t���O
	int shift_r_ = 0; //�V�t�g�p����
	float shift_dis_ = 0; //�V�t�g����
	const int SHIFT_SPEED_ = 36; //�V�t�g�ɂ����鎞��

	const float POS_Z_ = 300.0f; //����Z���W
	const float DEAD_Z_ = -160.0f; //����Z���W

	const float JUDGE_Z_ = -96.0f; //����Z���W
	const float RANGE_PERFECT_ = 10.0f; //�p�[�t�F�N�g����͈̔�
	const float RANGE_GOOD_ = 30.0f; //�O�b�h����͈̔�
	bool perfect_ = false; //�p�[�t�F�N�g����
	bool good_ = false; //�O�b�h����
	const float MISS_Z_ = JUDGE_Z_ - RANGE_GOOD_; //���s����Z���W
	const float RANGE_MISS_ = 15.0f;
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
	const int TIME_SHOT_ = 36; //�e���΂��܂ł̎���
	const int TIME_STOP_ = 72; //��~����

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

class EnemyGrifin : public EnemyBase {
public:
	EnemyGrifin(ScenePlay* scene, int lane);
	~EnemyGrifin() {}
	void update(float delta_time) override;

	// =========== �֐� ==========

	// ========== ��{�X�e�[�^�X ==========

	const float SHOT_Z_ = 170.0f; //�e�𔭎˂���Z���W
	const int TIME_SHOT_ = 24; //�e���΂��܂ł̎���
	const int TIME_STOP_ = 48; //��~����

	const float SHIFT_Z_ = 120.0f; //���[�����ړ�����Z���W

	const int ATK_ = 30;
	const int EXP_ = 300;

	void getImage() override {
		// ====================================
		//  �����ɃA�j���[�V�����̉摜����ׂ�
		// ====================================
		images_.emplace_back("graphics/chara/enemy/grifin.png");
		it = images_.begin();
	}
};

class EnemyGrifinBullet : public EnemyBase {
public:
	EnemyGrifinBullet(ScenePlay* scene, int lane);
	~EnemyGrifinBullet() {}
	void update(float delta_time) override;

	// =========== �֐� ==========

	// ========== ��{�X�e�[�^�X ==========

	const int ATK_ = 40;
	const int EXP_ = 15;

	const int FRAME_ = 3;

	void getImage() override {
		// ====================================
		//  �����ɃA�j���[�V�����̉摜����ׂ�
		// ====================================
		images_.emplace_back("graphics/effect/wind/wind_001.png");
		images_.emplace_back("graphics/effect/wind/wind_002.png");
		images_.emplace_back("graphics/effect/wind/wind_003.png");
		images_.emplace_back("graphics/effect/wind/wind_004.png");
		images_.emplace_back("graphics/effect/wind/wind_005.png");
		images_.emplace_back("graphics/effect/wind/wind_006.png");
		images_.emplace_back("graphics/effect/wind/wind_007.png");
		images_.emplace_back("graphics/effect/wind/wind_008.png");
		images_.emplace_back("graphics/effect/wind/wind_009.png");
		images_.emplace_back("graphics/effect/wind/wind_010.png");
		images_.emplace_back("graphics/effect/wind/wind_011.png");
		images_.emplace_back("graphics/effect/wind/wind_012.png");
		images_.emplace_back("graphics/effect/wind/wind_013.png");
		images_.emplace_back("graphics/effect/wind/wind_014.png");
		images_.emplace_back("graphics/effect/wind/wind_015.png");
		it = images_.begin();
	}
};

class EnemyBad : public EnemyBase {
public:
	EnemyBad(ScenePlay* scene, int lane);
	~EnemyBad() {}
	void update(float delta_time) override;

	// =========== �֐� ==========

	// ========== ��{�X�e�[�^�X ==========

	const int ATK_ = 30;
	const int EXP_ = 150;

	void getImage() override {
		// ====================================
		//  �����ɃA�j���[�V�����̉摜����ׂ�
		// ====================================
		images_.emplace_back("graphics/chara/enemy/bad.png");
		it = images_.begin();
	}
};

class EnemyMagician : public EnemyBase {
public:
	EnemyMagician(ScenePlay* scene, int lane);
	~EnemyMagician() {}
	void update(float delta_time) override;

	// =========== �֐� ==========

	// ========== ��{�X�e�[�^�X ==========

	const float SHOT_Z_ = 170.0f; //�e�𔭎˂���Z���W
	const int TIME_SHOT_ = 24; //�e���΂��܂ł̎���
	const int TIME_STOP_ = 60; //��~����

	const int ATK_ = 20;
	const int EXP_ = 250;

	void getImage() override {
		// ====================================
		//  �����ɃA�j���[�V�����̉摜����ׂ�
		// ====================================
		images_.emplace_back("graphics/chara/enemy/magician.png");
		it = images_.begin();
	}
};

class EnemyMagicianBullet : public EnemyBase {
public:
	EnemyMagicianBullet(ScenePlay* scene, int lane);
	~EnemyMagicianBullet() {}
	void update(float delta_time) override;

	// =========== �֐� ==========

	// ========== ��{�X�e�[�^�X ==========

	const int ATK_ = 40;
	const int EXP_ = 20;

	const int FRAME_ = 3;

	void getImage() override {
		// ====================================
		//  �����ɃA�j���[�V�����̉摜����ׂ�
		// ====================================
		images_.emplace_back("graphics/effect/ice/ice_001.png");
		images_.emplace_back("graphics/effect/ice/ice_002.png");
		images_.emplace_back("graphics/effect/ice/ice_003.png");
		images_.emplace_back("graphics/effect/ice/ice_004.png");
		images_.emplace_back("graphics/effect/ice/ice_005.png");
		images_.emplace_back("graphics/effect/ice/ice_006.png");
		images_.emplace_back("graphics/effect/ice/ice_007.png");
		images_.emplace_back("graphics/effect/ice/ice_008.png");
		it = images_.begin();
	}
};

class EnemySnake : public EnemyBase {
public:
	EnemySnake(ScenePlay* scene, int lane);
	~EnemySnake() {}
	void update(float delta_time) override;

	// =========== �֐� ==========

	// ========== ��{�X�e�[�^�X ==========

	const float SHIFT_Z_ = 100.0f; //���[�����ړ�����Z���W

	const int ATK_ = 20;
	const int EXP_ = 200;

	void getImage() override {
		// ====================================
		//  �����ɃA�j���[�V�����̉摜����ׂ�
		// ====================================
		images_.emplace_back("graphics/chara/enemy/snake.png");
		it = images_.begin();
	}
};

class EnemySinigami : public EnemyBase {
public:
	EnemySinigami(ScenePlay* scene, int lane);
	~EnemySinigami() {}
	void update(float delta_time) override;

	// =========== �֐� ==========

	// ========== ��{�X�e�[�^�X ==========

	const float SHOT_Z_ = 160.0f; //�e�𔭎˂���Z���W
	const int TIME_SHOT_ = 12; //�e���΂��܂ł̎���
	const int TIME_STOP_ = 24; //��~����

	const float SHIFT_Z_ = 120.0f; //���[�����ړ�����Z���W

	const int ATK_ = 50;
	const int EXP_ = 500;

	void getImage() override {
		// ====================================
		//  �����ɃA�j���[�V�����̉摜����ׂ�
		// ====================================
		images_.emplace_back("graphics/chara/enemy/sinigami.png");
		it = images_.begin();
	}
};

class EnemySinigamiBullet : public EnemyBase {
public:
	EnemySinigamiBullet(ScenePlay* scene, int lane);
	~EnemySinigamiBullet() {}
	void update(float delta_time) override;

	// =========== �֐� ==========

	// ========== ��{�X�e�[�^�X ==========

	const int ATK_ = 20;
	const int EXP_ = 10;

	const int FRAME_ = 3;

	void getImage() override {
		// ====================================
		//  �����ɃA�j���[�V�����̉摜����ׂ�
		// ====================================
		images_.emplace_back("graphics/effect/badball/badball_001.png");
		images_.emplace_back("graphics/effect/badball/badball_002.png");
		images_.emplace_back("graphics/effect/badball/badball_003.png");
		images_.emplace_back("graphics/effect/badball/badball_004.png");
		images_.emplace_back("graphics/effect/badball/badball_005.png");
		images_.emplace_back("graphics/effect/badball/badball_006.png");
		images_.emplace_back("graphics/effect/badball/badball_007.png");
		images_.emplace_back("graphics/effect/badball/badball_008.png");
		images_.emplace_back("graphics/effect/badball/badball_009.png");
		images_.emplace_back("graphics/effect/badball/badball_010.png");
		it = images_.begin();
	}
};

class EnemyJellyA : public EnemyBase {
public:
	EnemyJellyA(ScenePlay* scene, int lane);
	~EnemyJellyA() {}
	void update(float delta_time) override;

	// =========== �֐� ==========

	// ========== ��{�X�e�[�^�X ==========

	const int ATK_ = 40;
	const int EXP_ = 300;

	void getImage() override {
		// ====================================
		//  �����ɃA�j���[�V�����̉摜����ׂ�
		// ====================================
		images_.emplace_back("graphics/chara/enemy/jelly_a.png");
		it = images_.begin();
	}
};

class EnemyJellyB : public EnemyBase {
public:
	EnemyJellyB(ScenePlay* scene, int lane);
	~EnemyJellyB() {}
	void update(float delta_time) override;

	// =========== �֐� ==========

	// ========== ��{�X�e�[�^�X ==========

	const float SHOT_Z_ = 120.0f; //�e�𔭎˂���Z���W
	const int TIME_SHOT_ = 24; //�e���΂��܂ł̎���
	const int TIME_STOP_ = 48; //��~����

	const int ATK_ = 10;
	const int EXP_ = 400;

	void getImage() override {
		// ====================================
		//  �����ɃA�j���[�V�����̉摜����ׂ�
		// ====================================
		images_.emplace_back("graphics/chara/enemy/jelly_b.png");
		it = images_.begin();
	}
};

class EnemyJellyBullet : public EnemyBase {
public:
	EnemyJellyBullet(ScenePlay* scene, int lane);
	~EnemyJellyBullet() {}
	void update(float delta_time) override;

	// =========== �֐� ==========

	// ========== ��{�X�e�[�^�X ==========

	const int ATK_ = 60;
	const int EXP_ = 25;

	void getImage() override {
		// ====================================
		//  �����ɃA�j���[�V�����̉摜����ׂ�
		// ====================================
		images_.emplace_back("graphics/effect/thunder.png");
		it = images_.begin();
	}
};

class EnemyJellyC : public EnemyBase {
public:
	EnemyJellyC(ScenePlay* scene, int lane);
	~EnemyJellyC() {}
	void update(float delta_time) override;

	// =========== �֐� ==========

	// ========== ��{�X�e�[�^�X ==========

	const float SHIFT_Z_ = 120.0f; //���[�����ړ�����Z���W

	const int ATK_ = 40;
	const int EXP_ = 400;

	void getImage() override {
		// ====================================
		//  �����ɃA�j���[�V�����̉摜����ׂ�
		// ====================================
		images_.emplace_back("graphics/chara/enemy/jelly_c.png");
		it = images_.begin();
	}
};

class EnemyKingPig : public EnemyBase {
public:
	EnemyKingPig(ScenePlay* scene, int lane);
	~EnemyKingPig() {}
	void update(float delta_time) override;

	// =========== �֐� ==========

	// ========== ��{�X�e�[�^�X ==========

	const int ATK_ = 60;
	const int EXP_ = 600;

	void getImage() override {
		// ====================================
		//  �����ɃA�j���[�V�����̉摜����ׂ�
		// ====================================
		images_.emplace_back("graphics/chara/enemy/pig_king.png");
		it = images_.begin();
	}
};

class EnemyKingRizard : public EnemyBase {
public:
	EnemyKingRizard(ScenePlay* scene, int lane);
	~EnemyKingRizard() {}
	void update(float delta_time) override;

	// =========== �֐� ==========

	// ========== ��{�X�e�[�^�X ==========

	const float SHOT_Z_ = 120.0f; //�e�𔭎˂���Z���W
	const int TIME_SHOT1_ = 24; //�e���΂��܂ł̎���
	const int TIME_SHOT2_ = 48; //�e���΂��܂ł̎���
	const int TIME_STOP_ = 72; //��~����

	const int ATK_ = 40;
	const int EXP_ = 600;

	void getImage() override {
		// ====================================
		//  �����ɃA�j���[�V�����̉摜����ׂ�
		// ====================================
		images_.emplace_back("graphics/chara/enemy/rizard_king.png");
		it = images_.begin();
	}
};

class EnemyKingRizardBullet : public EnemyBase {
public:
	EnemyKingRizardBullet(ScenePlay* scene, int lane);
	~EnemyKingRizardBullet() {}
	void update(float delta_time) override;

	// =========== �֐� ==========

	// ========== ��{�X�e�[�^�X ==========

	const int ATK_ = 70;
	const int EXP_ = 30;

	void getImage() override {
		// ====================================
		//  �����ɃA�j���[�V�����̉摜����ׂ�
		// ====================================
		images_.emplace_back("graphics/effect/fireball.png");
		it = images_.begin();
	}
};

class EnemyKingMash : public EnemyBase {
public:
	EnemyKingMash(ScenePlay* scene, int lane);
	~EnemyKingMash() {}
	void update(float delta_time) override;

	// =========== �֐� ==========

	// ========== ��{�X�e�[�^�X ==========

	const float SHIFT_Z1_ = 260.0f; //���[�����ړ�����Z���W
	const float SHIFT_Z2_ = 100.0f; //���[�����ړ�����Z���W
	bool isShift2_ = false; //2��ڂ̃V�t�g�����邽�߂̃t���O

	const int ATK_ = 60;
	const int EXP_ = 600;

	void getImage() override {
		// ====================================
		//  �����ɃA�j���[�V�����̉摜����ׂ�
		// ====================================
		images_.emplace_back("graphics/chara/enemy/mash_king.png");
		it = images_.begin();
	}
};

class EnemyKingGrifin : public EnemyBase {
public:
	EnemyKingGrifin(ScenePlay* scene, int lane);
	~EnemyKingGrifin() {}
	void update(float delta_time) override;

	// =========== �֐� ==========

	// ========== ��{�X�e�[�^�X ==========

	const float SHOT_Z1_ = 0.0f; //�e�𔭎˂���Z���W1
	const float SHOT_Z2_ = 200.0f; //�e�𔭎˂���Z���W2
	const int TIME_SHOT1_ = 12; //�e���΂��܂ł̎���
	const int TIME_SHOT2_ = 36; //�e���΂��܂ł̎���
	const int TIME_STOP_ = 60; //��~����

	const float SHIFT_Z_ = 160.0f; //���[�����ړ�����Z���W

	const int ATK_ = 80;
	const int EXP_ = 1000;

	void getImage() override {
		// ====================================
		//  �����ɃA�j���[�V�����̉摜����ׂ�
		// ====================================
		images_.emplace_back("graphics/chara/enemy/grifin_king.png");
		it = images_.begin();
	}
};

class EnemyKingGrifinBullet : public EnemyBase {
public:
	EnemyKingGrifinBullet(ScenePlay* scene, int lane);
	~EnemyKingGrifinBullet() {}
	void update(float delta_time) override;

	// =========== �֐� ==========

	// ========== ��{�X�e�[�^�X ==========

	const int ATK_ = 70;
	const int EXP_ = 50;

	const int FRAME_ = 3;

	void getImage() override {
		// ====================================
		//  �����ɃA�j���[�V�����̉摜����ׂ�
		// ====================================
		images_.emplace_back("graphics/effect/wind/wind_001.png");
		images_.emplace_back("graphics/effect/wind/wind_002.png");
		images_.emplace_back("graphics/effect/wind/wind_003.png");
		images_.emplace_back("graphics/effect/wind/wind_004.png");
		images_.emplace_back("graphics/effect/wind/wind_005.png");
		images_.emplace_back("graphics/effect/wind/wind_006.png");
		images_.emplace_back("graphics/effect/wind/wind_007.png");
		images_.emplace_back("graphics/effect/wind/wind_008.png");
		images_.emplace_back("graphics/effect/wind/wind_009.png");
		images_.emplace_back("graphics/effect/wind/wind_010.png");
		images_.emplace_back("graphics/effect/wind/wind_011.png");
		images_.emplace_back("graphics/effect/wind/wind_012.png");
		images_.emplace_back("graphics/effect/wind/wind_013.png");
		images_.emplace_back("graphics/effect/wind/wind_014.png");
		images_.emplace_back("graphics/effect/wind/wind_015.png");
		it = images_.begin();
	}
};