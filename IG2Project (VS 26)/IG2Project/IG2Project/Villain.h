#pragma once
#include "Character.h"

class Villain : public Character
{
public:

    Villain(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, String mesh);
    void update(Laberinto* lab, Real dt) override;

    virtual Real getSpeed() const override { return 30.f; }
};