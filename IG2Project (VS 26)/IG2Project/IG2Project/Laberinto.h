#pragma once

#include "IG2Object.h"

#include <string>
#include <fstream>

class SpecialVillain;
class Character;
class Villain;
class Hero;
class Block;
class Laberinto : public IG2Object
{
private:
	std::ifstream stageFile;

	int numRows, numCols;

	vector<Block*> blocks;

	bool fin;

public:
	Laberinto(Vector3 initPos, SceneNode* node, SceneManager* sceneMng);

	void createLabyrinth(std::string stageFileName);
	void moveCharacter(Character* character, Ogre::Real time);

	Block* getBlock(Vector3 position);
	void stepForward(Character* c, Block* act, Block* sig, Ogre::Real time);
	bool blockCenterReached(Ogre::Vector3 difference, Ogre::Vector3 direction);
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	void frameRendered(const Ogre::FrameEvent& evt) override;

	Hero* getHero() { return sinbad; }

	Hero* sinbad = nullptr;
	Ogre::SceneNode* mSinbadNode = nullptr;

	vector<Villain*> vils;
};

