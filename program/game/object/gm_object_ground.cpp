#include "gm_object_ground.h"

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
	if (mesh_->pos_.z == MIN_) mesh_->pos_.z = MAX_;
}