#include "../gm_manager.h"
#include "gm_scene_map.h"
#include "gm_scene_play.h"


void SceneMap::initialzie() {
	//�E�B���h�E�摜���擾
	getWindow();

	//�}�b�v�摜���擾
	world_map_ = LoadGraph(map_[progress_]);

}

void SceneMap::update(float delta_time)
{
	GameManager* mgr = GameManager::GetInstance();

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		mgr->chengeScene(new ScenePlay());
	}
}

void SceneMap::render()
{
	DrawStringEx(100, 100, -1, "SceneMap");
	DrawRotaGraph(MAP_X_, MAP_Y_, 0.4f, 0, world_map_, true);
	drawWindow(WINDOW_X_, WINDOW_Y_, WINDOW_W_, WINDOW_H_);
	drawWindow(SUB_X_, SUB_Y_, SUB_W_, SUB_H_);
}

void SceneMap::getMgrStatus() {
	GameManager* mgr = GameManager::GetInstance();
	progress_ = mgr->flag_stage_;
}

void SceneMap::getWindow() {
	//�E�B���h�E�摜�ǂݍ���
	window_top_left_ = LoadGraph("graphics/ui/window_b/window_b_001.png");
	window_top_center_ = LoadGraph("graphics/ui/window_b/window_b_002.png");
	window_top_right_ = LoadGraph("graphics/ui/window_b/window_b_003.png");
	window_left_ = LoadGraph("graphics/ui/window_b/window_b_004.png");
	window_center_ = LoadGraph("graphics/ui/window_b/window_b_005.png");
	window_right_ = LoadGraph("graphics/ui/window_b/window_b_006.png");
	window_bot_left_ = LoadGraph("graphics/ui/window_b/window_b_007.png");
	window_bot_center_ = LoadGraph("graphics/ui/window_b/window_b_008.png");
	window_bot_right_ = LoadGraph("graphics/ui/window_b/window_b_009.png");
}

void SceneMap::drawWindow(int x, int y, int width, int height) {
	int center_x1 = x - width / 2 + 20;
	int center_x2 = x + width / 2 - 20;
	int center_y1 = y - height / 2 + 20;
	int center_y2 = y + height / 2 - 20;
	DrawExtendGraph(center_x1, center_y1, center_x2, center_y2, window_center_, true); //���S
	DrawExtendGraph(center_x1 - 20, center_y1, center_x1, center_y2, window_left_, true); //��
	DrawExtendGraph(center_x2, center_y1, center_x2 + 20, center_y2, window_right_, true); //�E
	DrawExtendGraph(center_x1, center_y1 - 20, center_x2, center_y1, window_top_center_, true); //��
	DrawExtendGraph(center_x1, center_y2, center_x2, center_y2 + 20, window_bot_center_, true); //��
	DrawExtendGraph(center_x1 - 20, center_y1 - 20, center_x1, center_y1, window_top_left_, true); //����
	DrawExtendGraph(center_x2, center_y1 - 20, center_x2 + 20, center_y1, window_top_right_, true); //�E��
	DrawExtendGraph(center_x1 - 20, center_y2, center_x1, center_y2 + 20, window_bot_left_, true); //����
	DrawExtendGraph(center_x2, center_y2, center_x2 + 20, center_y2 + 20, window_bot_right_, true); //�E��
}