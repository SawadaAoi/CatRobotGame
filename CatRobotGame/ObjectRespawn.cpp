/* ========================================
	CatRobotGame/
	------------------------------------
	リスポーン用cpp
	------------------------------------
	ObjectRespawn.cpp
========================================== */

// =============== インクルード ===================
#include "ObjectRespawn.h"
#include "ObjectPlayer.h"
#include "SceneBase.h"
#include "SceneManager.h"
#include "ComponentTransform.h"
#include "ComponentCollisionAABB.h"


/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：初期化
	-------------------------------------
	引数：所有シーン
=========================================== */
ObjectRespawn::ObjectRespawn(SceneBase* pScene)
	: ObjectBase(pScene)
	, m_RespawnType(E_RespawnType::RT_RELOAD_SCENE)
	, m_RespawnPosition(Vector3<float>(0.0f, 0.0f, 0.0f))
	, m_pCompColAABB(nullptr)
	, m_IsReloadScene(false)
{
}

/* ========================================
	初期化関数
	-------------------------------------
	内容：初期化
=========================================== */
void ObjectRespawn::InitLocal()
{
	// 当たり判定設定
	m_pCompColAABB = AddComponent<ComponentCollisionAABB>();
	m_pCompColAABB->SetTrigger(true);
	m_pCompColAABB->SetDynamic(false);

}

/* ========================================
	更新関数
	-------------------------------------
	内容：更新
=========================================== */
void ObjectRespawn::UpdateLocal()
{
	// シーンを再読み込み
	if (m_IsReloadScene)	SceneManager::ReloadScene();
}

/* ========================================
	衝突判定(開始時)関数
	-------------------------------------
	内容：他オブジェクトとの衝突判定(開始時)
	-------------------------------------
	引数：衝突相手オブジェクト
=========================================== */
void ObjectRespawn::OnCollisionEnter(ObjectBase* pHit)
{
	// プレイヤーと当たった場合
	if (pHit->GetTag() == E_ObjectTag::Player)
	{
		// リスポーン種類によって処理を変える
		switch (m_RespawnType)
		{
		// シーンを再読み込み
		case E_RespawnType::RT_RELOAD_SCENE:
			// 当たり判定処理内でシーン再読み込み行うと、自身の所有シーンが破棄されるため、
			// フラグを立ててUpdate処理で再読み込みする
			m_IsReloadScene = true;
			break;
		// 決まった位置からリスポーン
		case E_RespawnType::RT_POSITION:	
			pHit->GetTransform()->SetLocalPosition(m_RespawnPosition);
			break;
		}
	}
}

/* ========================================
	ゲッター(リスポーン種類)関数
	-------------------------------------
	戻値：リスポーン種類
=========================================== */
ObjectRespawn::E_RespawnType ObjectRespawn::GetRespawnType() const
{
	return m_RespawnType;
}


/* ========================================
	ゲッター(リスポーン位置)関数
	-------------------------------------
	戻値：リスポーン位置
=========================================== */
Vector3<float> ObjectRespawn::GetRespawnPosition() const
{
	return m_RespawnPosition;
}

/* ========================================
	セッター(リスポーン種類)関数
	-------------------------------------
	引数：リスポーン種類
=========================================== */
void ObjectRespawn::SetRespawnType(E_RespawnType type)
{
	m_RespawnType = type;
}

/* ========================================
	セッター(リスポーン位置)関数
	-------------------------------------
	引数：リスポーン位置
=========================================== */
void ObjectRespawn::SetRespawnPosition(const Vector3<float>& pos)
{
	m_RespawnPosition = pos;
}