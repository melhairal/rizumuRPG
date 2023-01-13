#pragma once
#include "gm_scene_base.h"

class GmCamera;
class ObjectBase;
class Actor;

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

	// ========== 基本ステータス ==========

	GmCamera* camera_ = nullptr;
	dxe::Mesh* frame_ = nullptr;
	std::list<ObjectBase*> objects_; //オブジェクトリスト
	std::list<Actor*> actors_; //アクターリスト
	Actor* player_ = nullptr; //プレイヤーポインタ

	const float FIELD_H_ = 450.0f; //床の縦幅
	const float FIELD_W_ = 300.0f; //床の横幅
	const float BACK_W_ = 700.0f; //背景の横幅
	const float FIELD_Z1_ = 75.0f; //床画像1枚目の初期Z座標
	const float FIELD_Z2_ = 525.0f; //床画像2枚目の初期Z座標
	std::string road_img = "graphics/base/road.png"; //道画像パス
	std::string back_img = "graphics/base/ground.png"; //背景画像パス
};

