#include "gm_object_boss.h"
#include "gm_object_effect.h"
#include "../scene/gm_scene_play.h"
#include "../gm_camera.h"
#include "../gm_ui.h"
#include "../gm_bgm.h"

void BossEnemy::initialize(ScenePlay* scene) {
	scene_ = scene;
	getImage();
	mesh_ = dxe::Mesh::CreatePlane({ MESH_W_ * 2, MESH_H_ * 2, 0 });
	mesh_->setTexture(dxe::Texture::CreateFromFile(*it));
	it++;
	mesh_->pos_ = { POS_X_[L],POS_Y_ * 2,POS_Z_ };
	mesh_->rot_q_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(60));
}

BossDragon::BossDragon(ScenePlay* scene) {
	initialize(scene);
}

void BossNotes::initialize(ScenePlay* scene, int damage, int lane) {
	scene_ = scene;
	lane_ = lane;
	damage_ = damage;
	getImage();
	mesh_ = dxe::Mesh::CreatePlane({ MESH_W_, MESH_H_, 0 });
	mesh_->setTexture(dxe::Texture::CreateFromFile(*it));
	it++;
	mesh_->pos_ = { POS_X_[lane_],POS_Y_,POS_Z_ };
	mesh_->rot_q_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(60));
}

void BossNotes::flow(float speed) {
	mesh_->pos_.z -= speed;
	if (mesh_->pos_.z < DEAD_Z_) {
		alive_ = false;
	}
}

bool BossNotes::judgeKey() {
	if (mesh_->pos_.x != POS_X_[LL] && tnl::Input::IsKeyDownTrigger(eKeys::KB_D)) return true;
	if (mesh_->pos_.x != POS_X_[L] && tnl::Input::IsKeyDownTrigger(eKeys::KB_F)) return true;
	if (mesh_->pos_.x != POS_X_[R] && tnl::Input::IsKeyDownTrigger(eKeys::KB_J)) return true;
	if (mesh_->pos_.x != POS_X_[RR] && tnl::Input::IsKeyDownTrigger(eKeys::KB_K)) return true;
	return false;
}

void BossNotes::judge() {
	if (mesh_->pos_.z < JUDGE_Z_ + RANGE_PERFECT_ && mesh_->pos_.z >= JUDGE_Z_ - RANGE_PERFECT_ && judge_ != good && judge_ != perfect) {
		if (judgeKey()) {
			//パーフェクト判定処理
			scene_->subUis_.emplace_back(new SubUiJudge(scene_, perfect, lane_));
			scene_->actors_.emplace_back(new EffectPerfect(scene_, lane_));
			scene_->bgm_->perfect_ = true;
			judge_ = perfect;
			scene_->combo_++;
		}
	}
	else if (mesh_->pos_.z < JUDGE_Z_ + RANGE_GOOD_ && mesh_->pos_.z >= JUDGE_Z_ - RANGE_GOOD_ && judge_ != good && judge_ != perfect) {
		if (judgeKey()) {
			//グッド判定処理
			scene_->subUis_.emplace_back(new SubUiJudge(scene_, good, lane_));
			scene_->actors_.emplace_back(new EffectGood(scene_, lane_));
			scene_->bgm_->perfect_ = true;
			judge_ = good;
			scene_->combo_++;
		}
	}
	else if (mesh_->pos_.z >= MISS_Z_ - RANGE_MISS_ && mesh_->pos_.z < JUDGE_Z_ + RANGE_GOOD_ + RANGE_MISS_
		&& mesh_->pos_.x == scene_->player_->mesh_->pos_.x && judge_ != miss) {
		//失敗判定処理
		scene_->subUis_.emplace_back(new SubUiJudge(scene_, miss, lane_));
		judge_ = miss;
		scene_->hp_ -= damage_;
		scene_->combo_ = 0;
		alive_ = false;
	}
}

void BossNotes::judgeAll() {
	if (mesh_->pos_.z < JUDGE_Z_ + RANGE_PERFECT_ && mesh_->pos_.z >= JUDGE_Z_ - RANGE_PERFECT_ && judge_ != good && judge_ != perfect) {
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE) && mesh_->pos_.x == scene_->player_->mesh_->pos_.x) {
			//パーフェクト判定処理
			scene_->subUis_.emplace_back(new SubUiJudge(scene_, perfect, lane_));
			scene_->actors_.emplace_back(new EffectPerfect(scene_, lane_));
			scene_->bgm_->perfect_ = true;
			judge_ = perfect;
			scene_->combo_++;
			alive_ = false;
		}
	}
	else if (mesh_->pos_.z < JUDGE_Z_ + RANGE_GOOD_ && mesh_->pos_.z >= JUDGE_Z_ - RANGE_GOOD_ && judge_ != good && judge_ != perfect) {
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE) && mesh_->pos_.x == scene_->player_->mesh_->pos_.x) {
			//グッド判定処理
			scene_->subUis_.emplace_back(new SubUiJudge(scene_, good, lane_));
			scene_->actors_.emplace_back(new EffectGood(scene_, lane_));
			scene_->bgm_->perfect_ = true;
			judge_ = good;
			scene_->combo_++;
			alive_ = false;
		}
	}
	else if (mesh_->pos_.z >= MISS_Z_ - RANGE_MISS_ && mesh_->pos_.z < JUDGE_Z_ + RANGE_GOOD_ + RANGE_MISS_
		&& mesh_->pos_.x == scene_->player_->mesh_->pos_.x && judge_ != miss) {
		//失敗判定処理
		scene_->subUis_.emplace_back(new SubUiJudge(scene_, miss, lane_));
		judge_ = miss;
		scene_->hp_ -= damage_;
		scene_->combo_ = 0;
		alive_ = false;
	}
}

NotesWarning::NotesWarning(ScenePlay* scene, int damage, int lane) {
	initialize(scene, damage, lane);
}

void NotesWarning::update(float delta_time) {
	flow(scene_->NOTES_SPEED_);
	judge();
}

NotesWarningAll::NotesWarningAll(ScenePlay* scene, int damage, int lane) {
	initialize(scene, damage, lane);
}

void NotesWarningAll::update(float delta_time) {
	flow(scene_->NOTES_SPEED_);
	judgeAll();
}

NotesDragonBless::NotesDragonBless(ScenePlay* scene, int damage, int lane) {
	initialize(scene, damage, lane);
}

void NotesDragonBless::update(float delta_time) {
	flow(scene_->NOTES_SPEED_);
	judge();
}