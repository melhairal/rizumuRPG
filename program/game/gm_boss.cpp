#include "gm_boss.h"
#include "scene/gm_scene_play.h"
#include "object/gm_object_actor.h"
#include "object/gm_object_boss.h"
#include "object/gm_object_ground.h"
#include "gm_camera.h"

Boss::Boss(ScenePlay* scene) {
	//シーンポインタ取得
	scene_ = scene;

	//床の再生成
	scene_->objects_.emplace_back(new Ground(scene_, scene_->BACK_W_, scene_->FIELD_H_, scene_->FIELD_Z1_, scene_->back_img))->move_ = false;
	scene_->objects_.emplace_back(new Ground(scene_, scene_->BACK_W_, scene_->FIELD_H_, scene_->FIELD_Z2_, scene_->back_img))->move_ = false;
	scene_->objects_.emplace_back(new Ground(scene_, scene_->FIELD_W_, scene_->FIELD_H_, scene_->FIELD_Z1_, scene_->road_img))->move_ = false;
	scene_->objects_.emplace_back(new Ground(scene_, scene_->FIELD_W_, scene_->FIELD_H_, scene_->FIELD_Z2_, scene_->road_img))->move_ = false;

	//床の補完
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

	//背景
	back_ = LoadGraph("graphics/base/sky.jpg");

	//ボス
	enemy_ = scene_->actors_.emplace_back(new BossEnemy(scene_));
}

void Boss::update(float delta_time) {
	//初期演出
	if (!init_) {
		initialize();
	}

	//カメラアングル処理
	if (is_changing_angle_ && is_battle_angle_) changeAngleCommand();
	if (is_changing_angle_ && is_command_angle_) changeAngleBattle();


	// ========== デバッグ等 ==========
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_V)) {
		is_changing_angle_ = true;
	}

}

void Boss::render() {
	DrawRotaGraph(DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT / 2, 2.5f, 0, back_, true); //背景の描画
	field_l1_->render(scene_->camera_);
	field_r1_->render(scene_->camera_);
	field_l2_->render(scene_->camera_);
	field_r2_->render(scene_->camera_);
	road_->render(scene_->camera_);
}

void Boss::initialize() {
	//アングルの変更が終わったら
	if (!is_changing_angle_) {
		//ボスを前進させる
		if (elapsed_ < INIT_TIMER_) {
			elapsed_++;
			enemy_->mesh_->pos_.z -= 2;
		}
		else if(elapsed_ == INIT_TIMER_) {
			//初期化終了
			elapsed_ = 0;
			init_ = true;
		}
	}
}

void Boss::changeAngleCommand() {
	if (elapsed_ < ANGLE_TIMER_) {
		is_changing_angle_ = true; //変更中フラグ
		elapsed_++;
		tnl::Vector3 rot = { tnl::ToRadian(-0.35f), 0, 0 };
		scene_->camera_->free_look_angle_xy_ += rot;
		scene_->player_->mesh_->rot_q_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(-0.35f));
		scene_->player_->mesh_->pos_.y += 0.05f;
		enemy_->mesh_->rot_q_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(-0.35f));
		enemy_->mesh_->pos_.y += 0.05f;
	}
	else if (elapsed_ == ANGLE_TIMER_) {
		is_changing_angle_ = false;
		is_battle_angle_ = false;
		is_command_angle_ = true;
		elapsed_ = 0;
	}
}

void Boss::changeAngleBattle() {
	if (elapsed_ < ANGLE_TIMER_) {
		is_changing_angle_ = true; //変更中フラグ
		elapsed_++;
		tnl::Vector3 rot = { tnl::ToRadian(0.35f), 0, 0 };
		scene_->camera_->free_look_angle_xy_ += rot;
		scene_->player_->mesh_->rot_q_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(0.35f));
		scene_->player_->mesh_->pos_.y -= 0.05f;
		enemy_->mesh_->rot_q_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(0.35f));
		enemy_->mesh_->pos_.y -= 0.05f;
	}
	else if (elapsed_ == ANGLE_TIMER_) {
		is_changing_angle_ = false;
		is_command_angle_ = false;
		is_battle_angle_ = true;
		elapsed_ = 0;
	}
}