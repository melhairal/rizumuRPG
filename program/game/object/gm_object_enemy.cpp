#include "gm_object_enemy.h"
#include "../scene/gm_scene_play.h"
#include "../gm_camera.h"

void EnemyBase::Initialize(ScenePlay* scene, int lane) {
	scene_ = scene;
	getImage();
	mesh_ = dxe::Mesh::CreatePlane({ MESH_W_, MESH_H_, 0 });
	mesh_->setTexture(dxe::Texture::CreateFromFile(*it));
	it++;
	mesh_->pos_ = { POS_X_[lane],POS_Y_,POS_Z_ };
	mesh_->rot_q_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(60));
}

void EnemyBase::flow(float speed) {
	mesh_->pos_.z -= speed;
	if (mesh_->pos_.z < DEAD_Z_) alive_ = false;
}

bool EnemyBase::checkLane() {
	if (scene_->player_->mesh_->pos_.x == mesh_->pos_.x) return true;
	else return false;
}


EnemyPig::EnemyPig(ScenePlay* scene, int lane) {
	//ƒƒbƒVƒ…‰Šú‰»
	Initialize(scene, lane);
}

void EnemyPig::update(float delta_time) {
	onPlayerLane = checkLane();
	flow(SPEED_);
}