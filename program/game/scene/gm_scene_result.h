#include "gm_scene_base.h"

class SceneResult : public SceneBase {
public:
	SceneResult() {}
	~SceneResult() {}

	void initialzie() override;
	void update(float delta_time) override;
	void render() override;

	// =========== 関数 ==========

	void getScore(); //スコアを取得
	void drawWindow(int x, int y, int width, int height); //ウィンドウを描画

	// ========== 基本ステータス ==========

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

	bool score_judge_ = true; //勝ったかどうか
	int score_ = 0; //スコア
	int score_perfect_ = 0; //パーフェクト数
	int score_good_ = 0; //グッド数
	int score_miss_ = 0; //ミス数
	int score_max_combo_ = 0; //最大コンボ数


};
