#pragma once
#include "../dxlib_ext/dxlib_ext.h"
class ScenePlay;

class Boss {
public:
	Boss(ScenePlay* scene);
	~Boss() {}
	void update(float delta_time);

	// =========== 関数 ==========


	// ========== 基本ステータス ==========

	ScenePlay* scene_ = nullptr; //シーンの変数を取得するためのポインタ

	int elapsed_ = 0; //時間計測用

};