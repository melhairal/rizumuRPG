#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
class SceneField;
class AnimSprite3D;

class SpriteBase {
public:
	SpriteBase() {}
	virtual ~SpriteBase() {
		delete sprite_;
	}
	virtual void update(float delta_time) {}
	virtual void render() {}

	// =========== �֐� ==========

	void hitPlayer(tnl::Vector3 size); //�v���C���[�Ƃ̏Փ˔���

	// =========== ��{�X�e�[�^�X ==========

	SceneField* scene_ = nullptr; //�V�[�������擾

	AnimSprite3D* sprite_ = nullptr; //�X�v���C�g���
	tnl::Vector3 pos_ = { 0,0,0 }; //���W
	tnl::Vector3 prev_pos_ = { 0,0,0 }; //���W

	bool move_ = true; //����t���O
	bool alive_ = true; //�����t���O
};

class SpritePlayer : public SpriteBase {
public:
	SpritePlayer(SceneField* scene);
	~SpritePlayer() {}
	void update(float delta_time);
	void render();

	// =========== �֐� ==========


	// =========== ��{�X�e�[�^�X ==========

	float speed_ = 2.0f; //�ړ����x
};

class SpriteTree : public SpriteBase {
public:
	SpriteTree(SceneField* scene, tnl::Vector3 pos);
	~SpriteTree() {}
	void update(float delta_time);
	void render();

	// =========== �֐� ==========

	// =========== ��{�X�e�[�^�X ==========

	tnl::Vector3 size_ = { 50,50,50 }; //�����蔻��p�T�C�Y

};

class SpriteNpc : public SpriteBase {
public:
	SpriteNpc() {}
	virtual ~SpriteNpc() {}
	virtual void update(float delta_time) {}
	virtual void render() {}

	// =========== �֐� ==========

	void getSurface(tnl::Vector3 size); //�J�����ɑ΂���ʂ��擾
	void randomWalk(int range, int speed); //�����_���ŕ���

	// =========== ��{�X�e�[�^�X ==========

	tnl::Vector3 dir_[4] = {
		{0,0,1}, //��
		{1,0,0}, //�E
		{0,0,-1}, //��
		{-1,0,0} //��
	};

	bool isWalk_ = false; //�ړ����t���O
	float next_x_ = 0; //�ړ����X���W
	float next_z_ = 0; //�ړ����Z���W

	bool isWait_ = false; //�ҋ@���t���O
	int elapsed_ = 0; //���Ԍv��
	int wait_time_ = 0; //�ҋ@����
};

class SpriteMurabito : public SpriteNpc {
public:
	SpriteMurabito(SceneField* scene, tnl::Vector3 pos);
	~SpriteMurabito() {}
	void update(float delta_time);
	void render();

	// =========== �֐� ==========

	// =========== ��{�X�e�[�^�X ==========

	tnl::Vector3 size_ = { 32,32,32 }; //�����蔻��p�T�C�Y
	int range_ = 120; //�ړ��͈�
	int speed_ = 2; //�ړ����x
};

class SpriteMurabitoF : public SpriteNpc {
public:
	SpriteMurabitoF(SceneField* scene, tnl::Vector3 pos);
	~SpriteMurabitoF() {}
	void update(float delta_time);
	void render();

	// =========== �֐� ==========

	// =========== ��{�X�e�[�^�X ==========

	tnl::Vector3 size_ = { 32,32,32 }; //�����蔻��p�T�C�Y
	int range_ = 100; //�ړ��͈�
	int speed_ = 2; //�ړ����x
};

class SpriteHeisi : public SpriteNpc {
public:
	SpriteHeisi(SceneField* scene, tnl::Vector3 pos, int look);
	~SpriteHeisi() {}
	void update(float delta_time);
	void render();

	// =========== �֐� ==========

	// =========== ��{�X�e�[�^�X ==========

	tnl::Vector3 size_ = { 32,32,32 }; //�����蔻��p�T�C�Y
};

class SpriteKazi : public SpriteNpc {
public:
	SpriteKazi(SceneField* scene, tnl::Vector3 pos, int look);
	~SpriteKazi() {}
	void update(float delta_time);
	void render();

	// =========== �֐� ==========

	// =========== ��{�X�e�[�^�X ==========

	tnl::Vector3 size_ = { 32,32,32 }; //�����蔻��p�T�C�Y
};