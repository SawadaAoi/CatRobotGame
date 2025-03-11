/* ========================================
	CatRobotGame/
	------------------------------------
	�V�[��(�X�e�[�W�Z���N�g)�pcpp
	------------------------------------
	SceneStageSelect.cpp
========================================== */

// =============== �C���N���[�h ===================
#include "SceneStageSelect.h"

#include "SceneManager.h"
#include "FileManager.h"
#include "SoundManager.h"
#include "Input.h"

#include "UIObjectText.h"
#include "UIComponentText.h"
#include "UIComponentSprite.h"

#include "ObjectLightDirectional.h"
#include "ObjectCamera.h"
#include "ComponentTransform.h"


// =============== �萔 ===================
// �V�[�����A�V�[���ύX�֐��̃}�b�v
const std::vector<std::function<void()>> SCENE_CALL =
{
	[]() { SceneManager::ChangeScene("SceneStage1"); },
	[]() { SceneManager::ChangeScene("SceneStage2"); },
	[]() { SceneManager::ChangeScene("SceneStage3"); },
	[]() { SceneManager::ChangeScene("SceneStage4"); },
};

// �X�e�[�W��
const std::vector<std::string> SCENE_NAME =
{
	"�X�e�[�W�P",
	"�X�e�[�W�Q",
	"�X�e�[�W�R",
	"�X�e�[�W�S",
};


// �X�e�[�W���f���f�[�^
// �t�@�C���ۑ��ʒu
const std::string MODEL_DATA_PATH = "Assets/Save/StageSelect/";
// �t�@�C����
const std::vector<std::string> MODEL_DATA_NAME =
{
	"Stage1_Select.slc",
	"Stage2_Select.slc",
	"Stage3_Select.slc",
	"Stage4_Select.slc",
};

const int STAGE_NUM_MAX = SCENE_NAME.size();	// �X�e�[�W��

// �J�����ʒu
const Vector3<float> CAMERA_POS_ZOOMIN	= { 0.0f, 30.0f, -40.0f };
const Vector3<float> CAMERA_POS_ZOOMOUT = { 0.0f, 120.0f, -150.0f };
const float CAMERA_ROT_X = 40.0f;	// �J������]�p�x

// UV�X�N���[�����x
const float UV_SCROLL_SPEED = 0.1f;

/* ========================================
	�R���X�g���N�^
	-------------------------------------
	���e�F�R���X�g���N�^
========================================== */
SceneStageSelect::SceneStageSelect()
	: m_bChangeStageModel(false)
	, m_nSelectStageNum(0)
	, m_nSelectStageNumOld(-1)
	, m_pCamera(nullptr)
	, m_pStageName(nullptr)
	, m_pScreenName(nullptr)
	, m_pBG_Image(nullptr)
{
}

/* ========================================
	�������֐�
	-------------------------------------
	���e�F����������
========================================== */
void SceneStageSelect::InitLocal()
{
	AddSceneObject<ObjectLightDirectional>("Light");

	// �J�����ǉ�
	m_pCamera = AddSceneObject<ObjectCamera>("Camera");
	m_pCamera->GetTransform()->SetPosition(CAMERA_POS_ZOOMIN);
	m_pCamera->GetTransform()->RotateX(CAMERA_ROT_X);

	// UI�ǂݍ���
	FileManager::UIInput("Assets/Save/UI/StageSelect.ui");

	// �X�e�[�W���A��ʖ��擾
	m_pStageName = GetSceneUI<UIObjectText>("StageNameText");			
	m_pStageName->GetCompText()->SetFontType(FontType::Letrogo);
	m_pScreenName = GetSceneUI<UIObjectText>("ScreenNameText");

	// �w�i�摜�擾
	m_pBG_Image = GetSceneUI<UIObjectBase>("BG_Image");
	m_pBG_Image->SetIs3DObjBackDraw(true);

	// �X�e�[�W���f���ǂݍ���
	FileManager::StageObjectInput(MODEL_DATA_PATH + MODEL_DATA_NAME[m_nSelectStageNum]);

	SceneManager::SetFadeInKind(FADE_KIND_NORMAL);
	SceneManager::SetFadeTime(2.0f);

	PLAY_BGM(BGM_KEY::BGM_SELECT);

}


/* ========================================
	�X�V�֐�
	-------------------------------------
	���e�F�X�V����
========================================== */
void SceneStageSelect::UpdateLocal()
{
	// UV�X�N���[��
	Vector2<float> vUvPos = m_pBG_Image->GetSprite()->GetUvPos();
	vUvPos.x -= UV_SCROLL_SPEED * DELTA_TIME;
	vUvPos.y -= UV_SCROLL_SPEED * DELTA_TIME;
	m_pBG_Image->GetSprite()->SetUvPos(vUvPos);

	// �X�e�[�W���f�����ύX���Ȃ�
	if (m_bChangeStageModel) 
	{
		// �X�e�[�W���f�������S�ɍ폜���ꂽ��
		if (!GetSceneObjectTag(E_ObjectTag::StageSampleParent))
		{
			FileManager::StageObjectInput(MODEL_DATA_PATH + MODEL_DATA_NAME[m_nSelectStageNum]);	// �X�e�[�W���f����ǂݍ���

			m_pCamera->GetTransform()->MoveTo(CAMERA_POS_ZOOMIN, 0.3f);	// �J�����ʒu��ύX(���f�����g�傳���悤�Ɍ�����ʒu��)
			m_bChangeStageModel = false;
		}	
	}
	else
	{
		StageChangeInput();	// �X�e�[�W�ύX����

		// �X�e�[�W���ύX���ꂽ��
		if (m_nSelectStageNum != m_nSelectStageNumOld)
		{
			m_pStageName->SetText(SCENE_NAME[m_nSelectStageNum]);			// �X�e�[�W����ύX
			GetSceneObjectTag(E_ObjectTag::StageSampleParent)->Destroy();	// ���ݕ\������Ă���X�e�[�W���f�����폜
			m_pCamera->GetTransform()->SetPosition(CAMERA_POS_ZOOMOUT);			// �J�����ʒu��ύX(���f�����k�������悤�Ɍ�����ʒu��)

			m_bChangeStageModel = true;

		}
	}

	m_nSelectStageNumOld = m_nSelectStageNum;
}



/* ========================================
	�X�e�[�W�ύX���͊֐�
	-------------------------------------
	���e�F�X�e�[�W�ύX���͏���
========================================== */
void SceneStageSelect::StageChangeInput()
{
	if (Input::IsKeyTrigger(VK_LEFT))
	{
		m_nSelectStageNum = (m_nSelectStageNum + STAGE_NUM_MAX - 1) % STAGE_NUM_MAX;

		PLAY_SE(SE_KEY::SE_MENU_CURSOR);
	}
	else if (Input::IsKeyTrigger(VK_RIGHT))
	{
		m_nSelectStageNum = (m_nSelectStageNum + 1) % STAGE_NUM_MAX;
		PLAY_SE(SE_KEY::SE_MENU_CURSOR);
	}

	if (Input::IsKeyTrigger(VK_RETURN))
	{
		SceneManager::SetFadeOutKind(FADE_KIND_NORMAL);
		SCENE_CALL[m_nSelectStageNum]();

		PLAY_SE(SE_KEY::SE_MENU_DECIDE);
	}
}

