#include "SceneStage1.h"

#include "ObjectPlayer.h"
#include "ObjectCameraPlayer.h"

#include "FileManager.h"

#include "ComponentTransform.h"
#include "ObjectGameStateManager.h"

void SceneStage1::InitLocal()
{
	FileManager::StageObjectInput("Assets/Save/Stage/Stage1_0107.stg");

	ObjectPlayer* pPlayer = AddSceneObject<ObjectPlayer>("Player");
	pPlayer->GetTransform()->SetLocalPosition(Vector3(15.5f, 1.0f, -15.5f));

	AddSceneObject<ObjectCameraPlayer>("PlayerCamera");

	FileManager::UIInput("Assets/Save/GameUI/PlayerHP.ui");


	AddSceneObject<ObjectGameStateManager>("GameStateManager");
}
