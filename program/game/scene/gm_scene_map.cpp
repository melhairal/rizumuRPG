#include "../gm_manager.h"
#include "gm_scene_map.h"
#include "gm_scene_play.h"
#include "gm_scene_field.h"

SceneMap::~SceneMap() {
	InitGraph();
	InitMusicMem();
	InitFontToHandle();
}

void SceneMap::initialzie() {
	//ステータス取得
	getMgrStatus();

	//ウィンドウ画像を取得
	getWindow();
	right_ = LoadGraph("graphics/ui/right.png");
	left_ = LoadGraph("graphics/ui/left.png");

	//フォント取得
	font_rondo_32_ = LoadFontDataToHandle("font/Rondo32.dft", 0);
	font_rondo_64_ = LoadFontDataToHandle("font/Rondo64.dft", 0);

	//マップ画像を取得
	world_map_ = LoadGraph(map_[max_index_ - 1]);

	//キャラ画像を取得
	img_player_[0] = LoadGraph(img_player_pass_[0]);
	img_player_[1] = LoadGraph(img_player_pass_[1]);
	img_player_[2] = LoadGraph(img_player_pass_[2]);

	//BGM取得
	bgm_ = LoadSoundMem("sound/map.mp3");
	se_select_ = LoadSoundMem("sound/select.mp3");
	PlaySoundMem(bgm_, DX_PLAYTYPE_LOOP);
}

void SceneMap::update(float delta_time)
{
	GameManager* mgr = GameManager::GetInstance();

	//選択する
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) {
		PlaySoundMem(se_select_, DX_PLAYTYPE_BACK);
		sel_--;
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)) {
		PlaySoundMem(se_select_, DX_PLAYTYPE_BACK);
		sel_++;
	}
	switch (sel_label_) {
	case 0:
		sel_ = std::clamp(sel_, 0, max_index_ - 1);
		break;
	case 1:
		sel_ = std::clamp(sel_, 0, MAX_INDEX_VILLAGE_ - 1);
		break;
	}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_LEFT)) {
		PlaySoundMem(se_select_, DX_PLAYTYPE_BACK);
		sel_label_--;
		sel_ = 0;
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RIGHT)) {
		PlaySoundMem(se_select_, DX_PLAYTYPE_BACK);
		sel_label_++;
		sel_ = 0;
	}
	sel_label_ = std::clamp(sel_label_, 0, MAX_INDEX_LABEL_ - 1);


	//選択中のタイトルを協調する
	for (int i = 0; i < max_index_; i++) {
		title_x_[i] = TITLE_DEF_X_;
		title_color_[i] = BROWN;
	}
	title_x_[sel_] = TITLE_SEL_X_;
	title_color_[sel_] = YELLOW;

	animation();
	movePlayer();

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		PlaySoundMem(se_select_, DX_PLAYTYPE_BACK);
		switch (sel_label_) {
		case 0:
			mgr->now_stage_ = sel_;
			StopSoundMem(bgm_);
			mgr->chengeScene(new ScenePlay());
			break;
		case 1:
			StopSoundMem(bgm_);
			mgr->chengeScene(new SceneField());
			break;
		}
	}
}

void SceneMap::render()
{
	DrawStringEx(100, 100, -1, "SceneMap");
	DrawRotaGraph(MAP_X_, MAP_Y_, 0.4f, 0, world_map_, true);
	drawWindow(WINDOW_X_, WINDOW_Y_, WINDOW_W_, WINDOW_H_);
	drawWindow(SUB_X_, SUB_Y_, SUB_W_, SUB_H_);
	DrawRotaGraph(player_x_, player_y_, 1, 0, img_player_[frame_], true);

	drawTitle();
}

void SceneMap::getMgrStatus() {
	GameManager* mgr = GameManager::GetInstance();
	max_index_ = mgr->flag_stage_;
	for (int i = 0; i < max_index_; i++) {
		best_score_[i] = mgr->best_score_[i];
	}
}

void SceneMap::getWindow() {
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
}

void SceneMap::animation() {
	if (elapsed_ >= FRAME_INTERVAL_) {
		elapsed_ = 0;
		frame_++;
		if (frame_ >= 3) {
			frame_ = 0;
		}
	}
	elapsed_++;
}

void SceneMap::movePlayer() {
	switch (sel_label_) {
	case 0:
		player_x_ = PLAYER_STAGE_X_[sel_];
		player_y_ = PLAYER_STAGE_Y_[sel_];
		break;
	case 1:
		player_x_ = PLAYER_VILLAGE_X_[sel_];
		player_y_ = PLAYER_VILLAGE_Y_[sel_];
		break;
	}
}

void SceneMap::drawWindow(int x, int y, int width, int height) {
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

void SceneMap::drawTitle() {
	switch (sel_label_) {
	case 0:
		for (int i = 0; i < max_index_; i++) {
			DrawStringToHandle(title_x_[i], title_y_[i], title_[i], title_color_[i], font_rondo_32_);
		}
		DrawStringToHandle(COMMENT_X_, COMMENT_Y_, comment_[sel_], BROWN, font_rondo_32_);
		DrawFormatStringToHandle(SCORE_X_, SCORE_Y_, BROWN, font_rondo_32_, "%8.0d", best_score_[sel_]);
		DrawRotaGraph(RIGHT_X_, LR_Y_, 0.5f, 0, right_, true);
		break;
	case 1:
		for (int i = 0; i < MAX_INDEX_VILLAGE_; i++) {
			DrawStringToHandle(title_x_[i], title_y_[i], title_village_[i], title_color_[i], font_rondo_32_);
		}
		DrawStringToHandle(COMMENT_X_, COMMENT_Y_, comment_village_[sel_], BROWN, font_rondo_32_);
		DrawRotaGraph(LEFT_X_, LR_Y_, 0.5f, 0, left_, true);
		break;
	}
	DrawStringToHandle(LABEL_X_, LABEL_Y_, label_[sel_label_], BROWN, font_rondo_32_);
}