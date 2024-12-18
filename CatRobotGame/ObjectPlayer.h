/* ========================================
	DX22Base/
	------------------------------------
	オブジェクト(プレイヤー)用ヘッダ
	------------------------------------
	説明：プレイヤー用
	------------------------------------
	ObjectPlayer.h
========================================== */
#pragma once

// =============== インクルード =====================
#include "ObjectBase.h"
#include <memory>


class ComponentTransform;
class ComponentGroundRaycast;
class ComponentRigidbody;
class ComponentModelAnime;
class ComponentPlayerController;

// =============== クラス定義 =====================
class ObjectPlayer :
    public ObjectBase
{
public:
	ObjectPlayer(SceneBase* pScene);
	void InitLocal();
	void UpdateLocal();
	void DrawLocal();

	// ゲッター
	DEFINE_OBJECT_TYPE(ObjectPlayer)	// オブジェクトの種類ID取得関数

private:
	ComponentGroundRaycast* m_pCompGroundRaycast;
	ComponentRigidbody* m_pCompRigidbody;
	ComponentModelAnime* m_pCompModelAnime;
	ComponentPlayerController* m_pCompPlayerController;
};

