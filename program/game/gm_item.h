#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class ItemList {
public:
	ItemList() {}
	~ItemList() {}
	std::string name_ = "-"; //–¼‘O
	std::string ex1_ = "-"; //à–¾•¶
	std::string ex2_ = "-"; //à–¾•¶
	int type_ = 0; //ƒ^ƒCƒv
	int num_ = 0; //‰ñ•œ—Ê
	int buy_ = 0; //w“üŠz
	int sell_ = 0; //”„‹pŠz
};