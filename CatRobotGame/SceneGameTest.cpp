/* ========================================
	CatRobotGame/
	------------------------------------
	�V�[��(�e�X�g)�pcpp
	------------------------------------
	SceneGameTest.cpp
========================================== */

// =============== �C���N���[�h ===================
#include "SceneGameTest.h"
#include "ObjectPlayerStart.h"
#include "FileManager.h"
#include "ObjectBlockGroundOBB.h"
#include "ComponentTransform.h"
#include "ObjectCoinGroupCircle.h"

#include "UIObjectPlayerCoin.h"

/* ========================================
	�������֐�
	-------------------------------------
	���e�F����������
======================================= */
void SceneGameTest::InitLocal()
{
	FileManager::StageObjectInput("Assets/Save/Stage/TestScene.stg");
	FileManager::UIInput("Assets/Save/UI/GameScene.ui");

	static_cast<ObjectPlayerStart*>(GetSceneObjectTag(E_ObjectTag::PlayerStart))->SetIsPlayerStart(true);

	
	AddSceneObject<ObjectCoinGroupCircle>("ObjectCoinGroupCircle")->GetTransform()->SetPosition(Vector3<float>(3.0f, 1.0f, -5.0f));

	
}

