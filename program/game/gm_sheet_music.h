#pragma once
#include "../dxlib_ext/dxlib_ext.h"
class ScenePlay;

class Sheet {
public:
	Sheet(ScenePlay* scene);
	~Sheet(){}
	void update(float delta_time);

	// =========== 関数 ==========


	// ========== 基本ステータス ==========

	ScenePlay* scene_ = nullptr; //シーンの変数を取得するためのポインタ
	std::vector<std::vector<std::string>> csv_; //譜面csv
	int bgm_ = 0; //bgm
	int bpm_ = 10; //ノーツ密度(ラインとラインの間にあるノーツの数)

	int elapsed_ = 0; //時間計測用
	const int INTERVAL_LINE_ = 120; //ラインが流れてくる間隔

	int bgm_timer_ = 0; //BGMラグ計測用
	const int START_INTERVAL_ = 99; //最初のラインが判定ラインに到達するまでのラグ

	int csv_y_ = 1;

	int save_ = 0;
};