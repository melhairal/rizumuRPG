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