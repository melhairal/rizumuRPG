#include "gm_field_ui.h"
#include "scene/gm_scene_field.h"
#include "3d_object/gm_3d_sprite.h"

FieldUi::FieldUi(SceneField* scene) {
	scene_ = scene;

	//フォント読み込み
	getFont();

	//メッセージウィンドウ画像読み込み
	img_message_ = LoadGraph("graphics/ui/message.png");

	//ウィンドウ画像読み込み
	getWindow();
}

void FieldUi::update(float delta_time) {
	if (sprite_ != nullptr) {
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			sprite_->it++;
			if (sprite_->it == sprite_->comment_.end()) {
				sprite_->it = sprite_->comment_.begin();
				sprite_->isComment_ = false;
				sprite_->isEvent_ = true;
				scene_->player_->isComment_ = false;
				sprite_ = nullptr;
			}
		}
	}
}

void FieldUi::render() {
	//セリフ描画
	if (sprite_ != nullptr) {
		DrawRotaGraph(MESSAGE_WIN_X_, MESSAGE_WIN_Y_, 0.8f, 0, img_message_, true);
		DrawStringToHandle(MESSAGE_X_, MESSAGE_Y_, *sprite_->it, 0, font_pop_32_);
	}

	//メニュー画面描画
	if (scene_->isMenu_) {
		drawWindow(WINDOW_LABEL_X_, WINDOW_LABEL_Y_, WINDOW_LABEL_W_, WINDOW_LABEL_H_);
		drawWindow(WINDOW_MAIN_X_, WINDOW_MAIN_Y_, WINDOW_MAIN_W_, WINDOW_MAIN_H_);
	}
}

void FieldUi::getFont() {
	font_rondo_16_ = LoadFontDataToHandle("font/Rondo16.dft", 0);
	font_rondo_24_ = LoadFontDataToHandle("font/Rondo24.dft", 0);
	font_rondo_32_ = LoadFontDataToHandle("font/Rondo32.dft", 0);
	font_rondo_64_ = LoadFontDataToHandle("font/Rondo64.dft", 0);
	font_rondo_128_ = LoadFontDataToHandle("font/Rondo128.dft", 0);
	font_pop_32_ = LoadFontDataToHandle("font/Novelpop32.dft", 0);
}

void FieldUi::getWindow() {
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

void FieldUi::drawWindow(int x, int y, int width, int height) {
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