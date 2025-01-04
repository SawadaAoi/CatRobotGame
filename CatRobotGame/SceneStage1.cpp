#include "SceneStage1.h"

#include "ObjectPlayer.h"
#include "ObjectCameraPlayer.h"

#include "FileManager.h"

#include "ComponentTransform.h"
#include "ObjectGameStateManager.h"

void SceneStage1::InitLocal()
{
	FileManager::StageObjectInput("Assets/Save/Stage/Stage1_Test.stg");

	ObjectPlayer* pPlayer = AddSceneObject<ObjectPlayer>("Player");
	pPlayer->GetTransform()->SetLocalPosition(Vector3(12.5f, 1.0f, -12.5f));

	AddSceneObject<ObjectCameraPlayer>("PlayerCamera");

	FileManager::UIInput("Assets/Save/GameUI/PlayerHP.ui");


	AddSceneObject<ObjectGameStateManager>("GameStateManager");
}
