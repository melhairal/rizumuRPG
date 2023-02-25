#include "../gm_manager.h"
#include "../gm_camera.h"
#include "../model/gm_anim_sprite3d.h"
#include "gm_scene_field.h"
#include "gm_scene_map.h"
#include "gm_scene_title.h"
#include "../3d_object/gm_3d_model.h"
#include "../3d_object/gm_3d_sprite.h"
#include "../gm_field_ui.h"
#include "../object/gm_object_attack.h"
#include "../gm_item.h"

extern tnl::Quaternion fix_rot;

SceneField::~SceneField() {
	delete camera_;
	delete ui_;
	delete field_;
	delete load_;
	for (auto sprite : sprites_) delete sprite;
	for (auto model : models_) delete model;
}

void SceneField::initialzie() {
	SetUseLighting(FALSE);

	//ステータス取得
	getStatus();
	getSkill();
	getItem();

	//カメラ
	camera_ = new GmCamera();
	camera_->pos_ = { 0, 150, -300 };
	camera_->free_look_angle_xy_.x = tnl::ToRadian(CAM_ROT_MIN_);

	//プレイヤー
	player_ = sprites_.emplace_back(new SpritePlayer(this));

	//UI
	ui_ = new FieldUi(this);

	//フィールドを生成
	setField1();

	//BGM取得
	bgm_ = LoadSoundMem("sound/village_1.mp3");
	se_select_ = LoadSoundMem("sound/select.mp3");
	se_esc_ = LoadSoundMem("sound/escape.mp3");
	PlaySoundMem(bgm_, DX_PLAYTYPE_LOOP);
}

void SceneField::update(float delta_time)
{
	GameManager* mgr = GameManager::GetInstance();

	//se処理
	playSe();

	//メニュー制御
	if (!isMenu_ && tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE) && !isShop_) {
		isMenu_ = true;
		player_->move_ = false;
		ui_->menu_depth_ = 1;
	}

	//カメラ制御
	if (player_->move_) moveCamera();

	//スプライト制御
	updateSprites(delta_time);

	//モデル制御
	updateModels(delta_time);

	//ui制御
	ui_->update(delta_time);

	//フィールドから出る処理
	outField();
}

void SceneField::render()
{
	camera_->update();

	DrawGridGround(camera_, 50, 20);

	DrawRotaGraph(DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT / 2, 2.5f, 0, img_back_, true); //背景の描画
	field_->render(camera_); //床の描画
	load_->render(camera_); //道の描画

	for (auto model : models_) model->render(); //モデルの描画
	for (auto sprite : sprites_) sprite->render(); //スプライトの描画

	ui_->render(); //UI描画
}

void SceneField::getStatus() {

	GameManager* mgr = GameManager::GetInstance();

	player_lv_ = mgr->player_lv_;
	player_hp_ = mgr->player_hp_;
	player_atk_ = mgr->player_atk_;
	player_exp_ = mgr->player_exp_;
	player_monney_ = mgr->player_monney_;
	player_skills_ = mgr->player_skills_ + 2;
	for (int i = 0; i < 8; ++i) {
		items_[i] = mgr->have_items_[i];
	}
}

void SceneField::getSkill() {
	for (int i = 0; i < 10; ++i) {
		csv_skill_ = tnl::LoadCsv("csv/skill.csv");
		skill_[i] = new SkillList();
		skill_[i]->name_ = csv_skill_[i + 1][0].c_str();
		skill_[i]->mp_ = std::atoi(csv_skill_[i + 1][1].c_str());
		skill_[i]->exp1_ = csv_skill_[i + 1][2].c_str();
		skill_[i]->exp2_ = csv_skill_[i + 1][3].c_str();
		skill_[i]->exp3_ = csv_skill_[i + 1][4].c_str();
		skill_[i]->class_name_ = csv_skill_[i + 1][5].c_str();
	}
}

void SceneField::getItem() {
	for (int i = 0; i < 5; ++i) {
		csv_skill_ = tnl::LoadCsv("csv/item.csv");
		item_[i] = new ItemList();
		item_[i]->name_ = csv_skill_[i + 1][0].c_str();
		item_[i]->ex1_ = csv_skill_[i + 1][3].c_str();
		item_[i]->ex2_ = csv_skill_[i + 1][4].c_str();
		item_[i]->type_ = std::atoi(csv_skill_[i + 1][1].c_str());
		item_[i]->num_ = std::atoi(csv_skill_[i + 1][2].c_str());
		item_[i]->buy_ = std::atoi(csv_skill_[i + 1][5].c_str());
		item_[i]->sell_ = std::atoi(csv_skill_[i + 1][6].c_str());
	}
}

void SceneField::setItem() {
	GameManager* mgr = GameManager::GetInstance();
	for (int i = 0; i < 8; ++i) {
		mgr->have_items_[i] = items_[i];
	}
}

void SceneField::moveCamera() {
	tnl::Vector3 rot[4] = {
		{ 0, tnl::ToRadian(CAM_ROT_SPEED_), 0 },
		{ 0, -tnl::ToRadian(CAM_ROT_SPEED_), 0 },
		{ tnl::ToRadian(CAM_ROT_SPEED_), 0, 0 },
		{ -tnl::ToRadian(CAM_ROT_SPEED_), 0, 0 } };
	tnl::Input::RunIndexKeyDown([&](uint32_t idx) {
		camera_->free_look_angle_xy_ += rot[idx];
		}, eKeys::KB_LEFT, eKeys::KB_RIGHT, eKeys::KB_UP, eKeys::KB_DOWN);
	//カメラ上下回転の上限
	camera_->free_look_angle_xy_.x = std::clamp(camera_->free_look_angle_xy_.x, tnl::ToRadian(CAM_ROT_MIN_), tnl::ToRadian(CAM_ROT_MAX_));

	if (tnl::Input::IsKeyDown(eKeys::KB_Z)) {
		camera_->target_distance_ += CAM_ZOOM_SPEED_;
	}
	if (tnl::Input::IsKeyDown(eKeys::KB_X)) {
		camera_->target_distance_ -= CAM_ZOOM_SPEED_;
	}
	//カメラズームの上限・下限
	camera_->target_distance_ = std::clamp(camera_->target_distance_, CAM_ZOOM_MIN_, CAM_ZOOM_MAX_);
	//カメラターゲット
	camera_->target_ = player_->sprite_->pos_;
}

void SceneField::updateSprites(float delta_time) {
	//全てのスプライトのアップデート
	for (auto sprite : sprites_) sprite->update(delta_time);

	//カメラに近い順にソート(近いオブジェクトから描画するため)
	sprites_.sort([&](const SpriteBase* l, const SpriteBase* r) {
		float ld = 0;
		float rd = 0;
		if (l->sprite_ != nullptr) ld = (camera_->pos_ - l->sprite_->pos_).length();
		if (r->sprite_ != nullptr) rd = (camera_->pos_ - r->sprite_->pos_).length();
		return ld > rd;
		});

	//スプライトの生存フラグがfalseになったらデリート
	auto it_sprite = sprites_.begin();
	while (it_sprite != sprites_.end()) {
		if (!(*it_sprite)->alive_) {
			delete (*it_sprite);
			it_sprite = sprites_.erase(it_sprite);
			continue;
		}
		it_sprite++;
	}
}

void SceneField::updateModels(float delta_time) {
	//全てのモデルのアップデート
	for (auto model : models_) model->update(delta_time);

	//モデルの生存フラグがfalseになったらデリート
	auto it_model = models_.begin();
	while (it_model != models_.end()) {
		if (!(*it_model)->alive_) {
			delete (*it_model);
			it_model = models_.erase(it_model);
			continue;
		}
		it_model++;
	}
}

void SceneField::outField() {
	if (player_->sprite_->pos_.z > 410 || player_->sprite_->pos_.z < -410) {
		GameManager* mgr = GameManager::GetInstance();
		setItem();
		StopSoundMem(bgm_);
		mgr->chengeScene(new SceneMap());
	}
}

void SceneField::setField1() {
	//家
	models_.emplace_back(new ModelHouse(this, { -300,0,0 }, 0));
	models_.emplace_back(new ModelHouse(this, { -200,0,250 }, 45));
	models_.emplace_back(new ModelHouse(this, { 200,0,150 }, 150));
	models_.emplace_back(new ModelHouse(this, { 200,0,-150 }, -150));

	//床
	field_ = dxe::Mesh::CreateDisk(FIELD_R_);
	field_->setTexture(dxe::Texture::CreateFromFile("graphics/base/ground.png"));
	field_->rot_q_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(90));
	field_->pos_ = { 0, FIELD_H_, 0 };

	//道
	load_ = dxe::Mesh::CreatePlane({ 150, 1600, 0 });
	load_->setTexture(dxe::Texture::CreateFromFile("graphics/base/road.png"));
	load_->rot_q_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(90));
	load_->pos_ = { 0, FIELD_H_ + 1, 0 };
	
	//背景
	img_back_ = LoadGraph("graphics/base/sky.jpg");

	//木
	for (int i = 0; i < 30; ++i) {
		if (i == 7 || i == 8 || i == 22 || i == 23) continue;
		double th = ((double)i / (double)30) * 3.14f * 2;
		float x = 390.0f * cos(th);
		float y = 390.0f * sin(th);
		sprites_.emplace_back(new SpriteTree(this, { x,25,y }));
	}
	for (int i = 0; i < 30; ++i) {
		if (i == 11 || i == 26) continue;
		double th = ((double)i / (double)30) * 3.14f * 2 + 15;
		float x = 450.0f * cos(th);
		float y = 450.0f * sin(th);
		sprites_.emplace_back(new SpriteTree(this, { x,25,y }));
	}

	//NPC
	sprites_.emplace_back(new SpriteMurabito(this, { 0,0,100 }));
	sprites_.emplace_back(new SpriteMurabitoF(this, { -200,0,-250 }));
	sprites_.emplace_back(new SpriteHeisi(this, { 60,0,370 }, 2));
	sprites_.emplace_back(new SpriteKazi(this, { -210,0,-20 }, 1));
	sprites_.emplace_back(new SpriteShop(this, { 110,0,-90 }, 3));

}

void SceneField::finishGame() {
	GameManager* mgr = GameManager::GetInstance();
	StopSoundMem(bgm_);
	mgr->chengeScene(new SceneTitle());
}

void SceneField::playSe() {
	if (isMenu_) {
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			PlaySoundMem(se_select_, DX_PLAYTYPE_BACK);
		}
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) {
			PlaySoundMem(se_select_, DX_PLAYTYPE_BACK);
		}
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)) {
			PlaySoundMem(se_select_, DX_PLAYTYPE_BACK);
		}
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
			PlaySoundMem(se_esc_, DX_PLAYTYPE_BACK);
		}
	}
	else {
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
			PlaySoundMem(se_select_, DX_PLAYTYPE_BACK);
		}
	}
	if (player_->isComment_) {
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			PlaySoundMem(se_select_, DX_PLAYTYPE_BACK);
		}
	}
}