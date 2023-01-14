#pragma once
#include "../dxlib_ext/dxlib_ext.h"
class ScenePlay;

class Bgm {
public:
	Bgm(ScenePlay* scene);
	~Bgm(){}
	void update(float delta_time);

	// =========== 関数 ==========


	// ========== 基本ステータス ==========

	ScenePlay* scene_ = nullptr; //シーンの変数を取得するためのポインタ
	int se_notes_ = 0; //ノーツ音
	int se_perfect_ = 0; //パーフェクト音

	bool perfect_ = false; //パーフェクト判定かどうか


};