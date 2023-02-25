#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class ItemList {
public:
	ItemList() {}
	~ItemList() {}
	std::string name_ = "-"; //名前
	std::string ex1_ = "-"; //説明文
	std::string ex2_ = "-"; //説明文
	int type_ = 0; //タイプ
	int num_ = 0; //回復量
};