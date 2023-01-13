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

	void Initialize(ScenePlay* scene, int lane); //���b�V���̏�����

	void flow(float speed); //����Ă���
	void shot(Actor* bullet); //�e���΂��Ă���
	void shift(); //���[����ς���

	bool checkLane(); //���[���̊m�F
	void notesEnemy(); //�G����
	void notesBullet(); //�U������

	// ========== ��{�X�e�[�^�X ==========

	bool onPlayerLane = false; //�v���C���[�Ɠ������[�����ǂ���

	const float POS_Z_ = 300.0f; //����Z���W
	const float DEAD_Z_ = -200.0f; //����Z���W
	const float SPEED_ = 5.0f; //�����X�s�[�h(��)
};

class EnemyPig : public EnemyBase {
public:
	EnemyPig(ScenePlay* scene, int lane);
	~EnemyPig() {}
	void update(float delta_time) override;

	// =========== �֐� ==========

	// ========== ��{�X�e�[�^�X ==========


	void getImage() override {
		// ====================================
		//  �����ɃA�j���[�V�����̉摜����ׂ�
		// ====================================
		images_.emplace_back("graphics/chara/enemy/pig_a.png");
		it = images_.begin();
	}
};