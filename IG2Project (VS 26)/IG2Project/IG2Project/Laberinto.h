#pragma once

#include "IG2Object.h"
#include "Character.h"

#include <string>
#include <fstream>

class Block;
class Laberinto : public IG2Object
{
private:
	std::ifstream stageFile;

	int numRows, numCols;

	vector<Block*> blocks;

	const char WALL_BLOCK = 'x';
	const char EMPTY_BLOCK = 'o';
	const int BLOCK_SIZE = 30;
public:
	Laberinto(Vector3 initPos, SceneNode* node, SceneManager* sceneMng);
	void createLabyrinth(std::string stageFileName);
	void moveCharacter(Character* character, Ogre::Real time);

	Block* getBlock(Vector3 position);
	void stepForward(Character* c, ... , Ogre::Real time);
	bool blockCenterReached(Ogre::Vector3 difference, Ogre::Vector3 direction);
};

