#include "gm_object_player.h"
#include "../scene/gm_scene_play.h"
#include "../gm_camera.h"

Player::Player(ScenePlay* scene) {
	scene_ = scene;
	getImage();
	mesh_ = dxe::Mesh::CreatePlane({ MESH_W_, MESH_H_, 0 });
	mesh_->setTexture(dxe::Texture::CreateFromFile(*it));
	it++;
	mesh_->pos_ = { POS_X_[L],POS_Y_,POS_Z_ };
	mesh_->rot_q_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(60));
}

void Player::update(float delta_time) {
	//アニメーション更新
	animation(FRAME_);

	//キーで他のラインに移動
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_D)) {
		mesh_->pos_.x = POS_X_[LL]; 
		lane_ = LL;
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_F)) {
		mesh_->pos_.x = POS_X_[L];
		lane_ = L;
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_J)) {
		mesh_->pos_.x = POS_X_[R];
		lane_ = R;
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_K)) {
		mesh_->pos_.x = POS_X_[RR];
		lane_ = RR;
	}
}