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
	//セリフ制御
	if (sprite_ != nullptr) {
		updateComment();
	}

	//メニュー画面制御
	if (scene_->isMenu_) {
		updateMenu();
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
		for (int i = 0; i < LABEL_INDEX_MAX_; ++i) {
			DrawStringToHandle(LABEL_X_, LABEL_Y_[i], label_[i], label_color_[i], font_pop_32_);
		}
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

void FieldUi::updateComment() {
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

void FieldUi::updateMenu() {
	//項目選択
	if (menu_depth_ == 0) {
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) {
			sel_label_--;
		}
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)) {
			sel_label_++;
		}
		sel_label_ = std::clamp(sel_label_, 0, LABEL_INDEX_MAX_ - 1);
	}

	for (int i = 0; i < LABEL_INDEX_MAX_; ++i) {
		label_color_[i] = BROWN;
	}
	label_color_[sel_label_] = YELLOW;


	//項目選択、メニュー閉じる
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
		menu_depth_--;
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		menu_depth_++;
	}
	menu_depth_ = std::clamp(menu_depth_, -1, 1);
	if (menu_depth_ == -1) {
		scene_->isMenu_ = false;
		scene_->player_->move_ = true;
	}
}