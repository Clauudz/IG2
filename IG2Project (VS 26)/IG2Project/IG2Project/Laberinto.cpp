#include "Laberinto.h"
#include "Block.h"

Laberinto::Laberinto(Vector3 initPos, SceneNode* node, SceneManager* sceneMng) : IG2Object(initPos, node, sceneMng)
{

}

void Laberinto::createLabyrinth(std::string stageFileName)
{
	stageFile.open(stageFileName);

	// Read the number of files and columns
	int numRows, numCols;

	stageFile >> numRows;
	stageFile >> numCols;

	int iRow = 0;
	bool ok = true;
	while (iRow < numRows && ok) {
		int iCol = 0;
		while (iCol < numCols && ok) {
			char cell;
			stageFile >> cell;
			// Inserts an empty block!
			if (cell == EMPTY_BLOCK) {
				//block = new Block(. . .);
				//labyrinth->addBlock(block);
			}
			// Wall block
			else if (cell == WALL_BLOCK) {
				Block *block = new Block(Vector3 (iRow * BLOCK_SIZE,0, iCol * BLOCK_SIZE), mNode->createChildSceneNode(), mSM);
				blocks.push_back(block);

				block->setScale(
					Vector3(
						BLOCK_SIZE/block->calculateBoxSize().x,
						BLOCK_SIZE/block->calculateBoxSize().y,
						BLOCK_SIZE/block->calculateBoxSize().z
					)
				);
			}
			// Wrong type of block
			else {
				ok = false;
			}
			iCol++;
		}
		iRow++;
	}

	Vector3 labSize(numRows * BLOCK_SIZE, 0, numCols * BLOCK_SIZE);
	mNode->setPosition(mNode->getPosition() - labSize/2);

	stageFile.close();
}

void Laberinto::moveCharacter(Character* character, Ogre::Real time)
{
	Block* charBlock, *inFrontBlock;

	// Get the block where the character is placed, and the next one
	charBlock = this->getBlock(character->getPosition());
	inFrontBlock = this->getBlock((character->getGridOrientation() * BLOCK_SIZE) + character->getPosition());
	// Character does not change its direction -> step forward!
	if (!character->isDirectionModified())
		stepForward(character, . . ., time);
	// New direction
	else {
		// Check the block in front of the character for the new direction
		Block* newDirBlock = this->getBlock(character->getPosition() + (character->getNexDirVector() * BLOCK_SIZE));
		// New position of the character after moving... (for checking if the center of the block is reached)
		Vector3 charNewPos = character->getPosition() + (character->getGridOrientation() * character->getSpeed() * time);
		Vector3 difference = Vector3(charNewPos.x - charBlock->getPosition().x, 0, charNewPos.z - charBlock->getPosition().z);
		// Check if the character can rotate for a new VALID direction
		if (newDirBlock->canPassThrough() && blockCenterReached(difference, character->getGridOrientation()))
			character->rotateToNewDirection();
		// 180 turn?
		else if (character->is180Turn())
			character->rotateToNewDirection();
		// Rotation cannot be performed... check if character can step forward
		else
			stepForward(character, . . ., time);
	}
}

Block* Laberinto::getBlock(Vector3 position)
{
	
}
