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

const Vector2<float> BG_SCALE		= { 400.0f, 85.0f };	// 背景スケール
const Vector2<float> BG_POSITION	= { 150.0f, 0.0f };		// 背景位置

const std::string		HEART_OBJECT_NAME = "Heart_";							// HPオブジェクト名
const Vector2<float>	HEART_TEXTURE_SCALE = Vector2<float>(100.0f, 100.0f);	// HPテクスチャのスケール
const float				HEART_TEXTURE_SPACE = 60.0f;							// HPテクスチャの間隔

/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：初期化
	-------------------------------------
	引数1：所有シーン
========================================== */
UIObjectPlayerHP::UIObjectPlayerHP(SceneBase* pScene)
	: UIObjectBase(pScene)
	, m_pBG(nullptr)
	, m_pPlayerIcon(nullptr)
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

	// 初期パラメータ設定
	m_pCompTransform->SetScale(DEFAULT_SCALE);
	m_pCompSprite->SetIsVisible(false);

	// 背景を設定
	m_pBG = m_pOwnerScene->AddSceneUI<UIObjectBase>("HPBG");
	m_pBG->GetComponent<UIComponentSprite>()->SetTexture(GET_TEXTURE_DATA(TEX_KEY::UI_FRAME_1));
	m_pBG->GetTransform()->SetScale(BG_SCALE);
	m_pBG->SetIsSave(false);

	AddChildUI(m_pBG);

	// プレイヤーアイコンを設定(一番左)
	m_pPlayerIcon = m_pOwnerScene->AddSceneUI<UIObjectBase>("0_PlayerIcon");
	m_pPlayerIcon->GetTransform()->SetScale(DEFAULT_SCALE);
	m_pPlayerIcon->GetComponent<UIComponentSprite>()->SetTexture(GET_TEXTURE_DATA(TEX_KEY::UI_PLAYER_ICON));
	m_pPlayerIcon->SetIsSave(false);
	AddChildUI(m_pPlayerIcon);

	m_pBG->GetTransform()->SetPosition(BG_POSITION);

	// プレイヤーが存在する場合はHPを生成
	if (m_pPlayer) CreateHP();
}


/* ========================================
	更新関数
	-------------------------------------
	内容：更新処理
========================================== */
void UIObjectPlayerHP::UpdateLocal()
{

	// プレイヤーが存在しない場合は取得する
	if (!m_pPlayer)
	{
		m_pPlayer = static_cast<ObjectPlayer*>(m_pOwnerScene->GetSceneObjectTag(E_ObjectTag::Player));
		if (m_pPlayer) CreateHP();		// プレイヤーが存在する場合はHPを生成

		return;
	}

	int nHP		= m_pPlayer->GetHp();		// TODO: プレイヤーのHPを取得する
	int nHPMax	= m_pPlayer->GetMaxHp();	// TODO: プレイヤーの最大HPを取得する

	// HPの表示数を更新
	for (int i = 0; i < nHPMax; i++)
	{
		m_pUIObjectHP[i]->GetComponent<UIComponentSprite>()->SetIsVisible(i < nHP);	
	}
}

/* ========================================
	HP生成関数
	-------------------------------------
	内容：HPを生成する
========================================== */
void UIObjectPlayerHP::CreateHP()
{
	int nHP = m_pPlayer->GetHp();		// TODO: プレイヤーのHPを取得する

	// HP数分のハートを生成
	for (int i = 1; i <= nHP; i++)
	{
		// ハートオブジェクトを生成(名前は"Heart_" + i)
		UIObjectBase* pUIObject = m_pOwnerScene->AddSceneUI<UIObjectBase>(HEART_OBJECT_NAME + std::to_string(i));

		pUIObject->SetIsSave(false);

		// トランスフォーム
		UIComponentTransform* pCompTrans = pUIObject->GetTransform();
		Vector2<float> vPos = GetTransform()->GetPosition() + Vector2<float>(i * HEART_TEXTURE_SPACE, 0.0f);
		pCompTrans->SetPosition(vPos);
		pCompTrans->SetScale(HEART_TEXTURE_SCALE);
		// スプライト
		UIComponentSprite* pCompSprite = pUIObject->GetComponent<UIComponentSprite>();
		pCompSprite->SetTexture(GET_TEXTURE_DATA(TEX_KEY::UI_HP_HEART));

		AddChildUI(pUIObject);
		m_pUIObjectHP.push_back(pUIObject);
	}
}

