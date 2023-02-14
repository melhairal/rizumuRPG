#include "../gm_manager.h"
#include "gm_scene_result.h"
#include "gm_scene_title.h"

void SceneResult::initialzie() {
	//ウィンドウ画像読み込み
	window_top_left_ = LoadGraph("graphics/ui/window_a/window_a_001.png");
	window_top_center_ = LoadGraph("graphics/ui/window_a/window_a_002.png");
	window_top_right_ = LoadGraph("graphics/ui/window_a/window_a_003.png");
	window_left_ = LoadGraph("graphics/ui/window_a/window_a_004.png");
	window_center_ = LoadGraph("graphics/ui/window_a/window_a_005.png");
	window_right_ = LoadGraph("graphics/ui/window_a/window_a_006.png");
	window_bot_left_ = LoadGraph("graphics/ui/window_a/window_a_007.png");
	window_bot_center_ = LoadGraph("graphics/ui/window_a/window_a_008.png");
	window_bot_right_ = LoadGraph("graphics/ui/window_a/window_a_009.png");

	//フォント読み込み
	font_rondo_16_ = LoadFontDataToHandle("font/Rondo16.dft", 0);
	font_rondo_24_ = LoadFontDataToHandle("font/Rondo24.dft", 0);
	font_rondo_32_ = LoadFontDataToHandle("font/Rondo32.dft", 0);
	font_rondo_64_ = LoadFontDataToHandle("font/Rondo64.dft", 0);
	font_rondo_128_ = LoadFontDataToHandle("font/Rondo128.dft", 0);

	//スコアを取得
	getScore();
}

void SceneResult::update(float delta_time)
{
	GameManager* mgr = GameManager::GetInstance();


	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		mgr->chengeScene(new SceneTitle());
	}
}

void SceneResult::render()
{
	drawWindow(DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT / 2, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);
	DrawFormatStringToHandle(100, 100, 0, font_rondo_64_, "%d", score_max_combo_);
	DrawFormatStringToHandle(100, 200, 0, font_rondo_64_, "%d", score_perfect_);
	DrawFormatStringToHandle(100, 300, 0, font_rondo_64_, "%d", score_good_);
	DrawFormatStringToHandle(100, 400, 0, font_rondo_64_, "%d", score_miss_);
	DrawFormatStringToHandle(100, 500, 0, font_rondo_64_, "%d", score_);
}

void SceneResult::getScore() {
	GameManager* mgr = GameManager::GetInstance();
	score_judge_ = mgr->result_judge_;
	score_perfect_ = mgr->result_perfect_;
	score_good_ = mgr->result_good_;
	score_miss_ = mgr->result_miss_;
	score_max_combo_ = mgr->result_max_combo_;
	score_ = mgr->result_score_;
}

void SceneResult::drawWindow(int x, int y, int width, int height) {
	int center_x1 = x - width / 2 + 20;
	int center_x2 = x + width / 2 - 20;
	int center_y1 = y - height / 2 + 20;
	int center_y2 = y + height / 2 - 20;
	DrawExtendGraph(center_x1, center_y1, center_x2, center_y2, window_center_, true); //中心
	DrawExtendGraph(center_x1 - 20, center_y1, center_x1, center_y2, window_left_, true); //左
	DrawExtendGraph(center_x2, center_y1, center_x2 + 20, center_y2, window_right_, true); //右
	DrawExtendGraph(center_x1, center_y1 - 20, center_x2, center_y1, window_top_center_, true); //上
	DrawExtendGraph(center_x1, center_y2, center_x2, center_y2 + 20, window_bot_center_, true); //下
	DrawExtendGraph(center_x1 - 20, center_y1 - 20, center_x1, center_y1, window_top_left_, true); //左上
	DrawExtendGraph(center_x2, center_y1 - 20, center_x2 + 20, center_y1, window_top_right_, true); //右上
	DrawExtendGraph(center_x1 - 20, center_y2, center_x1, center_y2 + 20, window_bot_left_, true); //左下
	DrawExtendGraph(center_x2, center_y2, center_x2 + 20, center_y2 + 20, window_bot_right_, true); //右下
}