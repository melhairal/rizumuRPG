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
	void command(); //コマンド選択処理
	void progress(); //進行演出処理
	void battle(); //戦闘開始(ノーツが流れ始める)
	void nextTurn(); //ターン進行演出
	void win(); //勝利処理
	void lose(); //敗北処理

	// ========== 基本ステータス ==========

	ScenePlay* scene_ = nullptr; //シーンの変数を取得するためのポインタ
	Actor* enemy_ = nullptr; //ボス
	dxe::Mesh* field_l1_ = nullptr; //床補完用(左上)
	dxe::Mesh* field_r1_ = nullptr; //床補完用(右上)
	dxe::Mesh* field_l2_ = nullptr; //床補完用(左下)
	dxe::Mesh* field_r2_ = nullptr; //床補完用(右下)
	dxe::Mesh* road_ = nullptr; //床補完用(道)
	std::shared_ptr<SkillBase> skills_ = nullptr; //スキルポインタ

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

	int hp_max_ = 10; //ボスHP
	int hp_ = hp_max_;

	bool command_ = false; //コマンドフラグ
	bool battle_ = false; //バトル開始フラグ
	bool progress_ = false; //進行演出フラグ
	bool next_turn_ = false;
	int action_num_ = -1; //アクション回数
	int player_action_[3] = { -1,-1,-1 }; //プレイヤーの行動を予約
	int enemy_action_[3] = { -1,-1,-1 }; //エネミーの行動を予約

	const int INDEX_MAX_ = 3; //インデックス最大数
	int index_main_ = 0; //メインコマンド選択用インデックス
	int index_sub_ = 0; //サブコマンド選択用インデックス
	int index_sub_list_ = 0; //サブコマンドリスト位置用インデックス
	bool main_command_ = true; //メインコマンドかどうか
	int select_num_ = 0; //選択した行動数

	bool init_progress_ = false; //演出初期処理

	bool win_ = false; //勝ちフラグ
	bool lose_ = false; //負けフラグ

	bool init_win_ = false; //勝ち演出の初期処理
	bool win_result_ = false; //リザルト画面へ遷移するフラグ

	bool init_lose_ = false; //負け演出の初期処理
	bool lose_result_ = false; //リザルト画面へ遷移するフラグ
};