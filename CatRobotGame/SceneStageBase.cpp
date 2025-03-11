/* ========================================
	CatRobotGame/
	------------------------------------
	シーン(ステージ基底)用cpp
	------------------------------------
	SceneStageBase.cpp
========================================== */

// =============== インクルード ===================
#include "SceneStageBase.h"
#include "Input.h"
#include "ObjectPlayer.h"
#include "ObjectPlayerStart.h"
#include "ObjectCameraPlayer.h"
#include "ObjectGameStateManager.h"

#include "UIObjectPause.h"

#include "FileManager.h"

/* ========================================
	コンストラクタ
	-------------------------------------
	内容：コンストラクタ
========================================== */
SceneStageBase::SceneStageBase()
	: m_bPause(false)
	, m_pPauseUI(nullptr)
{
}

/* ========================================
	初期化関数
	-------------------------------------
	内容：初期化処理
========================================== */
void SceneStageBase::InitLocal()
{
	// プレイヤーの生成
	static_cast<ObjectPlayerStart*>(GetSceneObjectTag(E_ObjectTag::PlayerStart))->SetIsPlayerStart(true);

	// カメラプレイヤーを追加
	AddSceneObject<ObjectCameraPlayer>("PlayerCamera");

	// UI読み込み
	FileManager::UIInput("Assets/Save/UI/GameScene.ui");

	// ゲームステートマネージャを追加
	m_pGameStateManager = AddSceneObject<ObjectGameStateManager>("GameStateManager");
}

/* ========================================
	更新関数
	-------------------------------------
	内容：更新処理
========================================== */
void SceneStageBase::UpdateLocal()
{
	// 通常状態でない場合はポーズ処理を行わない
	if (m_pGameStateManager->GetGameState() != ObjectGameStateManager::GS_NORMAL) return;

	// ポーズ処理
	if (Input::IsKeyTrigger('P'))
	{
		if (m_bPause)
		{
			Resume();
			m_pPauseUI->Destroy();
		}
		else
		{
			Pause();
			m_pPauseUI = AddSceneUI<UIObjectPause>("PauseUI");
		}

		m_bPause = !m_bPause;
	}
}

/* ========================================
	ポーズ処理
	-------------------------------------
	内容：ポーズ処理
		　シーンに登録されているオブジェクトを全て停止(アクティブ状態を一時停止状態に変更)
========================================== */
void SceneStageBase::Pause()
{
	// 所持オブジェクト配列
	for (auto& pObject : m_pObjects)
	{
		if (pObject->GetState() == OBJ_DEAD) continue;
		pObject->SetState(OBJ_PAUSE);
	}

	// 一時保存オブジェクト配列
	for (auto& pObject : m_pStandbyObjects)
	{
		if (pObject->GetState() == OBJ_DEAD) continue;
		pObject->SetState(OBJ_PAUSE);
	}
}

/* ========================================
	ポーズ解除処理
	-------------------------------------
	内容：ポーズ解除処理
		　シーンに登録されているオブジェクトを全て再開(一時停止状態をアクティブ状態に変更)
========================================== */
void SceneStageBase::Resume()
{
	// 所持オブジェクト配列
	for (auto& pObject : m_pObjects)
	{
		if (pObject->GetState() == OBJ_DEAD) continue;
		pObject->SetState(OBJ_ACTIVE);
	}

	// 一時保存オブジェクト配列
	for (auto& pObject : m_pStandbyObjects)
	{
		if (pObject->GetState() == OBJ_DEAD) continue;
		pObject->SetState(OBJ_ACTIVE);
	}
}
