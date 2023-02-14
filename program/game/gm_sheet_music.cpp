#include "gm_sheet_music.h"
#include "scene/gm_scene_play.h"
#include "object/gm_object_enemy.h"
#include "object/gm_object_ground.h"
#include "gm_bgm.h"
#include "gm_ui.h"
#include "gm_boss.h"

Sheet::Sheet(ScenePlay* scene, std::string csv) {
	scene_ = scene;
	csv_ = tnl::LoadCsv(csv);
	scene_->bgm_->bgm_stage_ = LoadSoundMem(csv_[0][0].c_str());
	type_ = std::atoi(csv_[1][0].c_str());
}

void Sheet::update(float delta_time) {
	//BGM
	if (bgm_timer_ == START_INTERVAL_) {
		PlaySoundMem(scene_->bgm_->bgm_stage_, DX_PLAYTYPE_BACK);
	}
	if (bgm_timer_ <= START_INTERVAL_) {
		bgm_timer_++;
	}

	//失敗フラグ
	if (scene_->hp_ == 0) {
		if (!init_lose_) {
			StopSoundMem(scene_->bgm_->bgm_stage_);
			PlaySoundMem(scene_->bgm_->sound_failed_, DX_PLAYTYPE_BACK);
			scene_->subUis_.emplace_back(new SubUiFailed(scene_));
			init_lose_ = true;
		}
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			lose_result_ = true;
		}
		return;
	}


	//ノーツ情報取得
	if (csv_y_ < csv_.size()) { //再生中
		elapsed_++;
		if (elapsed_ >= NODE_INTERVAL_) {
			elapsed_ = 0;
			if (csv_y_ == 2) {
				line_ = scene_->objects_.emplace_back(new Line(scene_));
			}
			for (int i = 0; i < 4; i++) {
				int n = std::atoi(csv_[csv_y_][i].c_str());
				createNotes(n, i);
			}
			csv_y_++;
		}
	}
	else { //再生終了
		StopSoundMem(scene_->bgm_->bgm_stage_);
		line_->alive_ = false;
		for (auto object : scene_->objects_) {
			object->alive_ = false;
		}
		scene_->boss_ = new Boss(scene_);
		alive_ = false;
	}

	// ========== デバッグ用 ==========
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_X)) {
		csv_y_ = csv_.size();
	}

}

void Sheet::createNotes(int id, int lane) {
	switch (type_) {
	case plains:
		switch (id) {
		case 0:
			break;
		case 1:
			scene_->actors_.emplace_back(new EnemyPig(scene_, lane));
			break;
		case 2:
			scene_->actors_.emplace_back(new EnemyRizard(scene_, lane));
			break;
		case 3:
			scene_->actors_.emplace_back(new EnemyMash(scene_, lane));
			break;
		case 4:
			scene_->actors_.emplace_back(new EnemyGrifin(scene_, lane));
			break;
		}
		break;

	case cave:
		switch (id) {
		case 0:
			break;
		case 1:
			scene_->actors_.emplace_back(new EnemyBad(scene_, lane));
			break;
		case 2:
			scene_->actors_.emplace_back(new EnemyMagician(scene_, lane));
			break;
		case 3:
			scene_->actors_.emplace_back(new EnemySnake(scene_, lane));
			break;
		case 4:
			scene_->actors_.emplace_back(new EnemySinigami(scene_, lane));
			break;
		}
		break;

	case sea:
		switch (id) {
		case 0:
			break;
		case 1:
			scene_->actors_.emplace_back(new EnemyJellyA(scene_, lane));
			break;
		case 2:
			scene_->actors_.emplace_back(new EnemyJellyB(scene_, lane));
			break;
		case 3:
			scene_->actors_.emplace_back(new EnemyJellyC(scene_, lane));
			break;
		}
		break;

	case forest:
		switch (id) {
		case 0:
			break;
		case 1:
			scene_->actors_.emplace_back(new EnemyKingPig(scene_, lane));
			break;
		case 2:
			scene_->actors_.emplace_back(new EnemyKingRizard(scene_, lane));
			break;
		case 3:
			scene_->actors_.emplace_back(new EnemyKingMash(scene_, lane));
			break;
		case 4:
			scene_->actors_.emplace_back(new EnemyKingGrifin(scene_, lane));
			break;
		}
		break;
	}
}