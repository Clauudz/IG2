#pragma once

#include "IG2Object.h"

class AnimacionInicial : public IG2Object
{
private:

	//objetos, entidades y nodos
	IG2Object* floor = nullptr;
	SceneNode* sinbadNode = nullptr;
	Entity* sinbadEnt = nullptr;
	Entity* swordL = nullptr;
	Entity* swordR = nullptr;
	SceneNode* lightNode = nullptr;
	Light* light = nullptr;

	//anims
	AnimationState* nodeAnim = nullptr; // la del nodo en bucle
	AnimationState* runBase = nullptr;  // del esqueleto
	AnimationState* runTop = nullptr;
	AnimationState* dance = nullptr;

	//metodos
	void createFloor();
	void createSinbad();
	void createLight();
	//void createNodeAnimation();
	//void addKeyframe(NodeAnimationTrack* track, Real time, const Quaternion& rot, const Vector3& pos);

	//actualizacion por frame
	//void updateSkeletalAnimations(Real dt);
	//void updateSwords();
public:
	AnimacionInicial(Vector3 initPos, SceneNode* node, SceneManager* sceneMng);
	~AnimacionInicial();

	//void update(Real dt); //lo llama IG2Project en cada frame
};

