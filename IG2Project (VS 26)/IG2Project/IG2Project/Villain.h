#pragma once
#include "Character.h"

class Villain : public Character
{
public:

    Villain(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, String mesh);
    void update(Laberinto* lab, Real dt) override;

    virtual Real getSpeed() const override { return 30.f; }
};

class RotatingPart : public IG2Object {
public:
    RotatingPart(Vector3 pos, SceneNode* node, SceneManager* sm,
        String mesh, int count, Real radius, Real itemScale,
        Real degPerSec, int intervalMs) : IG2Object(pos, node, sm), speed(degPerSec), intervalMs(intervalMs)
    {
        for (int i = 0; i < count; ++i) {
            Real angle = Ogre::Math::TWO_PI * i / count;
            Vector3 offset(radius * std::cos(angle), 0, radius * std::sin(angle));

            auto item = std::make_unique<IG2Object>(offset, mNode->createChildSceneNode(), sm, mesh);
            item->setScale(Vector3(itemScale, itemScale, itemScale));
            items.push_back(std::move(item));
        }
    }
    void update(Real dt) {
        if (timer.getMilliseconds() >= intervalMs) {
            timer.reset();
            speed = -speed;
        }
        rotate(Quaternion(Radian(Degree(speed * dt)), Vector3::UNIT_Y));
    }

private:
    std::vector<std::unique_ptr<IG2Object>> items;
    Ogre::Timer timer;
    Real speed;       // grados/s, con signo
    int intervalMs;
};

class SpecialVillain : public Villain
{
public:
    SpecialVillain(Vector3 initPos, SceneNode* node, SceneManager* sceneMng) : Villain(initPos, node, sceneMng, "robot.mesh"),
        partA(Vector3(0, 20, 0), mNode->createChildSceneNode(), sceneMng,
            "ninja.mesh", 5, 30, 0.5f, 90.f, 2000),
        partB(Vector3(0, 40, 0), mNode->createChildSceneNode(), sceneMng,
            "fish.mesh", 5, 50, 4.f, -60.f, 1500)
    {}

    void update(Laberinto* lab, Real dt) override {
        Villain::update(lab, dt);
        partA.update(dt);
        partB.update(dt);
    }

private:
    RotatingPart partA, partB;
};