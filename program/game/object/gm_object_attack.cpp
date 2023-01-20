#include "gm_object_attack.h"
#include "gm_object_effect.h"
#include "../scene/gm_scene_play.h"
#include "../gm_camera.h"
#include "../gm_ui.h"
#include "../gm_bgm.h"
#include "../gm_boss.h"

AttackNotes::AttackNotes(ScenePlay* scene, int lane) {
	scene_ = scene;
	lane_ = lane;
	getImage();
	mesh_ = dxe::Mesh::CreatePlane({ MESH_W_, MESH_H_, 0 });
	mesh_->setTexture(dxe::Texture::CreateFromFile(*it));
	it++;
	mesh_->pos_ = { POS_X_[lane_],POS_Y_,POS_Z_ };
	mesh_->rot_q_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(60));
}

void AttackNotes::flow(float speed) {
	mesh_->pos_.z -= speed;
	if (mesh_->pos_.z < DEAD_Z_) {
		scene_->subUis_.emplace_back(new SubUiJudge(scene_, miss, lane_));
		judge_ = miss;
		alive_ = false;
	}
}

bool AttackNotes::judgeKey() {
	if (mesh_->pos_.x == POS_X_[LL] && tnl::Input::IsKeyDownTrigger(eKeys::KB_D)) return true;
	if (mesh_->pos_.x == POS_X_[L] && tnl::Input::IsKeyDownTrigger(eKeys::KB_F)) return true;
	if (mesh_->pos_.x == POS_X_[R] && tnl::Input::IsKeyDownTrigger(eKeys::KB_J)) return true;
	if (mesh_->pos_.x == POS_X_[RR] && tnl::Input::IsKeyDownTrigger(eKeys::KB_K)) return true;
	return false;
}

void AttackNotes::judge() {
	if (mesh_->pos_.z < JUDGE_Z_ + RANGE_PERFECT_ && mesh_->pos_.z >= JUDGE_Z_ - RANGE_PERFECT_) {
		if (judgeKey()) {
			//パーフェクト判定処理
			scene_->subUis_.emplace_back(new SubUiJudge(scene_, perfect, lane_));
			scene_->actors_.emplace_back(new EffectPerfect(scene_, lane_));
			scene_->bgm_->perfect_ = true;
			judge_ = perfect;
			alive_ = false;
		}
	}
	else if (mesh_->pos_.z < JUDGE_Z_ + RANGE_GOOD_ && mesh_->pos_.z >= JUDGE_Z_ - RANGE_GOOD_) {
		if (judgeKey()) {
			//グッド判定処理
			scene_->subUis_.emplace_back(new SubUiJudge(scene_, good, lane_));
			scene_->actors_.emplace_back(new EffectGood(scene_, lane_));
			scene_->bgm_->perfect_ = true;
			judge_ = good;
			alive_ = false;
		}
	}
	else if (mesh_->pos_.z >= MISS_Z_ - RANGE_MISS_ && mesh_->pos_.z < JUDGE_Z_ + RANGE_GOOD_ + RANGE_MISS_) {
		if (judgeKey()) {
			//失敗判定処理
			scene_->subUis_.emplace_back(new SubUiJudge(scene_, miss, lane_));
			judge_ = miss;
			alive_ = false;
		}
	}
}

void AttackNotes::update(float delta_time) {
	judge();
	flow(scene_->NOTES_SPEED_);
}

void SkillBase::randomPop() {
	int r = rand() % 4;
	attacks_[num_] = scene_->actors_.emplace_back(new AttackNotes(scene_, r));
	num_++;
}

void SkillBase::checkJudge() {
	for (int i = 0; i < num_; ++i) {
		if (attacks_[i] == nullptr) continue;
		switch (attacks_[i]->judge_) {
		case AttackNotes::perfect:
			judges_[i] = AttackNotes::perfect;
			notesPerfect();
			attacks_[i] = nullptr;
			break;
		case AttackNotes::good:
			judges_[i] = AttackNotes::good;
			notesGood();
			attacks_[i] = nullptr;
			break;
		case AttackNotes::miss:
			judges_[i] = AttackNotes::miss;
			scene_->combo_ = 0;
			attacks_[i] = nullptr;
			break;
		}
	}
}

SkillNormalA::SkillNormalA(ScenePlay* scene) {
	scene_ = scene;
	name_ = NAME_;
	mp_ = MP_;
}

void SkillNormalA::update(float delta_time) {
	checkJudge();
	elapsed_++;
	if (elapsed_ >= INTERVAL_ && num_ < MAX_NUM_) {
		elapsed_ = 0;
		randomPop();
	}
	if (elapsed_ >= SKILL_INTERVAL_ && num_ == MAX_NUM_) {
		finish_ = true;
	}
}

void SkillNormalA::notesPerfect() {
	scene_->combo_++;
	if (scene_->boss_ != nullptr) scene_->boss_->hp_ -= 30;
}

void SkillNormalA::notesGood() {
	scene_->combo_++;
	if (scene_->boss_ != nullptr) scene_->boss_->hp_ -= 10;
}

SkillComboA::SkillComboA(ScenePlay* scene) {
	scene_ = scene;
	name_ = NAME_;
	mp_ = MP_;
}

void SkillComboA::update(float delta_time) {
	checkJudge();
	elapsed_++;
	if (elapsed_ >= INTERVAL_ && num_ < MAX_NUM_) {
		elapsed_ = 0;
		randomPop();
	}
	if (elapsed_ >= SKILL_INTERVAL_ && num_ == MAX_NUM_) {
		finish_ = true;
	}
}

void SkillComboA::notesPerfect() {
	scene_->combo_+= 3;
	if (scene_->boss_ != nullptr) scene_->boss_->hp_ -= 30;
}

void SkillComboA::notesGood() {
	scene_->combo_++;
	if (scene_->boss_ != nullptr) scene_->boss_->hp_ -= 10;
}