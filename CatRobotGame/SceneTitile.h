/* ========================================
	CatRobotGame/
	------------------------------------
	シーン(タイトル画面)用ヘッダ
	------------------------------------
	説明：タイトル画面のシーンクラス
	------------------------------------
	SceneTitile.h
========================================== */
#pragma once

// =============== インクルード ===================
#include "SceneBase.h"
#include <functional>

// =============== 前方宣言 ===================
class ObjectCamera;
class UIObjectText;
class ObjectGround;
class ComponentGeometry;
class ComponentSmokeEffect;
class UIObjectSelectMenu;

// =============== クラス定義 ===================
class SceneTitile :
    public SceneBase
{
public:
	SceneTitile();
	void InitLocal() override;
	void UpdateLocal() override;

private:
	void InitUI();
	void Init3dOjbect();

	// メニュー関数
	void FuncStart();
	void FuncEnd();

	DEFINE_SCENE_TYPE(SceneTitile)
private:
	// UI
	UIObjectBase*				m_pTitleLogo;

	// 3Dオブジェクト
	ObjectBase*				m_pCatRoboModel;
	ComponentSmokeEffect*	m_pSmokeEffect;

	ObjectGround*		m_pGround;
	ComponentGeometry*	m_pCompGeometry;

	ObjectBase*			m_pSkyBox;

	// カメラ
	std::vector<ObjectCamera*> m_pCameras;	
	int		m_nCameraSwitchNum;		// 0～3
	float	m_fCameraSwitchTime;

	UIObjectSelectMenu* m_pSelectMenuUI;
};

