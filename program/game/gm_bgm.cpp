#include "gm_bgm.h"
#include "scene/gm_scene_play.h"
#include "gm_boss.h"

Bgm::Bgm(ScenePlay* scene) {
	scene_ = scene;
	se_notes_ = LoadSoundMem("sound/notes.mp3");
	se_perfect_ = LoadSoundMem("sound/perfect.wav");
	se_hit_ = LoadSoundMem("sound/hit.mp3");

	se_select_ = LoadSoundMem("sound/select.mp3");
	se_esc_ = LoadSoundMem("sound/escape.mp3");
	sound_warning_ = LoadSoundMem("sound/warning.mp3");

	bgm_boss_ = LoadSoundMem("sound/stage_2_boss.mp3");

	prev_hp_ = scene_->hp_;
}

void Bgm::update(float delta_time) {
	//���[�����v���C���[���ړ����鉹
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_D)) {
		if(perfect_) PlaySoundMem(se_perfect_, DX_PLAYTYPE_BACK);
		else PlaySoundMem(se_notes_, DX_PLAYTYPE_BACK);
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_F)) {
		if (perfect_) PlaySoundMem(se_perfect_, DX_PLAYTYPE_BACK);
		else PlaySoundMem(se_notes_, DX_PLAYTYPE_BACK);
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_J)) {
		if (perfect_) PlaySoundMem(se_perfect_, DX_PLAYTYPE_BACK);
		else PlaySoundMem(se_notes_, DX_PLAYTYPE_BACK);
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_K)) {
		if (perfect_) PlaySoundMem(se_perfect_, DX_PLAYTYPE_BACK);
		else PlaySoundMem(se_notes_, DX_PLAYTYPE_BACK);
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE)) {
		if (perfect_) PlaySoundMem(se_perfect_, DX_PLAYTYPE_BACK);
	}
	perfect_ = false;

	//�_���[�W���󂯂��Ƃ��̉�
	if (prev_hp_ > scene_->hp_) {
		PlaySoundMem(se_hit_, DX_PLAYTYPE_BACK);
	}
	prev_hp_ = scene_->hp_;

	//�{�X��
	if (scene_->boss_ != nullptr) {
		//�x����
		if (!scene_->boss_->init_ && scene_->boss_->is_changing_angle_ && scene_->boss_->elapsed_ == 1) {
			PlaySoundMem(sound_warning_, DX_PLAYTYPE_BACK);
		}
		//�R�}���h�I����
		if (scene_->boss_->command_) {
			if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP) || tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN) || tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
				PlaySoundMem(se_select_, DX_PLAYTYPE_BACK);
			}
			if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
				PlaySoundMem(se_esc_, DX_PLAYTYPE_BACK);
			}
		}
	}
}