#include "gm_bgm.h"
#include "scene/gm_scene_play.h"

Bgm::Bgm(ScenePlay* scene) {
	scene_ = scene;
	se_notes_ = LoadSoundMem("sound/notes.mp3");
	se_perfect_ = LoadSoundMem("sound/perfect.wav");
}

void Bgm::update(float delta_time) {
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
	perfect_ = false;
}