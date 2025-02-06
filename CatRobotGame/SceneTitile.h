/* ========================================
	CatRobotGame/
	------------------------------------
	�V�[��(�^�C�g�����)�p�w�b�_
	------------------------------------
	�����F�^�C�g����ʂ̃V�[���N���X
	------------------------------------
	SceneTitile.h
========================================== */
#pragma once

// =============== �C���N���[�h ===================
#include "SceneBase.h"

// =============== �O���錾 ===================
class ObjectCamera;
class UIObjectText;
class ObjectGround;
class ComponentGeometry;
class ComponentSmokeEffect;

// =============== �N���X��` ===================
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

	// �J����
	std::vector<ObjectCamera*> m_pCameras;	
	int		m_nCameraSwitchNum;		// 0�`3
	float	m_fCameraSwitchTime;

	int m_nSelectNum;	// �I��ԍ�
	float m_fTextAnimeCnt;	// �e�L�X�g�A�j���[�V�����J�E���g


	std::vector<Function> m_MenuFunctions;
};

