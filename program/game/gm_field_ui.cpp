#include "gm_field_ui.h"
#include "scene/gm_scene_field.h"
#include "3d_object/gm_3d_sprite.h"
#include "object/gm_object_attack.h"
#include "gm_item.h"
#include "model/gm_anim_sprite3d.h"

FieldUi::FieldUi(SceneField* scene) {
	scene_ = scene;

	//フォント読み込み
	getFont();

	//メッセージウィンドウ画像読み込み
	img_message_ = LoadGraph("graphics/ui/message.png");
	img_button_[0] = LoadGraph("graphics/ui/menu_button_1.png");
	img_button_[1] = LoadGraph("graphics/ui/menu_button_2.png");

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

	//ショップ制御
	if (scene_->isShop_) {
		updateShop();
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
			DrawFormatStringToHandle(NUM_X_, STATUS_Y_[0], index_color_[0], font_rondo_32_, "MP:%d", scene_->skill_[sel_list_]->mp_);
			DrawFormatStringToHandle(NUM_X_, STATUS_Y_[1], index_color_[1], font_rondo_32_, "MP:%d", scene_->skill_[sel_list_ + 1]->mp_);
			DrawFormatStringToHandle(NUM_X_, STATUS_Y_[2], index_color_[2], font_rondo_32_, "MP:%d", scene_->skill_[sel_list_ + 2]->mp_);
			DrawFormatStringToHandle(NUM_X_, STATUS_Y_[3], index_color_[3], font_rondo_32_, "MP:%d", scene_->skill_[sel_list_ + 3]->mp_);
			if (scene_->player_skills_ >= 5) DrawFormatStringToHandle(NUM_X_, STATUS_Y_[4], index_color_[4], font_rondo_32_, "MP:%d", scene_->skill_[sel_list_ + 4]->mp_);
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
			if (item_num_ >= 1) {
				drawWindow(WINDOW_SUB_X_, WINDOW_SUB_Y_, WINDOW_SUB_W_, WINDOW_SUB_H_);
				DrawStringToHandle(COMMENT_X_, COMMENT_Y_[0], scene_->item_[scene_->items_[sel_index_ + sel_list_]]->ex1_.c_str(), BROWN, font_rondo_32_);
				DrawStringToHandle(COMMENT_X_, COMMENT_Y_[1], scene_->item_[scene_->items_[sel_index_ + sel_list_]]->ex2_.c_str(), BROWN, font_rondo_32_);
			}
			if (item_num_ == 0) DrawStringToHandle(STATUS_X_[0], STATUS_Y_[0], "なし", index_color_[0], font_rondo_32_);
		}
	}

	//ショップ画面表示
	if (scene_->isShop_) {
		drawWindow(WINDOW_MONEY_X_, WINDOW_MONEY_Y_, WINDOW_MONEY_W_, WINDOW_MONEY_H_);
		DrawFormatStringToHandle(MONEY_X_, MONEY_Y_, -1, font_rondo_32_, "%d G", scene_->player_monney_);
		drawWindow(WINDOW_LABEL_X_, WINDOW_LABEL_Y_, WINDOW_LABEL_W_, WINDOW_LABEL_H_);
		drawWindow(WINDOW_MAIN_X_, WINDOW_MAIN_Y_, WINDOW_MAIN_W_, WINDOW_MAIN_H_);
		for (int i = 0; i < SHOP_LABEL_INDEX_MAX_; ++i) {
			DrawStringToHandle(LABEL_X_, LABEL_Y_[i], shop_label_[i], shop_label_color_[i], font_rondo_32_);
		}
		//購入
		if (shop_sel_label_ == 0) {
			for (int i = 0; i < 5; ++i) {
				DrawStringToHandle(STATUS_X_[0], STATUS_Y_[i], scene_->item_[i]->name_.c_str(), shop_index_color_[i], font_rondo_32_);
				DrawFormatStringToHandle(NUM_X_, STATUS_Y_[i], shop_index_color_[i], font_rondo_32_, "%d G", scene_->item_[i]->buy_);
			}
			//説明文
			drawWindow(WINDOW_SUB_X_, WINDOW_SUB_Y_, WINDOW_SUB_W_, WINDOW_SUB_H_);
			DrawStringToHandle(COMMENT_X_, COMMENT_Y_[0], scene_->item_[shop_sel_index_]->ex1_.c_str(), BROWN, font_rondo_32_);
			DrawStringToHandle(COMMENT_X_, COMMENT_Y_[1], scene_->item_[shop_sel_index_]->ex2_.c_str(), BROWN, font_rondo_32_);
			//コメント
			if (shop_depth_ == 2) {
				DrawRotaGraph(MESSAGE_WIN_X_, MESSAGE_WIN_Y_, 0.8f, 0, img_message_, true);
				DrawStringToHandle(MESSAGE_X_, MESSAGE_Y_, shop_coment_[shop_check_], 0, font_pop_32_);
				if (shop_check_ == 0) {
					if (shop_sel_check_ == 0) {
						DrawRotaGraph(WINDOW_CHECK_X_[0], WINDOW_CHECK_Y_, 1.2f, 0, img_button_[0], true);
						DrawRotaGraph(WINDOW_CHECK_X_[1], WINDOW_CHECK_Y_, 1.2f, 0, img_button_[1], true);
					}
					else {
						DrawRotaGraph(WINDOW_CHECK_X_[0], WINDOW_CHECK_Y_, 1.2f, 0, img_button_[1], true);
						DrawRotaGraph(WINDOW_CHECK_X_[1], WINDOW_CHECK_Y_, 1.2f, 0, img_button_[0], true);
					}
					DrawStringToHandle(CHECK_X_[0], CHECK_Y_, "はい", shop_check_color_[0], font_pop_32_);
					DrawStringToHandle(CHECK_X_[1], CHECK_Y_, "いいえ", shop_check_color_[1], font_pop_32_);
				}
			}
		}
		//売却
		if (shop_sel_label_ == 1) {
			for (int i = 0; i < 8; i++) {
				if (item_num_ >= i + 1) {
					DrawStringToHandle(STATUS_X_[0], STATUS_Y_[i], scene_->item_[scene_->items_[i]]->name_.c_str(), shop_index_color_[i], font_rondo_32_);
					DrawFormatStringToHandle(NUM_X_, STATUS_Y_[i], shop_index_color_[i], font_rondo_32_, "%7.0d G", scene_->item_[scene_->items_[i]]->sell_);
				}
			}
			if (item_num_ == 0) {
				DrawStringToHandle(STATUS_X_[0], STATUS_Y_[0], "なし", shop_index_color_[0], font_rondo_32_);
			}
			//コメント
			if (shop_depth_ == 2) {
				DrawRotaGraph(MESSAGE_WIN_X_, MESSAGE_WIN_Y_, 0.8f, 0, img_message_, true);
				DrawStringToHandle(MESSAGE_X_, MESSAGE_Y_, shop_coment_[3], 0, font_pop_32_);
				if (shop_check_ == 3) {
					if (shop_sel_check_ == 0) {
						DrawRotaGraph(WINDOW_CHECK_X_[0], WINDOW_CHECK_Y_, 1.2f, 0, img_button_[0], true);
						DrawRotaGraph(WINDOW_CHECK_X_[1], WINDOW_CHECK_Y_, 1.2f, 0, img_button_[1], true);
					}
					else {
						DrawRotaGraph(WINDOW_CHECK_X_[0], WINDOW_CHECK_Y_, 1.2f, 0, img_button_[1], true);
						DrawRotaGraph(WINDOW_CHECK_X_[1], WINDOW_CHECK_Y_, 1.2f, 0, img_button_[0], true);
					}
					DrawStringToHandle(CHECK_X_[0], CHECK_Y_, "はい", shop_check_color_[0], font_pop_32_);
					DrawStringToHandle(CHECK_X_[1], CHECK_Y_, "いいえ", shop_check_color_[1], font_pop_32_);
				}
			}
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
			if (item_num_ == 0) {
				sel_index_ = std::clamp(sel_index_, 0, 0);
				sel_list_ = std::clamp(sel_list_, 0, 0);
			}
			else if (item_num_ < INDEX_MAX_) {
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
			break;
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

void FieldUi::updateShop() {
	//持ってるアイテムの数を取得
	item_num_ = 0;
	for (int i = 0; i < 8; i++) {
		if (scene_->items_[i] != -1) {
			item_num_++;
		}
	}
	//項目選択
	if (shop_depth_ == 0) {
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) {
			shop_sel_label_--;
		}
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)) {
			shop_sel_label_++;
		}
		shop_sel_label_ = std::clamp(shop_sel_label_, 0, SHOP_LABEL_INDEX_MAX_ - 1);
	}
	//選択してる項目の色を更新
	for (int i = 0; i < SHOP_LABEL_INDEX_MAX_; ++i) {
		shop_label_color_[i] = BROWN;
	}
	shop_label_color_[shop_sel_label_] = YELLOW;

	//項目の中での選択
	if (shop_depth_ == 1) {
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) {
			shop_sel_index_--;
		}
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)) {
			shop_sel_index_++;
		}
		switch (shop_sel_label_) {
		case 0:
			shop_sel_index_ = std::clamp(shop_sel_index_, 0, 4);
			break;
		case 1:
			if (item_num_ == 0) {
				shop_sel_index_ = std::clamp(shop_sel_index_, 0, 0);
			}
			else {
				shop_sel_index_ = std::clamp(shop_sel_index_, 0, item_num_ - 1);
			}
			break;
		default:
			shop_sel_index_ = std::clamp(shop_sel_index_, 0, 0);
			break;
		}
	}
	//選択してる項目の色を更新
	for (int i = 0; i < SHOP_INDEX_MAX_; ++i) {
		shop_index_color_[i] = BROWN;
	}
	if (shop_depth_ == 1) shop_index_color_[shop_sel_index_] = YELLOW;

	//最終確認
	if (shop_depth_ == 2 && (shop_check_ == 0 || shop_check_ == 3)) {
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_LEFT)) {
			shop_sel_check_ = 0;
		}
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RIGHT)) {
			shop_sel_check_ = 1;
		}
	}
	for (int i = 0; i < 2; ++i) {
		shop_check_color_[i] = -1;
	}
	shop_check_color_[shop_sel_check_] = BROWN;

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
		shop_depth_--;
		if (shop_depth_ != 2) shop_sel_index_ = 0;
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		if (shop_depth_ == 2) {
			switch (shop_sel_label_) {
			case 0:
				if (shop_check_ == 0 && shop_sel_check_ == 0) {
					scene_->player_monney_ -= scene_->item_[shop_sel_index_]->buy_;
					scene_->items_[item_num_] = shop_sel_index_;
					item_num_++;
				}
				shop_depth_--;
				break;
			case 1:
				if (shop_sel_check_ == 0) {
					scene_->player_monney_ += scene_->item_[scene_->items_[shop_sel_index_]]->sell_;
					if (shop_sel_index_ == item_num_ - 1) {
						scene_->items_[shop_sel_index_] = -1;
						item_num_--;
					}
					else {
						int i = 0;
						while (shop_sel_index_ + i < item_num_ - 1) {
							scene_->items_[shop_sel_index_ + i] = scene_->items_[shop_sel_index_ + i + 1];
							i++;
						}
						scene_->items_[shop_sel_index_ + i] = -1;
						item_num_--;
					}
				}
				if (item_num_ == 0) {
					shop_depth_ = 0;
				}
				else {
					shop_depth_--;
				}
				break;
			}
		}
		else if (shop_depth_ == 1) {
			shop_depth_++;
			switch (shop_sel_label_) {
			case 0 :
				if (item_num_ == 8) {
					shop_check_ = 2;
				}
				else if (scene_->item_[shop_sel_index_]->buy_ > scene_->player_monney_) {
					shop_check_ = 1;
				}
				else {
					shop_sel_check_ = 0;
					shop_check_ = 0;
				}
				break;
			case 1:
				shop_check_ = 3;
				shop_sel_check_ = 0;
				break;
			}
		}
		else {
			if (item_num_ != 0 || shop_sel_label_ != 1) {
				shop_depth_++;
			}
		}
	}
	shop_depth_ = std::clamp(shop_depth_, -1, 2);
	//ショップ終了処理
	if (shop_depth_ == -1) {
		sprite_shop_->sprite_->rot_ = tnl::Quaternion::LookAtAxisY(sprite_shop_->sprite_->pos_, sprite_shop_->sprite_->pos_ + sprite_shop_->dir_[sprite_shop_->look_]);
		sprite_shop_->getSurface({ 32,32,32 });
		sprite_shop_->sprite_->update(0);
		sprite_shop_->isEvent_ = false;
		sprite_shop_ = nullptr;
		scene_->player_->move_ = true;
		shop_depth_ = 0;
		shop_sel_index_ = 0;
		shop_sel_label_ = 0;
		scene_->isShop_ = false;
	}
}