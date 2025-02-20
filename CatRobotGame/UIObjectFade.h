/* ========================================
	DX22Base/
	------------------------------------
	UIオブジェクト(フェード)用ヘッダ
	------------------------------------
	説明：シーン切り替え時のフェードイン・アウトを行う
	------------------------------------
	UIObjectFade.h
========================================== */
#pragma once

// =============== インクルード ===================
#include "UIObjectBase.h"

// =============== 定数定義 =======================
#define FADE_MODE_NONE UIObjectFade::E_FadeType::FADE_NONE
#define FADE_MODE_IN UIObjectFade::E_FadeType::FADE_IN
#define FADE_MODE_OUT UIObjectFade::E_FadeType::FADE_OUT

// =============== クラス ===================
class UIObjectFade :
    public UIObjectBase
{
public:
	enum E_FadeType
	{
		FADE_NONE,
		FADE_IN,
		FADE_OUT,
	};

public:
	UIObjectFade(SceneBase* pScene);
	void InitLocal() override;
	void UpdateLocal() override;

	virtual void StartFade(E_FadeType eFadeType, float fFadeTime);

	// ゲッター
	E_FadeType GetFadeType();
private:
	void FadeIn();
	void FadeOut();
protected:
	E_FadeType	m_eFadeType;
	float		m_fFadeTime;
	float		m_fRatio;

};

