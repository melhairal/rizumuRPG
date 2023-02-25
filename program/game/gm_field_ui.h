#pragma once
#include "../dxlib_ext/dxlib_ext.h"
class SceneField;
class SpriteBase;

class FieldUi {
public:
	FieldUi(SceneField* scene);
	~FieldUi() {}
	void update(float delta_time);
	void render();

	// =========== 関数 ==========

	void getFont(); //フォント読み込み
	void getWindow(); //ウィンドウ画像読み込み
	void drawWindow(int x, int y, int width, int height); //可変ウィンドウ描画

	void updateComment(); //コメント制御
	void updateMenu(); //メニュー制御
	void updateShop(); //ショップ制御

	// ========== 基本ステータス ==========

	SceneField* scene_ = nullptr; //シーンの変数を取得するためのポインタ
	SpriteBase* sprite_ = nullptr; //セリフを呼び出したスプライト情報を格納
	SpriteBase* sprite_shop_ = nullptr; //ショップを呼び出したスプライト情報を格納

	int menu_depth_ = 1; //メニューのどの段階にいるか
	int sel_label_ = 0; //選択中のラベル
	const int LABEL_INDEX_MAX_ = 5; //ラベルのインデックス最大数
	const char* label_[5] = {
		"スキル",
		"どうぐ",
		"オプション",
		"セーブ",
		"おわる"
	};
	int label_color_[5] = { BROWN,BROWN,BROWN,BROWN,BROWN };
	int sel_index_ = 0; //選択中のインデックス
	int sel_list_ = 0; //リストのスクロール
	const int INDEX_MAX_ = 5; //インデックスの最大数
	int index_color_[5] = { BROWN,BROWN,BROWN,BROWN,BROWN };

	int item_num_ = 0; //アイテム所持数

	int shop_depth_ = 0; //ショップメニューのどの段階にいるか
	int shop_sel_label_ = 0; //選択中のラベル
	const int SHOP_LABEL_INDEX_MAX_ = 2; //ラベルのインデックス最大数
	const char* shop_label_[2] = {
		"買う",
		"売る"
	};
	int shop_label_color_[2] = { BROWN,BROWN };
	int shop_sel_index_ = 0; //選択中のインデックス
	const int SHOP_INDEX_MAX_ = 8; //インデックスの最大数
	int shop_index_color_[8] = { BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN };

	//色 RGB(B,G,R)
	const int RED = RGB(0, 0, 255);
	const int GREEN = RGB(0, 255, 0);
	const int BLUE = RGB(255, 0, 0);
	const int BROWN = RGB(48, 78, 115);
	const int YELLOW = RGB(0, 225, 255);

	//フォント
	int font_rondo_16_ = 0;
	int font_rondo_24_ = 0;
	int font_rondo_32_ = 0;
	int font_rondo_64_ = 0;
	int font_rondo_128_ = 0;
	int font_pop_32_ = 0;

	int img_message_ = 0;

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

	//座標
	const float MESSAGE_WIN_X_ = DXE_WINDOW_WIDTH / 2;
	const float MESSAGE_WIN_Y_ = DXE_WINDOW_HEIGHT * 0.85f;
	const float MESSAGE_X_ = DXE_WINDOW_WIDTH * 0.1f;
	const float MESSAGE_Y_ = MESSAGE_WIN_Y_ - 16;

	const float WINDOW_LABEL_X_ = DXE_WINDOW_WIDTH * 0.2f;
	const float WINDOW_LABEL_Y_ = DXE_WINDOW_HEIGHT / 2;
	const float WINDOW_LABEL_W_ = DXE_WINDOW_WIDTH * 0.2f;
	const float WINDOW_LABEL_H_ = DXE_WINDOW_HEIGHT * 0.6f;

	const float WINDOW_MAIN_X_ = DXE_WINDOW_WIDTH * 0.6f;
	const float WINDOW_MAIN_Y_ = DXE_WINDOW_HEIGHT / 2;
	const float WINDOW_MAIN_W_ = DXE_WINDOW_WIDTH * 0.6f;
	const float WINDOW_MAIN_H_ = DXE_WINDOW_HEIGHT * 0.6f;

	const float WINDOW_SUB_X_ = WINDOW_MAIN_X_;
	const float WINDOW_SUB_Y_ = DXE_WINDOW_HEIGHT * 0.7f;
	const float WINDOW_SUB_W_ = WINDOW_MAIN_W_;
	const float WINDOW_SUB_H_ = DXE_WINDOW_HEIGHT * 0.2f;

	const float LABEL_X_ = DXE_WINDOW_WIDTH * 0.13f;
	const float LABEL_Y_[5] = {
		 DXE_WINDOW_HEIGHT * 0.25f,
		 DXE_WINDOW_HEIGHT * 0.25f + 50,
		 DXE_WINDOW_HEIGHT * 0.25f + 100,
		 DXE_WINDOW_HEIGHT * 0.25f + 150,
		 DXE_WINDOW_HEIGHT * 0.25f + 200
	};

	const float STATUS_X_[2] = { 350,550 };
	const float STATUS_Y_[6] = { 200,250,300,350,400,450 };

	const float COMMENT_X_ = 350;
	const float COMMENT_Y_[3] = { 480,520,560 };
	const float NUM_X_ = 760;

};