#include "Character.h"

Character::Character(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, String mesh) : IG2Object(initPos, node, sceneMng, mesh)
{
}

Ogre::Vector3 Character::getNexDirVector()
{
    Vector3 newDirVector = Vector3::ZERO;
    if (nextDir == RIGHT)
        newDirVector = Vector3::UNIT_X;
    else if (nextDir == LEFT)
        newDirVector = Vector3::NEGATIVE_UNIT_X;
    else if (nextDir == DOWN)
        newDirVector = Vector3::UNIT_Z;
    else if (nextDir == UP)
        newDirVector = Vector3::NEGATIVE_UNIT_Z;

    return newDirVector;
}

bool Character::isDirectionModified()
{
    return getGridOrientation() != getNexDirVector();
}

Ogre::Quaternion Character::getQuaternionForNewDirection()
{
    Vector3 newDirVector = getNexDirVector();
    Quaternion q = getOrientation().getRotationTo(newDirVector);
    return q;
}

void Character::rotateToNewDirection()
{
    this->rotate(getQuaternionForNewDirection());
}

bool Character::is180Turn()
{
    return false;
}

void Character::setNextDirection(Direction dir)
{
    nextDir = dir;
}

