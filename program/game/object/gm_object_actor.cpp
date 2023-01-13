#include "gm_object_actor.h"
#include "../scene/gm_scene_play.h"
#include "../gm_camera.h"

void Actor::animation(int frame) {
	elapsed_++;
	if (elapsed_ >= frame) {
		elapsed_ = 0;
		frame_++;
		mesh_->setTexture(dxe::Texture::CreateFromFile(*it));
		it++;
		if (it == images_.end()) it = images_.begin();
	}
}