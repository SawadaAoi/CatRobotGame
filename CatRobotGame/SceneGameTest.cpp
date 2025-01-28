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
}

