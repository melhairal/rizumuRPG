#include "gm_ui.h"
#include "scene/gm_scene_play.h"
#include "gm_sheet_music.h"
#include "gm_boss.h"
#include "object/gm_object_attack.h"

Ui::Ui(ScenePlay* scene) {
	scene_ = scene;
	//フォント読み込み
	font_rondo_16_ = LoadFontDataToHandle("font/Rondo16.dft", 0);
	font_rondo_24_ = LoadFontDataToHandle("font/Rondo24.dft", 0);
	font_rondo_32_ = LoadFontDataToHandle("font/Rondo32.dft", 0);
	font_rondo_64_ = LoadFontDataToHandle("font/Rondo64.dft", 0);
	font_rondo_128_ = LoadFontDataToHandle("font/Rondo128.dft", 0);

	//バー画像読み込み
	hp_bar_[eBlue] = LoadGraph("graphics/ui/gauge_bar_blue.png");
	hp_bar_[eYellow] = LoadGraph("graphics/ui/gauge_bar_yellow.png");
	hp_bar_[eRed] = LoadGraph("graphics/ui/gauge_bar_pink.png");
	hp_back_ = LoadGraph("graphics/ui/gauge_background.png");
	hp_frame_ = LoadGraph("graphics/ui/gauge_frame.png");
	run_ = LoadGraph("graphics/ui/run.png");

	//ウィンドウ読み込み
	getWindow();

	//カーソル読み込み
	cursol_ = LoadGraph("graphics/ui/cursol.png");

	//攻撃ウィンドウ読み込み
	window_attack_player_ = LoadGraph("graphics/ui/window_attack_player.png");
	window_attack_boss_ = LoadGraph("graphics/ui/attack_boss.png");
}

void Ui::update(float delta_time) {
	if (scene_->boss_ != nullptr) {
		//選択中のコマンドの文字の色を変える
		for (int i = 0; i < 4; i++) {
			command_color_[i] = BROWN;
			command_sub_color_[i] = BROWN;
		}
		if (scene_->boss_->main_command_) command_color_[scene_->boss_->index_main_] = -1;
		else command_sub_color_[scene_->boss_->index_sub_] = -1;

		if (scene_->boss_->command_) { //コマンド選択中
			//登録中の攻撃ウィンドウの座標をずらす
			for (int i = 0; i < 3; i++) {
				attack_window_x_[i] = ATTACK_WINDOW_X_DEF_;
				attack_str_x_[i] = ATTACK_STR_X_DEF_;
			}
			if (scene_->boss_->select_num_ >= 0 && scene_->boss_->select_num_ < 3) {
				attack_window_x_[scene_->boss_->select_num_] = ATTACK_WINDOW_X_SEL_;
				attack_str_x_[scene_->boss_->select_num_] = ATTACK_STR_X_SEL_;
			}
		}

		if (scene_->boss_->battle_) { //バトル中
			//行動中の攻撃ウィンドウの座標をずらす
			for (int i = 0; i < 3; i++) {
				attack_window_x_[i] = ATTACK_WINDOW_X_DEF_;
				attack_str_x_[i] = ATTACK_STR_X_DEF_;
			}
			if (scene_->boss_->action_num_ >= 0 && scene_->boss_->action_num_ < 3) {
				attack_window_x_[scene_->boss_->action_num_] = ATTACK_WINDOW_X_SEL_;
				attack_str_x_[scene_->boss_->action_num_] = ATTACK_STR_X_SEL_;
			}
		}
	}
}

void Ui::render() {
	//進行メーター表示
	if (scene_->sheet_ != nullptr) {
		DrawGaugeProgress(HOME_HP_X_, HOME_HP_Y_, GAUGE_IMG_W_, GAUGE_IMG_H_, 2.0f, scene_->sheet_->csv_y_, scene_->sheet_->csv_.size(), eYellow);
	}

	if (scene_->boss_ != nullptr) {
		DrawGauge(HOME_HP_X_, HOME_HP_Y_, GAUGE_IMG_W_, GAUGE_IMG_H_, 2.0f, scene_->boss_->hp_, scene_->boss_->hp_max_, eYellow);
		//コマンド表示
		if (scene_->boss_->command_) {
			DrawWindow(COMMAND_X1_, COMMAND_Y_, COMMAND_W1_, COMMAND_H_, eBrown);
			DrawWindow(COMMAND_X2_, COMMAND_Y_, COMMAND_W2_, COMMAND_H_, eBrown);
			DrawWindow(COMMAND_X3_, COMMAND_Y_, COMMAND_W3_, COMMAND_H_, eBrown);
			DrawWindow(STATUS_X_, STATUS_Y_, STATUS_W_, STATUS_H_, eBrown);
			if (scene_->boss_->main_command_) DrawExtendGraph(COMMAND_MAIN_X_, COMMAND_LIST_Y_[scene_->boss_->index_main_], COMMAND_MAIN_X_ + 150, COMMAND_LIST_Y_[scene_->boss_->index_main_] + 35 , cursol_, true);
			DrawStringToHandle(COMMAND_MAIN_X_, COMMAND_LIST_Y_[0], "こうげき", command_color_[0], font_rondo_32_);
			DrawStringToHandle(COMMAND_MAIN_X_, COMMAND_LIST_Y_[1], "スキル", command_color_[1], font_rondo_32_);
			DrawStringToHandle(COMMAND_MAIN_X_, COMMAND_LIST_Y_[2], "どうぐ", command_color_[2], font_rondo_32_);
			DrawStringToHandle(COMMAND_MAIN_X_, COMMAND_LIST_Y_[3], "にげる", command_color_[3], font_rondo_32_);
			//サブコマンド
			switch (scene_->boss_->index_main_) {
			case 0:
				DrawStringToHandle(COMMAND_SUB_X_, COMMAND_LIST_Y_[0], scene_->skill_[0]->name_.c_str(), command_sub_color_[0], font_rondo_32_);
				DrawStringToHandle(COMMAND_SUB_X_, COMMAND_LIST_Y_[1], scene_->skill_[1]->name_.c_str(), command_sub_color_[1], font_rondo_32_);
				if (!scene_->boss_->main_command_) {
					//説明文
					DrawStringToHandle(COMMAND_EXP_X_, COMMAND_LIST_Y_[0], scene_->skill_[scene_->boss_->index_sub_]->exp1_.c_str(), BROWN, font_rondo_32_);
					DrawStringToHandle(COMMAND_EXP_X_, COMMAND_LIST_Y_[1], scene_->skill_[scene_->boss_->index_sub_]->exp2_.c_str(), BROWN, font_rondo_32_);
					DrawStringToHandle(COMMAND_EXP_X_, COMMAND_LIST_Y_[2], scene_->skill_[scene_->boss_->index_sub_]->exp3_.c_str(), BROWN, font_rondo_32_);
					DrawFormatStringToHandle(COMMAND_EXP_X_, COMMAND_LIST_Y_[3], BROWN, font_rondo_32_, "消費MP:%d", scene_->skill_[scene_->boss_->index_sub_]->mp_);
				}
				break;
			case 1:
				DrawStringToHandle(COMMAND_SUB_X_, COMMAND_LIST_Y_[0], scene_->skill_[2 + 0 + scene_->boss_->index_sub_list_]->name_.c_str(), command_sub_color_[0], font_rondo_32_);
				DrawStringToHandle(COMMAND_SUB_X_, COMMAND_LIST_Y_[1], scene_->skill_[2 + 1 + scene_->boss_->index_sub_list_]->name_.c_str(), command_sub_color_[1], font_rondo_32_);
				DrawStringToHandle(COMMAND_SUB_X_, COMMAND_LIST_Y_[2], scene_->skill_[2 + 2 + scene_->boss_->index_sub_list_]->name_.c_str(), command_sub_color_[2], font_rondo_32_);
				DrawStringToHandle(COMMAND_SUB_X_, COMMAND_LIST_Y_[3], scene_->skill_[2 + 3 + scene_->boss_->index_sub_list_]->name_.c_str(), command_sub_color_[3], font_rondo_32_);
				if (!scene_->boss_->main_command_) {
					//説明文
					DrawStringToHandle(COMMAND_EXP_X_, COMMAND_LIST_Y_[0], scene_->skill_[2 + scene_->boss_->index_sub_ + scene_->boss_->index_sub_list_]->exp1_.c_str(), BROWN, font_rondo_32_);
					DrawStringToHandle(COMMAND_EXP_X_, COMMAND_LIST_Y_[1], scene_->skill_[2 + scene_->boss_->index_sub_ + scene_->boss_->index_sub_list_]->exp2_.c_str(), BROWN, font_rondo_32_);
					DrawStringToHandle(COMMAND_EXP_X_, COMMAND_LIST_Y_[2], scene_->skill_[2 + scene_->boss_->index_sub_ + scene_->boss_->index_sub_list_]->exp3_.c_str(), BROWN, font_rondo_32_);
					DrawFormatStringToHandle(COMMAND_EXP_X_, COMMAND_LIST_Y_[3], BROWN, font_rondo_32_, "消費MP:%d", scene_->skill_[2 + scene_->boss_->index_sub_ + scene_->boss_->index_sub_list_]->mp_);
				}
				break;
			case 2:

				break;
			case 3:
				break;
			}
		}
		//攻撃表示ウィンドウ
		DrawRotaGraph(attack_window_x_[0], ATTACK_WINDOW_Y_[0], 1.2f, 0, window_attack_player_, true);
		DrawRotaGraph(attack_window_x_[1], ATTACK_WINDOW_Y_[1], 1.2f, 0, window_attack_player_, true);
		DrawRotaGraph(attack_window_x_[2], ATTACK_WINDOW_Y_[2], 1.2f, 0, window_attack_player_, true);
		//攻撃表示文字
		if (scene_->boss_->select_num_ >= 1) DrawStringToHandle(attack_str_x_[0], ATTACK_STR_Y_[0], scene_->skill_[scene_->boss_->player_action_[0]]->name_.c_str(), BROWN, font_rondo_24_);
		if (scene_->boss_->select_num_ >= 2) DrawStringToHandle(attack_str_x_[1], ATTACK_STR_Y_[1], scene_->skill_[scene_->boss_->player_action_[1]]->name_.c_str(), BROWN, font_rondo_24_);
		if (scene_->boss_->select_num_ >= 3) DrawStringToHandle(attack_str_x_[2], ATTACK_STR_Y_[2], scene_->skill_[scene_->boss_->player_action_[2]]->name_.c_str(), BROWN, font_rondo_24_);
	}

	//プレイヤーゲージ表示
	DrawWindow(STATUS_X_, STATUS_Y_, STATUS_W_, STATUS_H_, eBrown);
	DrawGauge(STATUS_GAUGE_X1_, STATUS_Y_, GAUGE_IMG_W_, GAUGE_IMG_H_, 1.5f, scene_->hp_, scene_->hp_max_, eRed);
	DrawGauge(STATUS_GAUGE_X2_, STATUS_Y_, GAUGE_IMG_W_, GAUGE_IMG_H_, 1.5f, scene_->mp_, scene_->mp_max_, eBlue);
	DrawFormatStringToHandle(STATUS_NUM_X1_, STATUS_NUM_Y_, BROWN, font_rondo_32_, "HP %d / %d", scene_->hp_, scene_->hp_max_);
	DrawFormatStringToHandle(STATUS_NUM_X2_, STATUS_NUM_Y_, BROWN, font_rondo_32_, "MP %d / %d", scene_->mp_, scene_->mp_max_);

	//コンボ数表示
	if (scene_->combo_ != 0) {
		DrawStringToHandle(COMBO_X_, COMBO_Y_, "Combo!", -1, font_rondo_32_);
		DrawFormatStringToHandle(COMBO_NUM_X_, COMBO_NUM_Y_, -1, font_rondo_64_, "%d", scene_->combo_);
	}

	//スコア表示
	DrawWindow(SCORE_WINDOW_X_, SCORE_WINDOW_Y_, SCORE_WINDOW_W_, SCORE_WINDOW_H_, eGlay);
	DrawStringToHandle(SCORE_X_, SCORE_Y_, "Score", -1, font_rondo_32_);
	DrawFormatStringToHandle(SCORE_NUM_X_, SCORE_NUM_Y_, -1, font_rondo_32_, "%7.0d", scene_->score_);

}

void Ui::getWindow() {
	//白
	window_top_left_[eWhite] = LoadGraph("graphics/ui/window_a/window_a_001.png");
	window_top_center_[eWhite] = LoadGraph("graphics/ui/window_a/window_a_002.png");
	window_top_right_[eWhite] = LoadGraph("graphics/ui/window_a/window_a_003.png");
	window_left_[eWhite] = LoadGraph("graphics/ui/window_a/window_a_004.png");
	window_center_[eWhite] = LoadGraph("graphics/ui/window_a/window_a_005.png");
	window_right_[eWhite] = LoadGraph("graphics/ui/window_a/window_a_006.png");
	window_bot_left_[eWhite] = LoadGraph("graphics/ui/window_a/window_a_007.png");
	window_bot_center_[eWhite] = LoadGraph("graphics/ui/window_a/window_a_008.png");
	window_bot_right_[eWhite] = LoadGraph("graphics/ui/window_a/window_a_009.png");
	//茶色
	window_top_left_[eBrown] = LoadGraph("graphics/ui/window_b/window_b_001.png");
	window_top_center_[eBrown] = LoadGraph("graphics/ui/window_b/window_b_002.png");
	window_top_right_[eBrown] = LoadGraph("graphics/ui/window_b/window_b_003.png");
	window_left_[eBrown] = LoadGraph("graphics/ui/window_b/window_b_004.png");
	window_center_[eBrown] = LoadGraph("graphics/ui/window_b/window_b_005.png");
	window_right_[eBrown] = LoadGraph("graphics/ui/window_b/window_b_006.png");
	window_bot_left_[eBrown] = LoadGraph("graphics/ui/window_b/window_b_007.png");
	window_bot_center_[eBrown] = LoadGraph("graphics/ui/window_b/window_b_008.png");
	window_bot_right_[eBrown] = LoadGraph("graphics/ui/window_b/window_b_009.png");
	//灰色
	window_top_left_[eGlay] = LoadGraph("graphics/ui/window_c/window_c_001.png");
	window_top_center_[eGlay] = LoadGraph("graphics/ui/window_c/window_c_002.png");
	window_top_right_[eGlay] = LoadGraph("graphics/ui/window_c/window_c_003.png");
	window_left_[eGlay] = LoadGraph("graphics/ui/window_c/window_c_004.png");
	window_center_[eGlay] = LoadGraph("graphics/ui/window_c/window_c_005.png");
	window_right_[eGlay] = LoadGraph("graphics/ui/window_c/window_c_006.png");
	window_bot_left_[eGlay] = LoadGraph("graphics/ui/window_c/window_c_007.png");
	window_bot_center_[eGlay] = LoadGraph("graphics/ui/window_c/window_c_008.png");
	window_bot_right_[eGlay] = LoadGraph("graphics/ui/window_c/window_c_009.png");
	//黒
	window_top_left_[eBlack] = LoadGraph("graphics/ui/window_d/window_d_001.png");
	window_top_center_[eBlack] = LoadGraph("graphics/ui/window_d/window_d_002.png");
	window_top_right_[eBlack] = LoadGraph("graphics/ui/window_d/window_d_003.png");
	window_left_[eBlack] = LoadGraph("graphics/ui/window_d/window_d_004.png");
	window_center_[eBlack] = LoadGraph("graphics/ui/window_d/window_d_005.png");
	window_right_[eBlack] = LoadGraph("graphics/ui/window_d/window_d_006.png");
	window_bot_left_[eBlack] = LoadGraph("graphics/ui/window_d/window_d_007.png");
	window_bot_center_[eBlack] = LoadGraph("graphics/ui/window_d/window_d_008.png");
	window_bot_right_[eBlack] = LoadGraph("graphics/ui/window_d/window_d_009.png");
}


void Ui::DrawGauge(int x, int y, int width, int height, double exrate, int num, int max, int color) {
	int gauge_x1 = x - width * exrate / 2;
	int gauge_y1 = y - height * exrate / 2;
	int gauge_y2 = y + height * exrate / 2;
	int gauge_x2 = gauge_x1 + width * exrate * ((double)num / (double)max);
	DrawRotaGraph(x, y, exrate, 0, hp_back_, true);
	DrawExtendGraph(gauge_x1, gauge_y1, gauge_x2, gauge_y2, hp_bar_[color], true);
	DrawRotaGraph(x, y, exrate, 0, hp_frame_, true);
}

void Ui::DrawGaugeProgress(int x, int y, int width, int height, double exrate, int num, int max, int color) {
	int gauge_x1 = x - width * exrate / 2;
	int gauge_y1 = y - height * exrate / 2;
	int gauge_y2 = y + height * exrate / 2;
	int gauge_x2 = gauge_x1 + width * exrate * ((double)num / (double)max);
	DrawRotaGraph(x, y, exrate, 0, hp_back_, true);
	DrawExtendGraph(gauge_x1, gauge_y1, gauge_x2, gauge_y2, hp_bar_[color], true);
	DrawRotaGraph(x, y, exrate, 0, hp_frame_, true);
	DrawRotaGraph(gauge_x2, y, exrate * 0.1f, 0, run_, true);
}

void Ui::DrawWindow(int x, int y, int width, int height, int color) {
	int center_x1 = x - width / 2 + 20;
	int center_x2 = x + width / 2 - 20;
	int center_y1 = y - height / 2 + 20;
	int center_y2 = y + height / 2 - 20;
	DrawExtendGraph(center_x1, center_y1, center_x2, center_y2, window_center_[color], true); //中心
	DrawExtendGraph(center_x1 - 20, center_y1, center_x1, center_y2, window_left_[color], true); //左
	DrawExtendGraph(center_x2, center_y1, center_x2 + 20, center_y2, window_right_[color], true); //右
	DrawExtendGraph(center_x1, center_y1 - 20, center_x2, center_y1, window_top_center_[color], true); //上
	DrawExtendGraph(center_x1, center_y2, center_x2, center_y2 + 20, window_bot_center_[color], true); //下
	DrawExtendGraph(center_x1 - 20, center_y1 - 20, center_x1, center_y1, window_top_left_[color], true); //左上
	DrawExtendGraph(center_x2, center_y1 - 20, center_x2 + 20, center_y1, window_top_right_[color], true); //右上
	DrawExtendGraph(center_x1 - 20, center_y2, center_x1, center_y2 + 20, window_bot_left_[color], true); //左下
	DrawExtendGraph(center_x2, center_y2, center_x2 + 20, center_y2 + 20, window_bot_right_[color], true); //右下
}

SubUiJudge::SubUiJudge(ScenePlay* scene, int judge, int lane) {
	scene_ = scene;
	judge_ = judge;
	lane_ = lane;
}

void SubUiJudge::update(float delta_time) {
	elapsed_++;
	judge_y_ -= 1.0f;
	if (elapsed_ >= RENDER_TIME_) alive_ = false;
}

void SubUiJudge::render() {
	switch (judge_) {
	case perfect:
		DrawStringToHandle(JUDGE_X_[lane_], judge_y_, "Perfect!!", scene_->ui_->YELLOW, scene_->ui_->font_rondo_32_);
		break;
	case good:
		DrawStringToHandle(JUDGE_X_[lane_], judge_y_, "Good!", -1, scene_->ui_->font_rondo_32_);
		break;
	case miss:
		DrawStringToHandle(JUDGE_X_[lane_], judge_y_, "Miss", scene_->ui_->RED, scene_->ui_->font_rondo_32_);
		break;
	}
}