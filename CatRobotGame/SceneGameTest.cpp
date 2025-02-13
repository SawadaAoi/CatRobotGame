/* ========================================
	CatRobotGame/
	------------------------------------
	シーン(テスト)用cpp
	------------------------------------
	SceneGameTest.cpp
========================================== */

// =============== インクルード ===================
#include "SceneGameTest.h"
#include "ObjectPlayerStart.h"
#include "FileManager.h"
#include "ObjectBlockGroundOBB.h"
#include "ComponentTransform.h"
#include "ObjectCoin.h"

/* ========================================
	初期化関数
	-------------------------------------
	内容：初期化処理
======================================= */
void SceneGameTest::InitLocal()
{
	FileManager::StageObjectInput("Assets/Save/Stage/TestScene.stg");
	FileManager::UIInput("Assets/Save/GameUI/PlayerHP.ui");

	static_cast<ObjectPlayerStart*>(GetSceneObjectTag(E_ObjectTag::PlayerStart))->SetIsPlayerStart(true);

	
	AddSceneObject<ObjectCoin>("ObjectCoin")->GetTransform()->SetPosition(Vector3<float>(3.0f, 4.0f, 0.0f));
}

