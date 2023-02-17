#include "gm_scene_base.h"

class SceneMap : public SceneBase {
public:
	SceneMap() {}
	~SceneMap() {}

	void initialzie() override;
	void update(float delta_time) override;
	void render() override;

	// =========== �֐� ==========

	void getMgrStatus(); //�Q�[���}�l�[�W���[����t���O���擾����
	void getWindow(); //�E�B���h�E�̃p�X���擾
	void animation(); //�v���C���[�摜�A�j���[�V����
	void movePlayer(); //�v���C���[�𓮂���
	void drawWindow(int x, int y, int width, int height); //�E�B���h�E��`��
	void drawTitle(); //�X�e�[�W����`��

	// ========== ��{�X�e�[�^�X ==========

	//�i�s�x�ɍ��킹�����[���h�}�b�v�摜
	const char* map_[7] = {
		"graphics/world/map_1.png",
		"graphics/world/map_2.png",
		"graphics/world/map_3.png",
		"graphics/world/map_4.png",
		"graphics/world/map_5.png",
		"graphics/world/map_6.png",
		"graphics/world/map_7.png"
	};
	int world_map_ = 0;

	//�t�H���g
	int font_rondo_32_ = 0;
	int font_rondo_64_ = 0;
	const int BROWN = RGB(48, 78, 115);
	const int YELLOW = RGB(0, 225, 255);

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

	//���摜
	int right_ = 0;
	int left_ = 0;

	//�L�����摜
	int img_player_[3] = { 0,0,0 };
	const char* img_player_pass_[3] = {
		"graphics/chara/player_3d/player_001.png",
		"graphics/chara/player_3d/player_002.png",
		"graphics/chara/player_3d/player_003.png"
	};

	//�i�s�x
	int progress_ = 0;

	//�X�e�[�W�^�C�g��
	const char* title_[6]{
		"�������̕���",
		"���̏Z�ދu",
		"���A�𔲂���",
		"����̏Z��",
		"��C������",
		"�ł̐X"
	};
	const char* title_village_[1] = { 
		"�͂��܂�̑�" 
	};

	const char* label_[2]{
		"�X�e�[�W",
		"�@���_�@"
	};

	//�I��
	int sel_ = 0;
	const int MAX_INDEX_ = 6;
	const int MAX_INDEX_VILLAGE_ = 1;
	int sel_label_ = 0;
	const int MAX_INDEX_LABEL_ = 2;

	int elapsed_ = 0; //���Ԍv���p
	int frame_ = 0; //�A�j���[�V�����t���[��
	const int FRAME_INTERVAL_ = 10; //�A�j���[�V�����X�V�Ԋu

	//�摜���W
	const float MAP_X_ = DXE_WINDOW_WIDTH * 0.35f; //�}�b�v�摜���W
	const float MAP_Y_ = DXE_WINDOW_HEIGHT * 0.25f;
	const float WINDOW_X_ = DXE_WINDOW_WIDTH * 0.15f; //�I��p�E�B���h�E�摜���W
	const float WINDOW_Y_ = DXE_WINDOW_HEIGHT * 0.42f;
	const float WINDOW_W_ = DXE_WINDOW_WIDTH * 0.25f;
	const float WINDOW_H_ = DXE_WINDOW_HEIGHT * 0.6f;
	const float SUB_X_ = DXE_WINDOW_WIDTH / 2; //�T�u�E�B���h�E�摜���W
	const float SUB_Y_ = DXE_WINDOW_HEIGHT * 0.92f;
	const float SUB_W_ = DXE_WINDOW_WIDTH;
	const float SUB_H_ = DXE_WINDOW_HEIGHT * 0.16f;

	//�X�e�[�W�^�C�g�����W
	const float TITLE_DEF_X_ = DXE_WINDOW_WIDTH * 0.05f;
	const float TITLE_SEL_X_ = TITLE_DEF_X_ + 20;
	float title_x_[6] = { TITLE_DEF_X_,TITLE_DEF_X_,TITLE_DEF_X_,TITLE_DEF_X_,TITLE_DEF_X_,TITLE_DEF_X_ };
	float title_y_[6] = { DXE_WINDOW_HEIGHT * 0.15f, DXE_WINDOW_HEIGHT * 0.15f + 40, DXE_WINDOW_HEIGHT * 0.15f + 80,
		DXE_WINDOW_HEIGHT * 0.15f + 120, DXE_WINDOW_HEIGHT * 0.15f + 160, DXE_WINDOW_HEIGHT * 0.15f + 200};
	int title_color_[6] = { BROWN,BROWN,BROWN,BROWN,BROWN,BROWN };

	const float LABEL_X_ = WINDOW_X_ - 65;
	const float LABEL_Y_ = DXE_WINDOW_HEIGHT * 0.65f;
	const float LEFT_X_ = LABEL_X_ - 30;
	const float RIGHT_X_ = LABEL_X_ + 160;
	const float LR_Y_ = LABEL_Y_ + 16;

	//�v���C���[���W
	float player_x_ = 500;
	float player_y_ = 500;
	const float PLAYER_STAGE_X_[6] = { 742,642,720,300,800,900 };
	const float PLAYER_STAGE_Y_[6] = { 88,70,180,350,500,600 };
	const float PLAYER_VILLAGE_X_[1] = { 825 };
	const float PLAYER_VILLAGE_Y_[1] = { 120 };


};
