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
	virtual void attackMeleeA(){} //�ߐڍU��1
	virtual void attackMeleeB(){} //�ߐڍU��2
	virtual void attackRangeA(){} //�S�̍U��1
	virtual void attackRangeB(){} //�S�̍U��2
	virtual void attackBulletA(){} //���u�U��1
	virtual void attackBulletB(){} //���u�U��2

	// ========== ��{�X�e�[�^�X ==========

	const float POS_Z_ = 300.0f; //Z���W
	const float MELEE_POS_Z_ = 50.0f; //�ڋ�Z���W
	const float BULLET_POS_Z_ = 150.0f; //���uZ���W

};

class BossDragon : public BossEnemy {
public:
	BossDragon(ScenePlay* scene);
	~BossDragon() {}
	void update(float delta_time);

	// =========== �֐� ==========


	// ========== ��{�X�e�[�^�X ==========





	void getImage() override {
		// ====================================
		//  �����ɃA�j���[�V�����̉摜����ׂ�
		// ====================================
		images_.emplace_back("graphics/chara/enemy/dragon.png");
		it = images_.begin();
	}
};

class BossNotes : public Actor {
public:
	BossNotes() {}
	virtual ~BossNotes() {}
	virtual void update(float delta_time) {}

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
};

class NotesWarning : public BossNotes {
public:
	NotesWarning(ScenePlay* scene, int lane);
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