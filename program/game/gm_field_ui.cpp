#include "gm_field_ui.h"
#include "scene/gm_scene_field.h"
#include "3d_object/gm_3d_sprite.h"
#include "object/gm_object_attack.h"
#include "gm_item.h"

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
			DrawStringToHandle(LABEL_X_, LABEL_Y_[i], label_[i], label_color_[i], font_rondo_32_);
		}
		//ステータス表示
		if (menu_depth_ == 0) {
			DrawFormatStringToHandle(STATUS_X_[0], STATUS_Y_[0], BROWN, font_rondo_32_, "Lv");
			DrawFormatStringToHandle(STATUS_X_[0], STATUS_Y_[1], BROWN, font_rondo_32_, "HP");
			DrawFormatStringToHandle(STATUS_X_[0], STATUS_Y_[2], BROWN, font_rondo_32_, "ATK");
			DrawFormatStringToHandle(STATUS_X_[0], STATUS_Y_[3], BROWN, font_rondo_32_, "EXP");
			DrawFormatStringToHandle(STATUS_X_[0], STATUS_Y_[4], BROWN, font_rondo_32_, "次のレベル");
			DrawFormatStringToHandle(STATUS_X_[0], STATUS_Y_[5], BROWN, font_rondo_32_, "所持金");
			DrawFormatStringToHandle(STATUS_X_[1], STATUS_Y_[0], BROWN, font_rondo_32_, "%6.0d", scene_->player_lv_);
			DrawFormatStringToHandle(STATUS_X_[1], STATUS_Y_[1], BROWN, font_rondo_32_, "%6.0d", scene_->player_hp_);
			DrawFormatStringToHandle(STATUS_X_[1], STATUS_Y_[2], BROWN, font_rondo_32_, "%6.0d", scene_->player_atk_);
			DrawFormatStringToHandle(STATUS_X_[1], STATUS_Y_[3], BROWN, font_rondo_32_, "%6.0d", scene_->player_exp_);
			DrawFormatStringToHandle(STATUS_X_[1], STATUS_Y_[4], BROWN, font_rondo_32_, "%6.0d", scene_->UP_EXP_[scene_->player_lv_ - 1]);
			DrawFormatStringToHandle(STATUS_X_[1], STATUS_Y_[5], BROWN, font_rondo_32_, "%6.0d", scene_->player_monney_);
		}
		//スキル一覧
		if (menu_depth_ == 1 && sel_label_ == 0) {
			DrawStringToHandle(STATUS_X_[0], STATUS_Y_[0], scene_->skill_[sel_list_]->name_.c_str(), index_color_[0], font_rondo_32_);
			DrawStringToHandle(STATUS_X_[0], STATUS_Y_[1], scene_->skill_[sel_list_ + 1]->name_.c_str(), index_color_[1], font_rondo_32_);
			DrawStringToHandle(STATUS_X_[0], STATUS_Y_[2], scene_->skill_[sel_list_ + 2]->name_.c_str(), index_color_[2], font_rondo_32_);
			DrawStringToHandle(STATUS_X_[0], STATUS_Y_[3], scene_->skill_[sel_list_ + 3]->name_.c_str(), index_color_[3], font_rondo_32_);
			if (scene_->player_skills_ >= 5) DrawStringToHandle(STATUS_X_[0], STATUS_Y_[4], scene_->skill_[sel_list_ + 4]->name_.c_str(), index_color_[4], font_rondo_32_);
			DrawFormatStringToHandle(NUM_X_, STATUS_Y_[0], BROWN, font_rondo_32_, "MP:%d", scene_->skill_[sel_list_]->mp_);
			DrawFormatStringToHandle(NUM_X_, STATUS_Y_[1], BROWN, font_rondo_32_, "MP:%d", scene_->skill_[sel_list_ + 1]->mp_);
			DrawFormatStringToHandle(NUM_X_, STATUS_Y_[2], BROWN, font_rondo_32_, "MP:%d", scene_->skill_[sel_list_ + 2]->mp_);
			DrawFormatStringToHandle(NUM_X_, STATUS_Y_[3], BROWN, font_rondo_32_, "MP:%d", scene_->skill_[sel_list_ + 3]->mp_);
			if (scene_->player_skills_ >= 5) DrawFormatStringToHandle(NUM_X_, STATUS_Y_[4], BROWN, font_rondo_32_, "MP:%d", scene_->skill_[sel_list_ + 4]->mp_);
			//説明文
			drawWindow(WINDOW_SUB_X_, WINDOW_SUB_Y_, WINDOW_SUB_W_, WINDOW_SUB_H_);
			DrawStringToHandle(COMMENT_X_, COMMENT_Y_[0], scene_->skill_[sel_index_ + sel_list_]->exp1_.c_str(), BROWN, font_rondo_32_);
			DrawStringToHandle(COMMENT_X_, COMMENT_Y_[1], scene_->skill_[sel_index_ + sel_list_]->exp2_.c_str(), BROWN, font_rondo_32_);
			DrawStringToHandle(COMMENT_X_, COMMENT_Y_[2], scene_->skill_[sel_index_ + sel_list_]->exp3_.c_str(), BROWN, font_rondo_32_);
		}
		//アイテム一覧
		if (menu_depth_ == 1 && sel_label_ == 1) {
			if (item_num_ >= 1) DrawStringToHandle(STATUS_X_[0], STATUS_Y_[0], scene_->item_[scene_->items_[sel_list_]]->name_.c_str(), index_color_[0], font_rondo_32_);
			if (item_num_ >= 2) DrawStringToHandle(STATUS_X_[0], STATUS_Y_[1], scene_->item_[scene_->items_[sel_list_ + 1]]->name_.c_str(), index_color_[1], font_rondo_32_);
			if (item_num_ >= 3) DrawStringToHandle(STATUS_X_[0], STATUS_Y_[2], scene_->item_[scene_->items_[sel_list_ + 2]]->name_.c_str(), index_color_[2], font_rondo_32_);
			if (item_num_ >= 4) DrawStringToHandle(STATUS_X_[0], STATUS_Y_[3], scene_->item_[scene_->items_[sel_list_ + 3]]->name_.c_str(), index_color_[3], font_rondo_32_);
			if (item_num_ >= 5) DrawStringToHandle(STATUS_X_[0], STATUS_Y_[4], scene_->item_[scene_->items_[sel_list_ + 4]]->name_.c_str(), index_color_[4], font_rondo_32_);
			//説明文
			drawWindow(WINDOW_SUB_X_, WINDOW_SUB_Y_, WINDOW_SUB_W_, WINDOW_SUB_H_);
			DrawStringToHandle(COMMENT_X_, COMMENT_Y_[0], scene_->item_[scene_->items_[sel_index_ + sel_list_]]->ex1_.c_str(), BROWN, font_rondo_32_);
			DrawStringToHandle(COMMENT_X_, COMMENT_Y_[1], scene_->item_[scene_->items_[sel_index_ + sel_list_]]->ex2_.c_str(), BROWN, font_rondo_32_);
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
	//選択してる項目の色を更新
	for (int i = 0; i < LABEL_INDEX_MAX_; ++i) {
		label_color_[i] = BROWN;
	}
	label_color_[sel_label_] = YELLOW;

	//持ってるアイテムの数を取得
	if (menu_depth_ == 1 && sel_label_ == 1) {
		item_num_ = 0;
		for (int i = 0; i < 8; i++) {
			if (scene_->items_[i] != -1) {
				item_num_++;
			}
		}
	}

	//項目の中での選択
	if (menu_depth_ == 1) {
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) {
			if (sel_index_ > 0) {
				sel_index_--;
			}
			else {
				sel_list_--;
			}
		}
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)) {
			if (sel_index_ < INDEX_MAX_ - 1) {
				sel_index_++;
			}
			else {
				sel_list_++;
			}
		}
		switch (sel_label_) {
		case 0:
			if (scene_->player_skills_ < INDEX_MAX_) {
				sel_index_ = std::clamp(sel_index_, 0, scene_->player_skills_ - 1);
				sel_list_ = std::clamp(sel_list_, 0, 0);
			}
			else {
				sel_index_ = std::clamp(sel_index_, 0, INDEX_MAX_ - 1);
				sel_list_ = std::clamp(sel_list_, 0, scene_->player_skills_ - INDEX_MAX_);
			}
			break;
		case 1:
			if (item_num_ < INDEX_MAX_) {
				sel_index_ = std::clamp(sel_index_, 0, item_num_ - 1);
				sel_list_ = std::clamp(sel_list_, 0, 0);
			}
			else {
				sel_index_ = std::clamp(sel_index_, 0, INDEX_MAX_ - 1);
				sel_list_ = std::clamp(sel_list_, 0, item_num_ - INDEX_MAX_);
			}
			break;
		default:
			sel_index_ = std::clamp(sel_index_, 0, 0);
		}
	}

	//選択してる項目の色を更新
	for (int i = 0; i < INDEX_MAX_; ++i) {
		index_color_[i] = BROWN;
	}
	index_color_[sel_index_] = YELLOW;


	//ゲーム終了
	if (sel_label_ == 4) {
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			scene_->finishGame();
		}
	}

	//項目選択、メニュー閉じる
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
		menu_depth_--;
		sel_index_ = 0;
		sel_list_ = 0;
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