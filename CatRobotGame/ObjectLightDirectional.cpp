/* ========================================
	DX22Base/
	------------------------------------
	ライトオブジェクト(方向ライト)用cpp
	------------------------------------
	ObjectLightDirectional.cpp
========================================== */

// =============== インクルード ===================
#include "ObjectLightDirectional.h"
#include "ComponentTransform.h"

// =============== 定数定義 =======================
const float DEFAULT_ROTATE_X = 70.0f;

/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：初期化
	-------------------------------------
	引数1：所有者オブジェクト
========================================== */
ObjectLightDirectional::ObjectLightDirectional(SceneBase* pScene)
	: ObjectLight(pScene)
{
}

/* ========================================
	初期化関数
	-------------------------------------
	内容：オブジェクトの初期化
========================================== */
void ObjectLightDirectional::InitLocal()
{
	// 親クラスの初期化関数を呼ぶ
	ObjectLight::InitLocal();

	// ライト種類を設定
	m_pCompLightBase->SetLightType(ComponentLightBase::E_LightType::DIRECTIONAL);

	// ライトの向きを設定
	m_pCompTransform->RotateX(DEFAULT_ROTATE_X);
}
