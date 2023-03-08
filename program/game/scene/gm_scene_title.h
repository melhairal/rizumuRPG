#include "gm_scene_base.h"

class SceneTitle : public SceneBase {
public:
	SceneTitle() {}
	~SceneTitle();

	void initialzie() override;
	void update(float delta_time) override;
	void render() override;

	// =========== �֐� ==========



	// ========== ��{�X�e�[�^�X ==========
	
	int bgm_ = 0; //BGM
	int se_select_ = 0; //�I����

	int img_title_ = 0; //�^�C�g���摜
	int font_rondo_32_ = 0; //�t�H���g

	const int YELLOW = RGB(0, 225, 255);

	int sel_ = 0; //�I�𒆂̔ԍ�
	const int MAX_INDEX_ = 3; //�ő區�ڐ�

	const int DEF_X_ = DXE_WINDOW_WIDTH / 2 - 80; //���I��X���W
	const int SEL_X_ = DXE_WINDOW_WIDTH / 2 - 60; //�I��X���W
	int start_color_[3] = { 0,0,0 }; //�F
	int start_x_[3] = { DEF_X_,DEF_X_,DEF_X_ }; //x���W
	const int start_y_[3] = { DXE_WINDOW_HEIGHT / 2 + 50, DXE_WINDOW_HEIGHT / 2 + 100 , DXE_WINDOW_HEIGHT / 2 + 150 }; //y���W
};
