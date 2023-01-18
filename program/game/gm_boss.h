#pragma once
#include "../dxlib_ext/dxlib_ext.h"
class ScenePlay;
class Actor;

class Boss {
public:
	Boss(ScenePlay* scene);
	~Boss() {}
	void update(float delta_time);
	void render();

	// =========== 関数 ==========


	// ========== 基本ステータス ==========

	ScenePlay* scene_ = nullptr; //シーンの変数を取得するためのポインタ
	Actor* enemy_ = nullptr; //ボス
	dxe::Mesh* field_l1_ = nullptr; //床補完用(左上)
	dxe::Mesh* field_r1_ = nullptr; //床補完用(右上)
	dxe::Mesh* field_l2_ = nullptr; //床補完用(左下)
	dxe::Mesh* field_r2_ = nullptr; //床補完用(右下)
	dxe::Mesh* road_ = nullptr; //床補完用(道)

	const float LEFT_X_ = -300.0f; //補完床用X座標
	const float RIGHT_X_ = 300.0f; //補完床用X座標
	const float ROAD_Z_ = -375.0f; //補完道用Z座標

	int back_ = 0; //背景

	int elapsed_ = 0; //時間計測用

};