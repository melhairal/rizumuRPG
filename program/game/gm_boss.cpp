#include "gm_boss.h"
#include "scene/gm_scene_play.h"
#include "object/gm_object_actor.h"
#include "object/gm_object_boss.h"
#include "object/gm_object_ground.h"
#include "gm_camera.h"
#include "object/gm_object_attack.h"

Boss::~Boss() {
	delete field_l1_;
	delete field_r1_;
	delete field_l2_;
	delete field_r2_;
	delete road_;
	delete skills_;
}

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
	enemy_ = scene_->actors_.emplace_back(new BossDragon(scene_));
}

void Boss::update(float delta_time) {
	//初期演出
	if (!init_) {
		initialize();
	}

	//カメラアングル処理
	if (is_changing_angle_ && is_battle_angle_) changeAngleCommand();
	if (is_changing_angle_ && is_command_angle_) changeAngleBattle();

	//バトル処理
	if (battle_) battle();
	
	//スキル処理
	if (skills_ != nullptr) {
		skills_->update(delta_time);
	}

	// ========== デバッグ等 ==========
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_C)) {
		is_changing_angle_ = true;
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_V)) {
		battle_ = true;
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
			command_ = true;
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

void Boss::switchSkill() {
	switch (player_action_[action_num_]) {
	case 0:
		skills_ = new SkillNormalA(scene_);
		break;
	case 1:
		skills_ = new SkillNormalB(scene_);
		break;
	case 2:
		skills_ = new SkillComboA(scene_);
		break;
	case 3:
		skills_ = new SkillComboB(scene_);
		break;
	case 4:
		skills_ = new SkillComboC(scene_);
		break;
	case 5:
		skills_ = new SkillComboD(scene_);
		break;
	case 6:
		skills_ = new SkillPowerA(scene_);
		break;
	case 7:
		skills_ = new SkillPowerB(scene_);
		break;
	case 8:
		skills_ = new SkillPowerC(scene_);
		break;
	case 9:
		skills_ = new SkillOtherA(scene_);
		break;
	}
}

void Boss::battle() {
	if (skills_ != nullptr) {
		if (skills_->finish_) {
			delete skills_;
			skills_ = nullptr;
			enemy_->action_ = enemy_action_[action_num_];
		}
	}
	if (skills_ == nullptr && enemy_->action_ == -1) {
		action_num_++;
		if (action_num_ != 5) {
			switchSkill();
		}
		else {
			for (int i = 0; i < 5; i++) {
				player_action_[i] = -1;
				enemy_action_[i] = -1;
			}
			action_num_ = -1;
			battle_ = false;
		}
	}
}

void Boss::command() {
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) {
		if (main_command_) index_main_ -= 1;
		else index_sub_ -= 1;
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)) {
		if (main_command_) index_main_ += 1;
		else index_sub_ += 1;
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		if (main_command_) main_command_ = false; //メインコマンドならサブコマンドに移る
		else {

		}
	}
	index_main_ = std::clamp(index_main_, 0, 3);
	index_sub_ = std::clamp(index_sub_, 0, 5);

}