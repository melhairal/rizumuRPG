#include <iostream>
#include <fstream>
#include "gm_make_sheet.h"
#include "object/gm_object_ground.h"
#include "scene/gm_scene_play.h"
#include "gm_camera.h"

using std::endl;
using std::ofstream;

ofstream ofs("csv/test.csv");  // ファイルパスを指定する

MakeSheet::~MakeSheet() {
	for (auto line : lines_) delete line;
}

MakeSheet::MakeSheet(ScenePlay* scene) {
	scene_ = scene;
	bgm_ = LoadSoundMem("sound/stage_1.mp3");
}

void MakeSheet::update(float delta_time) {
	//BGM
	if (bgm_timer_ == START_INTERVAL_) {
		save_ = true;
		PlaySoundMem(bgm_, DX_PLAYTYPE_BACK);
	}
	if (bgm_timer_ <= START_INTERVAL_) {
		bgm_timer_++;
	}

	//ノーツ作成
	elapsed_++;

	//キー入力を記憶
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_D)) {
		key_ = 1;
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_F)) {
		key_ = 2;
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_J)) {
		key_ = 3;
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_K)) {
		key_ = 4;
	}

	//csvに出力
	if (elapsed_ >= NODE_INTERVAL_) {
		elapsed_ = 0;
		if (line_num_ < LINE_NUM_MAX_) {
			lines_.emplace_back(new Line(scene_));
			line_num_++;
		}
		if (save_) {
			switch (key_) {
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
			key_ = 0;
		}
	}

	//全てのオブジェクトのアップデート
	for (auto lines_ : lines_) {
		if (lines_->move_)	lines_->update(delta_time);
	}
	//オブジェクトの生存フラグがfalseになったらデリート
	auto it_object = lines_.begin();
	while (it_object != lines_.end()) {
		if (!(*it_object)->alive_) {
			delete (*it_object);
			it_object = lines_.erase(it_object);
			continue;
		}
		it_object++;
	}
}

void MakeSheet::render() {
	for (auto line : lines_) {
		line->mesh_->render(scene_->camera_);
	}
}