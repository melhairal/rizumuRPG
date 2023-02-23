#include "gm_3d_model.h"
#include "gm_3d_sprite.h"
#include "../model/gm_anim_sprite3d.h"
#include "../scene/gm_scene_field.h"

void ModelBase::hitPlayer(tnl::Vector3 size) {
	if (tnl::IsIntersectAABB(pos_, size, scene_->player_->sprite_->pos_, { 32,32,32 })) {
		tnl::GetCorrectPositionIntersectAABB(scene_->player_->sprite_->pos_, { 32,32,32 }, pos_, size, scene_->player_->sprite_->pos_);
	}
}

bool ModelBase::rotateHit(tnl::Vector3 pos, float w, float h, float rot) {
	float ax = pos.x - w / 2 * cos(rot) + h / 2 * sin(rot);
	float ay = pos.z - w / 2 * sin(rot) - h / 2 * cos(rot);
	float bx = pos.x - w / 2 * cos(rot) - h / 2 * sin(rot);
	float by = pos.z - w / 2 * sin(rot) + h / 2 * cos(rot);
	float cx = pos.x + w / 2 * cos(rot) + h / 2 * sin(rot);
	float cy = pos.z + w / 2 * sin(rot) - h / 2 * cos(rot);
	float dx = pos.x + w / 2 * cos(rot) - h / 2 * sin(rot);
	float dy = pos.z + w / 2 * sin(rot) + h / 2 * cos(rot);
	float px = scene_->player_->sprite_->pos_.x;
	float py = scene_->player_->sprite_->pos_.z;

	float vec_x[4] = { ax - bx,bx - dx,dx - cx,cx - ax };
	float vec_y[4] = { ay - by,by - dy,dy - cy,cy - ay };
	float vec_px[4] = { ax - px,bx - px,dx - px,cx - px };
	float vec_py[4] = { ay - py,by - py,dy - py,cy - py };

	for (int i = 0; i < 4; ++i) {
		float cross = vec_x[i] * vec_py[i] - vec_px[i] * vec_y[i];
		if (cross > 0) return false;
	}
	return true;
}

ModelHouse::ModelHouse(SceneField* scene, tnl::Vector3 pos, float rot) {
	scene_ = scene;
	pos_ = pos;
	rot_ = rot;
	mv1_ = MV1LoadModel("mesh/WoodHouse.mv1");
	MV1SetPosition(mv1_, { pos_.x,pos_.y,pos_.z });
	MV1SetRotationXYZ(mv1_, { 0,tnl::ToRadian(rot_),0 });
	MV1SetScale(mv1_, { 0.5f,0.5f,0.5f });
}

void ModelHouse::update(float delta_time) {
	if (rotateHit(pos_, width_, height_, -rot_)) {
		scene_->player_->sprite_->pos_ = scene_->player_->prev_pos_;
	}
}

void ModelHouse::render() {
	if (!render_) return;
	MV1DrawModel(mv1_);
}