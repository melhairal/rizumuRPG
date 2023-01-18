#pragma once
#include "../dxlib_ext/dxlib_ext.h"
class ScenePlay;
class ObjectBase;

class MakeSheet {
public:
	MakeSheet(ScenePlay* scene);
	~MakeSheet();
	void update(float delta_time);
	void render();
	// =========== �֐� ==========

	// ========== ��{�X�e�[�^�X ==========

	ScenePlay* scene_ = nullptr; //�V�[���ۑ��p

	std::list<ObjectBase*> lines_; //���C�����X�g
	int line_num_ = 0; //���C���̖{��
	const int LINE_NUM_MAX_ = 10; //���C���̍ő吔

	int bgm_ = 0; //BGM
	int elapsed_ = 0; //���Ԍv���p
	const int NODE_INTERVAL_ = 12; //�m�[�h�����Ԋu
	int key_ = 0; //�L�[����

	int bgm_timer_ = 0; //BGM���O�v���p
	const int START_INTERVAL_ = 99; //�ŏ��̃��C�������胉�C���ɓ��B����܂ł̃��O
	bool save_ = false; //�L�^�J�n�t���O
};
