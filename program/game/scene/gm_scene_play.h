#pragma once
#include "gm_scene_base.h"

class GmCamera;
class ObjectBase;
class Actor;
class Ui;
class SubUiBase;
class Bgm;
class Sheet;
class MakeSheet;
class Boss;
class SkillList;
class ItemList;

class ScenePlay : public SceneBase {
public :
	ScenePlay(){}
	~ScenePlay();

	void initialzie() override;
	void update(float delta_time) override;
	void render() override;

	// =========== 関数 ==========

	void getStatus(); //ステータス取得
	void getSkill(); //スキル情報取得
	void setScore(); //スコア情報を記録
	void getItem();
	void getSheet(); //ステージを取得

	void updateObject(float delta_time); //オブジェクト制御
	void updateActor(float delta_time); //アクター制御
	void updateSubUi(float delta_time); //サブUi制御
	void deleteList(); //デリート処理

	void Debug(float delta_time); //デバッグ

	// ========== 基本ステータス ==========

	GmCamera* camera_ = nullptr;
	Ui* ui_ = nullptr; //メインUI
	Bgm* bgm_ = nullptr; //BGM,SE
	dxe::Mesh* frame_ = nullptr; //床の線
	dxe::Mesh* back_black1_ = nullptr; //背景用下地の黒画像
	dxe::Mesh* back_black2_ = nullptr; //背景用下地の黒画像
	std::list<ObjectBase*> objects_; //オブジェクトリスト
	std::list<Actor*> actors_; //アクターリスト
	std::list<SubUiBase*> subUis_; //サブUIリスト
	Actor* player_ = nullptr; //プレイヤーポインタ
	Sheet* sheet_ = nullptr; //譜面ポインタ
	MakeSheet* make_ = nullptr; //譜面作成用クラスポインタ
	Boss* boss_ = nullptr; //ボス戦クラス用ポインタ
	std::vector<std::vector<std::string>> csv_skill_; //スキル情報csv
	SkillList* skill_[10] = { nullptr }; //スキルリスト
	std::vector<std::vector<std::string>> csv_item_; //アイテム情報csv
	ItemList* item_[10] = { nullptr }; //アイテムリスト

	int have_item_[8] = { -1,-1,-1,-1,-1,-1,-1,-1 }; //持ってるアイテム
	int item_num_ = 0; //持ってるアイテムの数

	const float FIELD_H_ = 450.0f; //床の縦幅
	const float FIELD_W_ = 300.0f; //床の横幅
	const float BACK_W_ = 700.0f; //背景の横幅
	const float FIELD_Z1_ = 75.0f; //床画像1枚目の初期Z座標
	const float FIELD_Z2_ = 525.0f; //床画像2枚目の初期Z座標

	std::string road_img_[6] = {
		"graphics/base/road.png",
		"graphics/base/road.png",
		"graphics/base/road.png",
		"graphics/base/road.png",
		"graphics/base/road.png",
		"graphics/base/road.png"
	}; //道画像パス
	std::string back_img_[6] = {
		"graphics/base/ground.png",
		"graphics/base/ground.png",
		"graphics/base/cave_wall.jpeg",
		"graphics/base/cave_wall.jpeg",
		"graphics/base/sea.jpg",
		"graphics/base/kuraimori4.jpg"
	}; //背景画像パス

	std::string stage_csv_[6] = {
		"csv/stage_1.csv",
		"csv/stage_2.csv",
		"csv/stage_3.csv",
		"csv/stage_4.csv",
		"csv/stage_5.csv",
		"csv/stage_6.csv"
	};

	const int NOTES_SPEED_ = 4; //ノーツの流れる速度

	// ========== ゲーム内ステータス ==========

	bool isPause_ = false; //一時停止

	int stage_ = 1; //ステージ

	const int COMBO_MAX_ = 999; //最大コンボ数
	const int mp_max_ = 1000; //プレイヤー最大MP
	int combo_ = 0; //コンボ
	int score_ = 0; //スコア
	int hp_max_ = 0; //プレイヤー最大HP
	int hp_ = 0; //プレイヤーHP
	int mp_ = 0; //プレイヤーMP
	int atk_ = 0; //プレイヤー攻撃力
	int player_skills_ = 2; //覚えてるスキルの数

	bool score_judge_ = true; //勝ったかどうか
	int score_perfect_ = 0; //パーフェクト数
	int score_good_ = 0; //グッド数
	int score_miss_ = 0; //ミス数
	int score_max_combo_ = 0; //最大コンボ数
};