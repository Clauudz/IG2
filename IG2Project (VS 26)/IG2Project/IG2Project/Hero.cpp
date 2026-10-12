#include "Hero.h"

Hero::Hero(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, String mesh, int v) : Character(initPos, node, sceneMng, mesh),
	vida(v), puntos(0)
{
	mNode->setScale(Ogre::Vector3(4.0, 4.0, 4.0));
}

void Hero::quitaVida() {
	vida--;
}

bool Hero::estaVivo() {
	return vida > 0;
}

void Hero::addPuntos(int p) {
	puntos += p;
}

void Hero::respawn() {
	setPosition(initialPosition);
}