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

// =============== 前方宣言 ===================
class ObjectCamera;
class UIObjectText;
class ObjectGround;
class ComponentGeometry;
class ComponentSmokeEffect;

// =============== クラス定義 ===================
class SceneTitile :
    public SceneBase
{
public:
	using Function = void(SceneTitile::*)();
public:
	SceneTitile();
	void InitLocal() override;
	void UpdateLocal() override;

private:
	void InitUI();
	void Init3dOjbect();
	void UpdateSelect();
	void SelectMenuAnim();

	void FuncStart();
	void FuncEnd();
private:
	UIObjectBase* m_pTitleLogo;
	std::vector<UIObjectText*> m_pSelectMenu;

	ObjectBase* m_pCatRoboModel;
	ComponentSmokeEffect* m_pSmokeEffect;

	ObjectGround*		m_pGround;
	ComponentGeometry*	m_pCompGeometry;
	ObjectBase*			m_pSkyBox;

	// カメラ
	std::vector<ObjectCamera*> m_pCameras;	
	int		m_nCameraSwitchNum;		// 0～3
	float	m_fCameraSwitchTime;

	int m_nSelectNum;	// 選択番号
	float m_fTextAnimeCnt;	// テキストアニメーションカウント


	std::vector<Function> m_MenuFunctions;
};

