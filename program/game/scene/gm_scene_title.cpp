#include "../gm_manager.h"
#include "gm_scene_title.h"
#include "gm_scene_field.h"
#include "gm_scene_map.h"


void SceneTitle::initialzie() {
	img_title_ = LoadGraph("graphics/title/title.jpg");
	font_rondo_32_ = LoadFontDataToHandle("font/Rondo32.dft", 0);

}

void SceneTitle::update(float delta_time)
{
	GameManager* mgr = GameManager::GetInstance();

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) {
		sel_--;
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)) {
		sel_++;
	}
	sel_ = std::clamp(sel_, 0, MAX_INDEX_ - 1);

	for (int i = 0; i < MAX_INDEX_; i++) {
		start_color_[i] = 0;
		start_x_[i] = DEF_X_;
	}
	start_color_[sel_] = YELLOW;
	start_x_[sel_] = SEL_X_;


	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		switch (sel_) {
		case 0:
			mgr->chengeScene(new SceneField());
			break;
		case 1:
			break;
		case 2:
			break;
		}
	}
}

void SceneTitle::render()
{
	DrawRotaGraph(DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT / 2, 0.75f, 0, img_title_, true);
	DrawStringToHandle(start_x_[0], start_y_[0], "‚Í‚¶‚ß‚©‚ç", start_color_[0], font_rondo_32_);
	DrawStringToHandle(start_x_[1], start_y_[1], "‚Â‚Ã‚«‚©‚ç", start_color_[1], font_rondo_32_);
	DrawStringToHandle(start_x_[2], start_y_[2], "ƒIƒvƒVƒ‡ƒ“", start_color_[2], font_rondo_32_);
}
