#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class ItemList {
public:
	ItemList() {}
	~ItemList() {}
	std::string name_ = "-"; //���O
	std::string ex1_ = "-"; //������
	std::string ex2_ = "-"; //������
	int type_ = 0; //�^�C�v
	int num_ = 0; //�񕜗�
	int buy_ = 0; //�w���z
	int sell_ = 0; //���p�z
};