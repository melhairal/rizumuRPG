#include "gm_boss.h"
#include "scene/gm_scene_play.h"
#include "object/gm_object_actor.h"
#include "object/gm_object_boss.h"
#include "object/gm_object_ground.h"
#include "gm_camera.h"

Boss::Boss(ScenePlay* scene) {
	//ƒV[ƒ“ƒ|ƒCƒ“ƒ^Žæ“¾
	scene_ = scene;

	//°‚ÌÄ¶¬
	scene_->objects_.emplace_back(new Ground(scene_, scene_->BACK_W_, scene_->FIELD_H_, scene_->FIELD_Z1_, scene_->back_img))->move_ = false;
	scene_->objects_.emplace_back(new Ground(scene_, scene_->BACK_W_, scene_->FIELD_H_, scene_->FIELD_Z2_, scene_->back_img))->move_ = false;
	scene_->objects_.emplace_back(new Ground(scene_, scene_->FIELD_W_, scene_->FIELD_H_, scene_->FIELD_Z1_, scene_->road_img))->move_ = false;
	scene_->objects_.emplace_back(new Ground(scene_, scene_->FIELD_W_, scene_->FIELD_H_, scene_->FIELD_Z2_, scene_->road_img))->move_ = false;

	//°‚Ì•âŠ®
	field_l1_ = dxe::Mesh::CreatePlane({ scene_->BACK_W_,scene_->FIELD_H_,0 });
	field_l1_->setTexture(dxe::Texture::CreateFromFile(scene_->back_img));
	field_l1_->rot_q_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(90));
	field_l1_->pos_ = { LEFT_X_, 0, scene_->FIELD_Z2_ };

	field_r1_ = dxe::Mesh::CreatePlane({ scene_->BACK_W_,scene_->FIELD_H_,0 });
	field_r1_->setTexture(dxe::Texture::CreateFromFile(scene_->back_img));
	field_r1_->rot_q_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(90));
	field_r1_->pos_ = { RIGHT_X_, 0, scene_->FIELD_Z2_ };

	field_l2_ = dxe::Mesh::CreatePlane({ scene_->BACK_W_,scene_->FIELD_H_,0 });
	field_l2_->setTexture(dxe::Texture::CreateFromFile(scene_->back_img));
	field_l2_->rot_q_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(90));
	field_l2_->pos_ = { LEFT_X_, 0, scene_->FIELD_Z1_ };

	field_r2_ = dxe::Mesh::CreatePlane({ scene_->BACK_W_,scene_->FIELD_H_,0 });
	field_r2_->setTexture(dxe::Texture::CreateFromFile(scene_->back_img));
	field_r2_->rot_q_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(90));
	field_r2_->pos_ = { RIGHT_X_, 0, scene_->FIELD_Z1_ };

	road_ = dxe::Mesh::CreatePlane({ scene_->BACK_W_,scene_->FIELD_H_,0 });
	road_->setTexture(dxe::Texture::CreateFromFile(scene_->road_img));
	road_->rot_q_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(90));
	road_->pos_ = { 0, 0, ROAD_Z_ };

	//”wŒi
	back_ = LoadGraph("graphics/base/sky.jpg");

	//ƒ{ƒX
	enemy_ = scene_->actors_.emplace_back(new BossEnemy(scene_));
}

void Boss::update(float delta_time) {

	elapsed_++;
	if (elapsed_ < 120) {
		tnl::Vector3 rot = { tnl::ToRadian(-0.35f), 0, 0 };
		scene_->camera_->free_look_angle_xy_ += rot;
		scene_->player_->mesh_->rot_q_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(-0.35f));
		scene_->player_->mesh_->pos_.y += 0.05f;
		enemy_->mesh_->rot_q_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(-0.35f));
		enemy_->mesh_->pos_.y += 0.05f;
	}
	else {

	}


}

void Boss::render() {
	DrawRotaGraph(DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT / 2, 2.5f, 0, back_, true); //”wŒi‚Ì•`‰æ
	field_l1_->render(scene_->camera_);
	field_r1_->render(scene_->camera_);
	field_l2_->render(scene_->camera_);
	field_r2_->render(scene_->camera_);
	road_->render(scene_->camera_);
}