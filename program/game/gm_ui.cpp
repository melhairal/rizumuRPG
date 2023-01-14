#include "gm_ui.h"
#include "scene/gm_scene_play.h"

Ui::Ui(ScenePlay* scene) {
	scene_ = scene;
	//フォント読み込み
	font_rondo_16_ = LoadFontDataToHandle("font/Rondo16.dft", 0);
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
}

void Ui::update(float delta_time) {

}

void Ui::render() {
	//進行メーター表示
	DrawGaugeProgress(HOME_HP_X_, HOME_HP_Y_, GAUGE_IMG_W_, GAUGE_IMG_H_, 2.0f, scene_->progress_, scene_->progress_max_, eYellow);

	//プレイヤーゲージ表示
	DrawGauge(PLAYER_GAUGE_X_, PLAYER_GAUGE_Y1_, GAUGE_IMG_W_, GAUGE_IMG_H_, 1.5f, scene_->hp_, scene_->hp_max_, eRed);
	DrawGauge(PLAYER_GAUGE_X_, PLAYER_GAUGE_Y2_, GAUGE_IMG_W_, GAUGE_IMG_H_, 1.5f, scene_->mp_, scene_->mp_max_, eBlue);

	//コンボ数表示
	if (scene_->combo_ != 0) {
		DrawStringToHandle(COMBO_X_, COMBO_Y_, "Combo!", -1, font_rondo_32_);
		DrawFormatStringToHandle(COMBO_NUM_X_, COMBO_NUM_Y_, -1, font_rondo_64_, "%d", scene_->combo_);
	}
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