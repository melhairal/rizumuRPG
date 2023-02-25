#include "gm_scene_base.h"

class SceneResult : public SceneBase {
public:
	SceneResult() {}
	~SceneResult() {}

	void initialzie() override;
	void update(float delta_time) override;
	void render() override;

	// =========== �֐� ==========

	void getScore(); //�X�R�A���擾
	void setScore(); //�X�R�A���L��
	void drawWindow(int x, int y, int width, int height); //�E�B���h�E��`��

	// ========== ��{�X�e�[�^�X ==========

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

	//BGM
	int bgm_ = 0;

	int stage_ = 0; //�X�e�[�W

	//�X�e�[�W�^�C�g��
	const char* title_[6]{
		"�������̕���",
		"���̏Z�ދu",
		"���A�𔲂���",
		"����̏Z��",
		"��C������",
		"�ł̐X"
	};

	//�܋�
	const int MONNEY_[6] = {
		100,
		300,
		500,
		1000,
		2000,
		3000
	};

	//�o���l�e�[�u��
	const int UP_EXP_[9] = {
		1000,
		2000,
		3000,
		5000,
		10000,
		20000,
		30000,
		40000,
		50000
	};

	//���x�����̃X�e�[�^�X
	const int up_atk_ = 2;
	const int up_hp_ = 100;

	bool score_judge_ = true; //���������ǂ���
	int score_ = 0; //�X�R�A
	int draw_score_ = 0; //�X�R�A���o�p
	int score_perfect_ = 0; //�p�[�t�F�N�g��
	int score_good_ = 0; //�O�b�h��
	int score_miss_ = 0; //�~�X��
	int score_max_combo_ = 0; //�ő�R���{��
	int now_exp_ = 0; //�o���l
	int now_lv_ = 0; //���x��

	bool finish_ = false; //���o������������ǂ���
	int elapsed_ = 0; //���Ԍv���p
	const int INTERVAL_ = 30; //���o�Ԋu
	int num_ = 0; //���o���ǂ̂��炢�����񂾂�

	//���W
	const int TITLE_X_ = 250;
	const int TITLE_Y_ = 80;

	const int SCORE_X_[2] = { 100, 400 };
	const int SCORE_Y_ = 180;
	const int SCORE_SUB_Y_[4] = { 330,400,470,540 };

	const int RESULT_X_ = 580;
	const int RESULT_Y_ = 480;

	const int EXP_X_ = 200;
	const int EXP_Y_ = 660;
	const int LV_X_ = EXP_X_;
	const int LV_Y_ = EXP_Y_ + 50;



};
