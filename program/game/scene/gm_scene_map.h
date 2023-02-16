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
	void drawWindow(int x, int y, int width, int height); //�E�B���h�E��`��

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

	//�i�s�x
	int progress_ = 0;

	//�摜���W
	const float MAP_X_ = DXE_WINDOW_WIDTH * 0.35f; //�}�b�v�摜���W
	const float MAP_Y_ = DXE_WINDOW_HEIGHT * 0.25f;
	const float WINDOW_X_ = DXE_WINDOW_WIDTH * 0.15f; //�I��p�E�B���h�E�摜���W
	const float WINDOW_Y_ = DXE_WINDOW_HEIGHT * 0.42f;
	const float WINDOW_W_ = DXE_WINDOW_WIDTH * 0.3f;
	const float WINDOW_H_ = DXE_WINDOW_HEIGHT * 0.84f;
	const float SUB_X_ = DXE_WINDOW_WIDTH / 2; //�T�u�E�B���h�E�摜���W
	const float SUB_Y_ = DXE_WINDOW_HEIGHT * 0.92f;
	const float SUB_W_ = DXE_WINDOW_WIDTH;
	const float SUB_H_ = DXE_WINDOW_HEIGHT * 0.16f;
};
