/* ========================================
	CatRobotGame/
	------------------------------------
	�V�[��(�X�e�[�W3)�pcpp
	------------------------------------
	SceneStage3.cpp
========================================== */

// =============== �C���N���[�h ===================
#include "SceneStage3.h"

#include "ObjectPlayer.h"
#include "ObjectPlayerStart.h"
#include "ObjectCameraPlayer.h"

#include "FileManager.h"

#include "ComponentTransform.h"
#include "ObjectGameStateManager.h"


/* ========================================
	�������֐�
	-------------------------------------
	���e�F����������
======================================= */
void SceneStage3::InitLocal()
{
	FileManager::StageObjectInput("Assets/Save/Stage/Stage3.stg");

	static_cast<ObjectPlayerStart*>(GetSceneObjectTag(E_ObjectTag::PlayerStart))->SetIsPlayerStart(true);
	

	AddSceneObject<ObjectCameraPlayer>("PlayerCamera");

	FileManager::UIInput("Assets/Save/UI/GameScene.ui");


	AddSceneObject<ObjectGameStateManager>("GameStateManager");
}
