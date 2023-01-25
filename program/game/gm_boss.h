#pragma once
#include "../dxlib_ext/dxlib_ext.h"
class ScenePlay;
class Actor;
class SkillBase;

class Boss {
public:
	Boss(ScenePlay* scene);
	~Boss();
	void update(float delta_time);
	void render();

	// =========== 関数 ==========

	void initialize(); //初期遷移
	void changeAngleCommand(); //コマンド選択のカメラアングルに遷移
	void changeAngleBattle(); //バトルのカメラアングルに遷移
	void switchSkill(); //数値と発動させるスキルを対応させる
	void battle(); //戦闘開始(ノーツが流れ始める)

	// ========== 基本ステータス ==========

	ScenePlay* scene_ = nullptr; //シーンの変数を取得するためのポインタ
	Actor* enemy_ = nullptr; //ボス
	dxe::Mesh* field_l1_ = nullptr; //床補完用(左上)
	dxe::Mesh* field_r1_ = nullptr; //床補完用(右上)
	dxe::Mesh* field_l2_ = nullptr; //床補完用(左下)
	dxe::Mesh* field_r2_ = nullptr; //床補完用(右下)
	dxe::Mesh* road_ = nullptr; //床補完用(道)
	SkillBase* skills_ = nullptr; //スキル

	const float LEFT_X_ = -300.0f; //補完床用X座標
	const float RIGHT_X_ = 300.0f; //補完床用X座標
	const float ROAD_Z_ = -375.0f; //補完道用Z座標

	int back_ = 0; //背景

	bool init_ = false; //初期化フラグ
	int elapsed_ = 0; //時間計測用

	const int ANGLE_TIMER_ = 120; //カメラアングルが変わるのにかかる時間
	const int INIT_TIMER_ = 75; //初期化にかかる時間
	bool is_changing_angle_ = true; //カメラアングル変更フラグ
	bool is_command_angle_ = false; //コマンド画面アングル
	bool is_battle_angle_ = true; //バトル画面アングル

	int hp_max_ = 1000; //ボスHP
	int hp_ = hp_max_;


	bool battle_ = false; //バトル開始フラグ
	int action_num_ = -1; //アクション回数
	int player_action_[5] = { 1,2,3,4,5 }; //プレイヤーの行動を予約
	int enemy_action_[5] = { 0,1,2,3,5 }; //エネミーの行動を予約
};