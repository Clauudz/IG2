#include "Block.h"

Block::Block(Vector3 initPos, SceneNode* node, SceneManager* sceneMng) : IG2Object(initPos, node, sceneMng, "cube.mesh")
{
}

bool Block::canPassThrough()
{
	return true;
}
