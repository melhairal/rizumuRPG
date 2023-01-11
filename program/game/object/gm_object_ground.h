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