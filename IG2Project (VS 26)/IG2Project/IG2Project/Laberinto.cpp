#include "Laberinto.h"
#include "Block.h"
#include "Character.h"
#include "Hero.h"
#include "Villain.h"
#include "Config.h"

Laberinto::Laberinto(Vector3 initPos, SceneNode* node, SceneManager* sceneMng) : IG2Object(initPos, node, sceneMng), fin(false)
{
}

void Laberinto::createLabyrinth(std::string stageFileName)
{
	stageFile.open(stageFileName);

	// Read the number of files and columns

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
			if (cell == Config::EMPTY_BLOCK) {
				EmptyBlock* empBlock = new EmptyBlock(Vector3(iRow * Config::BLOCK_SIZE, 0, iCol * Config::BLOCK_SIZE), mNode->createChildSceneNode(), mSM);
				blocks.push_back(empBlock);	

				empBlock->move(Vector3(0, empBlock->calculateBoxSize().y / 2 + 1, 0));
			}
			// Wall block
			else if (cell == Config::WALL_BLOCK) {
				WallBlock *block = new WallBlock(Vector3 (iRow * Config::BLOCK_SIZE,0, iCol * Config::BLOCK_SIZE), mNode->createChildSceneNode(), mSM);
				blocks.push_back(block);

				block->setScale(
					Vector3(
						Config::BLOCK_SIZE/block->calculateBoxSize().x,
						Config::BLOCK_SIZE/block->calculateBoxSize().y,
						Config::BLOCK_SIZE/block->calculateBoxSize().z
					)
				);
				block->move(Vector3(0, block->calculateBoxSize().y / 2 + 1, 0));
			}
			else if (cell == Config::SINBAD_CHAR) {
				EmptyBlock* empBlock = new EmptyBlock(Vector3(iRow * Config::BLOCK_SIZE, 0, iCol * Config::BLOCK_SIZE), mNode->createChildSceneNode(), mSM);
				blocks.push_back(empBlock);

				empBlock->move(Vector3(0, empBlock->calculateBoxSize().y / 2 + 1, 0));

				mSinbadNode = mNode->createChildSceneNode("nSinbad");
				sinbad = new Hero(empBlock->getPosition(),
					mSinbadNode,
					mSM,
					"Sinbad.mesh", 3); // 3 vidas

				mSinbadNode->showBoundingBox(true);
				//sinbad->setScale(Ogre::Vector3(4.0, 4.0, 4.0));
				sinbad->move(Vector3(0, sinbad->calculateBoxSize().y / 2 + 1, 0));
				sinbad->setInitialPosition(sinbad->getPosition());
			}
			else if (cell == Config::VILLAIN_CHAR) {
				EmptyBlock* empBlock = new EmptyBlock(Vector3(iRow * Config::BLOCK_SIZE, 0, iCol * Config::BLOCK_SIZE), mNode->createChildSceneNode(), mSM);
				blocks.push_back(empBlock);

				empBlock->move(Vector3(0, empBlock->calculateBoxSize().y / 2 + 1, 0));

				Ogre::SceneNode* mVilNode = mNode->createChildSceneNode();
				Villain* v = new Villain(empBlock->getPosition(),
					mVilNode,
					mSM,
					"ogrehead.mesh");

				vils.push_back(v);

				mVilNode->showBoundingBox(true);
				//v->setScale(Ogre::Vector3(0.5, 0.5, 0.5));
				v->move(Vector3(0, v->calculateBoxSize().y / 2 + 1, 0));
			}
			else if (cell == Config::INVISIBLE_BLOCK) {
				InvisibleBlock* iBlock = new InvisibleBlock(Vector3(iRow * Config::BLOCK_SIZE, 0, iCol * Config::BLOCK_SIZE), mNode->createChildSceneNode(), mSM);
				blocks.push_back(iBlock);

				iBlock->setScale(
					Vector3(
						Config::BLOCK_SIZE / iBlock->calculateBoxSize().x,
						Config::BLOCK_SIZE / iBlock->calculateBoxSize().y,
						Config::BLOCK_SIZE / iBlock->calculateBoxSize().z
					)
				);
				iBlock->move(Vector3(0, iBlock->calculateBoxSize().y / 2 + 1, 0));
			}
			else if (cell == Config::FAKE_BLOCK) {
				FakeBlock* fBlock = new FakeBlock(Vector3(iRow * Config::BLOCK_SIZE, 0, iCol * Config::BLOCK_SIZE), mNode->createChildSceneNode(), mSM);
				blocks.push_back(fBlock);

				fBlock->setScale(
					Vector3(
						Config::BLOCK_SIZE / fBlock->calculateBoxSize().x,
						Config::BLOCK_SIZE / fBlock->calculateBoxSize().y,
						Config::BLOCK_SIZE / fBlock->calculateBoxSize().z
					)
				);
				fBlock->move(Vector3(0, fBlock->calculateBoxSize().y / 2 + 1, 0));
			}
			else if (cell == Config::BREAKABLE_BLOCK) {
				BreakableBlock* bBlock = new BreakableBlock(Vector3(iRow * Config::BLOCK_SIZE, 0, iCol * Config::BLOCK_SIZE), mNode->createChildSceneNode(), mSM);
				blocks.push_back(bBlock);

				bBlock->setScale(
					Vector3(
						Config::BLOCK_SIZE / bBlock->calculateBoxSize().x,
						Config::BLOCK_SIZE / bBlock->calculateBoxSize().y,
						Config::BLOCK_SIZE / bBlock->calculateBoxSize().z
					)
				);
				bBlock->move(Vector3(0, bBlock->calculateBoxSize().y / 2 + 1, 0));
			}
			// Wrong type of block
			else {
				ok = false;
			}
			iCol++;
		}
		iRow++;
	}

	Vector3 labSize(numRows * Config::BLOCK_SIZE, 0, numCols * Config::BLOCK_SIZE);
	mNode->setPosition(mNode->getPosition() - labSize/2);

	stageFile.close();
}

void Laberinto::moveCharacter(Character* character, Ogre::Real time)
{
	Block* charBlock, *inFrontBlock;

	// Get the block where the character is placed, and the next one
	charBlock = getBlock(character->getPosition());
	inFrontBlock = getBlock((character->getGridOrientation() * Config::BLOCK_SIZE / 2.f) + character->getPosition());
	/*// Character does not change its direction -> step forward!
	if (!character->isDirectionModified())*/
	stepForward(character, charBlock, inFrontBlock, time);
	// New direction


	//character->getPosition().distance(charBlock->getPosition())
	//180?
	if (character->is180Turn())
		character->rotateToNewDirection();
	else if (character->isDirectionModified() &&
		character->distanciaXZ(charBlock) < character->getSpeed() * time) {
		Block* wantedBlock = getBlock(charBlock->getPosition() + character->getNexDirVector() * Config::BLOCK_SIZE);

		if (wantedBlock->canPassThrough()) {
			character->rotateToNewDirection();
		}
	}

	/*else {
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
			stepForward(character, charBlock, inFrontBlock, time);
	}*/
}

Block* Laberinto::getBlock(Vector3 position)
{
	Vector3 fromFirstPosLabToPos = Vector3(position.x - blocks[0]->getPosition().x, 0, position.z - blocks[0]->getPosition().z);

	int iRow, iCol;

	iRow = std::round(fromFirstPosLabToPos.x / Config::BLOCK_SIZE);
	iCol = std::round(fromFirstPosLabToPos.z / Config::BLOCK_SIZE);

	int idx = iRow * numCols + iCol;

	return blocks[idx];
}

void Laberinto::stepForward(Character* c, Block* act, Block* sig, Ogre::Real time)
{
	if (sig->canPassThrough()) {
		c->move(c->getGridOrientation() * c->getSpeed() * time);
	}
	else {
		Vector3 p = act->getPosition();
		c->setPosition({p.x, c->getPosition().y, p.z});
	}
}

bool Laberinto::blockCenterReached(Ogre::Vector3 difference, Ogre::Vector3 direction)
{
	const Ogre::Real EPSILON = 0.01f;

	Ogre::Real componente = (direction.x != 0.f) ? std::abs(difference.x) : std::abs(difference.z);

	return componente >= EPSILON;
}

bool Laberinto::keyPressed(const OgreBites::KeyboardEvent& evt) {
	if (evt.keysym.sym == SDLK_UP) {
		cout << "Pressed UP" << endl;
		sinbad->setNextDirection(Character::UP);
	}
	else if (evt.keysym.sym == SDLK_DOWN) {
		cout << "Pressed DOWN" << endl;
		sinbad->setNextDirection(Character::DOWN);
	}
	else if (evt.keysym.sym == SDLK_LEFT) {
		cout << "Pressed LEFT" << endl;
		sinbad->setNextDirection(Character::LEFT);
	}
	else if (evt.keysym.sym == SDLK_RIGHT) {
		cout << "Pressed RIGHT" << endl;
		sinbad->setNextDirection(Character::RIGHT);
	}

	return true;
}

void Laberinto::frameRendered(const Ogre::FrameEvent& evt)
{
	if (fin) return;

	for (Block* b : blocks)
		b->update(evt.timeSinceLastFrame);

	moveCharacter(sinbad, evt.timeSinceLastFrame);
	for (Villain* v : vils) {
		v->update(this, evt.timeSinceLastFrame);
		moveCharacter(v, evt.timeSinceLastFrame);
	}

	for (Villain* v : vils) {
		if (sinbad->getAABB().intersects(v->getAABB())) {
			sinbad->quitaVida();
			if (sinbad->estaVivo()) {
				sinbad->respawn();
			}
			else {
				fin = true;
				cout << "FIN" << endl;
			}
			return;
		}
	}
}
