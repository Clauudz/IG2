#include "Villain.h"
#include "Config.h"
#include "Laberinto.h"
#include "Hero.h"
#include "Block.h"

#include <numeric>

Villain::Villain(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, String mesh) : Character(initPos, node, sceneMng, mesh)
{
    mNode->setScale(Ogre::Vector3(0.5, 0.5, 0.5));
}

void Villain::update(Laberinto* lab, Real dt)
{
	Block* vilBlock = lab->getBlock(getPosition());
    bool isIntersection = distanciaXZ(vilBlock) < getSpeed() * dt;

	if (!isIntersection) return;

	// blocks
	Block* upBlock, *rightBlock, *leftBlock, *downBlock;

    upBlock = lab->getBlock((Vector3::NEGATIVE_UNIT_Z * Config::BLOCK_SIZE) + getPosition());
	downBlock = lab->getBlock((Vector3::UNIT_Z * Config::BLOCK_SIZE) + getPosition());
	rightBlock = lab->getBlock((Vector3::UNIT_X * Config::BLOCK_SIZE) + getPosition());
	leftBlock = lab->getBlock((Vector3::NEGATIVE_UNIT_X * Config::BLOCK_SIZE) + getPosition());

	Vector3 charPos = lab->getHero()->getPosition();

	Direction minDir = RIGHT;
	float minDistance = std::numeric_limits<float>::max();

    if (upBlock->canPassThrough()) {
        float dist = upBlock->getPosition().distance(charPos);
        if (dist < minDistance) {
            minDir = UP;
            minDistance = dist;
        }
    }

    if (downBlock->canPassThrough()) {
        float dist = downBlock->getPosition().distance(charPos);
        if (dist < minDistance) {
            minDir = DOWN;
            minDistance = dist;
        }
    }

    if (leftBlock->canPassThrough()) {
        float dist = leftBlock->getPosition().distance(charPos);
        if (dist < minDistance) {
            minDir = LEFT;
            minDistance = dist;
        }
    }

    if (rightBlock->canPassThrough()) {
        float dist = rightBlock->getPosition().distance(charPos);
        if (dist < minDistance) {
            minDir = RIGHT;
            minDistance = dist;
        }
    }

    setNextDirection(minDir);
}
