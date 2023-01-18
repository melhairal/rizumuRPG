#include "gm_sheet_music.h"
#include "scene/gm_scene_play.h"
#include "object/gm_object_enemy.h"
#include "object/gm_object_ground.h"
#include "gm_camera.h"

Sheet::Sheet(ScenePlay* scene, std::string csv) {
	scene_ = scene;
	csv_ = tnl::LoadCsv(csv);
	bgm_ = LoadSoundMem(csv_[0][0].c_str());
	type_ = std::atoi(csv_[1][0].c_str());
}

void Sheet::update(float delta_time) {
	//BGM
	if (bgm_timer_ == START_INTERVAL_) {
		PlaySoundMem(bgm_, DX_PLAYTYPE_BACK);
	}
	if (bgm_timer_ <= START_INTERVAL_) {
		bgm_timer_++;
	}

	//ƒm[ƒcî•ñŽæ“¾
	if (csv_y_ < csv_.size()) {
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
	else {
		elapsed_++;
		if (elapsed_ < 120) {
			tnl::Vector3 rot = { tnl::ToRadian(-0.35f), 0, 0 };
			scene_->camera_->free_look_angle_xy_ += rot;
			scene_->player_->mesh_->rot_q_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(-0.35f));
			scene_->player_->mesh_->pos_.y += 0.05f;
			line_->alive_ = false;

			for (auto object : scene_->objects_) {
				object->move_ = false;
			}
		}
		else {

		}
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