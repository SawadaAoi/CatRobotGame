/* ========================================
	CatRobotGame/
	------------------------------------
	UIオブジェクト(プレイヤーHP)用cpp
	------------------------------------
	UIObjectPlayerHP.cpp
========================================== */

// =============== インクルード =====================
#include "ObjectPlayer.h"
#include "SceneBase.h"
#include "TextureManager.h"
// コンポーネント
#include "UIComponentSprite.h"
#include "UIComponentTransform.h"
#include "UIObjectPlayerHP.h"

// =============== 定数定義 =======================
const Vector2<float> DEFAULT_SCALE = Vector2<float>(100.0f, 100.0f);

const std::string HEART_OBJECT_NAME			= "Heart_";
const Vector2<float> HEART_TEXTURE_RATIO	= Vector2<float>(140.0f, 100.0f);

/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：初期化
	-------------------------------------
	引数1：所有シーン
========================================== */
UIObjectPlayerHP::UIObjectPlayerHP(SceneBase* pScene)
	: UIObjectBase(pScene)
	, m_pPlayer(nullptr)
{
}


/* ========================================
	初期化関数
	-------------------------------------
	内容：初期化処理
========================================== */
void UIObjectPlayerHP::InitLocal()
{
	m_pPlayer = static_cast<ObjectPlayer*>(m_pOwnerScene->GetSceneObjectTag(E_ObjectTag::Player));

	m_pCompTransform->SetLocalScale(DEFAULT_SCALE);
	m_pCompSprite->SetIsVisible(false);

	int nHP = m_pPlayer->GetHp();		// TODO: プレイヤーのHPを取得する

	// HP数分のハートを生成
	for (int i = 0; i < nHP; i++)
	{
		UIObjectBase* pUIObject = m_pOwnerScene->AddSceneUI<UIObjectBase>(HEART_OBJECT_NAME + std::to_string(i));

		UIComponentTransform* pCompTrans = pUIObject->GetComponent<UIComponentTransform>();
		pCompTrans->SetLocalPosition(Vector2(i * DEFAULT_SCALE.x, 0.0f));
		pCompTrans->SetLocalScale(HEART_TEXTURE_RATIO);

		UIComponentSprite* pCompSprite = pUIObject->GetComponent<UIComponentSprite>();
		pCompSprite->SetTexture(GET_TEXTURE_DATA(TEX_KEY::PLAYER_HP));

		AddChildUI(pUIObject);
		m_pUIObjectHP.push_back(pUIObject);
	}

}


/* ========================================
	更新関数
	-------------------------------------
	内容：更新処理
========================================== */
void UIObjectPlayerHP::UpdateLocal()
{
	if (!m_pPlayer)
	{
		m_pPlayer = static_cast<ObjectPlayer*>(m_pOwnerScene->GetSceneObjectTag(E_ObjectTag::Player));
	}

	int nHP		= m_pPlayer->GetHp();		// TODO: プレイヤーのHPを取得する
	int nHPMax	= m_pPlayer->GetMaxHp();	// TODO: プレイヤーの最大HPを取得する

	// HPの表示数を更新
	for (int i = 0; i < nHPMax; i++)
	{
		m_pUIObjectHP[i]->GetComponent<UIComponentSprite>()->SetIsVisible(i < nHP);	
	}
}

