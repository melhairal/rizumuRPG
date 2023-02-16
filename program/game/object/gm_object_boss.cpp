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

void BossEnemy::switchAction() {
	switch (action_) {
	case 0:
		attackMeleeA();
		break;
	case 1:
		attackRangeA();
		break;
	case 2:
		attackBulletA();
		break;
	case 3:
		attackMeleeB();
		break;
	case 4:
		attackRangeB();
		break;
	case 5:
		attackBulletB();
		break;
	}
}

void BossEnemy::setMove(float x, float z) {
	move_flame_ = MOVE_SPEED_;
	dir_x_ = (x - mesh_->pos_.x) / MOVE_SPEED_;
	dir_z_ = (z - mesh_->pos_.z) / MOVE_SPEED_;
}

void BossEnemy::move(float x, float z) {
	mesh_->pos_.x += x;
	mesh_->pos_.z += z;
	move_flame_--;
}

BossGorem::BossGorem(ScenePlay* scene) {
	initialize(scene);
}

void BossGorem::attackMeleeA() {
	for (int i = 0; i < 5; i++) {
		if (elapsed_ == ATTACK_INTERVAL_SLOW_ * i) { //1つ目のノーツ生成
			r_[i] = rand() % 4;
			scene_->actors_.emplace_back(new NotesWarning(scene_, ATK_MELEE_, r_[i]));
		}
		if (elapsed_ == ATTACK_INTERVAL_SLOW_ * i + FLOW_INTERVAL_ - MOVE_SPEED_) { //1つ目のノーツに向かって移動
			setMove(POS_X_[r_[i]], MELEE_POS_Z_);
		}
		if (elapsed_ == ATTACK_INTERVAL_SLOW_ * i + FLOW_INTERVAL_) { //1つ目のノーツのエフェクトを生成
			scene_->actors_.emplace_back(new EffectCrow(scene_, r_[i]));
		}
	}
	elapsed_++;

	if (elapsed_ >= ATTACK_INTERVAL_SLOW_ * 5 + FLOW_INTERVAL_ + 1) { //終了
		elapsed_ = 0;
		action_ = -1;
	}
}

void BossGorem::attackMeleeB() {
	for (int i = 0; i < 4; i++) {
		if (elapsed_ == ATTACK_INTERVAL_FAST_ * i) { //1つ目のノーツ生成
			r_[i] = rand() % 4;
			scene_->actors_.emplace_back(new NotesWarning(scene_, ATK_MELEE_, r_[i]));
		}
		if (elapsed_ == ATTACK_INTERVAL_FAST_ * i + FLOW_INTERVAL_ - MOVE_SPEED_) { //1つ目のノーツに向かって移動
			setMove(POS_X_[r_[i]], MELEE_POS_Z_);
		}
		if (elapsed_ == ATTACK_INTERVAL_FAST_ * i + FLOW_INTERVAL_) { //1つ目のノーツのエフェクトを生成
			scene_->actors_.emplace_back(new EffectCrow(scene_, r_[i]));
		}
	}
	elapsed_++;

	if (elapsed_ >= ATTACK_INTERVAL_FAST_ * 4 + FLOW_INTERVAL_ + 1) { //終了
		elapsed_ = 0;
		action_ = -1;
	}
}

void BossGorem::attackRangeA() {
	for (int i = 0; i < 2; i++) {
		if (elapsed_ == ATTACK_INTERVAL_SLOW_ * i) { //1つ目のノーツ生成
			scene_->actors_.emplace_back(new NotesWarningAll(scene_, ATK_RANGE_, 0));
			scene_->actors_.emplace_back(new NotesWarningAll(scene_, ATK_RANGE_, 1));
			scene_->actors_.emplace_back(new NotesWarningAll(scene_, ATK_RANGE_, 2));
			scene_->actors_.emplace_back(new NotesWarningAll(scene_, ATK_RANGE_, 3));
		}
		if (elapsed_ == FLOW_INTERVAL_ - MOVE_SPEED_) { //1つ目のノーツに向かって移動
			setMove(0, MELEE_POS_Z_);
		}
		if (elapsed_ == ATTACK_INTERVAL_SLOW_ * i + FLOW_INTERVAL_) { //1つ目のノーツのエフェクトを生成
			scene_->actors_.emplace_back(new EffectTail(scene_));
		}
	}
	elapsed_++;

	if (elapsed_ >= ATTACK_INTERVAL_SLOW_ * 2 + FLOW_INTERVAL_ + 1) { //終了
		elapsed_ = 0;
		action_ = -1;
	}
}

void BossGorem::attackRangeB() {
	for (int i = 0; i < 3; i++) {
		if (elapsed_ == ATTACK_INTERVAL_SLOW_ * i) { //1つ目のノーツ生成
			if (i == 2) {
				scene_->actors_.emplace_back(new NotesWarningAll(scene_, ATK_RANGE_, 0));
				scene_->actors_.emplace_back(new NotesWarningAll(scene_, ATK_RANGE_, 1));
				scene_->actors_.emplace_back(new NotesWarningAll(scene_, ATK_RANGE_, 2));
				scene_->actors_.emplace_back(new NotesWarningAll(scene_, ATK_RANGE_, 3));
			}
			else {
				r_[i] = rand() % 4;
				scene_->actors_.emplace_back(new NotesWarning(scene_, ATK_MELEE_, r_[i]));
			}
		}
		if (elapsed_ == ATTACK_INTERVAL_SLOW_ * i + FLOW_INTERVAL_ - MOVE_SPEED_) { //1つ目のノーツに向かって移動
			if (i == 2) {
				setMove(0, MELEE_POS_Z_);
			}
			else {
				setMove(POS_X_[r_[i]], MELEE_POS_Z_);
			}
		}
		if (elapsed_ == ATTACK_INTERVAL_SLOW_ * i + FLOW_INTERVAL_) { //1つ目のノーツのエフェクトを生成
			if (i == 2) {
				scene_->actors_.emplace_back(new EffectTail(scene_));
			}
			else {
				scene_->actors_.emplace_back(new EffectCrow(scene_, r_[i]));
			}
		}
	}
	elapsed_++;

	if (elapsed_ >= ATTACK_INTERVAL_SLOW_ * 3 + FLOW_INTERVAL_ + 1) { //終了
		elapsed_ = 0;
		action_ = -1;
	}
}

void BossGorem::attackBulletA() {
	attackMeleeB();
}

void BossGorem::attackBulletB() {
	attackRangeB();
}

void BossGorem::update(float delta_time) {
	if (move_flame_ != 0) move(dir_x_, dir_z_);
	if (action_ != -1)switchAction();
}


BossDragon::BossDragon(ScenePlay* scene) {
	initialize(scene);
}

void BossDragon::attackMeleeA() {
	for (int i = 0; i < 3; i++) {
		if (elapsed_ == ATTACK_INTERVAL_FAST_ * i) { //1つ目のノーツ生成
			r_[i] = rand() % 4;
			scene_->actors_.emplace_back(new NotesWarning(scene_, ATK_MELEE_, r_[i]));
		}
		if (elapsed_ == ATTACK_INTERVAL_FAST_ * i + FLOW_INTERVAL_ - MOVE_SPEED_) { //1つ目のノーツに向かって移動
			setMove(POS_X_[r_[i]], MELEE_POS_Z_);
		}
		if (elapsed_ == ATTACK_INTERVAL_FAST_ * i + FLOW_INTERVAL_) { //1つ目のノーツのエフェクトを生成
			scene_->actors_.emplace_back(new EffectCrow(scene_, r_[i]));
		}
	}
	elapsed_++;

	if (elapsed_ >= ATTACK_INTERVAL_FAST_ * 3 + FLOW_INTERVAL_ + 1) { //終了
		elapsed_ = 0;
		action_ = -1;
	}
}

void BossDragon::attackMeleeB() {
	for (int i = 0; i < 6; i++) {
		if (elapsed_ == ATTACK_INTERVAL_FAST_ * i) { //1つ目のノーツ生成
			r_[i] = rand() % 4;
			scene_->actors_.emplace_back(new NotesWarning(scene_, ATK_MELEE_, r_[i]));
		}
		if (elapsed_ == ATTACK_INTERVAL_FAST_ * i + FLOW_INTERVAL_ - MOVE_SPEED_) { //1つ目のノーツに向かって移動
			setMove(POS_X_[r_[i]], MELEE_POS_Z_);
		}
		if (elapsed_ == ATTACK_INTERVAL_FAST_ * i + FLOW_INTERVAL_) { //1つ目のノーツのエフェクトを生成
			scene_->actors_.emplace_back(new EffectCrow(scene_, r_[i]));
		}
	}
	elapsed_++;

	if (elapsed_ >= ATTACK_INTERVAL_FAST_ * 6 + FLOW_INTERVAL_ + 1) { //終了
		elapsed_ = 0;
		action_ = -1;
	}
}

void BossDragon::attackRangeA() {
	for (int i = 0; i < 2; i++) {
		if (elapsed_ == ATTACK_INTERVAL_SLOW_ * i) { //1つ目のノーツ生成
			scene_->actors_.emplace_back(new NotesWarningAll(scene_, ATK_RANGE_, 0));
			scene_->actors_.emplace_back(new NotesWarningAll(scene_, ATK_RANGE_, 1));
			scene_->actors_.emplace_back(new NotesWarningAll(scene_, ATK_RANGE_, 2));
			scene_->actors_.emplace_back(new NotesWarningAll(scene_, ATK_RANGE_, 3));
		}
		if (elapsed_ == FLOW_INTERVAL_ - MOVE_SPEED_) { //1つ目のノーツに向かって移動
			setMove(0, MELEE_POS_Z_);
		}
		if (elapsed_ == ATTACK_INTERVAL_SLOW_ * i + FLOW_INTERVAL_) { //1つ目のノーツのエフェクトを生成
			scene_->actors_.emplace_back(new EffectTail(scene_));
		}
	}
	elapsed_++;

	if (elapsed_ >= ATTACK_INTERVAL_SLOW_ * 2 + FLOW_INTERVAL_ + 1) { //終了
		elapsed_ = 0;
		action_ = -1;
	}
}

void BossDragon::attackRangeB() {
	for (int i = 0; i < 3; i++) {
		if (elapsed_ == ATTACK_INTERVAL_FAST_ * i) { //1つ目のノーツ生成
			scene_->actors_.emplace_back(new NotesWarningAll(scene_, ATK_RANGE_, 0));
			scene_->actors_.emplace_back(new NotesWarningAll(scene_, ATK_RANGE_, 1));
			scene_->actors_.emplace_back(new NotesWarningAll(scene_, ATK_RANGE_, 2));
			scene_->actors_.emplace_back(new NotesWarningAll(scene_, ATK_RANGE_, 3));
		}
		if (elapsed_ == FLOW_INTERVAL_ - MOVE_SPEED_) { //1つ目のノーツに向かって移動
			setMove(0, MELEE_POS_Z_);
		}
		if (elapsed_ == ATTACK_INTERVAL_FAST_ * i + FLOW_INTERVAL_) { //1つ目のノーツのエフェクトを生成
			scene_->actors_.emplace_back(new EffectTail(scene_));
		}
	}
	elapsed_++;

	if (elapsed_ >= ATTACK_INTERVAL_FAST_ * 3 + FLOW_INTERVAL_ + 1) { //終了
		elapsed_ = 0;
		action_ = -1;
	}
}

void BossDragon::attackBulletA() {
	for (int i = 0; i < 5; i++) {
		if (elapsed_ == ATTACK_INTERVAL_SLOW_ * i) { //1つ目のノーツ生成位置に移動
			r_[i] = rand() % 4;
			setMove(POS_X_[r_[i]], BULLET_POS_Z_);
		}
		if (elapsed_ == ATTACK_INTERVAL_SLOW_ * i + MOVE_SPEED_) { //1つ目のノーツ生成
			scene_->actors_.emplace_back(new NotesDragonBless(scene_, ATK_BULLET_, r_[i]));
		}
	}
	elapsed_++;

	if (elapsed_ >= ATTACK_INTERVAL_SLOW_ * 5 + BULLET_INTERVAL_ + 1) { //終了
		elapsed_ = 0;
		action_ = -1;
	}
}

void BossDragon::attackBulletB() {
	for (int i = 0; i < 8; i++) {
		if (elapsed_ == ATTACK_INTERVAL_FAST_ * i) { //1つ目のノーツ生成位置に移動
			setMove(POS_X_[i % 4], BULLET_POS_Z_);
		}
		if (elapsed_ == ATTACK_INTERVAL_FAST_ * i + MOVE_SPEED_) { //1つ目のノーツ生成
			scene_->actors_.emplace_back(new NotesDragonBless(scene_, ATK_BULLET_, i % 4));
		}
	}
	for (int i = 8; i < 13; i++) {
		if (elapsed_ == ATTACK_INTERVAL_FAST_ * i) { //1つ目のノーツ生成位置に移動
			r_[i - 8] = rand() % 4;
			setMove(POS_X_[r_[i - 8]], BULLET_POS_Z_);
		}
		if (elapsed_ == ATTACK_INTERVAL_FAST_ * i + MOVE_SPEED_) { //1つ目のノーツ生成
			scene_->actors_.emplace_back(new NotesDragonBless(scene_, ATK_BULLET_, r_[i - 8]));
		}
	}
	elapsed_++;

	if (elapsed_ >= ATTACK_INTERVAL_FAST_ * 13 + BULLET_INTERVAL_ + 1) { //終了
		elapsed_ = 0;
		action_ = -1;
	}
}

void BossDragon::update(float delta_time) {
	if (move_flame_ != 0) move(dir_x_, dir_z_);
	if (action_ != -1)switchAction();
}

BossKeruberos::BossKeruberos(ScenePlay* scene) {
	initialize(scene);
}

void BossKeruberos::attackMeleeA() {
	for (int i = 0; i < 8; i++) {
		if (elapsed_ == ATTACK_INTERVAL_FAST_ * i) { //1つ目のノーツ生成
			r_[i] = rand() % 4;
			scene_->actors_.emplace_back(new NotesWarning(scene_, ATK_MELEE_, r_[i]));
		}
		if (elapsed_ == ATTACK_INTERVAL_FAST_ * i + FLOW_INTERVAL_ - MOVE_SPEED_) { //1つ目のノーツに向かって移動
			setMove(POS_X_[r_[i]], MELEE_POS_Z_);
		}
		if (elapsed_ == ATTACK_INTERVAL_FAST_ * i + FLOW_INTERVAL_) { //1つ目のノーツのエフェクトを生成
			scene_->actors_.emplace_back(new EffectCrow(scene_, r_[i]));
		}
	}
	elapsed_++;

	if (elapsed_ >= ATTACK_INTERVAL_FAST_ * 8 + FLOW_INTERVAL_ + 1) { //終了
		elapsed_ = 0;
		action_ = -1;
	}
}

void BossKeruberos::attackMeleeB() {
	for (int i = 0; i < 6; i++) {
		if (elapsed_ == ATTACK_INTERVAL_SLOW_ * i) { //1つ目のノーツ生成
			r_[i] = rand() % 4;
			if (i > 0) {
				if (r_[i] == r_[i - 1]) {
					r_[i] = (r_[i] + 1) % 4;
				}
			}
			scene_->actors_.emplace_back(new NotesWarning(scene_, ATK_MELEE_, r_[i]));
		}
		if (elapsed_ == ATTACK_INTERVAL_SLOW_ * i + FLOW_INTERVAL_ - MOVE_SPEED_) { //1つ目のノーツに向かって移動
			setMove(POS_X_[r_[i]], MELEE_POS_Z_);
		}
		if (elapsed_ == ATTACK_INTERVAL_SLOW_ * i + FLOW_INTERVAL_) { //1つ目のノーツのエフェクトを生成
			scene_->actors_.emplace_back(new EffectBite(scene_, r_[i]));
		}
	}
	elapsed_++;

	if (elapsed_ >= ATTACK_INTERVAL_SLOW_ * 6 + FLOW_INTERVAL_ + 1) { //終了
		elapsed_ = 0;
		action_ = -1;
	}
}

void BossKeruberos::attackRangeA() {
	for (int i = 0; i < 4; i++) {
		if (elapsed_ == ATTACK_INTERVAL_SLOW_ * i) { //1つ目のノーツ生成
			scene_->actors_.emplace_back(new NotesWarningAll(scene_, ATK_RANGE_, 0));
			scene_->actors_.emplace_back(new NotesWarningAll(scene_, ATK_RANGE_, 1));
			scene_->actors_.emplace_back(new NotesWarningAll(scene_, ATK_RANGE_, 2));
			scene_->actors_.emplace_back(new NotesWarningAll(scene_, ATK_RANGE_, 3));
		}
		if (elapsed_ == FLOW_INTERVAL_ - MOVE_SPEED_) { //1つ目のノーツに向かって移動
			setMove(0, MELEE_POS_Z_);
		}
		if (elapsed_ == ATTACK_INTERVAL_SLOW_ * i + FLOW_INTERVAL_) { //1つ目のノーツのエフェクトを生成
			scene_->actors_.emplace_back(new EffectTail(scene_));
		}
	}
	elapsed_++;

	if (elapsed_ >= ATTACK_INTERVAL_SLOW_ * 4 + FLOW_INTERVAL_ + 1) { //終了
		elapsed_ = 0;
		action_ = -1;
	}
}

void BossKeruberos::attackRangeB() {
	for (int i = 0; i < 5; i++) {
		if (elapsed_ == ATTACK_INTERVAL_FAST_ * i) { //1つ目のノーツ生成
			if (i == 2 || i == 4) {
				scene_->actors_.emplace_back(new NotesWarningAll(scene_, ATK_RANGE_, 0));
				scene_->actors_.emplace_back(new NotesWarningAll(scene_, ATK_RANGE_, 1));
				scene_->actors_.emplace_back(new NotesWarningAll(scene_, ATK_RANGE_, 2));
				scene_->actors_.emplace_back(new NotesWarningAll(scene_, ATK_RANGE_, 3));
			}
			else {
				r_[i] = rand() % 4;
				scene_->actors_.emplace_back(new NotesWarning(scene_, ATK_MELEE_, r_[i]));
			}
		}
		if (elapsed_ == ATTACK_INTERVAL_FAST_ * i + FLOW_INTERVAL_ - MOVE_SPEED_) { //1つ目のノーツに向かって移動
			if (i == 2 || i == 4) {
				setMove(0, MELEE_POS_Z_);
			}
			else {
				setMove(POS_X_[r_[i]], MELEE_POS_Z_);
			}
		}
		if (elapsed_ == ATTACK_INTERVAL_FAST_ * i + FLOW_INTERVAL_) { //1つ目のノーツのエフェクトを生成
			if (i == 2 || i == 4) {
				scene_->actors_.emplace_back(new EffectTail(scene_));
			}
			else {
				scene_->actors_.emplace_back(new EffectCrow(scene_, r_[i]));
			}
		}
	}
	elapsed_++;

	if (elapsed_ >= ATTACK_INTERVAL_FAST_ * 5 + FLOW_INTERVAL_ + 1) { //終了
		elapsed_ = 0;
		action_ = -1;
	}
}

void BossKeruberos::attackBulletA() {
	for (int i = 0; i < 8; i++) {
		if (elapsed_ == ATTACK_INTERVAL_FAST_ * i) { //1つ目のノーツ生成位置に移動
			r_[i] = rand() % 4;
			if (i > 0) {
				if (r_[i] == r_[i - 1]) {
					r_[i] = (r_[i] + 1) % 4;
				}
			}
			setMove(POS_X_[r_[i]], BULLET_POS_Z_);
		}
		if (elapsed_ == ATTACK_INTERVAL_FAST_ * i + MOVE_SPEED_) { //1つ目のノーツ生成
			scene_->actors_.emplace_back(new NotesKeruberosBless(scene_, ATK_BULLET_, r_[i]));
		}
	}
	elapsed_++;

	if (elapsed_ >= ATTACK_INTERVAL_FAST_ * 8 + BULLET_INTERVAL_ + 1) { //終了
		elapsed_ = 0;
		action_ = -1;
	}
}

void BossKeruberos::attackBulletB() {
	attackRangeB();
}

void BossKeruberos::update(float delta_time) {
	if (move_flame_ != 0) move(dir_x_, dir_z_);
	if (action_ != -1)switchAction();
}

BossAnkou::BossAnkou(ScenePlay* scene) {
	initialize(scene);
}

void BossAnkou::attackMeleeA() {
	for (int i = 0; i < 7; i++) {
		if (elapsed_ == ATTACK_INTERVAL_SLOW_ * i) { //1つ目のノーツ生成
			r_[i] = rand() % 4;
			scene_->actors_.emplace_back(new NotesWarning(scene_, ATK_MELEE_, r_[i]));
		}
		if (elapsed_ == ATTACK_INTERVAL_SLOW_ * i + FLOW_INTERVAL_ - MOVE_SPEED_) { //1つ目のノーツに向かって移動
			setMove(POS_X_[r_[i]], MELEE_POS_Z_);
		}
		if (elapsed_ == ATTACK_INTERVAL_SLOW_ * i + FLOW_INTERVAL_) { //1つ目のノーツのエフェクトを生成
			scene_->actors_.emplace_back(new EffectBite(scene_, r_[i]));
		}
	}
	elapsed_++;

	if (elapsed_ >= ATTACK_INTERVAL_SLOW_ * 7 + FLOW_INTERVAL_ + 1) { //終了
		elapsed_ = 0;
		action_ = -1;
	}
}

void BossAnkou::attackMeleeB() {
	for (int i = 0; i < 4; i++) {
		if (elapsed_ == ATTACK_INTERVAL_SLOW_ * i) { //1つ目のノーツ生成
			r_[i] = rand() % 3;
			if (i > 0) {
				if (r_[i] == r_[i - 1]) {
					r_[i] = (r_[i] + 1) % 3;
				}
			}
			scene_->actors_.emplace_back(new NotesWarning(scene_, ATK_MELEE_, r_[i]));
			scene_->actors_.emplace_back(new NotesWarning(scene_, ATK_MELEE_, r_[i] + 1));
		}
		if (elapsed_ == ATTACK_INTERVAL_SLOW_ * i + FLOW_INTERVAL_ - MOVE_SPEED_) { //1つ目のノーツに向かって移動
			setMove((POS_X_[r_[i]] + POS_X_[r_[i] + 1]) / 2, MELEE_POS_Z_);
		}
		if (elapsed_ == ATTACK_INTERVAL_SLOW_ * i + FLOW_INTERVAL_) { //1つ目のノーツのエフェクトを生成
			scene_->actors_.emplace_back(new EffectBite(scene_, r_[i]));
			scene_->actors_.emplace_back(new EffectBite(scene_, r_[i] + 1));
		}
	}
	elapsed_++;

	if (elapsed_ >= ATTACK_INTERVAL_SLOW_ * 4 + FLOW_INTERVAL_ + 1) { //終了
		elapsed_ = 0;
		action_ = -1;
	}
}

void BossAnkou::attackRangeA() {
	attackBulletA();
}

void BossAnkou::attackRangeB() {
	attackBulletB();
}

void BossAnkou::attackBulletA() {
	for (int i = 0; i < 15; i++) {
		if (elapsed_ == ATTACK_INTERVAL_FAST_ * i) { //1つ目のノーツ生成位置に移動
			r_[i] = rand() % 4;
			if (i > 0) {
				if (r_[i] == r_[i - 1]) {
					r_[i] = (r_[i] + 1) % 4;
				}
			}
			setMove(POS_X_[r_[i]], BULLET_POS_Z_);
		}
		if (elapsed_ == ATTACK_INTERVAL_FAST_ * i + MOVE_SPEED_) { //1つ目のノーツ生成
			scene_->actors_.emplace_back(new NotesAnkouBless(scene_, ATK_BULLET_, r_[i]));
		}
	}
	elapsed_++;

	if (elapsed_ >= ATTACK_INTERVAL_FAST_ * 15 + BULLET_INTERVAL_ + 1) { //終了
		elapsed_ = 0;
		action_ = -1;
	}
}

void BossAnkou::attackBulletB() {
	for (int i = 0; i < 6; i++) {
		if (elapsed_ == ATTACK_INTERVAL_SLOW_ * i) { //1つ目のノーツ生成位置に移動
			r_[i] = rand() % 4;
			if (i > 0) {
				if (r_[i] == r_[i - 1]) {
					r_[i] = (r_[i] + 1) % 4;
				}
			}
			setMove(0, BULLET_POS_Z_);
		}
		if (elapsed_ == ATTACK_INTERVAL_SLOW_ * i + MOVE_SPEED_) { //1つ目のノーツ生成
			scene_->actors_.emplace_back(new NotesAnkouBless(scene_, ATK_BULLET_, r_[i]));
			r_[i] = (r_[i] + rand() % 3 + 1) % 4;
			scene_->actors_.emplace_back(new NotesAnkouBless(scene_, ATK_BULLET_, r_[i]));
		}
	}
	elapsed_++;

	if (elapsed_ >= ATTACK_INTERVAL_SLOW_ * 6 + BULLET_INTERVAL_ + 1) { //終了
		elapsed_ = 0;
		action_ = -1;
	}
}

void BossAnkou::update(float delta_time) {
	if (move_flame_ != 0) move(dir_x_, dir_z_);
	if (action_ != -1)switchAction();
}

BossSkall::BossSkall(ScenePlay* scene) {
	initialize(scene);
}

void BossSkall::attackMeleeA() {
	for (int i = 0; i < 20; i++) {
		if (elapsed_ == ATTACK_INTERVAL_FAST_ * i) { //1つ目のノーツ生成
			r_[i] = rand() % 4;
			if (i > 0) {
				if (r_[i] == r_[i - 1]) {
					r_[i] = (r_[i] + 1) % 4;
				}
			}
			scene_->actors_.emplace_back(new NotesWarning(scene_, ATK_MELEE_, r_[i]));
		}
		if (elapsed_ == ATTACK_INTERVAL_FAST_ * i + FLOW_INTERVAL_ - MOVE_SPEED_) { //1つ目のノーツに向かって移動
			setMove(POS_X_[r_[i]], MELEE_POS_Z_);
		}
		if (elapsed_ == ATTACK_INTERVAL_FAST_ * i + FLOW_INTERVAL_) { //1つ目のノーツのエフェクトを生成
			scene_->actors_.emplace_back(new EffectEnemySward(scene_, r_[i]));
		}
	}
	elapsed_++;

	if (elapsed_ >= ATTACK_INTERVAL_FAST_ * 20 + FLOW_INTERVAL_ + 1) { //終了
		elapsed_ = 0;
		action_ = -1;
	}
}

void BossSkall::attackMeleeB() {
	for (int i = 0; i < 5; i++) {
		if (elapsed_ == ATTACK_INTERVAL_SLOW_ * i) { //1つ目のノーツ生成
			r_[i] = rand() % 4;
			if (i > 0) {
				if (r_[i] == r_[i - 1]) {
					r_[i] = (r_[i] + 1) % 4;
				}
			}
			scene_->actors_.emplace_back(new NotesWarning(scene_, ATK_MELEE_, r_[i]));
		}
		if (elapsed_ == ATTACK_INTERVAL_SLOW_ * i + FLOW_INTERVAL_ - MOVE_SPEED_) { //1つ目のノーツに向かって移動
			setMove(POS_X_[r_[i]], MELEE_POS_Z_);
		}
		if (elapsed_ == ATTACK_INTERVAL_SLOW_ * i + FLOW_INTERVAL_) { //1つ目のノーツのエフェクトを生成
			scene_->actors_.emplace_back(new EffectEnemySward(scene_, r_[i]));
		}
	}
	for (int i = 5; i < 10; i++) {
		if (elapsed_ == ATTACK_INTERVAL_SLOW_ * 4 + ATTACK_INTERVAL_FAST_ * (i - 4)) { //1つ目のノーツ生成
			r_[i] = rand() % 4;
			if (i > 0) {
				if (r_[i] == r_[i - 1]) {
					r_[i] = (r_[i] + 1) % 4;
				}
			}
			scene_->actors_.emplace_back(new NotesWarning(scene_, ATK_MELEE_, r_[i]));
		}
		if (elapsed_ == ATTACK_INTERVAL_SLOW_ * 4 + ATTACK_INTERVAL_FAST_ * (i - 4) + FLOW_INTERVAL_ - MOVE_SPEED_) { //1つ目のノーツに向かって移動
			setMove(POS_X_[r_[i]], MELEE_POS_Z_);
		}
		if (elapsed_ == ATTACK_INTERVAL_SLOW_ * 4 + ATTACK_INTERVAL_FAST_ * (i - 4) + FLOW_INTERVAL_) { //1つ目のノーツのエフェクトを生成
			scene_->actors_.emplace_back(new EffectEnemySward(scene_, r_[i]));
		}
	}
	elapsed_++;

	if (elapsed_ >= ATTACK_INTERVAL_SLOW_ * 4 + ATTACK_INTERVAL_FAST_ * 5 + FLOW_INTERVAL_ + 1) { //終了
		elapsed_ = 0;
		action_ = -1;
	}
}

void BossSkall::attackRangeA() {
	attackMeleeA();
}

void BossSkall::attackRangeB() {
	attackMeleeB();
}

void BossSkall::attackBulletA() {
	for (int i = 0; i < 6; i++) {
		if (elapsed_ == ATTACK_INTERVAL_FAST_ * i) { //1つ目のノーツ生成位置に移動
			r_[i] = rand() % 4;
			if (i > 0) {
				if (r_[i] == r_[i - 1]) {
					r_[i] = (r_[i] + 1) % 4;
				}
			}
			setMove(POS_X_[r_[i]], BULLET_POS_Z_);
		}
		if (elapsed_ == ATTACK_INTERVAL_FAST_ * i + MOVE_SPEED_) { //1つ目のノーツ生成
			scene_->actors_.emplace_back(new NotesSkallSward(scene_, ATK_BULLET_, r_[i]));
		}
	}
	elapsed_++;

	if (elapsed_ >= ATTACK_INTERVAL_FAST_ * 6 + BULLET_INTERVAL_ + 1) { //終了
		elapsed_ = 0;
		action_ = -1;
	}
}

void BossSkall::attackBulletB() {
	for (int i = 0; i < 4; i++) {
		if (elapsed_ == ATTACK_INTERVAL_SLOW_ * i) { //1つ目のノーツ生成位置に移動
			r_[i] = rand() % 4;
			if (i > 0) {
				if (r_[i] == r_[i - 1]) {
					r_[i] = (r_[i] + 1) % 4;
				}
			}
			setMove(POS_X_[r_[i]], BULLET_POS_Z_);
		}
		if (elapsed_ == ATTACK_INTERVAL_SLOW_ * i + MOVE_SPEED_) { //1つ目のノーツ生成
			scene_->actors_.emplace_back(new NotesSkallSward(scene_, ATK_BULLET_, r_[i]));
		}
	}
	for (int i = 4; i < 7; i++) {
		if (elapsed_ == ATTACK_INTERVAL_SLOW_ * 3 + ATTACK_INTERVAL_FAST_ * (i - 3)) { //1つ目のノーツ生成
			r_[i] = rand() % 4;
			if (i > 0) {
				if (r_[i] == r_[i - 1]) {
					r_[i] = (r_[i] + 1) % 4;
				}
			}
			scene_->actors_.emplace_back(new NotesWarning(scene_, ATK_MELEE_, r_[i]));
		}
		if (elapsed_ == ATTACK_INTERVAL_SLOW_ * 3 + ATTACK_INTERVAL_FAST_ * (i - 3) + FLOW_INTERVAL_ - MOVE_SPEED_) { //1つ目のノーツに向かって移動
			setMove(POS_X_[r_[i]], MELEE_POS_Z_);
		}
		if (elapsed_ == ATTACK_INTERVAL_SLOW_ * 3 + ATTACK_INTERVAL_FAST_ * (i - 3) + FLOW_INTERVAL_) { //1つ目のノーツのエフェクトを生成
			scene_->actors_.emplace_back(new EffectEnemySward(scene_, r_[i]));
		}
	}
	elapsed_++;

	if (elapsed_ >= ATTACK_INTERVAL_SLOW_ * 3 + ATTACK_INTERVAL_FAST_ * 4 + FLOW_INTERVAL_ + 1) { //終了
		elapsed_ = 0;
		action_ = -1;
	}
}

void BossSkall::update(float delta_time) {
	if (move_flame_ != 0) move(dir_x_, dir_z_);
	if (action_ != -1)switchAction();
}

BossKing::BossKing(ScenePlay* scene) {
	initialize(scene);
}

void BossKing::attackMeleeA() {
	for (int i = 0; i < 18; i++) {
		if (elapsed_ == ATTACK_INTERVAL_FAST_ * i) { //1つ目のノーツ生成
			r_[i] = rand() % 4;
			if (i > 0) {
				if (r_[i] == r_[i - 1]) {
					r_[i] = (r_[i] + 1) % 4;
				}
			}
			scene_->actors_.emplace_back(new NotesWarning(scene_, ATK_MELEE_, r_[i]));
		}
		if (elapsed_ == ATTACK_INTERVAL_FAST_ * i + FLOW_INTERVAL_ - MOVE_SPEED_) { //1つ目のノーツに向かって移動
			setMove(POS_X_[r_[i]], MELEE_POS_Z_);
		}
		if (elapsed_ == ATTACK_INTERVAL_FAST_ * i + FLOW_INTERVAL_) { //1つ目のノーツのエフェクトを生成
			scene_->actors_.emplace_back(new EffectCrow(scene_, r_[i]));
		}
	}
	elapsed_++;

	if (elapsed_ >= ATTACK_INTERVAL_FAST_ * 18 + FLOW_INTERVAL_ + 1) { //終了
		elapsed_ = 0;
		action_ = -1;
	}
}

void BossKing::attackMeleeB() {
	for (int i = 0; i < 10; i++) {
		if (elapsed_ == ATTACK_INTERVAL_SLOW_ * i) { //1つ目のノーツ生成
			r_[i] = rand() % 3;
			if (i > 0) {
				if (r_[i] == r_[i - 1]) {
					r_[i] = (r_[i] + 1) % 3;
				}
			}
			scene_->actors_.emplace_back(new NotesWarning(scene_, ATK_MELEE_, r_[i]));
			scene_->actors_.emplace_back(new NotesWarning(scene_, ATK_MELEE_, r_[i] + 1));
		}
		if (elapsed_ == ATTACK_INTERVAL_SLOW_ * i + FLOW_INTERVAL_ - MOVE_SPEED_) { //1つ目のノーツに向かって移動
			setMove((POS_X_[r_[i]] + POS_X_[r_[i] + 1]) / 2, MELEE_POS_Z_);
		}
		if (elapsed_ == ATTACK_INTERVAL_SLOW_ * i + FLOW_INTERVAL_) { //1つ目のノーツのエフェクトを生成
			scene_->actors_.emplace_back(new EffectBite(scene_, r_[i]));
			scene_->actors_.emplace_back(new EffectBite(scene_, r_[i] + 1));
		}
	}
	elapsed_++;

	if (elapsed_ >= ATTACK_INTERVAL_SLOW_ * 10 + FLOW_INTERVAL_ + 1) { //終了
		elapsed_ = 0;
		action_ = -1;
	}
}

void BossKing::attackRangeA() {
	for (int i = 0; i < 10; i++) {
		if (elapsed_ == ATTACK_INTERVAL_SLOW_ * i) { //1つ目のノーツ生成
			if (i == 2 || i == 4 || i == 6 || i ==7 || i == 9) {
				scene_->actors_.emplace_back(new NotesWarningAll(scene_, ATK_RANGE_, 0));
				scene_->actors_.emplace_back(new NotesWarningAll(scene_, ATK_RANGE_, 1));
				scene_->actors_.emplace_back(new NotesWarningAll(scene_, ATK_RANGE_, 2));
				scene_->actors_.emplace_back(new NotesWarningAll(scene_, ATK_RANGE_, 3));
			}
			else {
				r_[i] = rand() % 3;
				scene_->actors_.emplace_back(new NotesWarning(scene_, ATK_MELEE_, r_[i]));
				scene_->actors_.emplace_back(new NotesWarning(scene_, ATK_MELEE_, r_[i] + 1));
			}
		}
		if (elapsed_ == ATTACK_INTERVAL_SLOW_ * i + FLOW_INTERVAL_) { //1つ目のノーツに向かって移動
			if (i == 2 || i == 4 || i == 6 || i == 7 || i == 9) {
				setMove(0, MELEE_POS_Z_);
			}
			else {
				setMove((POS_X_[r_[i]] + POS_X_[r_[i] + 1]) / 2, MELEE_POS_Z_);
			}
		}
		if (elapsed_ == ATTACK_INTERVAL_SLOW_ * i + FLOW_INTERVAL_) { //1つ目のノーツのエフェクトを生成
			if (i == 2 || i == 4 || i == 6 || i == 7 || i == 9) {
				scene_->actors_.emplace_back(new EffectTail(scene_));
			}
			else {
				scene_->actors_.emplace_back(new EffectBite(scene_, r_[i]));
				scene_->actors_.emplace_back(new EffectBite(scene_, r_[i] + 1));
			}
		}
	}
	elapsed_++;

	if (elapsed_ >= ATTACK_INTERVAL_SLOW_ * 10 + FLOW_INTERVAL_ + 1) { //終了
		elapsed_ = 0;
		action_ = -1;
	}
}

void BossKing::attackRangeB() {
	for (int i = 0; i < 14; i++) {
		if (elapsed_ == ATTACK_INTERVAL_FAST_ * i) { //1つ目のノーツ生成
			if (i == 3 || i == 7 || i == 10 || i == 11 || i == 13) {
				scene_->actors_.emplace_back(new NotesWarningAll(scene_, ATK_RANGE_, 0));
				scene_->actors_.emplace_back(new NotesWarningAll(scene_, ATK_RANGE_, 1));
				scene_->actors_.emplace_back(new NotesWarningAll(scene_, ATK_RANGE_, 2));
				scene_->actors_.emplace_back(new NotesWarningAll(scene_, ATK_RANGE_, 3));
			}
			else {
				r_[i] = rand() % 4;
				if (i > 0) {
					if (r_[i] == r_[i - 1]) {
						r_[i] = (r_[i] + 1) % 4;
					}
				}
				scene_->actors_.emplace_back(new NotesWarning(scene_, ATK_MELEE_, r_[i]));
			}
		}
		if (elapsed_ == ATTACK_INTERVAL_FAST_ * i + FLOW_INTERVAL_ - MOVE_SPEED_) { //1つ目のノーツに向かって移動
			if (i == 3 || i == 7 || i == 10 || i == 11 || i == 13) {
				setMove(0, MELEE_POS_Z_);
			}
			else {
				setMove(POS_X_[r_[i]], MELEE_POS_Z_);
			}
		}
		if (elapsed_ == ATTACK_INTERVAL_FAST_ * i + FLOW_INTERVAL_) { //1つ目のノーツのエフェクトを生成
			if (i == 3 || i == 7 || i == 10 || i == 11 || i == 13) {
				scene_->actors_.emplace_back(new EffectTail(scene_));
			}
			else {
				scene_->actors_.emplace_back(new EffectCrow(scene_, r_[i]));
			}
		}
	}
	elapsed_++;

	if (elapsed_ >= ATTACK_INTERVAL_FAST_ * 14 + FLOW_INTERVAL_ + 1) { //終了
		elapsed_ = 0;
		action_ = -1;
	}
}

void BossKing::attackBulletA() {
	for (int i = 0; i < 15; i++) {
		if (elapsed_ == ATTACK_INTERVAL_FAST_ * i) { //1つ目のノーツ生成位置に移動
			r_[i] = rand() % 4;
			if (i > 0) {
				if (r_[i] == r_[i - 1]) {
					r_[i] = (r_[i] + 2) % 4;
				}
			}
			setMove(POS_X_[r_[i]], BULLET_POS_Z_);
		}
		if (elapsed_ == ATTACK_INTERVAL_FAST_ * i + MOVE_SPEED_) { //1つ目のノーツ生成
			scene_->actors_.emplace_back(new NotesDragonBless(scene_, ATK_BULLET_, r_[i]));
		}
	}
	elapsed_++;

	if (elapsed_ >= ATTACK_INTERVAL_FAST_ * 15 + BULLET_INTERVAL_ + 1) { //終了
		elapsed_ = 0;
		action_ = -1;
	}
}

void BossKing::attackBulletB() {
	for (int i = 0; i < 20; i++) {
		if (elapsed_ == ATTACK_INTERVAL_FAST_ * i) { //1つ目のノーツ生成位置に移動
			r_[i] = rand() % 3 + 1;
			if (i == 0) {
				setMove(0, BULLET_POS_Z_);
			}
		}
		if (elapsed_ == ATTACK_INTERVAL_FAST_ * i + MOVE_SPEED_) { //1つ目のノーツ生成
			if (i == 0) {
				scene_->actors_.emplace_back(new EffectMaho(scene_,5));
			}
			scene_->actors_.emplace_back(new NotesKingBless(scene_, ATK_BULLET_, r_[i]));
			r_[i] = (r_[i] + rand() % 3 + 1) % 4;
			scene_->actors_.emplace_back(new NotesKingBless(scene_, ATK_BULLET_, r_[i]));
		}
	}
	elapsed_++;

	if (elapsed_ >= ATTACK_INTERVAL_FAST_ * 20 + BULLET_INTERVAL_ + 1) { //終了
		elapsed_ = 0;
		action_ = -1;
	}
}

void BossKing::update(float delta_time) {
	if (move_flame_ != 0) move(dir_x_, dir_z_);
	if (action_ != -1)switchAction();
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
			scene_->score_ += 10 * scene_->combo_ * 2;
			scene_->bgm_->perfect_ = true;
			judge_ = perfect;
			scene_->combo_++;
		}
	}
	else if (mesh_->pos_.z < JUDGE_Z_ + RANGE_GOOD_ && mesh_->pos_.z >= JUDGE_Z_ - RANGE_GOOD_ && judge_ != good && judge_ != perfect) {
		if (judgeKey()) {
			//グッド判定処理
			scene_->subUis_.emplace_back(new SubUiJudge(scene_, good, lane_));
			scene_->score_ += 10 * scene_->combo_;
			scene_->bgm_->perfect_ = true;
			judge_ = good;
			scene_->combo_++;
		}
	}
	else if (mesh_->pos_.z >= MISS_Z_ - RANGE_MISS_ && mesh_->pos_.z < MISS_Z_
		&& mesh_->pos_.x == scene_->player_->mesh_->pos_.x && judge_ != miss) {
		//失敗判定処理
		scene_->subUis_.emplace_back(new SubUiJudge(scene_, miss, lane_));
		scene_->actors_.emplace_back(new EffectHit(scene_, lane_));
		scene_->subUis_.emplace_back(new SubUiPlayerDamage(scene_, damage_, scene_->player_->lane_));
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
			scene_->actors_.emplace_back(new EffectGard(scene_, lane_));
			scene_->score_ += 30 * scene_->combo_ * 2;
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
			scene_->actors_.emplace_back(new EffectGard(scene_, lane_));
			scene_->score_ += 30 * scene_->combo_;
			scene_->bgm_->perfect_ = true;
			judge_ = good;
			scene_->combo_++;
			alive_ = false;
		}
	}
	else if ((mesh_->pos_.z >= MISS_Z_ - RANGE_MISS_ && mesh_->pos_.z < MISS_Z_
		&& mesh_->pos_.x == scene_->player_->mesh_->pos_.x && judge_ != miss) || 
		(mesh_->pos_.z >= JUDGE_Z_ + RANGE_GOOD_ && mesh_->pos_.z < JUDGE_Z_ + RANGE_GOOD_ + RANGE_MISS_
			&& mesh_->pos_.x == scene_->player_->mesh_->pos_.x && judge_ != miss && tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE))) {
		//失敗判定処理
		scene_->subUis_.emplace_back(new SubUiJudge(scene_, miss, lane_));
		scene_->actors_.emplace_back(new EffectHit(scene_, lane_));
		scene_->subUis_.emplace_back(new SubUiPlayerDamage(scene_, damage_, scene_->player_->lane_));
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
	mesh_->pos_.z = BULLET_POS_Z_;
}

void NotesDragonBless::update(float delta_time) {
	flow(scene_->NOTES_SPEED_);
	judge();
}

NotesKeruberosBless::NotesKeruberosBless(ScenePlay* scene, int damage, int lane) {
	initialize(scene, damage, lane);
	mesh_->pos_.z = BULLET_POS_Z_;
}

void NotesKeruberosBless::update(float delta_time) {
	flow(scene_->NOTES_SPEED_);
	judge();
}

NotesSkallSward::NotesSkallSward(ScenePlay* scene, int damage, int lane) {
	scene_ = scene;
	lane_ = lane;
	damage_ = damage;
	getImage();
	mesh_ = dxe::Mesh::CreatePlane({ MESH_W_ * 0.5f, MESH_H_ * 2, 0 });
	mesh_->setTexture(dxe::Texture::CreateFromFile(*it));
	it++;
	mesh_->pos_ = { POS_X_[lane_],POS_Y_,POS_Z_ };
	mesh_->rot_q_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(60));
	mesh_->pos_.z = BULLET_POS_Z_;
}

void NotesSkallSward::update(float delta_time) {
	flow(scene_->NOTES_SPEED_);
	judge();
}

NotesAnkouBless::NotesAnkouBless(ScenePlay* scene, int damage, int lane) {
	initialize(scene, damage, lane);
	mesh_->pos_.z = BULLET_POS_Z_;
}

void NotesAnkouBless::update(float delta_time) {
	flow(scene_->NOTES_SPEED_);
	judge();
}

NotesKingBless::NotesKingBless(ScenePlay* scene, int damage, int lane) {
	initialize(scene, damage, lane);
	mesh_->pos_.z = BULLET_POS_Z_;
}

void NotesKingBless::update(float delta_time) {
	flow(scene_->NOTES_SPEED_);
	judge();
}