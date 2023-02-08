#pragma once
#include <unordered_map>
#include <functional>
#include <memory>
#include "gm_object_attack.h"
class ScenePlay;

std::unordered_map<std::string, std::function<std::shared_ptr<SkillBase>(ScenePlay*)>> generator_map;

const int generator_register(const std::string& name,
	std::function<std::shared_ptr<SkillBase>(ScenePlay*)> gen) {
	generator_map.insert(std::make_pair(name, gen));
	return 0;
}


std::shared_ptr<SkillBase> generateSkillNormalA(ScenePlay* scene) {
	std::shared_ptr<SkillBase> p = std::make_shared<SkillNormalA>(scene);
	return p;
}
const int a = generator_register(typeid(SkillNormalA).name(), generateSkillNormalA);

std::shared_ptr<SkillBase> generateSkillNormalB(ScenePlay* scene) {
	std::shared_ptr<SkillBase> p = std::make_shared<SkillNormalB>(scene);
	return p;
}
const int b = generator_register(typeid(SkillNormalB).name(), generateSkillNormalB);

std::shared_ptr<SkillBase> generateSkillComboA(ScenePlay* scene) {
	std::shared_ptr<SkillBase> p = std::make_shared<SkillComboA>(scene);
	return p;
}
const int c = generator_register(typeid(SkillComboA).name(), generateSkillComboA);

std::shared_ptr<SkillBase> generateSkillComboB(ScenePlay* scene) {
	std::shared_ptr<SkillBase> p = std::make_shared<SkillComboB>(scene);
	return p;
}
const int d = generator_register(typeid(SkillComboB).name(), generateSkillComboB);

std::shared_ptr<SkillBase> generateSkillComboC(ScenePlay* scene) {
	std::shared_ptr<SkillBase> p = std::make_shared<SkillComboC>(scene);
	return p;
}
const int e = generator_register(typeid(SkillComboC).name(), generateSkillComboC);

std::shared_ptr<SkillBase> generateSkillComboD(ScenePlay* scene) {
	std::shared_ptr<SkillBase> p = std::make_shared<SkillComboD>(scene);
	return p;
}
const int f = generator_register(typeid(SkillComboD).name(), generateSkillComboD);

std::shared_ptr<SkillBase> generateSkillPowerA(ScenePlay* scene) {
	std::shared_ptr<SkillBase> p = std::make_shared<SkillPowerA>(scene);
	return p;
}
const int g = generator_register(typeid(SkillPowerA).name(), generateSkillPowerA);

std::shared_ptr<SkillBase> generateSkillPowerB(ScenePlay* scene) {
	std::shared_ptr<SkillBase> p = std::make_shared<SkillPowerB>(scene);
	return p;
}
const int h = generator_register(typeid(SkillPowerB).name(), generateSkillPowerB);

std::shared_ptr<SkillBase> generateSkillPowerC(ScenePlay* scene) {
	std::shared_ptr<SkillBase> p = std::make_shared<SkillPowerC>(scene);
	return p;
}
const int i = generator_register(typeid(SkillPowerC).name(), generateSkillPowerC);

std::shared_ptr<SkillBase> generateSkillOtherA(ScenePlay* scene) {
	std::shared_ptr<SkillBase> p = std::make_shared<SkillOtherA>(scene);
	return p;
}
const int j = generator_register(typeid(SkillOtherA).name(), generateSkillOtherA);