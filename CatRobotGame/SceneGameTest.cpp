#include "SceneGameTest.h"
#include "ObjectPlayer.h"
#include "ObjectGround.h"

#include "Input.h"

#include "ComponentTransform.h"
#include "CameraManager.h"
#include "ComponentCameraBase.h"
#include "ComponentGeometry.h"
#include "ComponentCollisionAABB.h"
#include "ComponentCollisionSphere.h"
#include "ComponentCollisionOBB.h"
#include "SceneManager.h"
#include "UIComponentTransform.h"
#include "UIComponentSprite.h"
#include "UIComponentText.h"

#include "ComponentModelAnime.h"
#include "ModelAnimeManager.h"

#include "FileManager.h"

#include "ObjectBlock.h"
#include "ObjectLight.h"
#include "ObjectLightDirectional.h"
#include "ObjectLightPoint.h"
#include "ObjectLightSpot.h"

void SceneGameTest::InitLocal()
{
	AddSceneObject<ObjectLightDirectional>("LightDirectional");
	AddSceneObject<ObjectLightSpot>("ObjectLightSpot");

	m_pPlayer = AddSceneObject<ObjectPlayer>("Player");
	m_pPlayer->GetComponent<ComponentTransform>()->SetLocalPosition(Vector3(-2.0f, 3.0f, 0.0f));

	m_StaticPlane = AddSceneObject<ObjectGround>("Ground");
	m_StaticPlane->GetComponent<ComponentTransform>()->SetLocalPosition(Vector3(0.0f, 0.0f, 0.0f));
	m_StaticPlane->GetComponent<ComponentTransform>()->SetLocalScale(Vector3(100.0f, 1.0f, 100.0f));


}

void SceneGameTest::UninitLocal()
{
	//FileManager::StageUIOutput("Assets/Save/TestUI.ui");
}

void SceneGameTest::UpdateLocal()
{

}
