/* ========================================
	CatRobotGame/
	------------------------------------
	UIオブジェクト(プレイヤー所持コイン)用ヘッダ
	------------------------------------
	説明：プレイヤーの所持コインを表示するUIオブジェクト
	------------------------------------
	UIObjectPlayerCoin.h
========================================== */
#pragma once

// =============== インクルード =====================
#include "UIObjectBase.h"

// =============== 前方宣言 =====================
class UIObjectText;
class ObjectPlayer;

// =============== クラス定義 =====================
class UIObjectPlayerCoin :
    public UIObjectBase
{
public:
	UIObjectPlayerCoin(SceneBase* pScene);
	void InitLocal() override;
	void UpdateLocal() override;

	DEFINE_UI_OBJECT_TYPE(UIObjectPlayerCoin)
private:
	UIObjectBase*	m_pBG;			// 背景
	UIObjectBase*	m_pCoinIcon;	// コインアイコン
	UIObjectText*	m_pTextCoin;	// コイン数テキスト
	ObjectPlayer*	m_pPlayer;
};

