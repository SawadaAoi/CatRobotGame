/* ========================================
	DX22Base/
	------------------------------------
	UIオブジェクト(フェード(アイリスアウト))用ヘッダ
	------------------------------------
	説明：画面が円型、テクスチャ型でアイリスアウトする
	------------------------------------
	UIObjectFadeIrisOut
========================================== */
#pragma once

// =============== インクルード ===================
#include "UIObjectFade.h"

// =============== クラス ===================
class UIObjectFadeIrisOut :
    public UIObjectFade
{
public:
	enum E_IrisOutType
	{
		IRIS_OUT_CIRCLE,
		IRIS_OUT_TEXTURE,
	};
public:
	UIObjectFadeIrisOut(SceneBase* pScene);
	void InitLocal() override;
	void UpdateLocal() override;

	void StartFade(E_FadeType eFadeType, float fFadeTime) override;

	// セッター
	void SetIrisOutType(E_IrisOutType eIrisOutType);

private:
	void StartFadeIn();
	void StartFadeOut();
	void FadeIn();
	void FadeOut();
private:
	E_IrisOutType m_eIrisOutType;
};

