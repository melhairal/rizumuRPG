#pragma once
#include "gm_scene_base.h"
#include "../../dxlib_ext/dxlib_ext.h"
class GmCamera;
class AnimSprite3D;
class SpriteBase;
class ModelBase;

class SceneField : public SceneBase {
public:
	SceneField() {}
	~SceneField();

	void initialzie() override;
	void update(float delta_time) override;
	void render() override;

	// =========== 関数 ==========

	void moveCamera(); //カメラ制御
	void updateSprites(float delta_time); //スプライト制御
	void updateModels(float delta_time); //モデル制御

	void setField1(); //フィールド1番を生成

	// ========== 基本ステータス ==========

	GmCamera* camera_ = nullptr; //カメラ
	SpriteBase* player_ = nullptr; //プレイヤー
	std::list<SpriteBase*> sprites_; //スプライトリスト
	std::list<ModelBase*> models_; //3Dモデルリスト

	int img_back_ = 0; //背景画像
	dxe::Mesh* field_ = nullptr; //床

	const float CAM_ROT_SPEED_ = 1.0f; //カメラ回転速度
	const float CAM_ROT_MAX_ = 60.0f; //カメラ回転上限
	const float CAM_ROT_MIN_ = 10.0f; //カメラ回転下限
	const float CAM_ZOOM_SPEED_ = 5.0f; //カメラズーム速度
	const float CAM_ZOOM_MAX_ = 400.0f; //カメラズーム下限
	const float CAM_ZOOM_MIN_ = 200.0f; //カメラズーム上限

	const float FIELD_H_ = -15.0f; //地面の高さ座標
	const int FIELD_R_ = 800; //フィールドの半径

};