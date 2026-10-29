#include "AnimacionInicial.h"

AnimacionInicial::AnimacionInicial(Vector3 initPos, SceneNode* node, SceneManager* sceneMng) : IG2Object(initPos, node, sceneMng)
{
	createFloor();
	createSinbad();
	createLight();
}

AnimacionInicial::~AnimacionInicial()
{
	if (swordL->isAttached()) swordL->detachFromParent();
	if (swordR->isAttached()) swordR->detachFromParent();

	mSM->destroyEntity(swordL);
	mSM->destroyEntity(swordR);
	mSM->destroyEntity(sinbadEnt);
	mSM->destroySceneNode(sinbadNode);
	mSM->destroyLight(light);
	mSM->destroySceneNode(lightNode);

	delete floor;


}

void AnimacionInicial::createFloor()
{
	MeshManager::getSingleton().createPlane("floor2", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Plane(Vector3::UNIT_Y, 0),
		300.f, 150.f, 50, 50, true, 1, 10, 5,
		Vector3::UNIT_Z);

	floor = new IG2Object({0,0,0}, mNode->createChildSceneNode(), mSM, "floor2");
	floor->setMaterialName("example/stonesFloor");
}

void AnimacionInicial::createSinbad()
{
	sinbadNode = mNode->createChildSceneNode();
	sinbadEnt = mSM->createEntity("Sinbad.mesh");
	sinbadNode->attachObject(sinbadEnt);
	
	sinbadNode->setPosition(0.f, 20.f, 0.f);
	sinbadNode->setScale(4.f, 4.f, 4.f);

	swordL = mSM->createEntity("Sword.mesh");
	swordR = mSM->createEntity("Sword.mesh");
}

void AnimacionInicial::createLight()
{
	light = mSM->createLight("luzInicial");
	lightNode = mNode->createChildSceneNode();
	lightNode->attachObject(light);

	light->setType(Ogre::Light::LT_DIRECTIONAL);
	lightNode->setDirection({ -1, -1, -1 });

	light->setDiffuseColour(0.75, 0.75, 0.75);
	light->setSpecularColour(0.5, 0.5, 0.5);
}
