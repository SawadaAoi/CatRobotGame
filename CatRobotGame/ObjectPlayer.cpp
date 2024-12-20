/* ========================================
	CatRobotGame/
	------------------------------------
	オブジェクト(プレイヤー)用cpp
	------------------------------------
	ObjectPlayer.cpp
========================================== */

// =============== インクルード =====================
#include "ObjectPlayer.h"


// コンポーネント
#include "ComponentTransform.h"
#include "ComponentRigidbody.h"
#include "ComponentCollisionOBB.h"
#include "ComponentPlayerController.h"
#include "ComponentGroundRaycast.h"
#include "ComponentModelAnime.h"


/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：初期化
	-------------------------------------
	引数1：所有シーンポインタ
=========================================== */
ObjectPlayer::ObjectPlayer(SceneBase* pScene)
	: ObjectBase(pScene)
	, m_pCompGroundRaycast(nullptr)
	, m_pCompRigidbody(nullptr)
	, m_pCompModelAnime(nullptr)
	, m_pCompPlayerController(nullptr)
{
	SetTag(E_ObjectTag::Player);	// タグの設定
}

/* ========================================
	初期化関数
	-------------------------------------
	内容：初期化処理
========================================= */
void ObjectPlayer::InitLocal()
{
	m_pCompTransform =GetComponent<ComponentTransform>();

	m_pCompGroundRaycast = AddComponent<ComponentGroundRaycast>();
	m_pCompGroundRaycast->SetStartPosOffset(Vector3<float>(0.0f, -0.4f, 0.0f));
	m_pCompGroundRaycast->SetRayLength(0.2f);

	AddComponent<ComponentCollisionOBB>();
	
	m_pCompRigidbody = AddComponent<ComponentRigidbody>();
	m_pCompRigidbody->SetUseGravity(true);
	m_pCompRigidbody->SetGroundDrag(0.9f);

	m_pCompPlayerController = AddComponent<ComponentPlayerController>();

	m_pCompModelAnime = AddComponent<ComponentModelAnime>();

}

/* ========================================
	更新関数
	-------------------------------------
	内容：更新処理
========================================= */
void ObjectPlayer::UpdateLocal()
{
	// 地面に設置している場合　かつ　ジャンプ中でない場合
	if (m_pCompGroundRaycast->GetHitFlg() && m_pCompRigidbody->GetVelocity().y <=0.0f)
	{
		Vector3<float> vPos = m_pCompTransform->GetWorldPosition();
		vPos.y = m_pCompGroundRaycast->GetHitPos().y + 0.5f;
		m_pCompTransform->SetLocalPosition(vPos);

		m_pCompPlayerController->SetUseJump(true);
	}
	else
	{
		m_pCompPlayerController->SetUseJump(false);
	}

}


