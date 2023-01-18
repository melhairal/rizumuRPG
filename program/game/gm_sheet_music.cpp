#include "gm_sheet_music.h"
#include "scene/gm_scene_play.h"
#include "object/gm_object_enemy.h"
#include "object/gm_object_ground.h"

#include <iostream>
#include <fstream>

using std::endl;
using std::ofstream;

ofstream ofs("csv/test.csv");  // ファイルパスを指定する

Sheet::Sheet(ScenePlay* scene) {
	scene_ = scene;
	csv_ = tnl::LoadCsv("csv/stage_2.csv");
	bgm_ = LoadSoundMem(csv_[0][0].c_str());
}

void Sheet::update(float delta_time) {
	//BGM
	if (bgm_timer_ == START_INTERVAL_) {
		PlaySoundMem(bgm_, DX_PLAYTYPE_BACK);
	}
	if (bgm_timer_ <= START_INTERVAL_) {
		bgm_timer_++;
	}

	//ノーツ情報取得
	if (csv_y_ < csv_.size()) {
		elapsed_++;
		if (elapsed_ >= INTERVAL_LINE_ / bpm_) {
			elapsed_ = 0;
			if (csv_y_ == 2) {
				scene_->objects_.emplace_back(new Line(scene_));
			}
			for (int i = 0; i < 4; i++) {
				int n = std::atoi(csv_[csv_y_][i].c_str());
				switch (n) {
				case 0:
					break;
				case 1:
					scene_->actors_.emplace_back(new EnemyPig(scene_, i));
					break;
				case 2:
					scene_->actors_.emplace_back(new EnemyRizard(scene_, i));
					break;
				case 3:
					scene_->actors_.emplace_back(new EnemyMash(scene_, i));
					break;
				case 4:
					scene_->actors_.emplace_back(new EnemyGrifin(scene_, i));
					break;
				}
			}
			csv_y_++;
		}
	}

	/*
	//ノーツ作成	//BGM
	if (bgm_timer_ == 0) {
		PlaySoundMem(bgm_, DX_PLAYTYPE_BACK);
	}
	if (bgm_timer_ <= 0) {
		bgm_timer_++;
	}
	elapsed_++;
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_D)) {
		save_ = 1;
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_F)) {
		save_ = 2;
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_J)) {
		save_ = 3;
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_K)) {
		save_ = 4;
	}
	if (elapsed_ >= INTERVAL_LINE_ / 10) {
		elapsed_ = 0;
		switch (save_) {
		case 0:
			ofs << 0 << ", " << 0 << ", " << 0 << ", " << 0 << ", " << endl;
			break;
		case 1:
			ofs << 1 << ", " << 0 << ", " << 0 << ", " << 0 << ", " << endl;
			break;
		case 2:
			ofs << 0 << ", " << 1 << ", " << 0 << ", " << 0 << ", " << endl;
			break;
		case 3:
			ofs << 0 << ", " << 0 << ", " << 1 << ", " << 0 << ", " << endl;
			break;
		case 4:
			ofs << 0 << ", " << 0 << ", " << 0 << ", " << 1 << ", " << endl;
			break;
		}
		save_ = 0;
	}

	*/

}