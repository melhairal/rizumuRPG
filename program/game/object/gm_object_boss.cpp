#include "gm_object_boss.h"
#include "../scene/gm_scene_play.h"
#include "../gm_camera.h"

BossEnemy::BossEnemy(ScenePlay* scene) {
	scene_ = scene;
	getImage();
	mesh_ = dxe::Mesh::CreatePlane({ MESH_W_ * 2, MESH_H_ * 2, 0 });
	mesh_->setTexture(dxe::Texture::CreateFromFile(*it));
	it++;
	mesh_->pos_ = { POS_X_[L],POS_Y_ * 2,POS_Z_ };
	mesh_->rot_q_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(60));
}

void BossEnemy::update(float delta_time) {

}