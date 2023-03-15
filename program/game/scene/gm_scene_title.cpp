#include "../gm_manager.h"
#include "gm_scene_title.h"
#include "gm_scene_field.h"
#include "gm_scene_map.h"

SceneTitle::~SceneTitle() {
	InitGraph();
	InitMusicMem();
	InitFontToHandle();
}

void SceneTitle::initialzie() {
	img_title_ = LoadGraph("graphics/title/title_2.jpg");
	font_rondo_32_ = LoadFontDataToHandle("font/Rondo32.dft", 0);

	//BGMŽæ“¾
	bgm_ = LoadSoundMem("sound/title.mp3");
	se_select_ = LoadSoundMem("sound/select.mp3");
	PlaySoundMem(bgm_, DX_PLAYTYPE_LOOP);
}

void SceneTitle::update(float delta_time)
{
	GameManager* mgr = GameManager::GetInstance();

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) {
		PlaySoundMem(se_select_, DX_PLAYTYPE_BACK);
		sel_--;
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)) {
		PlaySoundMem(se_select_, DX_PLAYTYPE_BACK);
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
		PlaySoundMem(se_select_, DX_PLAYTYPE_BACK);
		switch (sel_) {
		case 0:
			StopSoundMem(bgm_);
			startFirst();
			mgr->chengeScene(new SceneField());
			break;
		case 1:
			StopSoundMem(bgm_);
			startContinue();
			mgr->chengeScene(new SceneField());
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

void SceneTitle::startFirst() {
	GameManager* mgr = GameManager::GetInstance();
	mgr->player_lv_ = 1;
	mgr->player_atk_ = 10;
	mgr->player_hp_ = 1000;
	mgr->player_mp_ = 0;
	mgr->player_exp_ = 0;
	mgr->player_monney_ = 500;
	mgr->player_skills_ = 2;
	mgr->flag_stage_ = 1;
	mgr->have_items_[0] = 0;
	mgr->have_items_[1] = 3;
	for (int i = 2; i < 8; i++) {
		mgr->have_items_[i] = -1;
	}
}

void SceneTitle::startContinue() {
	GameManager* mgr = GameManager::GetInstance();
	mgr->player_lv_ = 10;
	mgr->player_atk_ = 30;
	mgr->player_hp_ = 2000;
	mgr->player_mp_ = 0;
	mgr->player_exp_ = 50000;
	mgr->player_monney_ = 3000;
	mgr->player_skills_ = 8;
	mgr->flag_stage_ = 6;
	mgr->have_items_[0] = 0;
	mgr->have_items_[1] = 1;
	mgr->have_items_[2] = 1;
	mgr->have_items_[3] = 2;
	mgr->have_items_[4] = 2;
	mgr->have_items_[5] = 3;
	mgr->have_items_[6] = 3;
	mgr->have_items_[7] = 4;
}