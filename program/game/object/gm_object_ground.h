#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "gm_object_base.h"

class Ground : public ObjectBase {
public:
	Ground(ScenePlay* scene, float w, float h, float z, const std::string img);
	~Ground() {}
	void update(float delta_time) override;

	// =========== 関数 ==========


	// ========== 基本ステータス ==========

	const int SPEED_ = 3;
	const int MIN_ = -375;
	const int MAX_ = 525;
};

class Line : public ObjectBase {
public:
	Line(ScenePlay* scene);
	~Line() {}
	void update(float delta_time) override;

	// =========== 関数 ==========


	// ========== 基本ステータス ==========

	const float MESH_W_ = 300.0f; //メッシュの横幅
	const float MESH_H_ = 5.0f; //メッシュの立幅
	const float POS_Z_ = 300.0f; //初期Z座標
	const float DEAD_Z_ = -180.0f; //消滅Z座標

};