#include "gm_scene_base.h"

class SceneTitle : public SceneBase {
public:
	SceneTitle() {}
	~SceneTitle();

	void initialzie() override;
	void update(float delta_time) override;
	void render() override;

	// =========== 関数 ==========



	// ========== 基本ステータス ==========
	
	int bgm_ = 0; //BGM
	int se_select_ = 0; //選択音

	int img_title_ = 0; //タイトル画像
	int font_rondo_32_ = 0; //フォント

	const int YELLOW = RGB(0, 225, 255);

	int sel_ = 0; //選択中の番号
	const int MAX_INDEX_ = 3; //最大項目数

	const int DEF_X_ = DXE_WINDOW_WIDTH / 2 - 80; //未選択X座標
	const int SEL_X_ = DXE_WINDOW_WIDTH / 2 - 60; //選択中X座標
	int start_color_[3] = { 0,0,0 }; //色
	int start_x_[3] = { DEF_X_,DEF_X_,DEF_X_ }; //x座標
	const int start_y_[3] = { DXE_WINDOW_HEIGHT / 2 + 50, DXE_WINDOW_HEIGHT / 2 + 100 , DXE_WINDOW_HEIGHT / 2 + 150 }; //y座標
};
