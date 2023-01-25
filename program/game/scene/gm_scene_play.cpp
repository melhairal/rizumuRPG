#include "../gm_manager.h"
#include "../gm_camera.h"
#include "../model/gm_anim_sprite3d.h"
#include "gm_scene_play.h"
#include "gm_scene_result.h"
#include "../gm_ui.h"
#include "../gm_bgm.h"
#include "../gm_sheet_music.h"
#include "../gm_make_sheet.h"
#include "../object/gm_object_ground.h"
#include "../object/gm_object_actor.h"
#include "../object/gm_object_player.h"
#include "../object/gm_object_enemy.h"
#include "../gm_boss.h"


tnl::Quaternion	fix_rot;

ScenePlay::~ScenePlay() {
	delete camera_;
	delete ui_;
	delete bgm_;
	delete frame_;
	if (sheet_ != nullptr) delete sheet_;
	if (make_ != nullptr) delete make_;
	if (boss_ != nullptr) delete boss_;
	for (auto object : objects_) delete object;
	for (auto actor : actors_) delete actor;
	for (auto ui : subUis_) delete ui;
}


void ScenePlay::initialzie() {
	//カメラの生成
	camera_ = new GmCamera();
	camera_->target_ = { 0,0,0 };

	//uiの生成
	ui_ = new Ui(this);

	//bgmの生成
	bgm_ = new Bgm(this);
	
	//マスの生成
	frame_ = dxe::Mesh::CreatePlane({ FIELD_W_,FIELD_H_,0 });
	frame_->setTexture(dxe::Texture::CreateFromFile("graphics/base/frame.png"));
	frame_->rot_q_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(90));
	frame_->pos_ = { 0, 0, FIELD_Z1_ };

	//背景と床の生成
	objects_.emplace_back(new Ground(this, BACK_W_, FIELD_H_, FIELD_Z1_, back_img));
	objects_.emplace_back(new Ground(this, BACK_W_, FIELD_H_, FIELD_Z2_, back_img));
	objects_.emplace_back(new Ground(this, FIELD_W_, FIELD_H_, FIELD_Z1_, road_img));
	objects_.emplace_back(new Ground(this, FIELD_W_, FIELD_H_, FIELD_Z2_, road_img));

	//プレイヤーの生成
	player_ = actors_.emplace_back(new Player(this));
}

void ScenePlay::update(float delta_time)
{
	GameManager* mgr = GameManager::GetInstance();

	//aliveがfalseになったオブジェクトを消す
	deleteList();

	//オブジェクト制御
	updateObject(delta_time);

	//アクター制御
	updateActor(delta_time);

	//UIアップデート
	ui_->update(delta_time);
	updateSubUi(delta_time);

	//Bgmアップデート
	bgm_->update(delta_time);

	//譜面アップテート
	if (sheet_ != nullptr) {
		sheet_->update(delta_time);
		if (!sheet_->alive_) {
			delete sheet_;
			sheet_ = nullptr;
		}
	}

	//譜面作成アップデート
	if (make_ != nullptr) make_->update(delta_time);

	//ボス戦アップデート
	if (boss_ != nullptr) boss_->update(delta_time);

	//値のクランプ
	hp_ = std::clamp(hp_, 0, hp_max_);
	mp_ = std::clamp(mp_, 0, mp_max_);
	combo_ = std::clamp(combo_, 0, 999);
	score_ = std::clamp(score_, 0, 9999999);

	// ==================== デバッグ等 ====================
	
	Debug(delta_time);

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		mgr->chengeScene(new SceneResult());
	}
}

void ScenePlay::render()
{
	camera_->update();
	DrawGridGround(camera_, 50, 20);

	//ボス戦描画
	if (boss_ != nullptr) boss_->render();

	//全オブジェクトの描画
	for (auto object : objects_) {
		if (object->mesh_ != nullptr) object->mesh_->render(camera_);
	}

	//譜面作成用描画
	if (make_ != nullptr) make_->render();

	//マスの描画
	frame_->render(camera_);

	//全アクターの描画
	for (auto actor : actors_) {
		if (actor->mesh_ != nullptr) actor->mesh_->render(camera_);
	}

	//UIの描画
	ui_->render();
	for (auto ui : subUis_) {
		ui->render();
	}


	// ==================== デバッグ等 ====================

	DrawStringEx(50, 50, -1, "scene play");
}

void ScenePlay::updateObject(float delta_time) {
	//全てのオブジェクトのアップデート
	for (auto object : objects_) {
		if (object->move_)	object->update(delta_time);
	}
}

void ScenePlay::updateActor(float delta_time) {
	//全てのアクターのアップデート
	for (auto actor : actors_) {
		if (actor->move_)	actor->update(delta_time);
	}

	// カメラに近い順にソート(近いオブジェクトから描画するため)
	actors_.sort([&](const Actor* l, const Actor* r) {
		float ld = 0;
		float rd = 0;
		if (l->mesh_ != nullptr) ld = (camera_->pos_ - l->mesh_->pos_).length();
		if (r->mesh_ != nullptr) rd = (camera_->pos_ - r->mesh_->pos_).length();
		return ld > rd;
		});
}

void ScenePlay::updateSubUi(float delta_time) {
	//全てのオブジェクトのアップデート
	for (auto ui : subUis_) {
		if (ui->move_)	ui->update(delta_time);
	}
}

void ScenePlay::deleteList() {
	//オブジェクトの生存フラグがfalseになったらデリート
	auto it_object = objects_.begin();
	while (it_object != objects_.end()) {
		if (!(*it_object)->alive_) {
			delete (*it_object);
			it_object = objects_.erase(it_object);
			continue;
		}
		it_object++;
	}

	//アクターの生存フラグがfalseになったらデリート
	auto it_actor = actors_.begin();
	while (it_actor != actors_.end()) {
		if (!(*it_actor)->alive_) {
			delete (*it_actor);
			it_actor = actors_.erase(it_actor);
			continue;
		}
		it_actor++;
	}

	//サブUIの生存フラグがfalseになったらデリート
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

void ScenePlay::Debug(float delta_time) {
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_A)) {
		make_ = new MakeSheet(this);
	}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_Q)) {
		combo_++;
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_W)) {
		combo_ = 0;
	}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_Z)) {
		sheet_ = new Sheet(this, stage_2_csv_);
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_1)) {
		boss_->enemy_->action_ = 0;
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_2)) {
		boss_->enemy_->action_ = 1;
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_3)) {
		boss_->enemy_->action_ = 2;
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_4)) {
		boss_->enemy_->action_ = 3;
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_5)) {
		boss_->enemy_->action_ = 4;
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_6)) {
		boss_->enemy_->action_ = 5;
	}


	//デバッグ用（スキルアップデート）

}