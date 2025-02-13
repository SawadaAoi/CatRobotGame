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
#include "ObjectCoin.h"

/* ========================================
	�������֐�
	-------------------------------------
	���e�F����������
======================================= */
void SceneGameTest::InitLocal()
{
	FileManager::StageObjectInput("Assets/Save/Stage/TestScene.stg");
	FileManager::UIInput("Assets/Save/GameUI/PlayerHP.ui");

	static_cast<ObjectPlayerStart*>(GetSceneObjectTag(E_ObjectTag::PlayerStart))->SetIsPlayerStart(true);

	
	AddSceneObject<ObjectCoin>("ObjectCoin")->GetTransform()->SetPosition(Vector3<float>(3.0f, 4.0f, 0.0f));
}

