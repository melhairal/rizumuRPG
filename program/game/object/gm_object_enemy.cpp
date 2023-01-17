#include "gm_object_enemy.h"
#include "gm_object_effect.h"
#include "../scene/gm_scene_play.h"
#include "../gm_camera.h"
#include "../gm_ui.h"
#include "../gm_bgm.h"

void EnemyBase::Initialize(ScenePlay* scene, int lane, int atk, int exp) {
	scene_ = scene;
	lane_ = lane;
	atk_ = atk;
	exp_ = exp;
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
		if (!isBullet_ && !miss_) {
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

void EnemyBase::shift() {
	if (!initElapsed_) {
		elapsed_ = 0;
		initElapsed_ = true;
	}
	if (elapsed_ == 0) {
		shift_r_ = rand() % 4;
		shift_dis_ = POS_X_[shift_r_] - POS_X_[lane_];
		elapsed_++;
	}
	else if (elapsed_ <= SHIFT_SPEED_) {
		mesh_->pos_.x += shift_dis_ / SHIFT_SPEED_;
		elapsed_++;
	}
	else {
		mesh_->pos_.x = POS_X_[shift_r_];
		lane_ = shift_r_;
		elapsed_ = 0;
		isShift_ = true;
	}
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
	if (perfect_ && !miss_) {
		if (notesEnemyKey()) {
			//パーフェクト判定処理
			scene_->subUis_.emplace_back(new SubUiJudge(scene_, perfect, lane_));
			scene_->actors_.emplace_back(new EffectPerfect(scene_, lane_));
			scene_->combo_++;
			scene_->mp_ += (1 + (scene_->combo_ * 0.1f)) * 2;
			scene_->score_ += exp_ * scene_->combo_ * 2;
			scene_->bgm_->perfect_ = true;
			alive_ = false;
		}
	}
	else if(good_ && !miss_) {
		if (notesEnemyKey()) {
			//グッド判定処理
			scene_->subUis_.emplace_back(new SubUiJudge(scene_, good, lane_));
			scene_->actors_.emplace_back(new EffectGood(scene_, lane_));
			scene_->combo_++;
			scene_->mp_ += 1 + (scene_->combo_ * 0.1f);
			scene_->score_ += exp_ * scene_->combo_;
			scene_->bgm_->perfect_ = true;
			alive_ = false;
		}
	}
	if (!miss_ && checkLane() &&
		((mesh_->pos_.z < MISS_Z_ && mesh_->pos_.z >= MISS_Z_ - RANGE_MISS_) || 
			(mesh_->pos_.z < JUDGE_Z_ + RANGE_GOOD_ + RANGE_MISS_ && mesh_->pos_.z >= JUDGE_Z_ + RANGE_GOOD_ && notesEnemyKey()))) {
		miss_ = true;
		//失敗判定処理
		scene_->subUis_.emplace_back(new SubUiJudge(scene_, miss, lane_));
		scene_->actors_.emplace_back(new EffectHit(scene_, lane_));
		scene_->combo_ = 0;
		scene_->hp_ -= atk_;
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
	if (perfect_ && !miss_) {
		if (notesBulletKey()) {
			//パーフェクト判定処理
			scene_->subUis_.emplace_back(new SubUiJudge(scene_, perfect, lane_));
			scene_->mp_ += (1 + (scene_->combo_ * 0.1f)) * 2;
			scene_->score_ += exp_ * scene_->combo_ * 2;
			scene_->combo_++;
			scene_->bgm_->perfect_ = true;
		}
	}
	else if (good_ && !miss_) {
		if (notesBulletKey()) {
			//グッド判定処理
			scene_->subUis_.emplace_back(new SubUiJudge(scene_, good, lane_));
			scene_->mp_ += 1 + (scene_->combo_ * 0.1f);
			scene_->score_ += exp_ * scene_->combo_;
			scene_->combo_++;
			scene_->bgm_->perfect_ = true;
		}
	}
	if (!miss_ && checkLane() &&
		mesh_->pos_.z < MISS_Z_ && mesh_->pos_.z >= MISS_Z_ - RANGE_MISS_) {
		miss_ = true;
		//失敗判定処理
		scene_->subUis_.emplace_back(new SubUiJudge(scene_, miss, lane_));
		scene_->actors_.emplace_back(new EffectHit(scene_, lane_));
		scene_->combo_ = 0;
		scene_->hp_ -= atk_;
		alive_ = false;
	}
}

EnemyPig::EnemyPig(ScenePlay* scene, int lane) {
	//メッシュ初期化
	Initialize(scene, lane, ATK_, EXP_);
}

void EnemyPig::update(float delta_time) {
	checkJudge();
	notesEnemy();
	flow(SPEED_);
}

EnemyRizard::EnemyRizard(ScenePlay* scene, int lane) {
	//メッシュ初期化
	Initialize(scene, lane, ATK_, EXP_);
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
	Initialize(scene, lane, ATK_, EXP_);
	isBullet_ = true;
}

void EnemyRizardBullet::update(float delta_time) {
	checkJudge();
	notesBullet();
	flow(SPEED_);
}

EnemyMash::EnemyMash(ScenePlay* scene, int lane) {
	//メッシュ初期化
	Initialize(scene, lane, ATK_, EXP_);
}

void EnemyMash::update(float delta_time) {
	checkJudge();
	notesEnemy();

	if (mesh_->pos_.z < SHIFT_Z_) {
		if (!isShift_) shift();
		else flow(SPEED_);
	}
	else {
		flow(SPEED_);
	}
}

EnemyGrifin::EnemyGrifin(ScenePlay* scene, int lane) {
	//メッシュ初期化
	Initialize(scene, lane, ATK_, EXP_);
}

void EnemyGrifin::update(float delta_time) {
	checkJudge();
	notesEnemy();

	if (mesh_->pos_.z < SHOT_Z_) {
		if (elapsed_ < TIME_STOP_) elapsed_++;
		if (elapsed_ == TIME_SHOT_) shot(new EnemyGrifinBullet(scene_, lane_));
		if (elapsed_ == TIME_STOP_) flow(SPEED_);
	}
	else if (mesh_->pos_.z < SHIFT_Z_) {
		if (!isShift_) shift();
		else flow(SPEED_);
	}
	else {
		flow(SPEED_);
	}
}

EnemyGrifinBullet::EnemyGrifinBullet(ScenePlay* scene, int lane) {
	//メッシュ初期化
	Initialize(scene, lane, ATK_, EXP_);
	isBullet_ = true;
}

void EnemyGrifinBullet::update(float delta_time) {
	animation(FRAME_);
	checkJudge();
	notesBullet();
	flow(SPEED_);
}

EnemyBad::EnemyBad(ScenePlay* scene, int lane) {
	//メッシュ初期化
	Initialize(scene, lane, ATK_, EXP_);
}

void EnemyBad::update(float delta_time) {
	checkJudge();
	notesEnemy();
	flow(SPEED_);
}

EnemyMagician::EnemyMagician(ScenePlay* scene, int lane) {
	//メッシュ初期化
	Initialize(scene, lane, ATK_, EXP_);
}

void EnemyMagician::update(float delta_time) {
	checkJudge();
	notesEnemy();

	if (mesh_->pos_.z < SHOT_Z_) {
		if (elapsed_ < TIME_STOP_) elapsed_++;
		if (elapsed_ == TIME_SHOT_) shot(new EnemyMagicianBullet(scene_, lane_));
		if (elapsed_ == TIME_STOP_) flow(SPEED_);
	}
	else {
		flow(SPEED_);
	}
}

EnemyMagicianBullet::EnemyMagicianBullet(ScenePlay* scene, int lane) {
	//メッシュ初期化
	Initialize(scene, lane, ATK_, EXP_);
	isBullet_ = true;
}

void EnemyMagicianBullet::update(float delta_time) {
	animation(FRAME_);
	checkJudge();
	notesBullet();
	flow(SPEED_);
}

EnemySnake::EnemySnake(ScenePlay* scene, int lane) {
	//メッシュ初期化
	Initialize(scene, lane, ATK_, EXP_);
}

void EnemySnake::update(float delta_time) {
	checkJudge();
	notesEnemy();

	if (mesh_->pos_.z < SHIFT_Z_) {
		if (!isShift_) shift();
		else flow(SPEED_);
	}
	else {
		flow(SPEED_);
	}
}

EnemySinigami::EnemySinigami(ScenePlay* scene, int lane) {
	//メッシュ初期化
	Initialize(scene, lane, ATK_, EXP_);
}

void EnemySinigami::update(float delta_time) {
	checkJudge();
	notesEnemy();

	if (mesh_->pos_.z < SHOT_Z1_) {
		if (elapsed_ < TIME_STOP_) elapsed_++;
		if (elapsed_ == TIME_SHOT_) shot(new EnemySinigamiBullet(scene_, lane_));
		if (elapsed_ == TIME_STOP_) flow(SPEED_);
	}
	else if (mesh_->pos_.z < SHIFT_Z_) {
		if (!isShift_) shift();
		else flow(SPEED_);
	}
	else if (mesh_->pos_.z < SHOT_Z2_) {
		if (elapsed_ < TIME_STOP_) elapsed_++;
		if (elapsed_ == TIME_SHOT_) shot(new EnemySinigamiBullet(scene_, lane_));
		if (elapsed_ == TIME_STOP_) flow(SPEED_);
	}
	else {
		flow(SPEED_);
	}
}

EnemySinigamiBullet::EnemySinigamiBullet(ScenePlay* scene, int lane) {
	//メッシュ初期化
	Initialize(scene, lane, ATK_, EXP_);
	isBullet_ = true;
}

void EnemySinigamiBullet::update(float delta_time) {
	animation(FRAME_);
	checkJudge();
	notesBullet();
	flow(SPEED_);
}