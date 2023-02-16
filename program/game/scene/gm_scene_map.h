#include "gm_scene_base.h"

class SceneMap : public SceneBase {
public:
	SceneMap() {}
	~SceneMap() {}

	void initialzie() override;
	void update(float delta_time) override;
	void render() override;

	// =========== 関数 ==========

	void getMgrStatus(); //ゲームマネージャーからフラグを取得する
	void getWindow(); //ウィンドウのパスを取得
	void drawWindow(int x, int y, int width, int height); //ウィンドウを描画

	// ========== 基本ステータス ==========

	//進行度に合わせたワールドマップ画像
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

	//ウィンドウ画像
	int window_top_left_ = 0;
	int window_top_center_ = 0;
	int window_top_right_ = 0;
	int window_left_ = 0;
	int window_center_ = 0;
	int window_right_ = 0;
	int window_bot_left_ = 0;
	int window_bot_center_ = 0;
	int window_bot_right_ = 0;

	//進行度
	int progress_ = 0;

	//画像座標
	const float MAP_X_ = DXE_WINDOW_WIDTH * 0.35f; //マップ画像座標
	const float MAP_Y_ = DXE_WINDOW_HEIGHT * 0.25f;
	const float WINDOW_X_ = DXE_WINDOW_WIDTH * 0.15f; //選択用ウィンドウ画像座標
	const float WINDOW_Y_ = DXE_WINDOW_HEIGHT * 0.42f;
	const float WINDOW_W_ = DXE_WINDOW_WIDTH * 0.3f;
	const float WINDOW_H_ = DXE_WINDOW_HEIGHT * 0.84f;
	const float SUB_X_ = DXE_WINDOW_WIDTH / 2; //サブウィンドウ画像座標
	const float SUB_Y_ = DXE_WINDOW_HEIGHT * 0.92f;
	const float SUB_W_ = DXE_WINDOW_WIDTH;
	const float SUB_H_ = DXE_WINDOW_HEIGHT * 0.16f;
};
