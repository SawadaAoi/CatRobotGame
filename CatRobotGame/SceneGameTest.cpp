#include "CameraManager.h"
#include "ComponentCameraBase.h"
#include "ComponentCollisionAABB.h"
#include "ComponentCollisionOBB.h"
#include "ComponentCollisionSphere.h"
#include "ComponentGeometry.h"
#include "ComponentModelAnime.h"
#include "ComponentTransform.h"
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
#include "SceneGameTest.h"
#include "SceneManager.h"
#include "UIComponentSprite.h"
#include "UIComponentText.h"
#include "UIComponentTransform.h"

void SceneGameTest::InitLocal()
{
	//FileManager::StageUIOutput("Assets/Save/TestUI.ui");

	AddSceneObject<ObjectLightDirectional>("LightDirectional");
	m_pPlayer = AddSceneObject<ObjectPlayer>("Player");

	AddSceneObject<ObjectCameraPlayer>("PlayerCamera");

	FileManager::UIInput("Assets/Save/GameUI/PlayerHP.ui");


	AddSceneObject<ObjectCameraDebug>("ObjectCameraDebug");

	m_pPlayer->GetComponent<ComponentTransform>()->SetLocalPosition(Vector3(0.0f, 3.0f, 5.0f));

	m_StaticPlane = AddSceneObject<ObjectGround>("Ground");
	m_StaticPlane->GetComponent<ComponentTransform>()->SetLocalPosition(Vector3(0.0f, 0.0f, 0.0f));
	m_StaticPlane->GetComponent<ComponentTransform>()->SetLocalScale(Vector3(100.0f, 1.0f, 100.0f));


	ObjectBase* pBlock = AddSceneObject<ObjectBlock>("Block1");
	pBlock->SetTag(E_ObjectTag::Enemy);
}

void SceneGameTest::UninitLocal()
{
}

void SceneGameTest::UpdateLocal()
{

}
