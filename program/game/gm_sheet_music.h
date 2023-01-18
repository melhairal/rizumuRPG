#pragma once
#include "../dxlib_ext/dxlib_ext.h"
class ScenePlay;
class ObjectBase;

class Sheet {
public:
	Sheet(ScenePlay* scene, std::string csv);
	~Sheet(){}
	void update(float delta_time);

	// =========== 関数 ==========

	void createNotes(int id, int lane); //ノード作成

	// ========== 基本ステータス ==========

	enum {
		plains,
		cave,
		sea,
		forest
	};

	ScenePlay* scene_ = nullptr; //シーンの変数を取得するためのポインタ
	ObjectBase* line_ = nullptr; //ラインのポインタ
	std::vector<std::vector<std::string>> csv_; //譜面csv
	int bgm_ = 0; //bgm
	int type_ = plains; //ステージタイプ

	int elapsed_ = 0; //時間計測用
	const int NODE_INTERVAL_ = 12; //ノード生成間隔

	int bgm_timer_ = 0; //BGMラグ計測用
	const int START_INTERVAL_ = 99; //最初のラインが判定ラインに到達するまでのラグ

	int csv_y_ = 2; //csvの何行目か

	bool alive_ = true; //生存フラグ
};