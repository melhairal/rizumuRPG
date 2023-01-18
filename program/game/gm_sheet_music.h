#pragma once
#include "../dxlib_ext/dxlib_ext.h"
class ScenePlay;
class ObjectBase;

class Sheet {
public:
	Sheet(ScenePlay* scene, std::string csv);
	~Sheet(){}
	void update(float delta_time);

	// =========== �֐� ==========

	void createNotes(int id, int lane); //�m�[�h�쐬

	// ========== ��{�X�e�[�^�X ==========

	enum {
		plains,
		cave,
		sea,
		forest
	};

	ScenePlay* scene_ = nullptr; //�V�[���̕ϐ����擾���邽�߂̃|�C���^
	ObjectBase* line_ = nullptr; //���C���̃|�C���^
	std::vector<std::vector<std::string>> csv_; //����csv
	int bgm_ = 0; //bgm
	int type_ = plains; //�X�e�[�W�^�C�v

	int elapsed_ = 0; //���Ԍv���p
	const int NODE_INTERVAL_ = 12; //�m�[�h�����Ԋu

	int bgm_timer_ = 0; //BGM���O�v���p
	const int START_INTERVAL_ = 99; //�ŏ��̃��C�������胉�C���ɓ��B����܂ł̃��O

	int csv_y_ = 2; //csv�̉��s�ڂ�

	bool alive_ = true; //�����t���O
};