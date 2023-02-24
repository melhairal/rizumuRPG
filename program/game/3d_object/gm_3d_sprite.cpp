#include "gm_3d_sprite.h"
#include "../gm_camera.h"
#include "../model/gm_anim_sprite3d.h"
#include "../scene/gm_scene_field.h"

void SpriteBase::hitPlayer(tnl::Vector3 size) {
	if (tnl::IsIntersectAABB(sprite_->pos_, size, scene_->player_->sprite_->pos_, { 32,32,32 })) {
		tnl::GetCorrectPositionIntersectAABB(scene_->player_->sprite_->pos_, { 32,32,32 }, sprite_->pos_, size, scene_->player_->sprite_->pos_);
	}
}

SpritePlayer::SpritePlayer(SceneField* scene) {
	scene_ = scene;
	sprite_ = new AnimSprite3D(scene_->camera_);
	sprite_->regist(32, 32, "walk_front", "graphics/chara/player_3d/player_up.png", tnl::SeekUnit::ePlayMode::REPEAT, 1.0f, 3, 32, 0);
	sprite_->regist(32, 32, "walk_back", "graphics/chara/player_3d/player_down.png", tnl::SeekUnit::ePlayMode::REPEAT, 1.0f, 3, 32, 0);
	sprite_->regist(32, 32, "walk_left", "graphics/chara/player_3d/player_left.png", tnl::SeekUnit::ePlayMode::REPEAT, 1.0f, 3, 32, 0);
	sprite_->regist(32, 32, "walk_right", "graphics/chara/player_3d/player_right.png", tnl::SeekUnit::ePlayMode::REPEAT, 1.0f, 3, 32, 0);
	sprite_->setCurrentAnim("walk_front");
	prev_pos_ = sprite_->pos_;
}

void SpritePlayer::update(float delta_time) {
	if (!move_) return;
	// 移動制御
	int t = tnl::GetXzRegionPointAndOBB(
		scene_->camera_->pos_
		, sprite_->pos_
		, { 32, 48, 32 }
	, sprite_->rot_);

	std::string anim_names[4] = {
		"walk_back", "walk_right", "walk_front", "walk_left"
	};
	sprite_->setCurrentAnim(anim_names[t]);

	tnl::Vector3 move_v = { 0,0,0 };
	tnl::Vector3 dir[4] = {
		scene_->camera_->front().xz(),
		scene_->camera_->right().xz(),
		scene_->camera_->back().xz(),
		scene_->camera_->left().xz(),
	};
	tnl::Input::RunIndexKeyDown([&](uint32_t idx) {
		move_v += dir[idx];
		}, eKeys::KB_W, eKeys::KB_D, eKeys::KB_S, eKeys::KB_A);

	if (tnl::Input::IsKeyDown(eKeys::KB_W, eKeys::KB_D, eKeys::KB_S, eKeys::KB_A)) {
		move_v.normalize();
		sprite_->rot_.slerp(tnl::Quaternion::LookAtAxisY(sprite_->pos_, sprite_->pos_ + move_v), 0.3f);
		prev_pos_ = sprite_->pos_;
		sprite_->pos_ += move_v * speed_;
	}
	sprite_->update(delta_time);
}

void SpritePlayer::render() {
	sprite_->render(scene_->camera_);
}

SpriteTree::SpriteTree(SceneField* scene, tnl::Vector3 pos) {
	scene_ = scene;
	pos_ = pos;
	sprite_ = new AnimSprite3D(scene_->camera_);
	sprite_->regist(100, 100, "def", "graphics/base/tree.png", tnl::SeekUnit::ePlayMode::SINGLE, 1.0f, 1, 700, 0);
	sprite_->setCurrentAnim("def");
	sprite_->pos_ = pos_;
	sprite_->update(0);
}

void SpriteTree::update(float delta_time) {
	if (!move_) return;
	hitPlayer(size_);
	sprite_->update(delta_time);
}

void SpriteTree::render() {
	sprite_->render(scene_->camera_);
}

void SpriteNpc::getSurface(tnl::Vector3 size) {
	//カメラの向きに対してどの面がこちらを向いているか
	int t = tnl::GetXzRegionPointAndOBB(
		scene_->camera_->pos_
		, sprite_->pos_
		, size
		, sprite_->rot_);

	std::string anim_names[4] = {
		"walk_back", "walk_right", "walk_front", "walk_left"
	};
	sprite_->setCurrentAnim(anim_names[t]);
}

void SpriteNpc::randomWalk(int range, int speed) {
	if (isWait_) {
		elapsed_++;
		if (elapsed_ >= wait_time_) {
			elapsed_ = 0;
			isWait_ = false;
		}
	}
	else {
		if (!isWalk_) {
			//移動目標を設定
			next_x_ = pos_.x + rand() % range - range / 2;
			next_z_ = pos_.z + rand() % range - range / 2;

			//向きを回転
			sprite_->rot_ = tnl::Quaternion::LookAtAxisY(sprite_->pos_, { next_x_,0,next_z_ });
			isWalk_ = true;
		}
		else {
			//移動
			if (sprite_->pos_.x > next_x_) {
				sprite_->pos_.x -= speed;
				if (sprite_->pos_.x <= next_x_) {
					sprite_->pos_.x = next_x_;
				}
			}
			if (sprite_->pos_.x < next_x_) {
				sprite_->pos_.x += speed;
				if (sprite_->pos_.x >= next_x_) {
					sprite_->pos_.x = next_x_;
				}
			}
			if (sprite_->pos_.z > next_z_) {
				sprite_->pos_.z -= speed;
				if (sprite_->pos_.z <= next_z_) {
					sprite_->pos_.z = next_z_;
				}
			}
			if (sprite_->pos_.z < next_z_) {
				sprite_->pos_.z += speed;
				if (sprite_->pos_.z >= next_z_) {
					sprite_->pos_.z = next_z_;
				}
			}

			if (sprite_->pos_.x == next_x_ && sprite_->pos_.z == next_z_) {
				isWalk_ = false;
				isWait_ = true;
				//待機時間を3秒から5秒に設定
				wait_time_ = rand() % 120 + 180;
			}
		}
	}
}

SpriteMurabito::SpriteMurabito(SceneField* scene, tnl::Vector3 pos) {
	scene_ = scene;
	pos_ = pos;
	sprite_ = new AnimSprite3D(scene_->camera_);
	sprite_->regist(32, 32, "walk_front", "graphics/chara/human/murabito/murabito_004.png", tnl::SeekUnit::ePlayMode::REPEAT, 1.0f, 3, 32, 0);
	sprite_->regist(32, 32, "walk_back", "graphics/chara/human/murabito/murabito_001.png", tnl::SeekUnit::ePlayMode::REPEAT, 1.0f, 3, 32, 0);
	sprite_->regist(32, 32, "walk_left", "graphics/chara/human/murabito/murabito_002.png", tnl::SeekUnit::ePlayMode::REPEAT, 1.0f, 3, 32, 0);
	sprite_->regist(32, 32, "walk_right", "graphics/chara/human/murabito/murabito_003.png", tnl::SeekUnit::ePlayMode::REPEAT, 1.0f, 3, 32, 0);
	sprite_->setCurrentAnim("walk_front");
	sprite_->pos_ = pos_;
	sprite_->update(0);
	prev_pos_ = sprite_->pos_;
}

void SpriteMurabito::update(float delta_time) {
	if (!move_) return;
	hitPlayer(size_);

	//カメラの向きに対してどの面がこちらを向いているか
	getSurface(size_);

	//一定の範囲を徘徊
	randomWalk(range_, speed_);


	sprite_->update(delta_time);
}

void SpriteMurabito::render() {
	sprite_->render(scene_->camera_);
}

SpriteMurabitoF::SpriteMurabitoF(SceneField* scene, tnl::Vector3 pos) {
	scene_ = scene;
	pos_ = pos;
	sprite_ = new AnimSprite3D(scene_->camera_);
	sprite_->regist(32, 32, "walk_front", "graphics/chara/human/murabitof/murabitof_004.png", tnl::SeekUnit::ePlayMode::REPEAT, 1.0f, 3, 32, 0);
	sprite_->regist(32, 32, "walk_back", "graphics/chara/human/murabitof/murabitof_001.png", tnl::SeekUnit::ePlayMode::REPEAT, 1.0f, 3, 32, 0);
	sprite_->regist(32, 32, "walk_left", "graphics/chara/human/murabitof/murabitof_002.png", tnl::SeekUnit::ePlayMode::REPEAT, 1.0f, 3, 32, 0);
	sprite_->regist(32, 32, "walk_right", "graphics/chara/human/murabitof/murabitof_003.png", tnl::SeekUnit::ePlayMode::REPEAT, 1.0f, 3, 32, 0);
	sprite_->setCurrentAnim("walk_front");
	sprite_->pos_ = pos_;
	sprite_->update(0);
	prev_pos_ = sprite_->pos_;
}

void SpriteMurabitoF::update(float delta_time) {
	if (!move_) return;
	hitPlayer(size_);

	//カメラの向きに対してどの面がこちらを向いているか
	getSurface(size_);

	//一定の範囲を徘徊
	randomWalk(range_, speed_);


	sprite_->update(delta_time);
}

void SpriteMurabitoF::render() {
	sprite_->render(scene_->camera_);
}

SpriteHeisi::SpriteHeisi(SceneField* scene, tnl::Vector3 pos, int look) {
	scene_ = scene;
	pos_ = pos;
	sprite_ = new AnimSprite3D(scene_->camera_);
	sprite_->regist(32, 32, "walk_front", "graphics/chara/human/heisi/heisi_004.png", tnl::SeekUnit::ePlayMode::REPEAT, 1.0f, 3, 32, 0);
	sprite_->regist(32, 32, "walk_back", "graphics/chara/human/heisi/heisi_001.png", tnl::SeekUnit::ePlayMode::REPEAT, 1.0f, 3, 32, 0);
	sprite_->regist(32, 32, "walk_left", "graphics/chara/human/heisi/heisi_002.png", tnl::SeekUnit::ePlayMode::REPEAT, 1.0f, 3, 32, 0);
	sprite_->regist(32, 32, "walk_right", "graphics/chara/human/heisi/heisi_003.png", tnl::SeekUnit::ePlayMode::REPEAT, 1.0f, 3, 32, 0);
	sprite_->setCurrentAnim("walk_front");
	sprite_->pos_ = pos_;
	sprite_->rot_ = tnl::Quaternion::LookAtAxisY(sprite_->pos_, sprite_->pos_ + dir_[look]);
	sprite_->update(0);
	prev_pos_ = sprite_->pos_;
}

void SpriteHeisi::update(float delta_time) {
	if (!move_) return;
	hitPlayer(size_);

	//カメラの向きに対してどの面がこちらを向いているか
	getSurface(size_);

	sprite_->update(delta_time);
}

void SpriteHeisi::render() {
	sprite_->render(scene_->camera_);
}

SpriteKazi::SpriteKazi(SceneField* scene, tnl::Vector3 pos, int look) {
	scene_ = scene;
	pos_ = pos;
	sprite_ = new AnimSprite3D(scene_->camera_);
	sprite_->regist(32, 32, "walk_front", "graphics/chara/human/kazi/kazi_004.png", tnl::SeekUnit::ePlayMode::REPEAT, 1.0f, 3, 32, 0);
	sprite_->regist(32, 32, "walk_back", "graphics/chara/human/kazi/kazi_001.png", tnl::SeekUnit::ePlayMode::REPEAT, 1.0f, 3, 32, 0);
	sprite_->regist(32, 32, "walk_left", "graphics/chara/human/kazi/kazi_002.png", tnl::SeekUnit::ePlayMode::REPEAT, 1.0f, 3, 32, 0);
	sprite_->regist(32, 32, "walk_right", "graphics/chara/human/kazi/kazi_003.png", tnl::SeekUnit::ePlayMode::REPEAT, 1.0f, 3, 32, 0);
	sprite_->setCurrentAnim("walk_front");
	sprite_->pos_ = pos_;
	sprite_->rot_ = tnl::Quaternion::LookAtAxisY(sprite_->pos_, sprite_->pos_ + dir_[look]);
	sprite_->update(0);
	prev_pos_ = sprite_->pos_;
}

void SpriteKazi::update(float delta_time) {
	if (!move_) return;
	hitPlayer(size_);

	//カメラの向きに対してどの面がこちらを向いているか
	getSurface(size_);

	sprite_->update(delta_time);
}

void SpriteKazi::render() {
	sprite_->render(scene_->camera_);
}