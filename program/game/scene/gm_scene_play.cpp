#include "../gm_manager.h"
#include "../gm_camera.h"
#include "../model/gm_anim_sprite3d.h"
#include "gm_scene_play.h"
#include "gm_scene_result.h"
#include "../object/gm_object_ground.h"
#include "../object/gm_object_actor.h"

tnl::Quaternion	fix_rot;

ScenePlay::~ScenePlay() {
	delete camera_;
	for (auto object : objects_) delete object;
	for (auto actor : actors_) delete actor;
}


void ScenePlay::initialzie() {
	camera_ = new GmCamera();
	camera_->target_ = { 0,0,0 };

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
	actors_.emplace_back(new Player(this));
}

void ScenePlay::update(float delta_time)
{
	GameManager* mgr = GameManager::GetInstance();

	//オブジェクト制御
	updateObject(delta_time);

	//アクター制御
	updateActor(delta_time);


	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		mgr->chengeScene(new SceneResult());
	}
}

void ScenePlay::render()
{
	camera_->update();
	DrawGridGround(camera_, 50, 20);

	//全オブジェクトの描画
	for (auto object : objects_) {
		if (object->mesh_ != nullptr) object->mesh_->render(camera_);
	}

	//マスの描画
	frame_->render(camera_);

	//全アクターの描画
	for (auto actor : actors_) {
		if (actor->mesh_ != nullptr) actor->mesh_->render(camera_);
	}

	DrawStringEx(50, 50, -1, "scene play");

}

void ScenePlay::updateObject(float delta_time) {
	//全てのオブジェクトのアップデート
	for (auto object : objects_) {
		if (object->move_)	object->update(delta_time);
	}

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
}

void ScenePlay::updateActor(float delta_time) {
	//全てのアクターのアップデート
	for (auto actor : actors_) {
		if (actor->move_)	actor->update(delta_time);
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
}