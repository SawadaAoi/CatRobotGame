#include "CameraManager.h"
#include "ComponentCameraBase.h"
#include "ComponentCollisionAABB.h"
#include "ComponentCollisionOBB.h"
#include "ComponentCollisionSphere.h"
#include "ComponentGeometry.h"
#include "ComponentModelAnime.h"
#include "ComponentTransform.h"
#include "ComponentGroundBox.h"
#include "FileManager.h"
#include "Input.h"
#include "ModelAnimeManager.h"
#include "ObjectBlock.h"
#include "ObjectBullet.h"
#include "ObjectCameraDebug.h"
#include "ObjectCameraPlayer.h"
#include "ObjectGround.h"
#include "ObjectLight.h"
#include "ObjectLightDirectional.h"
#include "ObjectLightPoint.h"
#include "ObjectLightSpot.h"
#include "ObjectPlayer.h"
#include "ObjectEnemy.h"
#include "ObjectEnemyLinear.h"
#include "ObjectEnemyChase.h"
#include "ObjectEnemyRandom.h"
#include "ObjectGoal.h"
#include "ObjectGameStateManager.h"
#include "ObjectSkyBox.h"
#include "SceneGameTest.h"
#include "SceneManager.h"
#include "UIComponentSprite.h"
#include "UIComponentText.h"
#include "UIComponentTransform.h"

void SceneGameTest::InitLocal()
{
	//FileManager::UIOutput("Assets/Save/TestUI.ui");

	AddSceneObject<ObjectSkyBox>("SkyBox");

	AddSceneObject<ObjectLightDirectional>("LightDirectional");
	GetSceneObject<ObjectLightDirectional>("LightDirectional")->GetTransform()->SetLocalRotationEuler(Vector3(110.0f, 0.0f, 0.0f));

	m_pPlayer = AddSceneObject<ObjectPlayer>("Player");

	AddSceneObject<ObjectCameraPlayer>("PlayerCamera");

	FileManager::UIInput("Assets/Save/GameUI/PlayerHP.ui");


	AddSceneObject<ObjectCameraDebug>("ObjectCameraDebug");

	m_pPlayer->GetComponent<ComponentTransform>()->SetLocalPosition(Vector3(0.0f, 3.0f, 5.0f));

	m_StaticPlane = AddSceneObject<ObjectGround>("Ground");
	m_StaticPlane->GetComponent<ComponentTransform>()->SetLocalPosition(Vector3(0.0f, 0.0f, 0.0f));
	m_StaticPlane->GetComponent<ComponentTransform>()->SetLocalScale(Vector3(100.0f, 1.0f, 100.0f));


	AddSceneObject<ObjectEnemyLinear>("ObjectEnemy")->GetTransform()->SetLocalPosition(Vector3(0.0f, 1.0f, 0.0f));
	//AddSceneObject<ObjectEnemyChase>("ObjectEnemyChase")->GetTransform()->SetLocalPosition(Vector3(0.0f, 1.0f, 0.0f));

	AddSceneObject<ObjectGoal>("ObjectGoal")->GetTransform()->SetLocalPosition(Vector3(0.0f, 1.0f, 10.0f));

	AddSceneObject<ObjectGameStateManager>("GameStateManager");

	AddSceneObject<ObjectBlock>("Block1")->GetTransform()->SetLocalPosition(Vector3(5.0f, 0.5f, 5.0f));
	GetSceneObject<ObjectBlock>("Block1")->GetTransform()->SetLocalScale(Vector3(5.0f, 1.0f, 5.0f));

	GetSceneObject<ObjectBlock>("Block1")->AddComponent<ComponentGroundBox>();
	GetSceneObject<ObjectBlock>("Block1")->SetTag(E_ObjectTag::Ground);

	AddSceneObject<ObjectBlock>("Block2")->GetTransform()->SetLocalPosition(Vector3(0.0f, 0.5f, -6.0f));
	AddSceneObject<ObjectBlock>("Block3")->GetTransform()->SetLocalPosition(Vector3(0.0f, 0.5f, -5.0f));
}

void SceneGameTest::UninitLocal()
{
}

void SceneGameTest::UpdateLocal()
{

}
