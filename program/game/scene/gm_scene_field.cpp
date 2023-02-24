#include "../gm_manager.h"
#include "../gm_camera.h"
#include "../model/gm_anim_sprite3d.h"
#include "gm_scene_field.h"
#include "gm_scene_map.h"
#include "../3d_object/gm_3d_model.h"
#include "../3d_object/gm_3d_sprite.h"

extern tnl::Quaternion fix_rot;

SceneField::~SceneField() {
	delete camera_;
	delete field_;
	delete load_;
	for (auto sprite : sprites_) delete sprite;
	for (auto model : models_) delete model;
}


void SceneField::initialzie() {
	SetUseLighting(FALSE);

	//�J����
	camera_ = new GmCamera();
	camera_->pos_ = { 0, 150, -300 };
	camera_->free_look_angle_xy_.x = tnl::ToRadian(CAM_ROT_MIN_);

	//�v���C���[
	player_ = sprites_.emplace_back(new SpritePlayer(this));

	//�t�B�[���h�𐶐�
	setField1();

}

void SceneField::update(float delta_time)
{
	GameManager* mgr = GameManager::GetInstance();

	//�J��������
	moveCamera();

	//�X�v���C�g����
	updateSprites(delta_time);

	//���f������
	updateModels(delta_time);

	//�t�B�[���h����o�鏈��
	outField();

}

void SceneField::render()
{
	camera_->update();

	DrawGridGround(camera_, 50, 20);

	DrawRotaGraph(DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT / 2, 2.5f, 0, img_back_, true); //�w�i�̕`��
	field_->render(camera_); //���̕`��
	load_->render(camera_); //���̕`��

	for (auto model : models_) model->render(); //���f���̕`��
	for (auto sprite : sprites_) sprite->render(); //�X�v���C�g�̕`��
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
	//�J�����㉺��]�̏��
	camera_->free_look_angle_xy_.x = std::clamp(camera_->free_look_angle_xy_.x, tnl::ToRadian(CAM_ROT_MIN_), tnl::ToRadian(CAM_ROT_MAX_));

	if (tnl::Input::IsKeyDown(eKeys::KB_Z)) {
		camera_->target_distance_ += CAM_ZOOM_SPEED_;
	}
	if (tnl::Input::IsKeyDown(eKeys::KB_X)) {
		camera_->target_distance_ -= CAM_ZOOM_SPEED_;
	}
	//�J�����Y�[���̏���E����
	camera_->target_distance_ = std::clamp(camera_->target_distance_, CAM_ZOOM_MIN_, CAM_ZOOM_MAX_);
	//�J�����^�[�Q�b�g
	camera_->target_ = player_->sprite_->pos_;
}

void SceneField::updateSprites(float delta_time) {
	//�S�ẴX�v���C�g�̃A�b�v�f�[�g
	for (auto sprite : sprites_) sprite->update(delta_time);

	//�J�����ɋ߂����Ƀ\�[�g(�߂��I�u�W�F�N�g����`�悷�邽��)
	sprites_.sort([&](const SpriteBase* l, const SpriteBase* r) {
		float ld = 0;
		float rd = 0;
		if (l->sprite_ != nullptr) ld = (camera_->pos_ - l->sprite_->pos_).length();
		if (r->sprite_ != nullptr) rd = (camera_->pos_ - r->sprite_->pos_).length();
		return ld > rd;
		});

	//�X�v���C�g�̐����t���O��false�ɂȂ�����f���[�g
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
	//�S�Ẵ��f���̃A�b�v�f�[�g
	for (auto model : models_) model->update(delta_time);

	//���f���̐����t���O��false�ɂȂ�����f���[�g
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
		mgr->chengeScene(new SceneMap());
	}
}

void SceneField::setField1() {
	//��
	models_.emplace_back(new ModelHouse(this, { -300,0,0 }, 0));
	models_.emplace_back(new ModelHouse(this, { -200,0,250 }, 45));
	//models_.emplace_back(new ModelHouse(this, { -200,0,-250 }, -45));
	models_.emplace_back(new ModelHouse(this, { 200,0,150 }, 150));
	models_.emplace_back(new ModelHouse(this, { 200,0,-150 }, -150));

	//��
	field_ = dxe::Mesh::CreateDisk(FIELD_R_);
	field_->setTexture(dxe::Texture::CreateFromFile("graphics/base/ground.png"));
	field_->rot_q_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(90));
	field_->pos_ = { 0, FIELD_H_, 0 };

	//��
	load_ = dxe::Mesh::CreatePlane({ 150, 1600, 0 });
	load_->setTexture(dxe::Texture::CreateFromFile("graphics/base/road.png"));
	load_->rot_q_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(90));
	load_->pos_ = { 0, FIELD_H_ + 1, 0 };
	
	//�w�i
	img_back_ = LoadGraph("graphics/base/sky.jpg");

	//��
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

}