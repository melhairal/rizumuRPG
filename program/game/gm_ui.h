#pragma once
#include "../dxlib_ext/dxlib_ext.h"
class ScenePlay;

class Ui {
public:
	Ui(ScenePlay* scene);
	~Ui() {}
	void update(float delta_time);
	void render();

	// =========== �֐� ==========

	//�σQ�[�W��`�� x:x���W y:y���W width:�摜�T�C�Y(����) height:�摜�T�C�Y(�c��) exrate:�g�嗦 num:�Q�[�W�̒l max:�Q�[�W�̍ő�l color:�F(enum)
	void DrawGauge(int x, int y, int width, int height, double exrate, int num, int max, int color); 
	void DrawGaugeProgress(int x, int y, int width, int height, double exrate, int num, int max, int color);

	// ========== ��{�X�e�[�^�X ==========

	enum {
		eBlue,
		eYellow,
		eRed
	};

	ScenePlay* scene_ = nullptr; //�V�[���̕ϐ����擾���邽�߂̃|�C���^

	//�F RGB(B,G,R)
	const int RED = RGB(0, 0, 255);
	const int GREEN = RGB(0, 255, 0);
	const int BLUE = RGB(255, 0, 0);
	const int BROWN = RGB(48, 78, 115);
	const int YELLOW = RGB(0, 225, 255);

	//�t�H���g
	int font_rondo_16_ = 0;
	int font_rondo_32_ = 0;
	int font_rondo_64_ = 0;
	int font_rondo_128_ = 0;

	//HP�Q�[�W
	int hp_bar_[3] = { 0,0,0 };
	int hp_back_ = 0;
	int hp_frame_ = 0;

	// ========== ���W ==========

	//�Q�[�W�摜�T�C�Y
	const int GAUGE_IMG_W_ = 156;
	const int GAUGE_IMG_H_ = 8;

	//�i�s�x/�{�XHP
	const int HOME_HP_X_ = DXE_WINDOW_WIDTH / 2;
	const int HOME_HP_Y_ = DXE_WINDOW_HEIGHT * 0.05f;
	int run_ = 0; //����A�C�R��
	const int RUN_X_ = HOME_HP_X_;

	//�v���C���[HP/MP
	const int PLAYER_GAUGE_X_ = DXE_WINDOW_WIDTH / 2;
	const int PLAYER_GAUGE_Y1_ = DXE_WINDOW_HEIGHT * 0.95f;
	const int PLAYER_GAUGE_Y2_ = PLAYER_GAUGE_Y1_ + 20;

	const int PLAYER_ICON_X_ = PLAYER_GAUGE_X_ - 140;

	//�R���{
	const int COMBO_X_ = DXE_WINDOW_WIDTH * 0.9f;
	const int COMBO_Y_ = DXE_WINDOW_HEIGHT * 0.2f;
	const int COMBO_NUM_X_ = COMBO_X_ - 100;
	const int COMBO_NUM_Y_ = COMBO_Y_ - 20;

	//����
	const float JUDGE_X_[4] = { DXE_WINDOW_WIDTH * 0.2f,DXE_WINDOW_WIDTH * 0.4f,DXE_WINDOW_WIDTH * 0.6f,DXE_WINDOW_WIDTH * 0.8f }; //4�̃��[���̍��W
	const float JUDGE_Y_ = DXE_WINDOW_HEIGHT * 0.75f; 
};

class SubUiJudge {
public:
	SubUiJudge(ScenePlay* scene, int judge, int lane);
	~SubUiJudge(){}
	void update(float delta_time);
	void render();

	// =========== �֐� ==========

	// ========== ��{�X�e�[�^�X ==========

	ScenePlay* scene_ = nullptr; //�V�[���̕ϐ����擾���邽�߂̃|�C���^
	bool alive_ = true; //�����t���O
	bool move_ = true; //����t���O

	enum {
		perfect,
		good,
		miss
	};

	int judge_ = 0;
	int lane_ = 0;
	int elapsed_ = 0;
	const int RENDER_TIME_ = 30; //�\������

	//���W
	const float JUDGE_X_[4] = { DXE_WINDOW_WIDTH * 0.2f - 20,DXE_WINDOW_WIDTH * 0.4f - 20,DXE_WINDOW_WIDTH * 0.6f - 20,DXE_WINDOW_WIDTH * 0.8f - 20 }; //4�̃��[���̍��W
	float judge_y_ = DXE_WINDOW_HEIGHT * 0.75f;

};