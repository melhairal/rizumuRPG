#include "../gm_manager.h"
#include "gm_scene_result.h"
#include "gm_scene_title.h"

void SceneResult::initialzie() {
	//ウィンドウ画像読み込み
	window_top_left_ = LoadGraph("graphics/ui/window_b/window_b_001.png");
	window_top_center_ = LoadGraph("graphics/ui/window_b/window_b_002.png");
	window_top_right_ = LoadGraph("graphics/ui/window_b/window_b_003.png");
	window_left_ = LoadGraph("graphics/ui/window_b/window_b_004.png");
	window_center_ = LoadGraph("graphics/ui/window_b/window_b_005.png");
	window_right_ = LoadGraph("graphics/ui/window_b/window_b_006.png");
	window_bot_left_ = LoadGraph("graphics/ui/window_b/window_b_007.png");
	window_bot_center_ = LoadGraph("graphics/ui/window_b/window_b_008.png");
	window_bot_right_ = LoadGraph("graphics/ui/window_b/window_b_009.png");

	//フォント読み込み
	font_rondo_16_ = LoadFontDataToHandle("font/Rondo16.dft", 0);
	font_rondo_24_ = LoadFontDataToHandle("font/Rondo24.dft", 0);
	font_rondo_32_ = LoadFontDataToHandle("font/Rondo32.dft", 0);
	font_rondo_64_ = LoadFontDataToHandle("font/Rondo64.dft", 0);
	font_rondo_128_ = LoadFontDataToHandle("font/Rondo128.dft", 0);

	//bgm読み込み
	bgm_ = LoadSoundMem("sound/result.mp3");
	PlaySoundMem(bgm_, DX_PLAYTYPE_LOOP);

	//スコアを取得
	getScore();
}

void SceneResult::update(float delta_time)
{
	GameManager* mgr = GameManager::GetInstance();

	if (num_ < 5) {
		if (elapsed_ >= INTERVAL_) {
			elapsed_ = 0;
			num_++;
		}
		elapsed_++;
	}
	else {
		if (draw_score_ < score_) {
			draw_score_ += 10000;
		}
		if (draw_score_ >= score_) {
			draw_score_ = score_;
			finish_ = true;
		}
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			if (finish_) {
				StopSoundMem(bgm_);
				mgr->chengeScene(new SceneTitle());
			}
			else {
				draw_score_ = score_;
			}
		}
	}
}

void SceneResult::render()
{
	drawWindow(DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT / 2, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);
	drawTitle(stage_);
	
	if (num_ >= 5)DrawFormatStringToHandle(SCORE_X_, SCORE_Y_, -1, font_rondo_128_, "Score %d", draw_score_);
	if (num_ >= 1)DrawFormatStringToHandle(SCORE_X_, SCORE_SUB_Y_[0], -1, font_rondo_64_, "Max Combo %d", score_max_combo_);
	if (num_ >= 2)DrawFormatStringToHandle(SCORE_X_, SCORE_SUB_Y_[1], YELLOW, font_rondo_64_, "Perfect %d", score_perfect_);
	if (num_ >= 3)DrawFormatStringToHandle(SCORE_X_, SCORE_SUB_Y_[2], BLUE, font_rondo_64_, "Good    %d", score_good_);
	if (num_ >= 4)DrawFormatStringToHandle(SCORE_X_, SCORE_SUB_Y_[3], RED, font_rondo_64_, "Miss    %d", score_miss_);

	if (finish_) {
		if (score_judge_) {
			DrawStringToHandle(RESULT_X_, RESULT_Y_, "CLEAR!!", YELLOW, font_rondo_128_);
		}
		else {
			DrawStringToHandle(RESULT_X_, RESULT_Y_, "FAILED", BLUE, font_rondo_128_);
		}
	}
}

void SceneResult::getScore() {
	GameManager* mgr = GameManager::GetInstance();
	score_judge_ = mgr->result_judge_;
	score_perfect_ = mgr->result_perfect_;
	score_good_ = mgr->result_good_;
	score_miss_ = mgr->result_miss_;
	score_max_combo_ = mgr->result_max_combo_;
	score_ = mgr->result_score_;
	stage_ = mgr->result_stage_;
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

void SceneResult::drawTitle(int stage) {
	switch (stage) {
	case 1:
		DrawStringToHandle(TITLE_X_, TITLE_Y_, "旅立ち", -1, font_rondo_64_);
		break;
	case 2:
		DrawStringToHandle(TITLE_X_, TITLE_Y_, "草原を駆け抜けて", -1, font_rondo_64_);
		break;
	case 3:
		DrawStringToHandle(TITLE_X_, TITLE_Y_, "魔獣の洞窟", -1, font_rondo_64_);
		break;
	case 4:
		DrawStringToHandle(TITLE_X_, TITLE_Y_, "洞窟を抜けて", -1, font_rondo_64_);
		break;
	case 5:
		DrawStringToHandle(TITLE_X_, TITLE_Y_, "大海を往く", -1, font_rondo_64_);
		break;
	case 6:
		DrawStringToHandle(TITLE_X_, TITLE_Y_, "闇の森", -1, font_rondo_64_);
		break;
	}
}