#pragma once

#include "IG2Object.h"

class Character: public IG2Object
{
private:
    Ogre::Quaternion getQuaternionForNewDirection();

public:

    enum Direction { RIGHT, LEFT, UP, DOWN };
    Direction nextDir = RIGHT;

    void setNextDirection(Direction dir);

    static constexpr float SPEED = 50.f;

    Character(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, String mesh);

    Ogre::Vector3 getNexDirVector();
    bool isDirectionModified();
    void rotateToNewDirection();

    float getSpeed() { return SPEED; };
    bool is180Turn();
};

