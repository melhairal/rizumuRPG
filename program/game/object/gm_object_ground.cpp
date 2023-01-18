#include "gm_object_ground.h"
#include "../scene/gm_scene_play.h"

Ground::Ground(ScenePlay* scene, float w, float h , float z, std::string img) {
	scene_ = scene;
	mesh_w_ = w;
	mesh_h_ = h;
	mesh_ = dxe::Mesh::CreatePlane({ mesh_w_,mesh_h_,0 });
	mesh_->setTexture(dxe::Texture::CreateFromFile(img));
	mesh_->rot_q_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(90));
	mesh_->pos_ = { 0, 0, z };
}

void Ground::update(float delta_time) {
	mesh_->pos_.z -= SPEED_;
	if (mesh_->pos_.z <= MIN_) mesh_->pos_.z = MAX_;
}

Line::Line(ScenePlay* scene) {
	scene_ = scene;
	mesh_ = dxe::Mesh::CreatePlane({ MESH_W_,MESH_H_,0 });
	mesh_->setTexture(dxe::Texture::CreateFromFile("graphics/base/line.png"));
	mesh_->rot_q_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(90));
	mesh_->pos_ = { 0, 0, POS_Z_ };
}

void Line::update(float delta_time) {
	mesh_->pos_.z -= scene_->NOTES_SPEED_;
	if (mesh_->pos_.z <= DEAD_Z_) mesh_->pos_.z = POS_Z_;
}