#pragma once
#include "../dxlib_ext/dxlib_ext.h"
class ScenePlay;
class ObjectBase;

class MakeSheet {
public:
	MakeSheet(ScenePlay* scene);
	~MakeSheet();
	void update(float delta_time);
	void render();
	// =========== 関数 ==========

	// ========== 基本ステータス ==========

	ScenePlay* scene_ = nullptr; //シーン保存用

	std::list<ObjectBase*> lines_; //ラインリスト
	int line_num_ = 0; //ラインの本数
	const int LINE_NUM_MAX_ = 10; //ラインの最大数

	int bgm_ = 0; //BGM
	int elapsed_ = 0; //時間計測用
	const int NODE_INTERVAL_ = 12; //ノード生成間隔
	int key_ = 0; //キー入力

	int bgm_timer_ = 0; //BGMラグ計測用
	const int START_INTERVAL_ = 99; //最初のラインが判定ラインに到達するまでのラグ
	bool save_ = false; //記録開始フラグ
};
