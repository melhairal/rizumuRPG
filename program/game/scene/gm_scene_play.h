#pragma once
#include "gm_scene_base.h"

class GmCamera;
class ObjectBase;
class Actor;
class Ui;
class SubUiJudge;
class Bgm;
class Sheet;
class MakeSheet;
class Boss;

class ScenePlay : public SceneBase {
public :
	ScenePlay(){}
	~ScenePlay();

	void initialzie() override;
	void update(float delta_time) override;
	void render() override;

	// =========== 関数 ==========

	void updateObject(float delta_time); //オブジェクト制御
	void updateActor(float delta_time); //アクター制御
	void updateSubUi(float delta_time); //サブUi制御

	void Debug(); //デバッグ

	// ========== 基本ステータス ==========

	GmCamera* camera_ = nullptr;
	Ui* ui_ = nullptr; //メインUI
	Bgm* bgm_ = nullptr; //BGM,SE
	dxe::Mesh* frame_ = nullptr; //床の線
	std::list<ObjectBase*> objects_; //オブジェクトリスト
	std::list<Actor*> actors_; //アクターリスト
	std::list<SubUiJudge*> subUis_; //サブUIリスト
	Actor* player_ = nullptr; //プレイヤーポインタ
	Sheet* sheet_ = nullptr; //譜面ポインタ
	MakeSheet* make_ = nullptr; //譜面作成用クラスポインタ
	Boss* boss_ = nullptr; //ボス戦クラス用ポインタ

	const float FIELD_H_ = 450.0f; //床の縦幅
	const float FIELD_W_ = 300.0f; //床の横幅
	const float BACK_W_ = 700.0f; //背景の横幅
	const float FIELD_Z1_ = 75.0f; //床画像1枚目の初期Z座標
	const float FIELD_Z2_ = 525.0f; //床画像2枚目の初期Z座標
	std::string road_img = "graphics/base/road.png"; //道画像パス
	std::string back_img = "graphics/base/ground.png"; //背景画像パス

	std::string stage_2_csv_ = "csv/stage_2.csv"; //csvパス

	const int NOTES_SPEED_ = 4; //ノーツの流れる速度

	// ========== ゲーム内ステータス ==========

	const int COMBO_MAX_ = 999; //最大コンボ数
	int combo_ = 0; //コンボ

	int score_ = 0; //スコア

	int hp_max_ = 1000; //プレイヤー最大HP
	int hp_ = hp_max_; //プレイヤーHP

	int mp_max_ = 1000; //プレイヤー最大MP
	int mp_ = 0; //プレイヤーMP
};

