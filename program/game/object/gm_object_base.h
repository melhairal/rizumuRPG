#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
class ScenePlay;

class ObjectBase {
public:
	ScenePlay* scene_ = nullptr; //シーンの変数を取得するためのポインタ
	ObjectBase() {};
	virtual ~ObjectBase();
	virtual void update(float delta_time) {}

	// =========== 関数 ==========


	// ========== 基本ステータス ==========

	dxe::Mesh* mesh_ = nullptr; //実体
	float mesh_w_ = 0; //メッシュの横幅
	float mesh_h_ = 0; //メッシュの横幅

	bool move_ = true; //動作フラグ
	bool alive_ = true; //生存フラグ
};
