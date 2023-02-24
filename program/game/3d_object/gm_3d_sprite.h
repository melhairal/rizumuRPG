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
	virtual void getComment() {} //�Z���t�Z�b�g

	// =========== �֐� ==========

	void getSurface(tnl::Vector3 size); //�J�����ɑ΂���ʂ��擾
	virtual void eventAction() {} //�C�x���g
	void hitPlayer(tnl::Vector3 size); //�v���C���[�Ƃ̏Փ˔���

	// =========== ��{�X�e�[�^�X ==========

	SceneField* scene_ = nullptr; //�V�[�������擾

	AnimSprite3D* sprite_ = nullptr; //�X�v���C�g���
	tnl::Vector3 pos_ = { 0,0,0 }; //���W
	tnl::Vector3 prev_pos_ = { 0,0,0 }; //���W
	tnl::Vector3 look_ = { 0,0,0 }; //���Ă�������x�N�g��

	std::list<const char*> comment_; //�Z���t���X�g
	std::list<const char*>::iterator it; //�Z���t���X�g�p�C�e���[�^

	bool isComment_ = false; //�Z���t���t���O
	bool isEvent_ = false; //�C�x���g���t���O
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

	void movePlayer(); //�ړ�����
	void getEvent(); //�C�x���g����(�G���^�[�L�[�ŃC�x���g���N����)

	// =========== ��{�X�e�[�^�X ==========

	float speed_ = 2.0f; //�ړ����x

	tnl::Vector3 size_ = { 32,32,32 }; //�����蔻��p�T�C�Y

	
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
	virtual void getComment() {} //�Z���t�Z�b�g

	// =========== �֐� ==========

	virtual void eventAction() {} //�C�x���g
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
	
	void eventAction(); //�C�x���g

	// =========== ��{�X�e�[�^�X ==========

	tnl::Vector3 size_ = { 32,32,32 }; //�����蔻��p�T�C�Y
	int range_ = 120; //�ړ��͈�
	int speed_ = 2; //�ړ����x

	void getComment() override {
		// ====================================
		//  �����ɃZ���t����ׂ�
		// ====================================
		comment_.emplace_back("...");
		comment_.emplace_back("�����͎n�܂�̑�");
		comment_.emplace_back("�G�݉��⑕�����������");
		it = comment_.begin();
	}
};

class SpriteMurabitoF : public SpriteNpc {
public:
	SpriteMurabitoF(SceneField* scene, tnl::Vector3 pos);
	~SpriteMurabitoF() {}
	void update(float delta_time);
	void render();

	// =========== �֐� ==========

	void eventAction(); //�C�x���g

	// =========== ��{�X�e�[�^�X ==========

	tnl::Vector3 size_ = { 32,32,32 }; //�����蔻��p�T�C�Y
	int range_ = 100; //�ړ��͈�
	int speed_ = 2; //�ړ����x

	void getComment() override {
		// ====================================
		//  �����ɃZ���t����ׂ�
		// ====================================
		comment_.emplace_back("...");
		comment_.emplace_back("�m���Ă�H");
		comment_.emplace_back("�����X�^�[�̍U�����^�C�~���O�ǂ�������ƁA");
		comment_.emplace_back("�X�R�A�ƃR���{���{�[�i�X�ŉ��Z�����񂾂��āI");
		it = comment_.begin();
	}
};

class SpriteHeisi : public SpriteNpc {
public:
	SpriteHeisi(SceneField* scene, tnl::Vector3 pos, int look);
	~SpriteHeisi() {}
	void update(float delta_time);
	void render();

	// =========== �֐� ==========

	void eventAction(); //�C�x���g

	// =========== ��{�X�e�[�^�X ==========

	tnl::Vector3 size_ = { 32,32,32 }; //�����蔻��p�T�C�Y
	int look_ = 0; //�����Ă����

	void getComment() override {
		// ====================================
		//  �����ɃZ���t����ׂ�
		// ====================================
		comment_.emplace_back("...");
		comment_.emplace_back("�O�ɏo��ƃ����X�^�[�����邼");
		comment_.emplace_back("�������菀�����Ă���s����");
		it = comment_.begin();
	}
};

class SpriteKazi : public SpriteNpc {
public:
	SpriteKazi(SceneField* scene, tnl::Vector3 pos, int look);
	~SpriteKazi() {}
	void update(float delta_time);
	void render();

	// =========== �֐� ==========

	void eventAction(); //�C�x���g

	// =========== ��{�X�e�[�^�X ==========

	tnl::Vector3 size_ = { 32,32,32 }; //�����蔻��p�T�C�Y
	int look_ = 0; //�����Ă����

	void getComment() override {
		// ====================================
		//  �����ɃZ���t����ׂ�
		// ====================================
		comment_.emplace_back("...");
		comment_.emplace_back("�����͑�������");
		comment_.emplace_back("�����h��𒅂���Ƌ����Ȃ邼");
		it = comment_.begin();
	}
};

class SpriteShop : public SpriteNpc {
public:
	SpriteShop(SceneField* scene, tnl::Vector3 pos, int look);
	~SpriteShop() {}
	void update(float delta_time);
	void render();

	// =========== �֐� ==========

	void eventAction(); //�C�x���g

	// =========== ��{�X�e�[�^�X ==========

	tnl::Vector3 size_ = { 32,32,32 }; //�����蔻��p�T�C�Y
	int look_ = 0; //�����Ă����

	void getComment() override {
		// ====================================
		//  �����ɃZ���t����ׂ�
		// ====================================
		comment_.emplace_back("...");
		comment_.emplace_back("�����͎G�݉���");
		comment_.emplace_back("���̂����ɉ񕜃A�C�e���͂������H");
		it = comment_.begin();
	}
};