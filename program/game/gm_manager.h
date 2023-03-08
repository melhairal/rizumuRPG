#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class SceneBase;
class GameManager {
private:
	GameManager();
	~GameManager();

	int img_black_ = 0;

	static GameManager* instance_;

	// 画面遷移演出の時間
	const float SCENE_TRANSITION_FIX_TIME = 0.5f;
	float scene_transition_time_ = 0;
	float scene_transition_alpha_ = 1.0f;

	tnl::Sequence<GameManager> sequence_ =
		tnl::Sequence<GameManager>(this, &GameManager::seqSceneInTransition);

	// 画面遷移( フェードインプロセス )
	bool seqSceneInTransition(const float delta_time);

	// ゲームプロセス
	bool seqGameProcess(const float delta_time);

	// 画面遷移( フェードアウトプロセス )
	bool seqSceneOutTransition(const float delta_time);

	// 現在のシーン
	SceneBase* scene_now_ = nullptr;
	// 予約シーン
	SceneBase* scene_next_ = nullptr;

public:

	// インスタンスの取得
	static GameManager* GetInstance();

	// 破棄
	static void Destroy();

	// 更新
	void update(float delta_time);

	// シーンの変更
	// arg1... SceneBase を継承したクラスインスタンス
	void chengeScene(SceneBase* next);

public:

	// ゲーム全体で参照したい変数はここで用意

	//プレイヤーステータス
	int player_lv_ = 1; //デフォルト1
	int player_atk_ = 10; //デフォルト10
	int player_hp_ = 1000; //デフォルト1000
	int player_mp_ = 0;
	int player_exp_ = 0;
	int player_monney_ = 500; //デフォルト500
	int player_skills_ = 8; //デフォルト値は2s
	int have_items_[8] = { 0,3,-1,-1,-1,-1,-1,-1 }; //持ってるアイテム(id)

	//リザルト画面用
	bool result_judge_ = true;
	int result_score_ = 0;
	int result_max_combo_ = 0;
	int result_perfect_ = 0;
	int result_good_ = 0;
	int result_miss_ = 0;

	int now_stage_ = 0; //選んだステージ

	//進行フラグ(クリアフラグ)
	int flag_stage_ = 6;
	int max_score_[6] = { 0,0,0,0,0,0 };

	//ハイスコア
	int best_score_[6] = { 0,0,0,0,0,0 };
};