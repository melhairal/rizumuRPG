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
	void drawTitle(int stage); //ステージ名を描画

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

	//BGM
	int bgm_ = 0;

	int stage_ = 0; //ステージ

	bool score_judge_ = true; //勝ったかどうか
	int score_ = 0; //スコア
	int draw_score_ = 0; //スコア演出用
	int score_perfect_ = 0; //パーフェクト数
	int score_good_ = 0; //グッド数
	int score_miss_ = 0; //ミス数
	int score_max_combo_ = 0; //最大コンボ数

	bool finish_ = false; //演出がおわったかどうか
	int elapsed_ = 0; //時間計測用
	const int INTERVAL_ = 30; //演出間隔
	int num_ = 0; //演出がどのくらいすすんだか

	//座標
	const int TITLE_X_ = 250;
	const int TITLE_Y_ = 100;

	const int SCORE_X_ = 100;
	const int SCORE_Y_ = 200;
	const int SCORE_SUB_Y_[4] = { 350,420,490,560 };

	const int RESULT_X_ = 500;
	const int RESULT_Y_ = 500;



};
