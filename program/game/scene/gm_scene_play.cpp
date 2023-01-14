#include "../gm_manager.h"
#include "../gm_camera.h"
#include "../model/gm_anim_sprite3d.h"
#include "gm_scene_play.h"
#include "gm_scene_result.h"
#include "../gm_ui.h"
#include "../gm_bgm.h"
#include "../object/gm_object_ground.h"
#include "../object/gm_object_actor.h"
#include "../object/gm_object_player.h"
#include "../object/gm_object_enemy.h"

tnl::Quaternion	fix_rot;

ScenePlay::~ScenePlay() {
	delete camera_;
	delete ui_;
	delete bgm_;
	delete frame_;
	for (auto object : objects_) delete object;
	for (auto actor : actors_) delete actor;
	for (auto ui : subUis_) delete ui;
}


void ScenePlay::initialzie() {
	//�J�����̐���
	camera_ = new GmCamera();
	camera_->target_ = { 0,0,0 };

	//ui�̐���
	ui_ = new Ui(this);

	//bgm�̐���
	bgm_ = new Bgm(this);
	
	//�}�X�̐���
	frame_ = dxe::Mesh::CreatePlane({ FIELD_W_,FIELD_H_,0 });
	frame_->setTexture(dxe::Texture::CreateFromFile("graphics/base/frame.png"));
	frame_->rot_q_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(90));
	frame_->pos_ = { 0, 0, FIELD_Z1_ };

	//�w�i�Ə��̐���
	objects_.emplace_back(new Ground(this, BACK_W_, FIELD_H_, FIELD_Z1_, back_img));
	objects_.emplace_back(new Ground(this, BACK_W_, FIELD_H_, FIELD_Z2_, back_img));
	objects_.emplace_back(new Ground(this, FIELD_W_, FIELD_H_, FIELD_Z1_, road_img));
	objects_.emplace_back(new Ground(this, FIELD_W_, FIELD_H_, FIELD_Z2_, road_img));

	//�v���C���[�̐���
	player_ = actors_.emplace_back(new Player(this));
}

void ScenePlay::update(float delta_time)
{
	GameManager* mgr = GameManager::GetInstance();

	//�I�u�W�F�N�g����
	updateObject(delta_time);

	//�A�N�^�[����
	updateActor(delta_time);

	//UI�A�b�v�f�[�g
	ui_->update(delta_time);
	updateSubUi(delta_time);

	//Bgm�A�b�v�f�[�g
	bgm_->update(delta_time);

	//�l�̃N�����v
	hp_ = std::clamp(hp_, 0, hp_max_);
	mp_ = std::clamp(mp_, 0, mp_max_);
	combo_ = std::clamp(combo_, 0, 999);
	score_ = std::clamp(score_, 0, 9999999);

	// ==================== �f�o�b�O�� ====================

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_1)) {
		actors_.emplace_back(new EnemyPig(this,EnemyBase::LL));
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_2)) {
		actors_.emplace_back(new EnemyPig(this, EnemyBase::L));
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_3)) {
		actors_.emplace_back(new EnemyRizard(this, EnemyBase::R));
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_4)) {
		actors_.emplace_back(new EnemyRizard(this, EnemyBase::RR));
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_Q)) {
		combo_++;
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_W)) {
		combo_ = 0;
	}

	progress_++;

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		mgr->chengeScene(new SceneResult());
	}
}

void ScenePlay::render()
{
	camera_->update();
	DrawGridGround(camera_, 50, 20);

	//�S�I�u�W�F�N�g�̕`��
	for (auto object : objects_) {
		if (object->mesh_ != nullptr) object->mesh_->render(camera_);
	}

	//�}�X�̕`��
	frame_->render(camera_);

	//�S�A�N�^�[�̕`��
	for (auto actor : actors_) {
		if (actor->mesh_ != nullptr) actor->mesh_->render(camera_);
	}

	//UI�̕`��
	ui_->render();
	for (auto ui : subUis_) {
		ui->render();
	}

	// ==================== �f�o�b�O�� ====================

	DrawStringEx(50, 50, -1, "scene play");

}

void ScenePlay::updateObject(float delta_time) {
	//�S�ẴI�u�W�F�N�g�̃A�b�v�f�[�g
	for (auto object : objects_) {
		if (object->move_)	object->update(delta_time);
	}

	//�I�u�W�F�N�g�̐����t���O��false�ɂȂ�����f���[�g
	auto it_object = objects_.begin();
	while (it_object != objects_.end()) {
		if (!(*it_object)->alive_) {
			delete (*it_object);
			it_object = objects_.erase(it_object);
			continue;
		}
		it_object++;
	}
}

void ScenePlay::updateActor(float delta_time) {
	//�S�ẴA�N�^�[�̃A�b�v�f�[�g
	for (auto actor : actors_) {
		if (actor->move_)	actor->update(delta_time);
	}

	//�A�N�^�[�̐����t���O��false�ɂȂ�����f���[�g
	auto it_actor = actors_.begin();
	while (it_actor != actors_.end()) {
		if (!(*it_actor)->alive_) {
			delete (*it_actor);
			it_actor = actors_.erase(it_actor);
			continue;
		}
		it_actor++;
	}

	// �J�����ɋ߂����Ƀ\�[�g(�߂��I�u�W�F�N�g����`�悷�邽��)
	actors_.sort([&](const Actor* l, const Actor* r) {
		float ld = 0;
		float rd = 0;
		if (l->mesh_ != nullptr) ld = (camera_->pos_ - l->mesh_->pos_).length();
		if (r->mesh_ != nullptr) rd = (camera_->pos_ - r->mesh_->pos_).length();
		return ld > rd;
		});
}

void ScenePlay::updateSubUi(float delta_time) {
	//�S�ẴI�u�W�F�N�g�̃A�b�v�f�[�g
	for (auto ui : subUis_) {
		if (ui->move_)	ui->update(delta_time);
	}

	//�I�u�W�F�N�g�̐����t���O��false�ɂȂ�����f���[�g
	auto it_ui = subUis_.begin();
	while (it_ui != subUis_.end()) {
		if (!(*it_ui)->alive_) {
			delete (*it_ui);
			it_ui = subUis_.erase(it_ui);
			continue;
		}
		it_ui++;
	}
}