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

	// ========== ��{�X�e�[�^�X ==========

	SceneField* scene_ = nullptr; //�V�[���̕ϐ����擾���邽�߂̃|�C���^
	SpriteBase* sprite_ = nullptr; //�Z���t���Ăяo�����X�v���C�g�����i�[

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


};