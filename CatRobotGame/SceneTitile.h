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
#include <functional>

// =============== �O���錾 ===================
class ObjectCamera;
class UIObjectText;
class ObjectGround;
class ComponentGeometry;
class ComponentSmokeEffect;
class UIObjectSelectMenu;

// =============== �N���X��` ===================
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

	// ���j���[�֐�
	void FuncStart();
	void FuncEnd();

	DEFINE_SCENE_TYPE(SceneTitile)
private:
	// UI
	UIObjectBase*				m_pTitleLogo;

	// 3D�I�u�W�F�N�g
	ObjectBase*				m_pCatRoboModel;
	ComponentSmokeEffect*	m_pSmokeEffect;

	ObjectGround*		m_pGround;
	ComponentGeometry*	m_pCompGeometry;

	ObjectBase*			m_pSkyBox;

	// �J����
	std::vector<ObjectCamera*> m_pCameras;	
	int		m_nCameraSwitchNum;		// 0�`3
	float	m_fCameraSwitchTime;

	UIObjectSelectMenu* m_pSelectMenuUI;
};

