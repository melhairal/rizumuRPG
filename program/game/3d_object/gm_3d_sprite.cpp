#include "gm_3d_sprite.h"
#include "../gm_camera.h"
#include "../model/gm_anim_sprite3d.h"
#include "../scene/gm_scene_field.h"

void SpriteBase::hitPlayer(tnl::Vector3 size) {
	if (tnl::IsIntersectAABB(pos_, size, scene_->player_->sprite_->pos_, { 32,32,32 })) {
		tnl::GetCorrectPositionIntersectAABB(scene_->player_->sprite_->pos_, { 32,32,32 }, pos_, size, scene_->player_->sprite_->pos_);
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
	// ˆÚ“®§Œä
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
	hitPlayer(size_);
	sprite_->update(delta_time);
}

void SpriteTree::render() {
	sprite_->render(scene_->camera_);
}
