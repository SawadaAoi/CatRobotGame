/* ========================================
	DX22Base/
	------------------------------------
	UIコンポーネント(拡縮エフェクト)用ヘッダ
	------------------------------------
	説明：文字を拡縮するエフェクト
	------------------------------------
	UIComponentEffectScale.h
========================================== */
#pragma once

// =============== インクルード ===================
#include "UIComponentBase.h"

// =============== クラス =======================
class UIComponentText;


// =============== クラス =======================
class UIComponentEffectScale :
    public UIComponentBase
{
public:
	UIComponentEffectScale(UIObjectBase* pOwner);
	virtual void Init() override;
	virtual void Update() override;

	// ゲッター
	bool GetOnEffect();

	// セッター
	void SetOnEffect(bool bOnEffect);
	void SetBaseFontSize(float fBaseFontSize);

#ifdef _DEBUG
	void Debug(DebugUI::Window& window) override;
#endif // _DEBUG

	DEFINE_UI_COMPONENT_TYPE
private:
	UIComponentText* m_pCompText;	// テキストコンポーネント

	bool m_bOnEffect;				// エフェクトON/OFF

	float m_fBaseFontSize;			// 基本のフォントサイズ

	float m_fAnimCnt;				// アニメーションカウント
	float m_fAnimSpeed;				// アニメーション速度
	float m_fAnimRange;				// アニメーション範囲
};

