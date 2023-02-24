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

	//���W
	const float MESSAGE_WIN_X_ = DXE_WINDOW_WIDTH / 2;
	const float MESSAGE_WIN_Y_ = DXE_WINDOW_HEIGHT * 0.85f;
	const float MESSAGE_X_ = DXE_WINDOW_WIDTH * 0.1f;
	const float MESSAGE_Y_ = MESSAGE_WIN_Y_ - 16;



};