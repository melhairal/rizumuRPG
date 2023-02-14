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

	bool score_judge_ = true; //���������ǂ���
	int score_ = 0; //�X�R�A
	int score_perfect_ = 0; //�p�[�t�F�N�g��
	int score_good_ = 0; //�O�b�h��
	int score_miss_ = 0; //�~�X��
	int score_max_combo_ = 0; //�ő�R���{��


};
