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
	void animation(); //プレイヤー画像アニメーション
	void movePlayer(); //プレイヤーを動かす
	void drawWindow(int x, int y, int width, int height); //ウィンドウを描画
	void drawTitle(); //ステージ名を描画

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

	//フォント
	int font_rondo_32_ = 0;
	int font_rondo_64_ = 0;
	const int BROWN = RGB(48, 78, 115);
	const int YELLOW = RGB(0, 225, 255);

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

	//矢印画像
	int right_ = 0;
	int left_ = 0;

	//キャラ画像
	int img_player_[3] = { 0,0,0 };
	const char* img_player_pass_[3] = {
		"graphics/chara/player_3d/player_001.png",
		"graphics/chara/player_3d/player_002.png",
		"graphics/chara/player_3d/player_003.png"
	};

	//進行度
	int progress_ = 0;

	//ステージタイトル
	const char* title_[6]{
		"旅立ちの平原",
		"竜の住む丘",
		"洞窟を抜けて",
		"悪霊の住処",
		"大海を往く",
		"闇の森"
	};
	const char* title_village_[1] = { 
		"はじまりの村" 
	};

	const char* label_[2]{
		"ステージ",
		"　拠点　"
	};

	//選択中
	int sel_ = 0;
	const int MAX_INDEX_ = 6;
	const int MAX_INDEX_VILLAGE_ = 1;
	int sel_label_ = 0;
	const int MAX_INDEX_LABEL_ = 2;

	int elapsed_ = 0; //時間計測用
	int frame_ = 0; //アニメーションフレーム
	const int FRAME_INTERVAL_ = 10; //アニメーション更新間隔

	//画像座標
	const float MAP_X_ = DXE_WINDOW_WIDTH * 0.35f; //マップ画像座標
	const float MAP_Y_ = DXE_WINDOW_HEIGHT * 0.25f;
	const float WINDOW_X_ = DXE_WINDOW_WIDTH * 0.15f; //選択用ウィンドウ画像座標
	const float WINDOW_Y_ = DXE_WINDOW_HEIGHT * 0.42f;
	const float WINDOW_W_ = DXE_WINDOW_WIDTH * 0.25f;
	const float WINDOW_H_ = DXE_WINDOW_HEIGHT * 0.6f;
	const float SUB_X_ = DXE_WINDOW_WIDTH / 2; //サブウィンドウ画像座標
	const float SUB_Y_ = DXE_WINDOW_HEIGHT * 0.92f;
	const float SUB_W_ = DXE_WINDOW_WIDTH;
	const float SUB_H_ = DXE_WINDOW_HEIGHT * 0.16f;

	//ステージタイトル座標
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

	//プレイヤー座標
	float player_x_ = 500;
	float player_y_ = 500;
	const float PLAYER_STAGE_X_[6] = { 742,642,720,300,800,900 };
	const float PLAYER_STAGE_Y_[6] = { 88,70,180,350,500,600 };
	const float PLAYER_VILLAGE_X_[1] = { 825 };
	const float PLAYER_VILLAGE_Y_[1] = { 120 };


};
