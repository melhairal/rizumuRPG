#pragma once
#include "../dxlib_ext/dxlib_ext.h"
class SceneField;
class SpriteBase;

class FieldUi {
public:
	FieldUi(SceneField* scene);
	~FieldUi() {}
	void update(float delta_time);
	void render();

	// =========== �֐� ==========

	void getFont(); //�t�H���g�ǂݍ���
	void getWindow(); //�E�B���h�E�摜�ǂݍ���
	void drawWindow(int x, int y, int width, int height); //�σE�B���h�E�`��

	void updateComment(); //�R�����g����
	void updateMenu(); //���j���[����
	void updateShop(); //�V���b�v����

	// ========== ��{�X�e�[�^�X ==========

	SceneField* scene_ = nullptr; //�V�[���̕ϐ����擾���邽�߂̃|�C���^
	SpriteBase* sprite_ = nullptr; //�Z���t���Ăяo�����X�v���C�g�����i�[
	SpriteBase* sprite_shop_ = nullptr; //�V���b�v���Ăяo�����X�v���C�g�����i�[

	int menu_depth_ = 1; //���j���[�̂ǂ̒i�K�ɂ��邩
	int sel_label_ = 0; //�I�𒆂̃��x��
	const int LABEL_INDEX_MAX_ = 5; //���x���̃C���f�b�N�X�ő吔
	const char* label_[5] = {
		"�X�L��",
		"�ǂ���",
		"�I�v�V����",
		"�Z�[�u",
		"�����"
	};
	int label_color_[5] = { BROWN,BROWN,BROWN,BROWN,BROWN };
	int sel_index_ = 0; //�I�𒆂̃C���f�b�N�X
	int sel_list_ = 0; //���X�g�̃X�N���[��
	const int INDEX_MAX_ = 5; //�C���f�b�N�X�̍ő吔
	int index_color_[5] = { BROWN,BROWN,BROWN,BROWN,BROWN };

	int item_num_ = 0; //�A�C�e��������

	int shop_depth_ = 0; //�V���b�v���j���[�̂ǂ̒i�K�ɂ��邩
	int shop_sel_label_ = 0; //�I�𒆂̃��x��
	const int SHOP_LABEL_INDEX_MAX_ = 2; //���x���̃C���f�b�N�X�ő吔
	const char* shop_label_[2] = {
		"����",
		"����"
	};
	int shop_label_color_[2] = { BROWN,BROWN };
	int shop_sel_index_ = 0; //�I�𒆂̃C���f�b�N�X
	const int SHOP_INDEX_MAX_ = 8; //�C���f�b�N�X�̍ő吔
	int shop_index_color_[8] = { BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN };

	//�F RGB(B,G,R)
	const int RED = RGB(0, 0, 255);
	const int GREEN = RGB(0, 255, 0);
	const int BLUE = RGB(255, 0, 0);
	const int BROWN = RGB(48, 78, 115);
	const int YELLOW = RGB(0, 225, 255);

	//�t�H���g
	int font_rondo_16_ = 0;
	int font_rondo_24_ = 0;
	int font_rondo_32_ = 0;
	int font_rondo_64_ = 0;
	int font_rondo_128_ = 0;
	int font_pop_32_ = 0;

	int img_message_ = 0;

	//�E�B���h�E�摜
	int window_top_left_ = 0;
	int window_top_center_ = 0;
	int window_top_right_ = 0;
	int window_left_ = 0;
	int window_center_ = 0;
	int window_right_ = 0;
	int window_bot_left_ = 0;
	int window_bot_center_ = 0;
	int window_bot_right_ = 0;

	//���W
	const float MESSAGE_WIN_X_ = DXE_WINDOW_WIDTH / 2;
	const float MESSAGE_WIN_Y_ = DXE_WINDOW_HEIGHT * 0.85f;
	const float MESSAGE_X_ = DXE_WINDOW_WIDTH * 0.1f;
	const float MESSAGE_Y_ = MESSAGE_WIN_Y_ - 16;

	const float WINDOW_LABEL_X_ = DXE_WINDOW_WIDTH * 0.2f;
	const float WINDOW_LABEL_Y_ = DXE_WINDOW_HEIGHT / 2;
	const float WINDOW_LABEL_W_ = DXE_WINDOW_WIDTH * 0.2f;
	const float WINDOW_LABEL_H_ = DXE_WINDOW_HEIGHT * 0.6f;

	const float WINDOW_MAIN_X_ = DXE_WINDOW_WIDTH * 0.6f;
	const float WINDOW_MAIN_Y_ = DXE_WINDOW_HEIGHT / 2;
	const float WINDOW_MAIN_W_ = DXE_WINDOW_WIDTH * 0.6f;
	const float WINDOW_MAIN_H_ = DXE_WINDOW_HEIGHT * 0.6f;

	const float WINDOW_SUB_X_ = WINDOW_MAIN_X_;
	const float WINDOW_SUB_Y_ = DXE_WINDOW_HEIGHT * 0.7f;
	const float WINDOW_SUB_W_ = WINDOW_MAIN_W_;
	const float WINDOW_SUB_H_ = DXE_WINDOW_HEIGHT * 0.2f;

	const float LABEL_X_ = DXE_WINDOW_WIDTH * 0.13f;
	const float LABEL_Y_[5] = {
		 DXE_WINDOW_HEIGHT * 0.25f,
		 DXE_WINDOW_HEIGHT * 0.25f + 50,
		 DXE_WINDOW_HEIGHT * 0.25f + 100,
		 DXE_WINDOW_HEIGHT * 0.25f + 150,
		 DXE_WINDOW_HEIGHT * 0.25f + 200
	};

	const float STATUS_X_[2] = { 350,550 };
	const float STATUS_Y_[6] = { 200,250,300,350,400,450 };

	const float COMMENT_X_ = 350;
	const float COMMENT_Y_[3] = { 480,520,560 };
	const float NUM_X_ = 760;

};