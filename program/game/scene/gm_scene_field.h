#pragma once
#include "gm_scene_base.h"
#include "../../dxlib_ext/dxlib_ext.h"
class GmCamera;
class AnimSprite3D;
class SpriteBase;
class ModelBase;
class FieldUi;
class SkillList;
class ItemList;

class SceneField : public SceneBase {
public:
	SceneField() {}
	~SceneField();

	void initialzie() override;
	void update(float delta_time) override;
	void render() override;

	// =========== 関数 ==========
	
	void getStatus(); //ステータスを取得
	void getSkill(); //スキル情報を取得
	void getItem(); //アイテム情報を取得
	void setItem(); //アイテム情報を登録

	void moveCamera(); //カメラ制御
	void updateSprites(float delta_time); //スプライト制御
	void updateModels(float delta_time); //モデル制御
	void playSe(); //SE制御

	void outField(); //フィールドから出る処理

	void setField1(); //フィールド1番を生成

	void finishGame(); //ゲーム終了

	// ========== 基本ステータス ==========

	GmCamera* camera_ = nullptr; //カメラ
	SpriteBase* player_ = nullptr; //プレイヤー
	std::list<SpriteBase*> sprites_; //スプライトリスト
	std::list<ModelBase*> models_; //3Dモデルリスト
	FieldUi* ui_ = nullptr; //UI

	int img_back_ = 0; //背景画像
	dxe::Mesh* field_ = nullptr; //床
	dxe::Mesh* load_ = nullptr; //道

	int bgm_ = 0; //BGM
	int se_select_ = 0; //選択音
	int se_esc_ = 0; //キャンセル音

	//プレイヤーステータス
	int player_lv_ = 0;
	int player_hp_ = 0;
	int player_atk_ = 0;
	int player_exp_ = 0;
	int player_monney_ = 0;
	int player_skills_ = 4;

	std::vector<std::vector<std::string>> csv_skill_; //スキル情報csv
	SkillList* skill_[10] = { nullptr }; //スキルリスト

	std::vector<std::vector<std::string>> csv_item_; //スキル情報csv
	ItemList* item_[5] = { nullptr }; //アイテムリスト
	int items_[8] = { -1,-1,-1,-1,-1,-1,-1,-1 };

	//経験値テーブル
	const int UP_EXP_[10] = {
		1000,
		2000,
		3000,
		5000,
		10000,
		20000,
		30000,
		40000,
		50000,
		0
	};

	const float CAM_ROT_SPEED_ = 1.0f; //カメラ回転速度
	const float CAM_ROT_MAX_ = 60.0f; //カメラ回転上限
	const float CAM_ROT_MIN_ = 10.0f; //カメラ回転下限
	const float CAM_ZOOM_SPEED_ = 5.0f; //カメラズーム速度
	const float CAM_ZOOM_MAX_ = 400.0f; //カメラズーム下限
	const float CAM_ZOOM_MIN_ = 200.0f; //カメラズーム上限

	const float FIELD_H_ = -15.0f; //地面の高さ座標
	const int FIELD_R_ = 800; //フィールドの半径

	bool isMenu_ = false; //メニューフラグ
	bool isShop_ = false; //ショップフラグ

};