#include "gm_object_effect.h"
#include "../scene/gm_scene_play.h"
#include "../gm_camera.h"

EffectHit::EffectHit(ScenePlay* scene, int lane) {
	scene_ = scene;
	getImage();
	mesh_ = dxe::Mesh::CreatePlane({ MESH_W_, MESH_H_, 0 });
	mesh_->setTexture(dxe::Texture::CreateFromFile(*it));
	it++;
	mesh_->pos_ = { POS_X_[lane],POS_Y_,POS_Z_ };
	mesh_->rot_q_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(60));
}

void EffectHit::update(float delta_time) {
	//アニメーション更新
	animation(FRAME_);
	if (it == images_.begin()) {
		alive_ = false;
	}
}

EffectGood::EffectGood(ScenePlay* scene, int lane) {
	scene_ = scene;
	getImage();
	mesh_ = dxe::Mesh::CreatePlane({ MESH_W_, MESH_H_, 0 });
	mesh_->setTexture(dxe::Texture::CreateFromFile(*it));
	it++;
	mesh_->pos_ = { POS_X_[lane],POS_Y_,POS_Z_ };
	mesh_->rot_q_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(60));
}

void EffectGood::update(float delta_time) {
	//アニメーション更新
	animation(FRAME_);
	if (it == images_.begin()) {
		alive_ = false;
	}
}
EffectPerfect::EffectPerfect(ScenePlay* scene, int lane) {
	scene_ = scene;
	getImage();
	mesh_ = dxe::Mesh::CreatePlane({ MESH_W_, MESH_H_, 0 });
	mesh_->setTexture(dxe::Texture::CreateFromFile(*it));
	it++;
	mesh_->pos_ = { POS_X_[lane],POS_Y_,POS_Z_ };
	mesh_->rot_q_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(60));
}

void EffectPerfect::update(float delta_time) {
	//アニメーション更新
	animation(FRAME_);
	if (it == images_.begin()) {
		alive_ = false;
	}
}