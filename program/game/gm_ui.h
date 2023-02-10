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

	//�E�B���h�E�摜�ǂݍ���
	void getWindow();

	//�σQ�[�W��`�� x:x���W y:y���W width:�摜�T�C�Y(����) height:�摜�T�C�Y(�c��) exrate:�g�嗦 num:�Q�[�W�̒l max:�Q�[�W�̍ő�l color:�F(enum)
	void DrawGauge(int x, int y, int width, int height, double exrate, int num, int max, int color);
	void DrawGaugeProgress(int x, int y, int width, int height, double exrate, int num, int max, int color);

	//�σE�B���h�E�`��
	void DrawWindow(int x, int y, int width, int height, int color);

	// ========== ��{�X�e�[�^�X ==========

	enum {
		eBlue,
		eYellow,
		eRed
	};

	enum {
		eWhite,
		eBrown,
		eGlay,
		eBlack
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
	int font_rondo_24_ = 0;
	int font_rondo_32_ = 0;
	int font_rondo_64_ = 0;
	int font_rondo_128_ = 0;

	//HP�Q�[�W
	int hp_bar_[3] = { 0,0,0 };
	int hp_back_ = 0;
	int hp_frame_ = 0;

	//�E�B���h�E
	int window_top_left_[4] = { 0,0,0,0 };
	int window_top_center_[4] = { 0,0,0,0 };
	int window_top_right_[4] = { 0,0,0,0 };
	int window_left_[4] = { 0,0,0,0 };
	int window_center_[4] = { 0,0,0,0 };
	int window_right_[4] = { 0,0,0,0 };
	int window_bot_left_[4] = { 0,0,0,0 };
	int window_bot_center_[4] = { 0,0,0,0 };
	int window_bot_right_[4] = { 0,0,0,0 };

	//�J�[�\��
	int cursol_ = 0;

	//�U���\���E�B���h�E
	int window_attack_player_ = 0;
	int window_attack_boss_ = 0;

	// ========== ���W ==========

	//�Q�[�W�摜�T�C�Y
	const int GAUGE_IMG_W_ = 156;
	const int GAUGE_IMG_H_ = 8;

	//�i�s�x/�{�XHP
	const int HOME_HP_X_ = DXE_WINDOW_WIDTH / 2;
	const int HOME_HP_Y_ = DXE_WINDOW_HEIGHT * 0.05f;
	int run_ = 0; //����A�C�R��
	const int RUN_X_ = HOME_HP_X_;

	//�R���{
	const int COMBO_X_ = DXE_WINDOW_WIDTH * 0.9f;
	const int COMBO_Y_ = DXE_WINDOW_HEIGHT * 0.2f;
	const int COMBO_NUM_X_ = COMBO_X_ - 100;
	const int COMBO_NUM_Y_ = COMBO_Y_ - 20;

	//�X�R�A
	const int SCORE_X_ = DXE_WINDOW_WIDTH * 0.8f;
	const int SCORE_Y_ = DXE_WINDOW_HEIGHT * 0.05f;
	const int SCORE_NUM_X_ = SCORE_X_ + 80;
	const int SCORE_NUM_Y_ = SCORE_Y_;
	const int SCORE_WINDOW_X_ = SCORE_X_ + 90;
	const int SCORE_WINDOW_Y_ = SCORE_Y_ + 16;
	const int SCORE_WINDOW_W_ = 220;
	const int SCORE_WINDOW_H_ = 50;


	//����
	const float JUDGE_X_[4] = { DXE_WINDOW_WIDTH * 0.2f,DXE_WINDOW_WIDTH * 0.4f,DXE_WINDOW_WIDTH * 0.6f,DXE_WINDOW_WIDTH * 0.8f }; //4�̃��[���̍��W
	const float JUDGE_Y_ = DXE_WINDOW_HEIGHT * 0.75f;

	//�E�B���h�E
	const int COMMAND_Y_ = DXE_WINDOW_HEIGHT * 0.85f;
	const int COMMAND_H_ = DXE_WINDOW_HEIGHT * 0.2f;
	const int COMMAND_X1_ = DXE_WINDOW_WIDTH * 0.1f;
	const int COMMAND_W1_ = DXE_WINDOW_WIDTH * 0.2f;
	const int COMMAND_X2_ = DXE_WINDOW_WIDTH * 0.35f;
	const int COMMAND_W2_ = DXE_WINDOW_WIDTH * 0.3f;
	const int COMMAND_X3_ = DXE_WINDOW_WIDTH * 0.75f;
	const int COMMAND_W3_ = DXE_WINDOW_WIDTH * 0.5f;
	const int STATUS_X_ = DXE_WINDOW_WIDTH * 0.5f;
	const int STATUS_W_ = DXE_WINDOW_WIDTH;
	const int STATUS_Y_ = DXE_WINDOW_HEIGHT * 0.975f;
	const int STATUS_H_ = DXE_WINDOW_HEIGHT * 0.05f;
	const int STATUS_GAUGE_X1_ = DXE_WINDOW_WIDTH * 0.36f;
	const int STATUS_GAUGE_X2_ = DXE_WINDOW_WIDTH * 0.86f;
	const int STATUS_NUM_Y_ = STATUS_Y_ - 16;
	const int STATUS_NUM_X1_ = STATUS_GAUGE_X1_ - 350;
	const int STATUS_NUM_X2_ = STATUS_GAUGE_X2_ - 350;

	//�R�}���h���W
	const int COMMAND_MAIN_X_ = DXE_WINDOW_WIDTH * 0.03f;
	const int COMMAND_SUB_X_ = DXE_WINDOW_WIDTH * 0.23f;
	float COMMAND_LIST_Y_[4] = { DXE_WINDOW_HEIGHT * 0.76f, DXE_WINDOW_HEIGHT * 0.76f + 35, DXE_WINDOW_HEIGHT * 0.76f + 70, DXE_WINDOW_HEIGHT * 0.76f + 105};
	int command_color_[4] = { 0,0,0,0 };
	int command_sub_color_[4] = { 0,0,0,0 };
	const int COMMAND_EXP_X_ = DXE_WINDOW_WIDTH * 0.51f;

	//�U���E�B���h�E���W
	//�E�B���h�E
	const int ATTACK_WINDOW_Y_[6] = { 100,150,200,250,300,350 };
	int attack_window_x_[6] = { 20,20,20,20,20,20 };
	const int ATTACK_WINDOW_X_DEF_ = 20;
	const int ATTACK_WINDOW_X_SEL_ = 40;
	//����
	const int ATTACK_STR_Y_[6] = { 92,142,192,242,292,342 };
	int attack_str_x_[6] = { 8,8,8,8,8,8 };
	const int ATTACK_STR_X_DEF_ = 8;
	const int ATTACK_STR_X_SEL_ = 28;


	//�^�[���i�s���o�p���W
	const int PROGRESS_Y_ = DXE_WINDOW_HEIGHT * 0.3f;
	int progress_x_ = 0;
	int progress_x_speed_ = 25;
	int progress_x_speed_center_ = 1;
	int progress_elapsed_ = 0;

};

class SubUiBase {
public:
	SubUiBase() {}
	virtual ~SubUiBase() {}
	virtual void update(float delta_time) {}
	virtual void render() {}

	// =========== �֐� ==========

	// ========== ��{�X�e�[�^�X ==========

	ScenePlay* scene_ = nullptr; //�V�[���̕ϐ����擾���邽�߂̃|�C���^
	bool alive_ = true; //�����t���O
	bool move_ = true; //����t���O

};

class SubUiJudge : public SubUiBase {
public:
	SubUiJudge(ScenePlay* scene, int judge, int lane);
	~SubUiJudge(){}
	void update(float delta_time);
	void render();

	// =========== �֐� ==========

	// ========== ��{�X�e�[�^�X ==========

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

class SubUiDamage : public SubUiBase {
public:
	SubUiDamage(ScenePlay* scene, int damage, int lane);
	~SubUiDamage() {}
	void update(float delta_time);
	void render();

	// =========== �֐� ==========

	// ========== ��{�X�e�[�^�X ==========

	int damage_ = 0;
	int lane_ = 0;
	int elapsed_ = 0;
	const int RENDER_TIME_ = 30; //�\������

	//���W
	const float DAMAGE_X_[4] = { DXE_WINDOW_WIDTH * 0.2f - 20,DXE_WINDOW_WIDTH * 0.4f - 20,DXE_WINDOW_WIDTH * 0.6f - 20,DXE_WINDOW_WIDTH * 0.8f - 20 }; //4�̃��[���̍��W
	float damage_y_ = DXE_WINDOW_HEIGHT * 0.5f;

};

class SubUiPlayerDamage : public SubUiBase {
public:
	SubUiPlayerDamage(ScenePlay* scene, int damage, int lane);
	~SubUiPlayerDamage() {}
	void update(float delta_time);
	void render();

	// =========== �֐� ==========

	// ========== ��{�X�e�[�^�X ==========

	int damage_ = 0;
	int lane_ = 0;
	int elapsed_ = 0;
	const int RENDER_TIME_ = 30; //�\������

	//���W
	const float DAMAGE_X_[4] = { DXE_WINDOW_WIDTH * 0.2f - 20,DXE_WINDOW_WIDTH * 0.4f - 20,DXE_WINDOW_WIDTH * 0.6f - 20,DXE_WINDOW_WIDTH * 0.8f - 20 }; //4�̃��[���̍��W
	float damage_y_ = DXE_WINDOW_HEIGHT * 0.8f;
};