#include "gm_boss.h"
#include "scene/gm_scene_play.h"
#include "object/gm_object_actor.h"
#include "gm_camera.h"

Boss::Boss(ScenePlay* scene) {
	scene_ = scene;
}

void Boss::update(float delta_time) {

	elapsed_++;
	if (elapsed_ < 120) {
		tnl::Vector3 rot = { tnl::ToRadian(-0.35f), 0, 0 };
		scene_->camera_->free_look_angle_xy_ += rot;
		scene_->player_->mesh_->rot_q_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(-0.35f));
		scene_->player_->mesh_->pos_.y += 0.05f;
	}
	else {

	}


}