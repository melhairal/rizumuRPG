#include "gm_field_ui.h"
#include "scene/gm_scene_field.h"
#include "3d_object/gm_3d_sprite.h"

FieldUi::FieldUi(SceneField* scene) {
	scene_ = scene;

	//�t�H���g�ǂݍ���
	getFont();

	//���b�Z�[�W�E�B���h�E�摜�ǂݍ���
	img_message_ = LoadGraph("graphics/ui/message.png");

	//�E�B���h�E�摜�ǂݍ���
	getWindow();
}

void FieldUi::update(float delta_time) {
	//�Z���t����
	if (sprite_ != nullptr) {
		updateComment();
	}

	//���j���[��ʐ���
	if (scene_->isMenu_) {
		updateMenu();
	}

}

void FieldUi::render() {
	//�Z���t�`��
	if (sprite_ != nullptr) {
		DrawRotaGraph(MESSAGE_WIN_X_, MESSAGE_WIN_Y_, 0.8f, 0, img_message_, true);
		DrawStringToHandle(MESSAGE_X_, MESSAGE_Y_, *sprite_->it, 0, font_pop_32_);
	}

	//���j���[��ʕ`��
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
	DrawExtendGraph(center_x1, center_y1, center_x2, center_y2, window_center_, true); //���S
	DrawExtendGraph(center_x1 - 20, center_y1, center_x1, center_y2, window_left_, true); //��
	DrawExtendGraph(center_x2, center_y1, center_x2 + 20, center_y2, window_right_, true); //�E
	DrawExtendGraph(center_x1, center_y1 - 20, center_x2, center_y1, window_top_center_, true); //��
	DrawExtendGraph(center_x1, center_y2, center_x2, center_y2 + 20, window_bot_center_, true); //��
	DrawExtendGraph(center_x1 - 20, center_y1 - 20, center_x1, center_y1, window_top_left_, true); //����
	DrawExtendGraph(center_x2, center_y1 - 20, center_x2 + 20, center_y1, window_top_right_, true); //�E��
	DrawExtendGraph(center_x1 - 20, center_y2, center_x1, center_y2 + 20, window_bot_left_, true); //����
	DrawExtendGraph(center_x2, center_y2, center_x2 + 20, center_y2 + 20, window_bot_right_, true); //�E��
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
	//���ڑI��
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


	//���ڑI���A���j���[����
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