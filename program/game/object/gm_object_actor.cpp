#include "gm_object_actor.h"
#include "../scene/gm_scene_play.h"
#include "../gm_camera.h"

void Actor::animation(int frame) {
	elapsed_++;
	if (elapsed_ >= frame) {
		elapsed_ = 0;
		frame_++;
		mesh_->setTexture(dxe::Texture::CreateFromFile(*it));
		it++;
		if (it == images_.end()) it = images_.begin();
	}
}

Player::Player(ScenePlay* scene) {
	scene_ = scene;
	getImage();
	mesh_ = dxe::Mesh::CreatePlane({ MESH_W_, MESH_H_, 0 });
	mesh_->setTexture(dxe::Texture::CreateFromFile(*it));
	it++;
	mesh_->pos_ = { X_L_,POS_Y_,POS_Z_ };
	mesh_->rot_q_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(60));
}

void Player::update(float delta_time) {
	//アニメーション更新
	animation(FRAME_);

	//キーで他のラインに移動
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_D)) mesh_->pos_.x = X_LL_;
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_F)) mesh_->pos_.x = X_L_;
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_J)) mesh_->pos_.x = X_R_;
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_K)) mesh_->pos_.x = X_RR_;
}