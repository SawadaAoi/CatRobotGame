/* ========================================
	DX22Base/
	------------------------------------
	コンポーネント用cpp
	------------------------------------
	ComponentBase.cpp
========================================== */

// =============== インクルード =====================
#include "ComponentBase.h"
#include <windows.h>
#include "ObjectBase.h"	// オブジェクト基底クラス

/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：初期化
	-------------------------------------
	引数1: 所有者オブジェクト
	引数2: 更新順序
=========================================== */
ComponentBase::ComponentBase(ObjectBase* pOwner, int nOrder)
	: m_pOwnerObj(pOwner)
	, m_nUpdateOrder(nOrder)
	, m_bActive(true)
{
	// 所有者オブジェクトがnullptrの場合はエラーを出力
	if (pOwner == nullptr)
	{
		OutputDebugStringA("ComponentBase::ComponentBase() : 所有者オブジェクトがnullptrです。\n");
	}

	// 子オブジェクトのコンストラクタでは引数に更新順序を持たせず、
	// コンポーネントごとに固定値として更新順序を設定する
}

/* ========================================
	初期化関数
	-------------------------------------
	内容：初期化処理
=========================================== */
void ComponentBase::Init()
{
	// 必要に応じて派生クラスでオーバーライドする
}

/* ========================================
	終了関数
	-------------------------------------
	内容：終了処理
=========================================== */
void ComponentBase::Uninit()
{
	// 必要に応じて派生クラスでオーバーライドする
}

/* ========================================
	更新関数
	-------------------------------------
	内容：更新処理
=========================================== */
void ComponentBase::Update()
{
	// 必要に応じて派生クラスでオーバーライドする
}

/* ========================================
	描画関数
	-------------------------------------
	内容：描画処理
=========================================== */
void ComponentBase::Draw()
{
	// 必要に応じて派生クラスでオーバーライドする
}

/* ========================================
	ゲッター(所有者オブジェクト)関数
	-------------------------------------
	戻値：所有者オブジェクト
=========================================== */
ObjectBase* ComponentBase::GetOwnerObject()
{
	return m_pOwnerObj;
}

/* ========================================
	ゲッター(更新順序)関数
	-------------------------------------
	戻値：更新順序
=========================================== */
int ComponentBase::GetUpdateOrder()
{
	return m_nUpdateOrder;
}

/* ========================================
	ゲッター(アクティブフラグ)関数
	-------------------------------------
	戻値：アクティブフラグ
=========================================== */
bool ComponentBase::GetActive()
{
	return m_bActive;
}

/* ========================================
	ゲッター(コンポーネントID)関数
	-------------------------------------
	戻値：コンポーネントID
=========================================== */
size_t ComponentBase::GetTypeID() const
{
	return 0;	// コンポーネントの親クラスではIDを持たない
}

/* ========================================
	ゲッター(コンポーネントID)関数(静的関数)
	-------------------------------------
	戻値：コンポーネントID
=========================================== */
size_t ComponentBase::GetStaticTypeID()
{
	return reinterpret_cast<size_t>(&GetStaticTypeID);
}

/* ========================================
	セッター(アクティブフラグ)関数
	-------------------------------------
	引数：アクティブフラグ
=========================================== */
void ComponentBase::SetActive(bool bActive)
{
	m_bActive = bActive;
}

