/* ========================================
	CatRobotGame/
	------------------------------------
	�V�[��(�^�C�g�����)�pcpp
	------------------------------------
	SceneTitile.cpp
========================================== */

// =============== �C���N���[�h ===================
#include "SceneTitile.h"

#include "ObjectBase.h"
#include "ObjectCamera.h"
#include "ObjectGround.h"
#include "ObjectLightDirectional.h"
#include "ObjectSkyBox.h"
#include "ComponentGeometry.h"
#include "ComponentModelAnime.h"
#include "ComponentTransform.h"
#include "ComponentSmokeEffect.h"

#include "UIObjectBase.h"
#include "UIObjectText.h"
#include "UIComponentSprite.h"
#include "UIComponentText.h"
#include "UIComponentTransform.h"

#include "CameraManager.h"
#include "ModelAnimeManager.h"
#include "TextureManager.h"
#include "SceneManager.h"
#include "SoundManager.h"

#include <vector>
#include "Input.h"

// =============== �萔 ===================
// �^�C�g�����S
const Vector2<float>	TITLE_LOGO_POS		= Vector2<float>(-150.0f, 100.0f);
const Vector2<float>	TITLE_LOGO_SCALE	= Vector2<float>(780.0f, 600.0f);

// �I�����j���[�e�L�X�g
const int 				SELECT_MENU_NUM = 2;					// �I�����j���[��
const float				TEXT_SIZE		= 60.0f;				// �e�L�X�g�T�C�Y
const FontType			TEXT_FONT		= FontType::Letrogo;	// �t�H���g
const float				TEXT_ANIME_SPEED = 5.0f;				// �e�L�X�g�A�j���[�V�������x
const float				TEXT_ANIME_RANGE = 0.2f;				// �e�L�X�g�A�j���[�V�����͈�(0.8�`1.2)
// ���W
const Vector2<float> SELECT_MENU_POS[SELECT_MENU_NUM] = {
	Vector2<float>(0.0f, -150.0f),
	Vector2<float>(0.0f, -250.0f),
};
// �e�L�X�g
const std::string SELECT_MENU_TEXT[SELECT_MENU_NUM] = {
	"�X�^�[�g",
	"��߂�",
};



// �L���{���f��
const Vector3<float>	CAT_ROBO_POS = Vector3<float>(0.0f, -1.0f, 0.0f);
const Vector3<float>	CAT_ROBO_SCALE = Vector3<float>(3.0f, 3.0f, 3.0f);
const float				CAT_ROBO_ROT_Y = 180.0f;
// �n��
const Vector3<float>	GROUND_POS = Vector3<float>(0.0f, -1.0f, 0.0f);
const Vector3<float>	GROUND_SCALE = Vector3<float>(200.0f, 1.0f, 200.0f);
const float				MOVE_UV_SPEED = -50.0f;
// �X�J�C�{�b�N�X
const float				SKY_BOX_SCALE_Y = 0.5f;

// �J����
const int				CAMERA_NUM			= 4;	// �J������
const float				CAMERA_SWITCH_TIME	= 10.0f;	// �J�����؂�ւ�����
// ���W
const Vector3<float> CAMERA_POS[CAMERA_NUM] = {
	Vector3<float>(-5.0f, 1.0f, -15.0f),	// ����
	Vector3<float>(20.0f, 0.0f, -5.0f),		// �E
	Vector3<float>(9.0f, 16.0f, 6.0f),		// ��
	Vector3<float>(3.0f, 1.0f, 11.0f),		// ���
};

// ��]
const Vector3<float> CAMERA_ROT_X[CAMERA_NUM] = {
	Vector3<float>(-5.0f, -8.0f, 0.0f),		// ����
	Vector3<float>(180.0f, 80.0f, -180.0f),	// �E
	Vector3<float>(-110.0f, 1.0f, 180.0f),	// ��
	Vector3<float>(175.0f, -15.0f, 180.0f),	// ���
};

/* ========================================
	�R���X�g���N�^�֐�
	-------------------------------------
	���e�F������
=========================================== */
SceneTitile::SceneTitile()
	: m_pTitleLogo(nullptr)
	, m_pCatRoboModel(nullptr)
	, m_pSmokeEffect(nullptr)
	, m_pGround(nullptr)
	, m_pCompGeometry(nullptr)
	, m_pSkyBox(nullptr)
	, m_nCameraSwitchNum(0)
	, m_fCameraSwitchTime(0.0f)
	, m_nSelectNum(0)
	, m_fTextAnimeCnt(0.0f)
{
}

/* ========================================
	�������֐�
	-------------------------------------
	���e�F����������
========================================== */
void SceneTitile::InitLocal()
{
	InitUI();
	Init3dOjbect();

	// �J����(4�̎��_)
	for (int i = 0; i < CAMERA_NUM; i++)
	{
		ObjectCamera* pCamera = AddSceneObject<ObjectCamera>("Camera_" + std::to_string(i));
		pCamera->GetTransform()->SetPosition(CAMERA_POS[i]);
		pCamera->GetTransform()->Rotate(CAMERA_ROT_X[i].x, CAMERA_ROT_X[i].y, CAMERA_ROT_X[i].z);
		m_pCameras.push_back(pCamera);
	}

	AddSceneObject<ObjectLightDirectional>("Light");

	m_MenuFunctions.push_back(&SceneTitile::FuncStart);
	m_MenuFunctions.push_back(&SceneTitile::FuncEnd);


	m_pSmokeEffect->SetMoveDir(Vector3<float>(0.0f, 0.0f, -1.0f));
	m_pSmokeEffect->SetCreatePosDist({ 2.0f, 0.5f, 2.0f });
	m_pSmokeEffect->SetScale(0.5f, 1.0f);
	m_pSmokeEffect->SetPosAdjust(-0.5f, 0.5f);

	//PLAY_BGM(BGM_KEY::BGM_TITLE);
}

/* ========================================
	�X�V�֐�
	-------------------------------------
	���e�F�X�V����
========================================== */
void SceneTitile::UpdateLocal()
{
	// �n�ʂ̃e�N�X�`���X�N���[��
	Vector2<float> vUvOffset = m_pCompGeometry->GetUvOffset();
	vUvOffset.y += MOVE_UV_SPEED * DELTA_TIME;
	m_pCompGeometry->SetUvOffset(vUvOffset);

	// ���Ԋu�ŃJ�����؂�ւ�
	m_fCameraSwitchTime += DELTA_TIME;
	if (m_fCameraSwitchTime > CAMERA_SWITCH_TIME)
	{
		m_fCameraSwitchTime = 0.0f;										// �^�C�}�[���Z�b�g
		m_nCameraSwitchNum	= (m_nCameraSwitchNum + 1) % CAMERA_NUM;	// �ő�l�𒴂�����0�ɖ߂�
		CAMERA_MNG_INST.SwitchCamera(m_pCameras[m_nCameraSwitchNum]);	// �J�����؂�ւ�
	}

	// �I���X�V
	UpdateSelect();

}


/* ========================================
	UI�������֐�
	-------------------------------------
	���e�FUI�̏���������
========================================== */
void SceneTitile::InitUI()
{
	m_pTitleLogo = AddSceneUI<UIObjectBase>("TitleLogo");
	m_pTitleLogo->GetComponent<UIComponentSprite>()->SetTexture(GET_TEXTURE_DATA(TEX_KEY::UI_TITLE_LOGO));
	m_pTitleLogo->GetTransform()->SetLocalPosition(TITLE_LOGO_POS);
	m_pTitleLogo->GetTransform()->SetLocalScale(TITLE_LOGO_SCALE);

	for (int i = 0; i < SELECT_MENU_NUM; i++)
	{
		UIObjectText* pText = AddSceneUI<UIObjectText>("SelectMenu_" + std::to_string(i));
		pText->GetTransform()->SetLocalPosition(SELECT_MENU_POS[i]);
		pText->SetText(SELECT_MENU_TEXT[i]);
		pText->GetCompText()->SetFontSize(TEXT_SIZE);
		pText->GetCompText()->SetFontType(TEXT_FONT);

		m_pSelectMenu.push_back(pText);
	}
}

/* ========================================
	3D�I�u�W�F�N�g�������֐�
	-------------------------------------
	���e�F3D�I�u�W�F�N�g�̏���������
========================================== */
void SceneTitile::Init3dOjbect()
{
	// �L���{���f��
	m_pCatRoboModel = AddSceneObject<ObjectBase>("CatRoboModel");
	ComponentModelAnime* pCompAnime = m_pCatRoboModel->AddComponent<ComponentModelAnime>();
	pCompAnime->SetModel(GET_MODEL_ANIME(ANIME_BASE_KEY::AB_PLAYER));
	pCompAnime->PlayAnime(ANIME_KEY_PLAYER::PLYR_WALK, true, 1.0f);
	m_pCatRoboModel->GetTransform()->SetPosition(CAT_ROBO_POS);
	m_pCatRoboModel->GetTransform()->SetScale(CAT_ROBO_SCALE);
	m_pCatRoboModel->GetTransform()->RotateY(CAT_ROBO_ROT_Y);
	// ���G�t�F�N�g
	m_pSmokeEffect = m_pCatRoboModel->AddComponent<ComponentSmokeEffect>();
	m_pSmokeEffect->SetCreatePosDist({ 1.0f, 1.0f, 1.0f });
	m_pSmokeEffect->SetCreateInterval(0.01f);
	m_pSmokeEffect->SetLifeTime(0.3f);
	m_pSmokeEffect->SetScale(0.5f, 2.0f);

	// ��
	m_pSkyBox = AddSceneObject<ObjectSkyBox>("SkyBox");
	m_pSkyBox->GetTransform()->ScaleY(SKY_BOX_SCALE_Y);	// �c�ɒׂ�(�_�������₷������)
	// �n��
	m_pGround = AddSceneObject<ObjectGround>("Ground");
	m_pGround->GetTransform()->SetPosition(GROUND_POS);
	m_pGround->GetTransform()->SetScale(GROUND_SCALE);
	m_pCompGeometry = m_pGround->GetComponent<ComponentGeometry>();
	m_pCompGeometry->SetTexture(GET_TEXTURE_DATA(TEX_KEY::BLOCK_GRASS_TOP));
	m_pCompGeometry->SetIsTex(true);
	m_pCompGeometry->SetUvScale({ 100.0f, 100.0f });
}

/* ========================================
	�I���X�V�֐�
	-------------------------------------
	���e�F�I������
========================================== */
void SceneTitile::UpdateSelect()
{
	int nOldSelectNum = m_nSelectNum;

	if (Input::IsKeyTrigger(VK_UP))
	{
		m_nSelectNum = (m_nSelectNum + SELECT_MENU_NUM - 1) % SELECT_MENU_NUM;
	}
	else if (Input::IsKeyTrigger(VK_DOWN))
	{
		m_nSelectNum = (m_nSelectNum + 1) % SELECT_MENU_NUM;
	}

	if (nOldSelectNum != m_nSelectNum)
	{
		m_fTextAnimeCnt = 0.0f;
		m_pSelectMenu[nOldSelectNum]->GetCompText()->SetFontSize(TEXT_SIZE);
	}

	SelectMenuAnim();	// �I�����j���[�A�j��

	// �X�y�[�X�L�[�őI��
	if (Input::IsKeyTrigger('K'))
	{
		(this->*m_MenuFunctions[m_nSelectNum])();
	}
}

/* ========================================
	�I�����j���[�A�j���֐�
	-------------------------------------
	���e�F�I�𒆂̃��j���[�̃A�j���[�V��������(�g�k)
========================================== */
void SceneTitile::SelectMenuAnim()
{
	// �I�𒆂̃��j���[�̃e�L�X�g���g�k������
	m_fTextAnimeCnt += DELTA_TIME;
	float fScale = 1.0f + sinf(m_fTextAnimeCnt * TEXT_ANIME_SPEED) * TEXT_ANIME_RANGE;

	m_pSelectMenu[m_nSelectNum]->GetCompText()->SetFontSize(TEXT_SIZE * fScale);
}

/* ========================================
	���j���[�I��(�X�^�[�g)�֐�
	-------------------------------------
	���e�F�X�^�[�g���j���[�I�����̏���
========================================== */
void SceneTitile::FuncStart()
{
	// �V�[���J��
	SceneManager::ChangeScene("SceneStageSelect");
}

/* ========================================
	���j���[�I��(�I��)�֐�
	-------------------------------------
	���e�F�I�����j���[�I�����̏���
========================================== */
void SceneTitile::FuncEnd()
{
	PostQuitMessage(0);	// �Q�[���I��
}
