#include "gm_3d_model.h"
#include "gm_3d_sprite.h"
#include "../model/gm_anim_sprite3d.h"
#include "../scene/gm_scene_field.h"

void ModelBase::hitPlayer(tnl::Vector3 size) {
	if (tnl::IsIntersectAABB(pos_, size, scene_->player_->sprite_->pos_, { 32,32,32 })) {
		tnl::GetCorrectPositionIntersectAABB(scene_->player_->sprite_->pos_, { 32,32,32 }, pos_, size, scene_->player_->sprite_->pos_);
	}
}

ModelHouse::ModelHouse(SceneField* scene, tnl::Vector3 pos, tnl::Vector3 rot) {
	scene_ = scene;
	pos_ = pos;
	mv1_ = MV1LoadModel("mesh/WoodHouse.mv1");
	MV1SetPosition(mv1_, { pos_.x,pos_.y,pos_.z });
	MV1SetRotationXYZ(mv1_, { rot.x,rot.y,rot.z });
	MV1SetScale(mv1_, { 0.5f,0.5f,0.5f });
}

void ModelHouse::update(float delta_time) {
	hitPlayer(size_);
}

void ModelHouse::render() {
	if (!render_) return;
	MV1DrawModel(mv1_);
}