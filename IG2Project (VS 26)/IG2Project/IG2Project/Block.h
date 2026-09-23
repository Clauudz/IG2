#pragma once
#include "IG2Object.h"
class Block : public IG2Object
{
public:
	Block(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, std::string mesh) : IG2Object(initPos, node, sceneMng, mesh){}
	Block(Vector3 initPos, SceneNode* node, SceneManager* sceneMng) : IG2Object(initPos, node, sceneMng) {}
	virtual bool canPassThrough() = 0;
};

class EmptyBlock : public Block
{
public:
	EmptyBlock(Vector3 initPos, SceneNode* node, SceneManager* sceneMng) : Block(initPos, node, sceneMng){}

	bool canPassThrough() override {
		return true;
	}
};

class WallBlock : public Block
{
public:
	WallBlock(Vector3 initPos, SceneNode* node, SceneManager* sceneMng) : Block(initPos, node, sceneMng, "cube.mesh") {}

	bool canPassThrough() override {
		return false;
	}
};
