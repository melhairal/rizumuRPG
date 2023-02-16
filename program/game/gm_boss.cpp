#include "gm_boss.h"
#include "scene/gm_scene_play.h"
#include "object/gm_object_actor.h"
#include "object/gm_object_boss.h"
#include "object/gm_object_ground.h"
#include "gm_camera.h"
#include "object/gm_object_attack.h"
#include "object/gm_object_effect.h"
#include "object/gm_object_skill_map.h"
#include "gm_ui.h"
#include "gm_bgm.h"

Boss::~Boss() {
	delete field_l1_;
	delete field_r1_;
	delete field_l2_;
	delete field_r2_;
	delete road_;
}

Boss::Boss(ScenePlay* scene) {
	//シーンポインタ取得
	scene_ = scene;

	//床の再生成
	scene_->objects_.emplace_back(new Ground(scene_, scene_->BACK_W_, scene_->FIELD_H_, scene_->FIELD_Z1_, scene_->back_img_[scene_->stage_]))->move_ = false;
	scene_->objects_.emplace_back(new Ground(scene_, scene_->BACK_W_, scene_->FIELD_H_, scene_->FIELD_Z2_, scene_->back_img_[scene_->stage_]))->move_ = false;
	scene_->objects_.emplace_back(new Ground(scene_, scene_->FIELD_W_, scene_->FIELD_H_, scene_->FIELD_Z1_, scene_->road_img_[scene_->stage_]))->move_ = false;
	scene_->objects_.emplace_back(new Ground(scene_, scene_->FIELD_W_, scene_->FIELD_H_, scene_->FIELD_Z2_, scene_->road_img_[scene_->stage_]))->move_ = false;

	//床の補完
	field_l1_ = dxe::Mesh::CreatePlane({ scene_->BACK_W_,scene_->FIELD_H_,0 });
	field_l1_->setTexture(dxe::Texture::CreateFromFile(scene_->back_img_[scene_->stage_]));
	field_l1_->rot_q_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(90));
	field_l1_->pos_ = { LEFT_X_, 0, scene_->FIELD_Z2_ };

	field_r1_ = dxe::Mesh::CreatePlane({ scene_->BACK_W_,scene_->FIELD_H_,0 });
	field_r1_->setTexture(dxe::Texture::CreateFromFile(scene_->back_img_[scene_->stage_]));
	field_r1_->rot_q_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(90));
	field_r1_->pos_ = { RIGHT_X_, 0, scene_->FIELD_Z2_ };

	field_l2_ = dxe::Mesh::CreatePlane({ scene_->BACK_W_,scene_->FIELD_H_,0 });
	field_l2_->setTexture(dxe::Texture::CreateFromFile(scene_->back_img_[scene_->stage_]));
	field_l2_->rot_q_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(90));
	field_l2_->pos_ = { LEFT_X_, 0, scene_->FIELD_Z1_ };

	field_r2_ = dxe::Mesh::CreatePlane({ scene_->BACK_W_,scene_->FIELD_H_,0 });
	field_r2_->setTexture(dxe::Texture::CreateFromFile(scene_->back_img_[scene_->stage_]));
	field_r2_->rot_q_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(90));
	field_r2_->pos_ = { RIGHT_X_, 0, scene_->FIELD_Z1_ };

	road_ = dxe::Mesh::CreatePlane({ scene_->BACK_W_,scene_->FIELD_H_,0 });
	road_->setTexture(dxe::Texture::CreateFromFile(scene_->road_img_[scene_->stage_]));
	road_->rot_q_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(90));
	road_->pos_ = { 0, 0, ROAD_Z_ };

	//背景
	back_ = LoadGraph(back_img_[scene_->stage_]);

	//ボス
	getBossClass();
}

void Boss::update(float delta_time) {
	//初期演出
	if (!init_) {
		initialize();
	}

	//カメラアングル処理
	if (is_changing_angle_ && is_battle_angle_) changeAngleCommand();
	if (is_changing_angle_ && is_command_angle_) changeAngleBattle();

	//コマンド処理
	if (command_) command();

	//進行演出処理
	if (progress_) progress();

	//バトル処理
	if (battle_) battle();

	//次のターンに移る処理
	if (next_turn_) nextTurn();

	//勝利処理
	if (win_) win();

	//敗北処理
	if (lose_) lose();
	
	//スキル処理
	if (skills_ != nullptr) {
		skills_->update(delta_time);
	}

	//値のクランプ
	hp_ = std::clamp(hp_, 0, hp_max_);

	// ========== デバッグ等 ==========

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
		if (elapsed_ == 0) {
		}
		//ボスを前進させる
		if (elapsed_ < INIT_TIMER_) {
			elapsed_++;
			enemy_->mesh_->pos_.z -= 2;
		}
		else if(elapsed_ == INIT_TIMER_) {
			//初期化終了
			PlaySoundMem(scene_->bgm_->bgm_boss_, DX_PLAYTYPE_LOOP);
			command_ = true;
			elapsed_ = 0;
			init_ = true;
		}
	}
}

void Boss::getBossClass() {
	switch (scene_->stage_) {
	case 0:
		enemy_ = scene_->actors_.emplace_back(new BossGorem(scene_));
		hp_max_ = 500;
		hp_ = hp_max_;
		break;
	case 1:
		enemy_ = scene_->actors_.emplace_back(new BossDragon(scene_));
		hp_max_ = 1000;
		hp_ = hp_max_;
		break;
	case 2:
		enemy_ = scene_->actors_.emplace_back(new BossKeruberos(scene_));
		hp_max_ = 2000;
		hp_ = hp_max_;
		break;
	case 3:
		enemy_ = scene_->actors_.emplace_back(new BossSkall(scene_));
		hp_max_ = 3000;
		hp_ = hp_max_;
		break;
	case 4:
		enemy_ = scene_->actors_.emplace_back(new BossAnkou(scene_));
		hp_max_ = 3500;
		hp_ = hp_max_;
		break;
	case 5:
		enemy_ = scene_->actors_.emplace_back(new BossKing(scene_));
		hp_max_ = 5000;
		hp_ = hp_max_;
		break;
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

void Boss::battle() {
	if (skills_ != nullptr) {
		if (skills_->finish_) {
			//delete skills_;
			skills_ = nullptr;
			if (hp_ == 0) {
				battle_ = false;
				win_ = true;
			}
			else {
				enemy_->action_ = enemy_action_[action_num_];
			}
		}
	}
	else if (enemy_->action_ == -1) {
		if (scene_->hp_ == 0) {
			battle_ = false;
			lose_ = true;
		}
		else {
			action_num_++;
			if (action_num_ < 3) {
				skills_ = generator_map[scene_->skill_[player_action_[action_num_]]->class_name_](scene_);
			}
			else {
				battle_ = false;
				next_turn_ = true;
			}
		}
	}
}

void Boss::command() {
	//上キーを入力したとき
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) {
		if (main_command_) {
			index_main_ -= 1;
		}
		else {
			if (index_sub_ > 0) {
				index_sub_ -= 1;
			}
			else {
				index_sub_list_ -= 1;
			}
		}
	}
	//下キーを入力したとき
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)) {
		if (main_command_) {
			index_main_ += 1;
		}
		else {
			if (index_sub_ < INDEX_MAX_) {
				index_sub_ += 1;
			}
			else {
				index_sub_list_ += 1;
			}
		}
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		if (main_command_) {
			if (index_main_ != 3) {
				main_command_ = false; //メインコマンドならサブコマンドに移る
			}
			else {
				command_ = false;
				lose_ = true;
			}
		}
		else {
			//コマンドを登録する
			if (select_num_ < 3) {
				switch (index_main_) {
				case 0:
					player_action_[select_num_] = index_sub_;
					break;
				case 1:
					if (scene_->mp_ >= scene_->skill_[index_sub_ + index_sub_list_ + 2]->mp_) {
						scene_->mp_ -= scene_->skill_[index_sub_ + index_sub_list_ + 2]->mp_;
						player_action_[select_num_] = index_sub_ + index_sub_list_ + 2;
					}
					else {
						select_num_--;
					}
					break;
				case 3:
					break;
				}
				select_num_++;
			}
			if (select_num_ == 3) {
				//アクション開始
				command_ = false;
				progress_ = true;
			}
		}
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
		if (!main_command_) {
			index_sub_ = 0;
			index_sub_list_ = 0;
			main_command_ = true; //サブコマンドならメインコマンドに戻る
		}
		else {
			//コマンドを削除する
			if (select_num_ > 0) {
				select_num_--;
				scene_->mp_ += scene_->skill_[player_action_[select_num_]]->mp_;
				player_action_[select_num_] = -1;
			}
		}
	}

	index_main_ = std::clamp(index_main_, 0, INDEX_MAX_);
	switch (index_main_) {
	case 0:
		index_sub_ = std::clamp(index_sub_, 0, 1);
		index_sub_list_ = std::clamp(index_sub_list_, 0, 0);
		break;
	case 1:
		index_sub_ = std::clamp(index_sub_, 0, 4);
		index_sub_list_ = std::clamp(index_sub_list_, 0, 4);
		break;
	case 2:
		index_sub_ = std::clamp(index_sub_, 0, 0);
		index_sub_list_ = std::clamp(index_sub_list_, 0, 0);
		break;
	}
}

void Boss::progress() {
	if (!init_progress_) {
		init_progress_ = true;
		is_changing_angle_ = true;
		enemy_action_[0] = rand() % 6;
		enemy_action_[1] = rand() % 6;
		enemy_action_[2] = rand() % 6;
	}
	if (!is_changing_angle_) {
		progress_ = false;
		init_progress_ = false;
		battle_ = true;
	}
}

void Boss::nextTurn() {
	if (!init_progress_) {
		init_progress_ = true;
		is_changing_angle_ = true;
		for (int i = 0; i < 3; i++) {
			player_action_[i] = -1;
			enemy_action_[i] = -1;
		}
		select_num_ = 0;
		action_num_ = -1;
		main_command_ = true;
		index_main_ = 0;
		index_sub_ = 0;
		index_sub_list_ = 0;
	}
	if (!is_changing_angle_) {
		next_turn_ = false;
		init_progress_ = false;
		command_ = true;
	}
}

void Boss::win() {
	if (!init_win_) {
		StopSoundMem(scene_->bgm_->bgm_boss_);
		PlaySoundMem(scene_->bgm_->sound_clear_, DX_PLAYTYPE_BACK);
		enemy_->mesh_->pos_ = { 0,-300,0 };
		scene_->actors_.emplace_back(new EffectClear(scene_));
		scene_->subUis_.emplace_back(new SubUiClear(scene_));
		init_win_ = true;
	}
	else if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		StopSoundMem(scene_->bgm_->sound_clear_);
		win_result_ = true;
	}
}

void Boss::lose() {
	if (!init_lose_) {
		StopSoundMem(scene_->bgm_->bgm_boss_);
		PlaySoundMem(scene_->bgm_->sound_failed_, DX_PLAYTYPE_BACK);
		scene_->subUis_.emplace_back(new SubUiFailed(scene_));
		init_lose_ = true;
	}
	else if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		StopSoundMem(scene_->bgm_->sound_failed_);
		lose_result_ = true;
	}
}