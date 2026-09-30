#pragma once
#include "IG2Object.h"
class Block : public IG2Object
{
public:
	Block(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, std::string mesh) : IG2Object(initPos, node, sceneMng, mesh){}
	Block(Vector3 initPos, SceneNode* node, SceneManager* sceneMng) : IG2Object(initPos, node, sceneMng) {}
	virtual bool canPassThrough() = 0;
	virtual void update(Real dt) = 0;
};

class EmptyBlock : public Block
{
public:
	EmptyBlock(Vector3 initPos, SceneNode* node, SceneManager* sceneMng) : Block(initPos, node, sceneMng){}

	bool canPassThrough() override {
		return true;
	}
	void update(Real dt) override {

	}
};

class WallBlock : public Block
{
public:
	WallBlock(Vector3 initPos, SceneNode* node, SceneManager* sceneMng) : Block(initPos, node, sceneMng, "cube.mesh") {}

	bool canPassThrough() override {
		return false;
	}
	void update(Real dt) override {

	}
};

class InvisibleBlock : public Block
{
private:
	bool visible;
	Timer timer;

	const uint64_t INVISIBLE_TIMER = 5;

public:
	InvisibleBlock(Vector3 initPos, SceneNode* node, SceneManager* sceneMng) : Block(initPos, node, sceneMng, "cube.mesh")
		,visible(true) {}

	bool canPassThrough() override {
		return false;
	}
	void update(Real dt) override {
		if (timer.getMilliseconds() >= INVISIBLE_TIMER * 1000) {
			visible = !visible;
			timer.reset();

			setVisible(visible);
		}
	}
};

class FakeBlock : public Block
{
public:
	FakeBlock(Vector3 initPos, SceneNode* node, SceneManager* sceneMng) : Block(initPos, node, sceneMng, "cube.mesh") {}

	bool canPassThrough() override {
		return true;
	}
	void update(Real dt) override {

	}
};

class BreakableBlock : public Block
{
public:
	BreakableBlock(Vector3 initPos, SceneNode* node, SceneManager* sceneMng) : Block(initPos, node, sceneMng, "cube.mesh") {}

	bool canPassThrough() override {
		return false;
	}
	void update(Real dt) override {

	}
};