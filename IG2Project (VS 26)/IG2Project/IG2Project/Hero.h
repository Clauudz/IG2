#pragma once
#include "Character.h"

class Hero : public Character
{
private:
	int vida;
	int puntos;
public:
	Hero(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, String mesh, int v);

	void quitaVida();
	bool estaVivo();
	void addPuntos(int p);

	int getPuntos() { return puntos; }
	int getVidas() { return vida; }

	void respawn();
};

