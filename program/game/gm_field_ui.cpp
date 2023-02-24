#include "gm_field_ui.h"
#include "scene/gm_scene_field.h"
#include "3d_object/gm_3d_sprite.h"

FieldUi::FieldUi(SceneField* scene) {
	scene_ = scene;

	//フォント読み込み
	font_rondo_16_ = LoadFontDataToHandle("font/Rondo16.dft", 0);
	font_rondo_24_ = LoadFontDataToHandle("font/Rondo24.dft", 0);
	font_rondo_32_ = LoadFontDataToHandle("font/Rondo32.dft", 0);
	font_rondo_64_ = LoadFontDataToHandle("font/Rondo64.dft", 0);
	font_rondo_128_ = LoadFontDataToHandle("font/Rondo128.dft", 0);
	font_pop_32_ = LoadFontDataToHandle("font/Novelpop32.dft", 0);

	//メッセージウィンドウ画像読み込み
	img_message_ = LoadGraph("graphics/ui/message.png");
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
	if (sprite_ != nullptr) {
		DrawRotaGraph(MESSAGE_WIN_X_, MESSAGE_WIN_Y_, 0.8f, 0, img_message_, true);
		DrawStringToHandle(MESSAGE_X_, MESSAGE_Y_, *sprite_->it, 0, font_pop_32_);
	}
}