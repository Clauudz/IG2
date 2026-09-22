#pragma once
#include "IG2Object.h"
class Block : public IG2Object
{
public:
	Block(Vector3 initPos, SceneNode* node, SceneManager* sceneMng);

	bool canPassThrough();
};

