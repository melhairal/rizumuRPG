#include "gm_object_enemy.h"
#include "../scene/gm_scene_play.h"
#include "../gm_camera.h"
#include "../gm_ui.h"

void EnemyBase::Initialize(ScenePlay* scene, int lane) {
	scene_ = scene;
	lane_ = lane;
	getImage();
	mesh_ = dxe::Mesh::CreatePlane({ MESH_W_, MESH_H_, 0 });
	mesh_->setTexture(dxe::Texture::CreateFromFile(*it));
	it++;
	mesh_->pos_ = { POS_X_[lane_],POS_Y_,POS_Z_ };
	mesh_->rot_q_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(60));
}

void EnemyBase::flow(float speed) {
	mesh_->pos_.z -= speed;
	if (mesh_->pos_.z < DEAD_Z_) {
		if (!isBullet && !miss_) {
			scene_->subUis_.emplace_back(new SubUiJudge(scene_, miss, lane_));
			scene_->combo_ = 0;
		}
		alive_ = false;
	}
}

void EnemyBase::shot(Actor* bullet) {
	scene_->actors_.emplace_back(bullet);
	bullet->mesh_->pos_ = mesh_->pos_;
}

bool EnemyBase::checkLane() {
	if (scene_->player_->mesh_->pos_.x == mesh_->pos_.x) return true;
	else return false;
}

void EnemyBase::checkJudge() {
	perfect_ = false;
	if (mesh_->pos_.z < JUDGE_Z_ + RANGE_PERFECT_ && mesh_->pos_.z >= JUDGE_Z_ - RANGE_PERFECT_) {
		perfect_ = true;
	}
	good_ = false;
	if (mesh_->pos_.z < JUDGE_Z_ + RANGE_GOOD_ && mesh_->pos_.z >= JUDGE_Z_ - RANGE_GOOD_) {
		good_ = true;
	}
}

bool EnemyBase::notesEnemyKey() {
	if (mesh_->pos_.x == POS_X_[LL] && tnl::Input::IsKeyDownTrigger(eKeys::KB_D)) return true;
	if (mesh_->pos_.x == POS_X_[L] && tnl::Input::IsKeyDownTrigger(eKeys::KB_F)) return true;
	if (mesh_->pos_.x == POS_X_[R] && tnl::Input::IsKeyDownTrigger(eKeys::KB_J)) return true;
	if (mesh_->pos_.x == POS_X_[RR] && tnl::Input::IsKeyDownTrigger(eKeys::KB_K)) return true;
	return false;
}

void EnemyBase::notesEnemy() {
	if (perfect_) {
		if (notesEnemyKey()) {
			//パーフェクト判定処理
			scene_->subUis_.emplace_back(new SubUiJudge(scene_, perfect, lane_));
			scene_->combo_++;
			alive_ = false;
		}
	}
	else if(good_) {
		if (notesEnemyKey()) {
			//グッド判定処理
			scene_->subUis_.emplace_back(new SubUiJudge(scene_, good, lane_));
			scene_->combo_++;
			alive_ = false;
		}
	}
	if (!miss_ && checkLane() && mesh_->pos_.z < MISS_Z_ && mesh_->pos_.z >= MISS_Z_ - RANGE_MISS_) {
		miss_ = true;
		//失敗判定処理
		scene_->subUis_.emplace_back(new SubUiJudge(scene_, miss, lane_));
		scene_->combo_ = 0;
	}
}

bool EnemyBase::notesBulletKey() {
	if (mesh_->pos_.x != POS_X_[LL] && tnl::Input::IsKeyDownTrigger(eKeys::KB_D)) return true;
	if (mesh_->pos_.x != POS_X_[L] && tnl::Input::IsKeyDownTrigger(eKeys::KB_F)) return true;
	if (mesh_->pos_.x != POS_X_[R] && tnl::Input::IsKeyDownTrigger(eKeys::KB_J)) return true;
	if (mesh_->pos_.x != POS_X_[RR] && tnl::Input::IsKeyDownTrigger(eKeys::KB_K)) return true;
	return false;
}

void EnemyBase::notesBullet() {
	if (perfect_) {
		if (notesBulletKey()) {
			//パーフェクト判定処理
			scene_->subUis_.emplace_back(new SubUiJudge(scene_, perfect, lane_));
			scene_->combo_++;
		}
	}
	else if (good_) {
		if (notesBulletKey()) {
			//グッド判定処理
			scene_->subUis_.emplace_back(new SubUiJudge(scene_, good, lane_));
			scene_->combo_++;
		}
	}
	if (!miss_ && checkLane() && mesh_->pos_.z < MISS_Z_ && mesh_->pos_.z >= MISS_Z_ - RANGE_MISS_) {
		miss_ = true;
		//失敗判定処理
		scene_->subUis_.emplace_back(new SubUiJudge(scene_, miss, lane_));
		scene_->combo_ = 0;
		alive_ = false;
	}
}

EnemyPig::EnemyPig(ScenePlay* scene, int lane) {
	//メッシュ初期化
	Initialize(scene, lane);
}

void EnemyPig::update(float delta_time) {
	checkJudge();
	notesEnemy();
	flow(SPEED_);
}

EnemyRizard::EnemyRizard(ScenePlay* scene, int lane) {
	//メッシュ初期化
	Initialize(scene, lane);
}

void EnemyRizard::update(float delta_time) {
	checkJudge();
	notesEnemy();

	if (mesh_->pos_.z < SHOT_Z_) {
		if (elapsed_ < TIME_STOP_) elapsed_++;
		if (elapsed_ == TIME_SHOT_) shot(new EnemyRizardBullet(scene_, lane_));
		if (elapsed_ == TIME_STOP_) flow(SPEED_);
	}
	else {
		flow(SPEED_);
	}
}

EnemyRizardBullet::EnemyRizardBullet(ScenePlay* scene, int lane) {
	//メッシュ初期化
	Initialize(scene, lane);
	isBullet = true;
}

void EnemyRizardBullet::update(float delta_time) {
	checkJudge();
	notesBullet();
	flow(SPEED_);
}