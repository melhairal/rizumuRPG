#pragma once
#include "../dxlib_ext/dxlib_ext.h"
class ScenePlay;

class Ui {
public:
	Ui(ScenePlay* scene);
	~Ui() {}
	void update(float delta_time);
	void render();

	// =========== 関数 ==========

	//可変ゲージを描画 x:x座標 y:y座標 width:画像サイズ(横幅) height:画像サイズ(縦幅) exrate:拡大率 num:ゲージの値 max:ゲージの最大値 color:色(enum)
	void DrawGauge(int x, int y, int width, int height, double exrate, int num, int max, int color); 
	void DrawGaugeProgress(int x, int y, int width, int height, double exrate, int num, int max, int color);

	// ========== 基本ステータス ==========

	enum {
		eBlue,
		eYellow,
		eRed
	};

	ScenePlay* scene_ = nullptr; //シーンの変数を取得するためのポインタ

	//色 RGB(B,G,R)
	const int RED = RGB(0, 0, 255);
	const int GREEN = RGB(0, 255, 0);
	const int BLUE = RGB(255, 0, 0);
	const int BROWN = RGB(48, 78, 115);
	const int YELLOW = RGB(0, 225, 255);

	//フォント
	int font_rondo_16_ = 0;
	int font_rondo_32_ = 0;
	int font_rondo_64_ = 0;
	int font_rondo_128_ = 0;

	//HPゲージ
	int hp_bar_[3] = { 0,0,0 };
	int hp_back_ = 0;
	int hp_frame_ = 0;

	// ========== 座標 ==========

	//ゲージ画像サイズ
	const int GAUGE_IMG_W_ = 156;
	const int GAUGE_IMG_H_ = 8;

	//進行度/ボスHP
	const int HOME_HP_X_ = DXE_WINDOW_WIDTH / 2;
	const int HOME_HP_Y_ = DXE_WINDOW_HEIGHT * 0.05f;
	int run_ = 0; //走るアイコン
	const int RUN_X_ = HOME_HP_X_;

	//プレイヤーHP/MP
	const int PLAYER_GAUGE_X_ = DXE_WINDOW_WIDTH / 2;
	const int PLAYER_GAUGE_Y1_ = DXE_WINDOW_HEIGHT * 0.95f;
	const int PLAYER_GAUGE_Y2_ = PLAYER_GAUGE_Y1_ + 20;

	const int PLAYER_ICON_X_ = PLAYER_GAUGE_X_ - 140;

	//コンボ
	const int COMBO_X_ = DXE_WINDOW_WIDTH * 0.9f;
	const int COMBO_Y_ = DXE_WINDOW_HEIGHT * 0.2f;
	const int COMBO_NUM_X_ = COMBO_X_ - 100;
	const int COMBO_NUM_Y_ = COMBO_Y_ - 20;

	//判定
	const float JUDGE_X_[4] = { DXE_WINDOW_WIDTH * 0.2f,DXE_WINDOW_WIDTH * 0.4f,DXE_WINDOW_WIDTH * 0.6f,DXE_WINDOW_WIDTH * 0.8f }; //4つのレーンの座標
	const float JUDGE_Y_ = DXE_WINDOW_HEIGHT * 0.75f; 
};

class SubUiJudge {
public:
	SubUiJudge(ScenePlay* scene, int judge, int lane);
	~SubUiJudge(){}
	void update(float delta_time);
	void render();

	// =========== 関数 ==========

	// ========== 基本ステータス ==========

	ScenePlay* scene_ = nullptr; //シーンの変数を取得するためのポインタ
	bool alive_ = true; //生存フラグ
	bool move_ = true; //動作フラグ

	enum {
		perfect,
		good,
		miss
	};

	int judge_ = 0;
	int lane_ = 0;
	int elapsed_ = 0;
	const int RENDER_TIME_ = 30; //表示時間

	//座標
	const float JUDGE_X_[4] = { DXE_WINDOW_WIDTH * 0.2f - 20,DXE_WINDOW_WIDTH * 0.4f - 20,DXE_WINDOW_WIDTH * 0.6f - 20,DXE_WINDOW_WIDTH * 0.8f - 20 }; //4つのレーンの座標
	float judge_y_ = DXE_WINDOW_HEIGHT * 0.75f;

};