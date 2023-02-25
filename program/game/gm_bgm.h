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
	int se_hit_ = 0; //被弾音
	int se_heal_ = 0; //回復音

	int se_select_ = 0; //コマンド選択音
	int se_esc_ = 0; //キャンセル音
	int sound_warning_ = 0; //警告音
	int sound_clear_ = 0; //成功音
	int sound_failed_ = 0; //失敗音

	int bgm_stage_ = 0; //BGM
	int bgm_boss_ = 0; //ボスBGM

	bool perfect_ = false; //パーフェクト判定かどうか

	int prev_hp_ = 0; //HPが減っているかどうかの確認


};