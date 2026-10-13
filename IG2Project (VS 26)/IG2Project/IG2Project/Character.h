#pragma once

#include "IG2Object.h"

class Block;
class Laberinto;
class Character: public IG2Object
{
private:
    Ogre::Quaternion getQuaternionForNewDirection();

public:

    enum Direction { RIGHT, LEFT, UP, DOWN };
    Direction nextDir = RIGHT;
    Direction actDir;

    void setNextDirection(Direction dir);

    Character(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, String mesh);
    virtual void update(Laberinto* lab, float dt) {};

    Ogre::Vector3 getNexDirVector();
    bool isDirectionModified();
    void rotateToNewDirection();

    virtual Real getSpeed() const { return 50.f; };
    bool is180Turn();
    Ogre::Real distanciaXZ(Block* b);
};

