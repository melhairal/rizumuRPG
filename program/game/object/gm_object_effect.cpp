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

EffectSkillGood::EffectSkillGood(ScenePlay* scene, int lane) {
	scene_ = scene;
	getImage();
	mesh_ = dxe::Mesh::CreatePlane({ MESH_W_ * 2, MESH_H_ * 2, 0 });
	mesh_->setTexture(dxe::Texture::CreateFromFile(*it));
	it++;
	mesh_->pos_ = { POS_X_[lane],POS_Y_,POS_Z_ };
	mesh_->rot_q_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(60));
}

void EffectSkillGood::update(float delta_time) {
	//アニメーション更新
	animation(FRAME_);
	if (it == images_.begin()) {
		alive_ = false;
	}
}
EffectSkillPerfect::EffectSkillPerfect(ScenePlay* scene, int lane) {
	scene_ = scene;
	getImage();
	mesh_ = dxe::Mesh::CreatePlane({ MESH_W_ * 2, MESH_H_ * 2, 0 });
	mesh_->setTexture(dxe::Texture::CreateFromFile(*it));
	it++;
	mesh_->pos_ = { POS_X_[lane],POS_Y_,POS_Z_ };
	mesh_->rot_q_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(60));
}

void EffectSkillPerfect::update(float delta_time) {
	//アニメーション更新
	animation(FRAME_);
	if (it == images_.begin()) {
		alive_ = false;
	}
}

EffectCrow::EffectCrow(ScenePlay* scene, int lane) {
	scene_ = scene;
	getImage();
	mesh_ = dxe::Mesh::CreatePlane({ MESH_W_ * 3, MESH_H_ * 3, 0 });
	mesh_->setTexture(dxe::Texture::CreateFromFile(*it));
	it++;
	mesh_->pos_ = { POS_X_[lane],POS_Y_,POS_Z_ };
	mesh_->rot_q_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(60));
}

void EffectCrow::update(float delta_time) {
	//アニメーション更新
	animation(FRAME_);
	if (it == images_.begin()) {
		alive_ = false;
	}
}

EffectTail::EffectTail(ScenePlay* scene) {
	scene_ = scene;
	getImage();
	mesh_ = dxe::Mesh::CreatePlane({ MESH_W_ * 4, MESH_H_ * 3, 0 });
	mesh_->setTexture(dxe::Texture::CreateFromFile(*it));
	it++;
	mesh_->pos_ = { 0,POS_Y_,POS_Z_ };
	mesh_->rot_q_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(60));
}

void EffectTail::update(float delta_time) {
	//アニメーション更新
	animation(FRAME_);
	if (it == images_.begin()) {
		alive_ = false;
	}
}

EffectBite::EffectBite(ScenePlay* scene, int lane) {
	scene_ = scene;
	getImage();
	mesh_ = dxe::Mesh::CreatePlane({ MESH_W_ * 3, MESH_H_ * 3, 0 });
	mesh_->setTexture(dxe::Texture::CreateFromFile(*it));
	it++;
	mesh_->pos_ = { POS_X_[lane],POS_Y_,POS_Z_ };
	mesh_->rot_q_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(60));
}

void EffectBite::update(float delta_time) {
	//アニメーション更新
	animation(FRAME_);
	if (it == images_.begin()) {
		alive_ = false;
	}
}

EffectMaho::EffectMaho(ScenePlay* scene, int loop) {
	scene_ = scene;
	getImage();
	mesh_ = dxe::Mesh::CreatePlane({ MESH_W_ * 4, MESH_H_ * 3, 0 });
	mesh_->setTexture(dxe::Texture::CreateFromFile(*it));
	it++;
	mesh_->pos_ = { 0,POS_Y_ * 3,POS_Z_ };
	mesh_->rot_q_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(60));
	loop_num_ = loop;
}

void EffectMaho::update(float delta_time) {
	//アニメーション更新
	animation(FRAME_);
	if (it == images_.begin()) {
		if (elapsed_ == 0) {
			loop_count_++;
		}
		if (loop_count_ >= loop_num_) {
			alive_ = false;
		}
	}
}

EffectGard::EffectGard(ScenePlay* scene, int lane) {
	scene_ = scene;
	getImage();
	mesh_ = dxe::Mesh::CreatePlane({ MESH_W_ * 2, MESH_H_ * 2, 0 });
	mesh_->setTexture(dxe::Texture::CreateFromFile(*it));
	it++;
	mesh_->pos_ = { POS_X_[lane],POS_Y_,POS_Z_ };
	mesh_->rot_q_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(60));
}

void EffectGard::update(float delta_time) {
	//アニメーション更新
	animation(FRAME_);
	if (it == images_.begin()) {
		alive_ = false;
	}
}

EffectClear::EffectClear(ScenePlay* scene) {
	scene_ = scene;
	getImage();
	mesh_ = dxe::Mesh::CreatePlane({ MESH_W_ * 5, MESH_H_ * 5, 0 });
	mesh_->setTexture(dxe::Texture::CreateFromFile(*it));
	it++;
	mesh_->pos_ = { 0,POS_Y_,0 };
	mesh_->rot_q_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(60));
}

void EffectClear::update(float delta_time) {
	//アニメーション更新
	animation(FRAME_);
	if (it == images_.begin()) {
		alive_ = false;
	}
}