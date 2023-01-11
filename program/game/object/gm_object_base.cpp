#include "gm_object_base.h"
#include "../scene/gm_scene_play.h"

ObjectBase::~ObjectBase() {
	if (mesh_ != nullptr) delete mesh_;
}