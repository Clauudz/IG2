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
