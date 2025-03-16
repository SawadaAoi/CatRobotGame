/* ========================================
	DX22Base/
	------------------------------------
	UI�I�u�W�F�N�g���pcpp
	------------------------------------
	UIObjectBase.cpp
========================================== */
#pragma once

// =============== �C���N���[�h =====================
#include "UIObjectBase.h"
#include "SceneBase.h"			// �V�[�����N���X
#include "UIComponentBase.h"	// UI�R���|�[�l���g���N���X
#include <windows.h>
#include "UIComponentTransform.h"
#include "UIComponentSprite.h"	
#include "SceneManager.h"
#include "TextureManager.h"

#include "UITypeRegistry.h"

/* ========================================
	�R���X�g���N�^�֐�
	-------------------------------------
	���e�F������
	-------------------------------------
	����1�F���L�V�[��
=========================================== */
UIObjectBase::UIObjectBase(SceneBase* pScene)
	: m_pOwnerScene(pScene)
	, m_pComponents()
	, m_pCompTransform(nullptr)
	, m_pCompSprite(nullptr)
	, m_sName("NoName")
	, m_eState(E_State::STATE_ACTIVE)
	, m_pParentUI(nullptr)
	, m_pChildUIs()
	, m_bIsFold(false)					// �I�u�W�F�N�g�ꗗ�܂肽���݃t���O��false�ɐݒ�
	, m_nDrawPriority(0)				// �`��D��x��0�ɐݒ�
	, m_bIsSave(true)					// �Z�[�u�t���O��true�ɐݒ�
	, m_bIs3DObjBackDraw(false)			// 3D�I�u�W�F�N�g���`��t���O��false�ɐݒ�
	, m_bIsDestroy(false)				// �I�u�W�F�N�g�j���t���O��false�ɐݒ�
	, m_fDestroyTime(0.0f)				// �j�����Ԃ�0�ɐݒ�
	, m_fDestroyTimeCnt(0.0f)			// �j�����ԃJ�E���g��0�ɐݒ�
{
	// ���L�V�[����nullptr�̏ꍇ�̓G���[���o��
	if (pScene == nullptr)
	{
		OutputDebugStringA("UIObjectBase::UIObjectBase() : ���L�V�[����nullptr�ł��B\n");
	}

}

/* ========================================
	�������֐�
	-------------------------------------
	���e�F����������
	-------------------------------------
	�����F�I�u�W�F�N�g��
=========================================== */
void UIObjectBase::Init(std::string sName)
{
	m_pComponents.clear();	// �R���|�[�l���g���X�g���N���A
	SetName(sName);			// �I�u�W�F�N�g����ݒ�
	InitDefaultComponent();	// �f�t�H���g�R���|�[�l���g��ǉ�

	InitLocal();			// �ʏ���������
}


/* ========================================
	�I���֐�
	-------------------------------------
	���e�F�I������
=========================================== */
void UIObjectBase::Uninit()
{
	// �����R���|�[�l���g�z��̑S�v�f���폜
	for (auto& pComponent : m_pComponents)
	{
		pComponent->Uninit();
		pComponent.reset();	// ���������

	}
	m_pComponents.clear();	// �N���A
	UninitLocal();	// �ʏI������
}

/* ========================================
	�X�V�֐�
	-------------------------------------
	���e�F�X�V����
=========================================== */
void UIObjectBase::Update()
{
	// �����R���|�[�l���g�z��̑S�v�f���X�V
	for (auto& pComponent : m_pComponents)
	{
		pComponent->Update();
	}
	UpdateLocal();	// �ʍX�V����

	// �q�I�u�W�F�N�g�̍X�V
	for (auto& pChild : m_pChildUIs)
	{
		if (pChild->GetState() == UI_DEAD)	continue;	// ���S��ԂłȂ��ꍇ�͍X�V���Ȃ�
		if (pChild->GetState() == UI_PAUSE) continue;	// �ꎞ��~��Ԃ̏ꍇ�͍X�V���Ȃ�
		pChild->Update();
	}

	if (m_bIsDestroy)
	{
		// �j�����Ԍo�߂Ŕj��
		m_fDestroyTimeCnt += DELTA_TIME;
		if (m_fDestroyTimeCnt >= m_fDestroyTime)
		{
			SetState(UI_DEAD);	// �폜�t���O�������Ă���ꍇ�͏�Ԃ����S�ɕύX
			DestroyChild();					// �q�I�u�W�F�N�g����Ԃ����S�ɕύX
		}
	}
}

/* ========================================
	�`��֐�
	-------------------------------------
	���e�F�`�揈��
=========================================== */
void UIObjectBase::Draw()
{
	// �����R���|�[�l���g�z��̑S�v�f��`��
	for (auto& pComponent : m_pComponents)
	{
		pComponent->Draw();
	}
	DrawLocal();	// �ʕ`�揈��

}

/* ========================================
	UI�폜�֐�
	-------------------------------------
	���e�FUI�ɍ폜�t���O�𗧂Ă�
		�@�����ڍ폜��Ԃɂ��Ȃ����R�́A�Փˏ�����ɍ폜���邽��
	-------------------------------------
	����1�F�폜����(���b��ɍ폜���邩)
		 �@���f�t�H���g��0�b
=========================================== */
void UIObjectBase::Destroy(float nTime)
{
	m_bIsDestroy = true;
	m_fDestroyTime = nTime;	// �ʏ�͑����폜
}

/* ========================================
	�e�I�u�W�F�N�g�ݒ�֐�
	-------------------------------------
	���e�F�e�I�u�W�F�N�g��ݒ肷��
	-------------------------------------
	����1�F�e�ɐݒ肷��I�u�W�F�N�g
=========================================== */
void UIObjectBase::SetParentUI(UIObjectBase* pParentObj)
{
	// ���ɐݒ肳��Ă���e�I�u�W�F�N�g���玩�g���폜
	if (m_pParentUI)
		m_pParentUI->RemoveChildUI(this);

	m_pParentUI = pParentObj;	// ���I�u�W�F�N�g�̍X�V

	// ���g�̃g�����X�t�H�[�����Čv�Z
	m_pCompTransform->RecalculateLocalTransform();

	// ���ɐe�I�u�W�F�N�g���X�V�ς݂��`�F�b�N
	// ���q�I�u�W�F�N�g�ǉ��֐�����Ăяo���ꂽ�ꍇ
	for (auto& pChild : m_pParentUI->m_pChildUIs)
	{
		if (pChild == this)	return;
	}

	m_pParentUI->AddChildUI(this);	// �e�I�u�W�F�N�g�̍X�V
}

/* ========================================
	�q�I�u�W�F�N�g�ǉ��֐�
	-------------------------------------
	���e�F�q�I�u�W�F�N�g��ǉ�����
	-------------------------------------
	����1�F�q�I�u�W�F�N�g�ɂ���I�u�W�F�N�g
=========================================== */
void UIObjectBase::AddChildUI(UIObjectBase* pChildObj)
{
	// ���Ɏq�I�u�W�F�N�g�ɓo�^����Ă���ꍇ�͒ǉ����Ȃ�
	for (auto& pChild : m_pChildUIs)
	{
		if (pChild == pChildObj)	return;
}
	m_pChildUIs.push_back(pChildObj);	// ���I�u�W�F�N�g�̍X�V

	// ���Ɏq�I�u�W�F�N�g���X�V�ς݂��`�F�b�N
	// ���e�I�u�W�F�N�g�ݒ�֐�����Ăяo���ꂽ�ꍇ
	if (pChildObj->GetParentUI() == this) return;

	pChildObj->SetParentUI(this);	// �q�I�u�W�F�N�g�̍X�V

}

/* ========================================
	�e�I�u�W�F�N�g�����֐�
	-------------------------------------
	���e�F�e�I�u�W�F�N�g����������
=========================================== */
void UIObjectBase::RemoveParentUI()
{
	// �e�I�u�W�F�N�g���Ȃ��ꍇ�͏������Ȃ�
	if (m_pParentUI == nullptr) return;

	m_pParentUI->RemoveChildUI(this);	// �e�I�u�W�F�N�g���玩�g���폜
	m_pParentUI = nullptr;					// �e�I�u�W�F�N�g����ɐݒ�

	// ���g��Transform�R���|�[�l���g�̐e��������
	this->GetComponent<UIComponentTransform>()->ClearParent();
}

/* ========================================
	�q�I�u�W�F�N�g�폜�֐�
	-------------------------------------
	���e�F�q�I�u�W�F�N�g���폜����
	-------------------------------------
	����1�F�폜����q�I�u�W�F�N�g
=========================================== */
void UIObjectBase::RemoveChildUI(UIObjectBase* pChildObj)
{
	// �q�I�u�W�F�N�g���������Ĕz�񂩂�폜
	m_pChildUIs.erase(
		std::remove(m_pChildUIs.begin(), m_pChildUIs.end(), pChildObj), m_pChildUIs.end());


	pChildObj->m_pParentUI = nullptr;								// �e�I�u�W�F�N�g����ɐݒ�
	pChildObj->GetComponent<UIComponentTransform>()->ClearParent();	// Transform�R���|�[�l���g�̐e��������
}

/* ========================================
	�S�q�I�u�W�F�N�g�폜�֐�
	-------------------------------------
	���e�F�S�q�I�u�W�F�N�g���폜����
=========================================== */
void UIObjectBase::RemoveAllChildUIs()
{
	// �q�I�u�W�F�N�g��S�Ĕz�񂩂�폜
	for (auto pChild : m_pChildUIs)
	{
		pChild->m_pParentUI = nullptr;									// �e�I�u�W�F�N�g����ɐݒ�
		pChild->GetComponent<UIComponentTransform>()->ClearParent();	// Transform�R���|�[�l���g�̐e��������

	}
	m_pChildUIs.clear();
}

/* ========================================
	���㐔�擾�֐�
	-------------------------------------
	���e�F���g�̐��㐔���擾����
	-------------------------------------
	�߂�l�F���㐔
=========================================== */
int UIObjectBase::GetGenerationCount()
{
	// �e�I�u�W�F�N�g���Ȃ��ꍇ
	if (m_pParentUI == nullptr)
	{
		return 0;
	}
	else
	{
		return m_pParentUI->GetGenerationCount() + 1;
	}
}

/* ========================================
	�q������֐�
	-------------------------------------
	���e�F�w�肵��UI���q�����ǂ����𔻒肷��
	-------------------------------------
	����1�F���肷��UI
	-------------------------------------
	�߂�l�F�q�����ǂ���
=========================================== */
bool UIObjectBase::CheckIsDescendant(UIObjectBase* pUI)
{
	// �q�I�u�W�F�N�g���Ȃ��ꍇ�͏������Ȃ�
	if (m_pChildUIs.empty()) return false;

	// �q�I�u�W�F�N�g������
	for (auto pChild : m_pChildUIs)
	{
		// �q�I�u�W�F�N�g���Ώۂ̃I�u�W�F�N�g�ƈ�v�����ꍇ��true��Ԃ�
		if (pChild == pUI) return true;

		// �q�I�u�W�F�N�g�̎q�����ċA�I�Ɍ���
		if (pChild->GetChildUIs().size() > 0)
		{
			// �q�I�u�W�F�N�g�̎q�����ċA�I�Ɍ���
			if (pChild->CheckIsDescendant(pUI)) return true;
		}
	}

	return false;
}


/* ========================================
	�R�s�[�֐�
	-------------------------------------
	���e�F�I�u�W�F�N�g���R�s�[����
	-------------------------------------
	�߂�l�F�R�s�[���ꂽ�I�u�W�F�N�g
=========================================== */
UIObjectBase* UIObjectBase::Copy()
{
	// Transform���擾
	UIComponentTransform* pTransform = this->GetComponent<UIComponentTransform>();

	UIObjectBase* pCopyUI = UI_TYPE_REGISTRY_INST.CreateUI(this->GetUIClassName());	// �R�s�[�p�I�u�W�F�N�g����
	pCopyUI->Init(m_pOwnerScene->CreateUniqueUIName(this->GetName()));				// ������
	pCopyUI->SetDrawPriority(this->GetDrawPriority());								// �`��D��x��ݒ�

	// Transform�R���|�[�l���g�̃R�s�[
	UIComponentTransform* pCopyTrans = pCopyUI->GetComponent<UIComponentTransform>();
	pCopyTrans->SetPosition(GetTransform()->GetPosition());
	pCopyTrans->SetRotation(GetTransform()->GetRotation());
	pCopyTrans->SetScale(GetTransform()->GetScale());

	// Sprite�R���|�[�l���g�̃R�s�[
	UIComponentSprite* pCopySprite = pCopyUI->GetComponent<UIComponentSprite>();
	pCopySprite->SetTexture(m_pCompSprite->GetTexture());
	pCopySprite->SetIsVisible(m_pCompSprite->GetIsVisible());

	m_pOwnerScene->AddSceneUI(pCopyUI);	// �V�[���ɃI�u�W�F�N�g��ǉ�

	// �e�q�֌W���Č�
	// �e�I�u�W�F�N�g������ꍇ
	if (this->GetParentUI())
	{
		pCopyUI->SetParentUI(this->GetParentUI());
	}

	// �q�I�u�W�F�N�g������ꍇ
	if (this->GetChildUIs().size() > 0)
	{
		for (auto& pChild : this->GetChildUIs())
		{
			UIObjectBase* pCopyChild = pChild->Copy();
			pCopyUI->AddChildUI(pCopyChild);
		}
	}

	return pCopyUI;
}


/* ========================================
	�f�t�H���g�R���|�[�l���g�ǉ��֐�
	-------------------------------------
	���e�F�I�u�W�F�N�g�Ƀf�t�H���g�Ŏ�������
		�@�R���|�[�l���g��ǉ�����
=========================================== */
void UIObjectBase::InitDefaultComponent()
{
	m_pCompTransform = AddComponent<UIComponentTransform>();	// Transform�R���|�[�l���g��ǉ�	
	m_pCompSprite = AddComponent<UIComponentSprite>();		// Sprite�R���|�[�l���g��ǉ�
}

/* ========================================
	�q�I�u�W�F�N�g���S��ԑJ�ڊ֐�
	-------------------------------------
	���e�F�q�I�u�W�F�N�g��S�Ď��S��ԂɑJ��
=========================================== */
void UIObjectBase::DestroyChild()
{
	// �q�I�u�W�F�N�g�S�Ă̍폜�t���O�𗧂Ă�
	for (auto& pChild : m_pChildUIs)
	{
		pChild->SetState(UI_DEAD);
		pChild->DestroyChild();
	}
}

/* ========================================
	�o�̓f�[�^�ʊ֐�
	-------------------------------------
	���e�F�I�u�W�F�N�g���ɏo�͂���f�[�^��ݒ�
	-------------------------------------
	����1�F�t�@�C��
=========================================== */
void UIObjectBase::OutPutLocalData(std::ofstream& file)
{
}

/* ========================================
	���̓f�[�^�ʊ֐�
	-------------------------------------
	���e�F�I�u�W�F�N�g���ɓ��͂���f�[�^��ݒ�
	-------------------------------------
	����1�F�t�@�C��
=========================================== */
void UIObjectBase::InputLocalData(std::ifstream& file)
{
}

/* ========================================
	�Q�b�^�[(�g�����X�t�H�[��)�֐�
	-------------------------------------
	�ߒl�FComponentTransform* �g�����X�t�H�[���R���|�[�l���g�̃|�C���^
=========================================== */
UIComponentTransform* UIObjectBase::GetTransform() const
{
	return m_pCompTransform;
}

/* ========================================
	�Q�b�^�[(�X�v���C�g)�֐�
	-------------------------------------
	�ߒl�FComponentSprite* �X�v���C�g�R���|�[�l���g�̃|�C���^
=========================================== */
UIComponentSprite* UIObjectBase::GetSprite() const
{
	return m_pCompSprite;
}

/* ========================================
	�Q�b�^�[(�����V�[��)�֐�
	-------------------------------------
	�ߒl�F���L�V�[���̃|�C���^
=========================================== */
SceneBase* UIObjectBase::GetOwnerScene() const
{
	return m_pOwnerScene;
}

/* ========================================
	�Q�b�^�[(�I�u�W�F�N�g���)�֐�
	-------------------------------------
	�ߒl�F�I�u�W�F�N�g���
=========================================== */
UIObjectBase::E_State UIObjectBase::GetState() const
{
	return m_eState;
}

/* ========================================
	�Q�b�^�[(�I�u�W�F�N�gID)�֐�
	-------------------------------------
	�ߒl�F�I�u�W�F�N�gID
=========================================== */
size_t UIObjectBase::GetTypeID() const
{
	return GetStaticTypeID();
}

/* ========================================
	�Q�b�^�[(�ÓI�I�u�W�F�N�gID)�֐�
	-------------------------------------
	�ߒl�F�ÓI�I�u�W�F�N�gID
=========================================== */
size_t UIObjectBase::GetStaticTypeID()
{
	static size_t nID = reinterpret_cast<size_t>(&GetStaticTypeID); 
	return nID;													
}

/* ========================================
	�Q�b�^�[(�I�u�W�F�N�g�N���X��)�֐�
	-------------------------------------
	�ߒl�F�I�u�W�F�N�g�N���X��
=========================================== */
std::string UIObjectBase::GetUIClassName() const
{
	return "UIObjectBase";
}

/* ========================================
	�Q�b�^�[(�I�u�W�F�N�g��)�֐�
	-------------------------------------
	�ߒl�F�I�u�W�F�N�g��
=========================================== */
std::string UIObjectBase::GetName() const
{
	return m_sName;
}

/* ========================================
	�Q�b�^�[(�Z�[�u�t���O)�֐�
	-------------------------------------
	�ߒl�F�Z�[�u�t���O
=========================================== */
bool UIObjectBase::GetIsSave() const
{
	return m_bIsSave;
}

/* ========================================
	�Q�b�^�[(�I�u�W�F�N�g�ꗗ�܂肽���݃t���O)�֐�
	-------------------------------------
	�ߒl�F�I�u�W�F�N�g�ꗗ�܂肽���݃t���O
=========================================== */
bool UIObjectBase::GetIsFold() const
{
	return m_bIsFold;
}

/* ========================================
	�Q�b�^�[(�`��D��x)�֐�
	-------------------------------------
	�ߒl�F�`��D��x
=========================================== */
int UIObjectBase::GetDrawPriority() const
{
	return m_nDrawPriority;
}

/* ========================================
	�Q�b�^�[(3D�I�u�W�F�N�g���`��t���O)�֐�
	-------------------------------------
	�ߒl�F3D�I�u�W�F�N�g���`��t���O
=========================================== */
bool UIObjectBase::GetIs3DObjBackDraw() const
{
	return m_bIs3DObjBackDraw;
}

/* ========================================
	�Q�b�^�[(�e�I�u�W�F�N�g)�֐�
	-------------------------------------
	�ߒl�F�e�I�u�W�F�N�g
=========================================== */
UIObjectBase* UIObjectBase::GetParentUI() const
{
	return m_pParentUI;
}

/* ========================================
	�Q�b�^�[(�q�I�u�W�F�N�g)�֐�
	-------------------------------------
	�ߒl�F�q�I�u�W�F�N�g
=========================================== */
std::vector<UIObjectBase*> UIObjectBase::GetChildUIs() const
{
	return m_pChildUIs;
}

/* ========================================
	�Z�b�^�[(�I�u�W�F�N�g���)�֐�
	-------------------------------------
	����1�F�I�u�W�F�N�g���
=========================================== */
void UIObjectBase::SetState(E_State eState)
{
	m_eState = eState;
}

/* ========================================
	�Z�b�^�[(�I�u�W�F�N�g��)�֐�
	-------------------------------------
	����1�F�I�u�W�F�N�g��
=========================================== */
void UIObjectBase::SetName(std::string sName)
{
	m_sName = sName;
}

/* ========================================
	�Z�b�^�[(�Z�[�u�t���O)�֐�
	-------------------------------------
	����1�F�Z�[�u�t���O
=========================================== */
void UIObjectBase::SetIsSave(bool bIsSave)
{
	m_bIsSave = bIsSave;
}

/* ========================================
	�Z�b�^�[(UI�ꗗ�܂肽���݃t���O)�֐�
	-------------------------------------
	����1�FUI�ꗗ�܂肽���݃t���O
=========================================== */
void UIObjectBase::SetIsFold(bool bIsFold)
{
	m_bIsFold = bIsFold;
}

/* ========================================
	�Z�b�^�[(�`��D��x)�֐�
	-------------------------------------
	����1�F�`��D��x
=========================================== */
void UIObjectBase::SetDrawPriority(int nPriority)
{
	m_nDrawPriority = nPriority;
}

/* ========================================
	�Z�b�^�[(3D�I�u�W�F�N�g���`��t���O)�֐�
	-------------------------------------
	����1�F3D�I�u�W�F�N�g���`��t���O
=========================================== */
void UIObjectBase::SetIs3DObjBackDraw(bool bIsBackDraw)
{
	m_bIs3DObjBackDraw = bIsBackDraw;
}

#ifdef _DEBUG
/* ========================================
	�f�o�b�O�p�֐�
	-------------------------------------
	���e�F�f�o�b�O�p�̏���
		�@��FUI���(�����R���|�[�l���g��)�̕\��
=========================================== */
void UIObjectBase::Debug()
{
	using namespace DebugUI;

	Window& pUIInfo = WIN_UI_INFO;

	// �I�u�W�F�N�g�ڍ׏����X�V
	pUIInfo.AddItem(Item::CreateValue("UIName", Item::Text, false));	// ���O
	pUIInfo["UIName"].SetText(this->GetName().c_str());				// �I�u�W�F�N�g����ݒ�

	Item* pGroupUIBase = Item::CreateGroup("UIBase");	// UI��{���O���[�v

	// �I�u�W�F�N�g���ύX
	pGroupUIBase->AddGroupItem(Item::CreateCallBack("ChangeName", Item::Kind::Command, [this](bool isWrite, void* arg)	// ���O�ύX�{�^��
	{
		ChangeName();
	}));
	pGroupUIBase->AddGroupItem(Item::CreateValue("UIReName", Item::Path, false, true));	// �ύX��̖��O

	pGroupUIBase->AddGroupItem(InitParentList());	// �e�I�u�W�F�N�g���X�g

	pGroupUIBase->AddGroupItem(Item::CreateBind("DrawPriority", Item::Int, &m_nDrawPriority, false));	// �`��D��x

	pUIInfo.AddItem(pGroupUIBase);	// �O���[�v��ǉ�

	pUIInfo["UIBase"]["UIReName"].SetPath(this->GetName().c_str());	// �ύX��̖��O��ݒ�


	// �e�R���|�[�l���g�����I�u�W�F�N�g���E�B���h�E�ɕ\��
	auto it = m_pComponents.begin();
	while (it != m_pComponents.end())
	{
		(*it)->Debug(pUIInfo);
		++it;
	}
}

/* ========================================
	�e�I�u�W�F�N�g���X�g�������֐�
	-------------------------------------
	���e�F�e�I�u�W�F�N�g���X�g�̏�����
	-------------------------------------
	�߂�l�F�e�I�u�W�F�N�g���X�g
=========================================== */
DebugUI::Item* UIObjectBase::InitParentList()
{
	using namespace DebugUI;

	// �e�I�u�W�F�N�g���X�g�쐬
	Item* pParentList = Item::CreateList("ParentUI", [this](const void* arg)
	{
		std::string sParentName = reinterpret_cast<const char*>(arg);
		ChangeParentList(sParentName);	// �e�I�u�W�F�N�g�ύX

	}, false, true);

	// �V�[����̃I�u�W�F�N�g�����X�g�ɒǉ�
	int nParentNo = 0;					// �I�𒆂̃I�u�W�F�N�g�ԍ�
	pParentList->AddListItem("None");	// ���X�g�̐擪�͐e�I�u�W�F�N�g�Ȃ�

	// �V�[����̃I�u�W�F�N�g�����X�g�ɒǉ�
	for (const auto pObj : SceneManager::GetScene()->GetAllSceneUIObjects())
	{
		if (pObj == this) continue;				// ���g�͒ǉ����Ȃ�
		if (CheckIsDescendant(pObj)) continue;	// �q�I�u�W�F�N�g�͏��O(���g�̎q�K�w�ɑ��݂���ꍇ�͏��O

		pParentList->AddListItem(pObj->GetName().c_str());	// �V�[����̃I�u�W�F�N�g����ǉ�
	}
	// �e�I�u�W�F�N�g������ꍇ
	if (m_pParentUI)
	{
		nParentNo = pParentList->GetListNo(m_pParentUI->GetName().c_str());	// �e�I�u�W�F�N�g��I��
	}

	pParentList->SetListNo(nParentNo);	// �I�𒆂̃I�u�W�F�N�g��ݒ�

	return pParentList;
}

/* ========================================
	���O�ύX�֐�
	-------------------------------------
	���e�FUI����ύX����
=========================================== */
void UIObjectBase::ChangeName()
{
	std::string sReName = WIN_UI_INFO["UIBase"]["UIReName"].GetPath();	// �ύX��̖��O
	std::string sOldName = this->GetName();								// �ύX�O�̖��O

	if (sReName.empty())		return;	// �ύX��̖��O����̏ꍇ�͏������Ȃ�
	if (sReName == sOldName)	return;	// �������O�̏ꍇ�͏������Ȃ�

	sReName = SceneManager::GetScene()->CreateUniqueUIName(sReName);	// �d�����Ȃ����O�ɕύX

	// �I�u�W�F�N�g���ύX
	this->SetName(sReName);												// �����̖��O�ύX

	WIN_UI_INFO["UIName"].SetText(this->GetName().c_str());		// �I�u�W�F�N�g�ڍׂ̖��O��ύX
}


/* ========================================
	�e�I�u�W�F�N�g���X�g�ύX�֐�
	-------------------------------------
	���e�F�e�I�u�W�F�N�g��ύX����
	-------------------------------------
	�����F�V�����e�I�u�W�F�N�g��
=========================================== */
void UIObjectBase::ChangeParentList(std::string sParentName)
{
	UIObjectBase* pParentNew = SceneManager::GetScene()->FindSceneUI(sParentName);	// �e�I�u�W�F�N�g�擾

	// ���ɐݒ肳��Ă���e�I�u�W�F�N�g�Ɠ����ꍇ�͏������Ȃ�
	if (pParentNew == m_pParentUI) return;

	if (pParentNew)
	{
		this->SetParentUI(pParentNew);	// �V�����e�I�u�W�F�N�g�ɐݒ�
		// �I�u�W�F�N�g�ꗗ�̑I���ʒu��ύX
		int nListNo = ITEM_UI_LIST.GetListNo(pParentNew->GetListName().c_str());	// �I�u�W�F�N�g�ꗗ�̕\���ʒu�擾
		ITEM_UI_LIST.SetListNo(nListNo + 1);
	}
	else
	{
		this->RemoveParentUI();			// �e�I�u�W�F�N�g���Ȃ��ꍇ(None��I��)�͉���
		ITEM_UI_LIST.SetListNo(-1);		// �I�u�W�F�N�g�ꗗ�̑I���ʒu��ύX
	}

	m_bIsFold = false;	// UI�ꗗ��W�J
}


/* ========================================
	���X�g�\�����擾�֐�
	-------------------------------------
	���e�F���X�g�\���p�̖��O���擾����
	-------------------------------------
	�߂�l�F���X�g�\���p�̖��O
=========================================== */
std::string UIObjectBase::GetListName()
{
	std::string sName;							// ���X�g�\����
	int nGeneCnt = this->GetGenerationCount();	// ���㐔�擾

	// �e�I�u�W�F�N�g������ꍇ
	if (nGeneCnt > 0)
	{
		// ���㐔���̃X�y�[�X��ǉ�(�\����i�K�I�ɂ��邽��)
		for (int i = 0; i < nGeneCnt; i++)
		{
			sName += DebugUI::CHILD_HEAD_SPACE;
		}
		sName += DebugUI::CHILD_HEAD_TEXT + this->GetName();
	}
	// �����ꍇ�͂��̂܂ܕ\��
	else
	{
		sName = this->GetName();
	}

	// �q�I�u�W�F�N�g������ꍇ�͖����ɕ�����ǉ�
	if (m_pChildUIs.size() > 0)
	{
		sName += DebugUI::PARENT_END_TEXT;
	}

	return sName;
}


#endif // _DEBUG