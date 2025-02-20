/* ========================================
	DX22Base/
	------------------------------------
	�V�[���pcpp
	------------------------------------
	SceneBase.cpp
========================================== */

// =============== �C���N���[�h =====================
#include "SceneBase.h"
#include "ObjectBase.h"
#include "ObjectCamera.h"
#include "CameraManager.h"
#include "ComponentCollisionBase.h"

// =============== �萔��` =======================
const int OBJECT_LIST_LINE_NUM = 17;	// �I�u�W�F�N�g���X�g�̍s��

/* ========================================
	�R���X�g���N�^�֐�
	-------------------------------------
	���e�F������
========================================== */
SceneBase::SceneBase()
	: m_bIsUpdating(false)		// �X�V���t���O��������
	, m_bIsUpdatingUI(false)	// UI�X�V���t���O��������
	, m_pObjects()				// �V�[���ɏ�������I�u�W�F�N�g�ꗗ
	, m_pStandbyObjects()		// �I�u�W�F�N�g���ꎞ�I�ɕۑ����Ă����z��
	, m_pUIObjects()			// �V�[���ɏ�������UI�I�u�W�F�N�g�ꗗ
	, m_pStandbyUIObjects()		// UI�I�u�W�F�N�g���ꎞ�I�ɕۑ����Ă����z��
	, m_pObjectCollision()		// �e�I�u�W�F�N�g�����Փ˔���R���|�[�l���g
#ifdef _DEBUG
	, m_pSelectObj(nullptr)		// �ꗗ�őI�𒆂̃I�u�W�F�N�g
	, m_nObjectListSelectNo(-1)	// �I�u�W�F�N�g���X�g�̔ԍ�
	, m_pSelectUI(nullptr)		// �ꗗ�őI�𒆂�UI�I�u�W�F�N�g
	, m_nUISelectNo(-1)			// UI�I�u�W�F�N�g���X�g�̔ԍ�
#endif // _DEBUG

{
}

/* ========================================
	�������֐�
	-------------------------------------
	���e�F����������
=========================================== */
void SceneBase::Init()
{
#ifdef _DEBUG
	InitObjectList();
	InitUIList();
#endif // _DEBUG

	// �N���A
	m_pObjects.clear();			// �V�[���ɏ�������I�u�W�F�N�g�ꗗ
	m_pStandbyObjects.clear();	// �I�u�W�F�N�g���ꎞ�I�ɕۑ����Ă����z��
	m_pUIObjects.clear();		// �V�[���ɏ�������UI�I�u�W�F�N�g�ꗗ
	m_pStandbyUIObjects.clear();	// UI�I�u�W�F�N�g���ꎞ�I�ɕۑ����Ă����z��

	m_bIsUpdating = false;		// �X�V���t���O��������
	InitLocal();				// �ʏ���������

	CAMERA_MNG_INST.Init(this);	// �V�[���̃J������������
}

/* ========================================
	�I���֐�
	-------------------------------------
	���e�F�I������
=========================================== */
void SceneBase::Uninit()
{
#ifdef _DEBUG
	WIN_OBJ_LIST.Clear();
	WIN_OBJ_INFO.Clear();
	WIN_UI_LIST.Clear();
	WIN_UI_INFO.Clear();
	WIN_CAMERA_INFO["CameraList"].RemoveListItemAll();

#endif // _DEBUG

	UninitLocal();	// �ʏI������

	// ����UI�I�u�W�F�N�g�z��̑S�v�f���폜
	for (auto& pObject : m_pUIObjects)
	{
		pObject->Uninit();
	}
	m_pUIObjects.clear();	// �N���A

	// �����I�u�W�F�N�g�z��̑S�v�f���폜
	for (auto& pObject : m_pObjects)
	{
		pObject->Uninit();
	}
	m_pObjects.clear();	// �N���A

	// �ꎞ�ۑ����Ă����I�u�W�F�N�g�z��̑S�v�f���폜
	for (auto& pObject : m_pStandbyObjects)
	{
		pObject->Uninit();
	}
	m_pStandbyObjects.clear();	// �N���A
	
	// �ꎞ�ۑ����Ă���UI�I�u�W�F�N�g�z��̑S�v�f���폜
	for (auto& pObject : m_pStandbyUIObjects)
	{
		pObject->Uninit();
	}
	m_pStandbyUIObjects.clear();	// �N���A

}

/* ========================================
	�X�V�֐�
	-------------------------------------
	���e�F�X�V����
=========================================== */
void SceneBase::Update()
{
#ifdef _DEBUG
	// ���X�g���I�����͑I���I�u�W�F�N�g���N���A
	if (m_nObjectListSelectNo == -1) m_pSelectObj = nullptr;
	// UI���X�g���I�����͑I��UI�I�u�W�F�N�g���N���A
	if (m_nUISelectNo == -1) m_pSelectUI = nullptr;

	ReloadDebugObjectList();	// �I�u�W�F�N�g���X�g�ēǂݍ���
	ReloadDebugUIList();		// UI�I�u�W�F�N�g���X�g�ēǂݍ���
#endif // _DEBUG

	SortUIObjects();	// UI�I�u�W�F�N�g��`�揇�ɕ��ёւ�
	UpdateObject();		// �I�u�W�F�N�g�X�V
	UpdateUI();			// UI�X�V
}

/* ========================================
	�`��֐�
	-------------------------------------
	���e�F�`�揈��
=========================================== */
void SceneBase::Draw()
{
	DirectXManager::SetBlendMode(DirectXManager::BlendMode::BLEND_UI);			// �u�����h���[�h�ύX(�����x0.0�`1.0)
	DirectXManager::SetDepthTest(DirectXManager::DepthState::DEPTH_DISABLE);	// �[�x�e�X�g����
	// 3D�I�u�W�F�N�g�̔w�i�ɕ`�悷��UI��`��
	for (auto& pUIObject : m_pUIObjects)
	{
		if (!pUIObject->GetIs3DObjBackDraw()) continue;
		pUIObject->Draw();
	}
	DirectXManager::SetBlendMode(DirectXManager::BlendMode::BLEND_ALPHA);				// �u�����h���[�h���ɖ߂�
	DirectXManager::SetDepthTest(DirectXManager::DepthState::DEPTH_ENABLE_WRITE_TEST);	// �[�x�e�X�g���ɖ߂�


	// �����I�u�W�F�N�g�z��̑S�v�f��`��
	for (auto& pObject : m_pObjects)
	{
		pObject->Draw();	
	}

	DirectXManager::SetBlendMode(DirectXManager::BlendMode::BLEND_UI);			// �u�����h���[�h�ύX(�����x0.0�`1.0)
	DirectXManager::SetDepthTest(DirectXManager::DepthState::DEPTH_DISABLE);	// �[�x�e�X�g����
	// ����UI�I�u�W�F�N�g�z��̑S�v�f��`��
	for (auto& pUIObject : m_pUIObjects)
	{
		if (pUIObject->GetIs3DObjBackDraw()) continue;
		pUIObject->Draw();
	}
	DirectXManager::SetBlendMode(DirectXManager::BlendMode::BLEND_ALPHA);				// �u�����h���[�h���ɖ߂�
	DirectXManager::SetDepthTest(DirectXManager::DepthState::DEPTH_ENABLE_WRITE_TEST);	// �[�x�e�X�g���ɖ߂�
	DrawLocal();	// �ʕ`�揈��
}

/* ========================================
	�I�u�W�F�N�g�X�V�֐�
	-------------------------------------
	���e�F�X�V����
=========================================== */
void SceneBase::UpdateObject()
{
	m_bIsUpdating = true;	// �X�V���t���O�𗧂Ă�

	// �����I�u�W�F�N�g�z��̑S�v�f���X�V
	for (auto& pObject : m_pObjects)
	{
		pObject->Update();
	}

	m_bIsUpdating = false;	// �X�V���t���O������

	// �ꎞ�ۑ��I�u�W�F�N�g�z��
	for (auto& pObject : m_pStandbyObjects)
	{
		pObject->Update();
		m_pObjects.emplace_back(std::move(pObject));	// �I�u�W�F�N�g�z��Ɉړ�
	}
	m_pStandbyObjects.clear();	// �N���A

	
	UpdateCollision();	// �e�����蔻��X�V(���S�����I�u�W�F�N�g��m_bColStatesMap����폜���邽�߂ɂ��̈ʒu�ɋL�q)
	RemoveDeadObjects();// ���S��Ԃ̃I�u�W�F�N�g���폜
}

/* ========================================
	UI�X�V�֐�
	-------------------------------------
	���e�F�X�V����
=========================================== */
void SceneBase::UpdateUI()
{
	m_bIsUpdatingUI = true;	// �X�V���t���O�𗧂Ă�

	// ����UI�I�u�W�F�N�g�z��̑S�v�f���X�V
	for (auto& pObject : m_pUIObjects)
	{
		pObject->Update();
	}

	m_bIsUpdatingUI = false;	// �X�V���t���O������

	// �ꎞ�ۑ�UI�I�u�W�F�N�g�z��
	for (auto& pObject : m_pStandbyUIObjects)
	{
		pObject->Update();
		m_pUIObjects.emplace_back(std::move(pObject));	// UI�I�u�W�F�N�g�z��Ɉړ�
	}
	m_pStandbyUIObjects.clear();	// �N���A

	RemoveDeadUIObjects();	// ���S��Ԃ�UI�I�u�W�F�N�g���폜
	UpdateLocal();			// �ʍX�V����
}

/* ========================================
	UI���ёւ��֐�
	-------------------------------------
	���e�F�D�揇�ʂɏ]����UI�I�u�W�F�N�g����ёւ�
=========================================== */
void SceneBase::SortUIObjects()
{
	// UI�I�u�W�F�N�g��`�揇�ɕ��ёւ�
	std::sort(m_pUIObjects.begin(), m_pUIObjects.end(),
		[](const std::unique_ptr<UIObjectBase>& pUI1, const std::unique_ptr<UIObjectBase>& pUI2)
	{
		return pUI1->GetDrawPriority() < pUI2->GetDrawPriority();
	});
}

/* ========================================
	�I�u�W�F�N�g�폜�֐�
	-------------------------------------
	���e�F���S��Ԃ̃I�u�W�F�N�g���폜
=========================================== */
void SceneBase::RemoveDeadObjects()
{
	// ���̃��[�v���ŃI�u�W�F�N�g�̏�Ԃ��ς��̂ŁA�ꎞ�ۑ��p�ɃR�s�[
	std::map<ObjectBase*, ObjectBase::E_State> pObjectStateMap;	
	for (auto& pObject : m_pObjects)
		pObjectStateMap.insert(std::make_pair(pObject.get(), pObject->GetState()));

	// ���S��Ԃ̃I�u�W�F�N�g���폜
	for (auto it = m_pObjects.begin(); it != m_pObjects.end();)
	{
		ObjectBase* pObject = it->get();
		// ���S��Ԃ��ǂ���
		if (pObjectStateMap.at(pObject) == OBJ_DEAD)
		{
#ifdef _DEBUG
			// �폜�ΏۃI�u�W�F�N�g���ꗗ�őI�𒆂̏ꍇ
			if(m_nObjectListSelectNo == ITEM_OBJ_LIST.GetListNo(pObject->GetListName().c_str()))
			{
				WIN_OBJ_INFO.Clear();	// �I�u�W�F�N�g���E�B���h�E�N���A

				m_nObjectListSelectNo = -1;								// �I��ԍ������Z�b�g
				ITEM_OBJ_LIST.SetListNo(-1);	// �I��ԍ������Z�b�g
			}
#endif
			// �q�I�u�W�F�N�g������ꍇ
			if (pObject->GetChildObjects().size() > 0)
			{
				for (auto& pChild : pObject->GetChildObjects())
				{
					this->RemoveSceneObject(pChild);	// �q�I�u�W�F�N�g���폜
				}
			}
			// �e�I�u�W�F�N�g������ꍇ
			if (pObject->GetParentObject())
			{
				pObject->GetParentObject()->RemoveChildObject(pObject);	// �e�I�u�W�F�N�g����폜
			}

			pObject->Uninit();			// �I������
			it = m_pObjects.erase(it);	// �폜

		}
		else
		{
			++it;	// ���̗v�f��
		}
	}

}

/* ========================================
	UI�I�u�W�F�N�g�폜�֐�
	-------------------------------------
	���e�F���S��Ԃ�UI�I�u�W�F�N�g���폜
=========================================== */
void SceneBase::RemoveDeadUIObjects()
{
	// ���̃��[�v����UI�I�u�W�F�N�g�̏�Ԃ��ς��̂ŁA�ꎞ�ۑ��p�ɃR�s�[
	std::map<UIObjectBase*, UIObjectBase::E_State> pUIObjectStateMap;
	for (auto& pUIObject : m_pUIObjects)
		pUIObjectStateMap.insert(std::make_pair(pUIObject.get(), pUIObject->GetState()));

	// ���S��Ԃ�UI�I�u�W�F�N�g���폜
	for (auto it = m_pUIObjects.begin(); it != m_pUIObjects.end();)
	{
		UIObjectBase* pUIObject = it->get();
		// ���S��Ԃ��ǂ���
		if (pUIObjectStateMap.at(pUIObject) == UIObjectBase::E_State::STATE_DEAD)
		{
#ifdef _DEBUG
			// �폜�Ώ�UI�I�u�W�F�N�g���ꗗ�őI�𒆂̏ꍇ
			if (m_nUISelectNo == WIN_UI_LIST[ITEM_UI_LIST_NAME.c_str()].GetListNo(pUIObject->GetListName().c_str()))
			{
				WIN_UI_INFO.Clear();	// UI�I�u�W�F�N�g���E�B���h�E�N���A

				m_nUISelectNo = -1;								// �I��ԍ������Z�b�g
				WIN_UI_LIST[ITEM_UI_LIST_NAME.c_str()].SetListNo(-1);	// �I��ԍ������Z�b�g
			}
#endif
			// �qUI�I�u�W�F�N�g������ꍇ
			if (pUIObject->GetChildUIs().size() > 0)
			{
				for (auto& pChild : pUIObject->GetChildUIs())
				{
					this->RemoveSceneUI(pChild);	// �qUI�I�u�W�F�N�g���폜
				}
			}
			// �eUI�I�u�W�F�N�g������ꍇ
			if (pUIObject->GetParentUI())
			{
				pUIObject->GetParentUI()->RemoveChildUI(pUIObject);	// �eUI�I�u�W�F�N�g����폜
			}

			pUIObject->Uninit();			// �I������
			it = m_pUIObjects.erase(it);	// �폜
		}
		else
		{
			++it;	// ���̗v�f��
		}
	}

}

/* ========================================
	�I�u�W�F�N�g�ǉ��֐�
	-------------------------------------
	���e�F�V�[���ɃI�u�W�F�N�g��ǉ�
		�@���t�@�C���f�[�^����I�u�W�F�N�g��ǉ�����ꍇ�Ɏg�p
	-------------------------------------
	�����F�ǉ�����I�u�W�F�N�g�|�C���^
=========================================== */
void SceneBase::AddSceneObjectBase(ObjectBase* pObject)
{
	// �V�[�����X�V�����ǂ������`�F�b�N���܂�
	if (m_bIsUpdating)
	{
		// �ꎞ�ۑ��p�̔z��Ƀ��j�[�N�|�C���^���ړ����܂�
		m_pStandbyObjects.push_back(std::unique_ptr<ObjectBase>(pObject));
	}
	else
	{
		// �V�[���̃I�u�W�F�N�g�z��Ƀ��j�[�N�|�C���^���ړ����܂�
		m_pObjects.push_back(std::unique_ptr<ObjectBase>(pObject));
	}
}

/* ========================================
	�I�u�W�F�N�g�ǉ��֐�
	-------------------------------------
	���e�F�V�[���ɃI�u�W�F�N�g��ǉ�
		�@���t�@�C���f�[�^����I�u�W�F�N�g��ǉ�����ꍇ�Ɏg�p
	-------------------------------------
	�ߒl�F�ǉ������I�u�W�F�N�g�|�C���^
=========================================== */
void SceneBase::AddSceneUI(UIObjectBase* pUIObject)
{
	// �V�[�����X�V�����ǂ������`�F�b�N���܂�
	if (m_bIsUpdatingUI)
	{
		// �ꎞ�ۑ��p�̔z��Ƀ��j�[�N�|�C���^���ړ����܂�
		m_pStandbyUIObjects.push_back(std::unique_ptr<UIObjectBase>(pUIObject));
	}
	else
	{
		// �V�[����UI�I�u�W�F�N�g�z��Ƀ��j�[�N�|�C���^���ړ����܂�
		m_pUIObjects.push_back(std::unique_ptr<UIObjectBase>(pUIObject));
	}
}

/* ========================================
	�I�u�W�F�N�g�����֐�
	-------------------------------------
	���e�F�V�[���ɏ�������I�u�W�F�N�g������
	-------------------------------------
	�����FsName	�I�u�W�F�N�g��
	-------------------------------------
	�ߒl�F�擾�I�u�W�F�N�g�|�C���^
=========================================== */
ObjectBase* SceneBase::FindSceneObject(std::string sName)
{
	// ���O����v����I�u�W�F�N�g������
	for (auto& pObject : m_pObjects)
	{
		if (pObject->GetName() == sName)
		{
			return pObject.get();
		}
	}

	return nullptr;
}

/* ========================================
	UI�I�u�W�F�N�g�����֐�
	-------------------------------------
	���e�F�V�[���ɏ�������UI�I�u�W�F�N�g������
	-------------------------------------
	�����FsName	UI�I�u�W�F�N�g��
	-------------------------------------
	�ߒl�F�擾UI�I�u�W�F�N�g�|�C���^
=========================================== */
UIObjectBase* SceneBase::FindSceneUI(std::string sName)
{
	// ���O����v����UI�I�u�W�F�N�g������
	for (auto& pUIObject : m_pUIObjects)
	{
		if (pUIObject->GetName() == sName)
		{
			return pUIObject.get();
		}
	}

	return nullptr;
}

/* ========================================
	�I�u�W�F�N�g�폜�֐�
	-------------------------------------
	���e�F�V�[���ɏ�������I�u�W�F�N�g���폜
		�@�����S��Ԃ̃I�u�W�F�N�g���폜����ꍇ�Ɏg�p(�q�I�u�W�F�N�g�̍폜��)
	-------------------------------------
	�����FpObject	�폜����I�u�W�F�N�g�|�C���^
=========================================== */
void SceneBase::RemoveSceneObject(ObjectBase* pObject)
{
	// �q�I�u�W�F�N�g������ꍇ
	if (pObject->GetChildObjects().size() > 0)
	{
		for (auto& pChild : pObject->GetChildObjects())
		{
			this->RemoveSceneObject(pChild);	// �q�I�u�W�F�N�g���폜
		}
	}

	pObject->RemoveParentObject();	// �e�I�u�W�F�N�g����폜
	pObject->Destroy();				// �j��

}

/* ========================================
	UI�I�u�W�F�N�g�폜�֐�
	-------------------------------------
	���e�F�V�[���ɏ�������UI�I�u�W�F�N�g���폜
		�@�����S��Ԃ�UI�I�u�W�F�N�g���폜����ꍇ�Ɏg�p(�qUI�I�u�W�F�N�g�̍폜��)
	-------------------------------------
	�����FpUIObject	�폜����UI�I�u�W�F�N�g�|�C���^
=========================================== */
void SceneBase::RemoveSceneUI(UIObjectBase* pUIObject)
{
	// �q�I�u�W�F�N�g������ꍇ
	if (pUIObject->GetChildUIs().size() > 0)
	{
		for (auto& pChild : pUIObject->GetChildUIs())
		{
			this->RemoveSceneUI(pChild);	// �qUI�I�u�W�F�N�g���폜
		}
	}
		
	pUIObject->RemoveParentUI();							// �eUI�I�u�W�F�N�g����폜
	pUIObject->SetState(UIObjectBase::E_State::STATE_DEAD);	// ���S��Ԃɐݒ�

}


/* ========================================
	�Փ˔���z��ǉ��֐�
	-------------------------------------
	���e�F�Փ˔�����Ǘ�����z��ɒǉ�
		�@�Փ˔���R���|�[�l���g�̏������ŌĂ΂��
	-------------------------------------
	����1�F�Փ˔���R���|�[�l���g
=========================================== */
void SceneBase::AddObjectCollision(ComponentCollisionBase* pCollision)
{
	m_pObjectCollision.emplace_back(pCollision);	// emplace_back�Œǉ�(�R�s�[�������)
}

/* ========================================
	�Փ˔���z��폜�֐�
	-------------------------------------
	���e�F�Փ˔�����Ǘ�����z�񂩂�폜
		�@�Փ˔���R���|�[�l���g�̏I�������ŌĂ΂��
	-------------------------------------
	����1�F�Փ˔���R���|�[�l���g
=========================================== */
void SceneBase::RemoveObjectCollision(ComponentCollisionBase* pCollision)
{
	// �Փ˔�����Ǘ�����z�񂩂�폜
	m_pObjectCollision.erase(
		std::remove(m_pObjectCollision.begin(), m_pObjectCollision.end(), pCollision), m_pObjectCollision.end());
}

/* ========================================
	�����蔻��z��X�V�֐�
	-------------------------------------
	���e�F�e�I�u�W�F�N�g���������蔻��
		�@�R���|�[�l���g���X�V����
=========================================== */
void SceneBase::UpdateCollision()
{
	// ��F0��1�A0��2�A1��2�A1��3�A2��3�A�ƑS�Ă̑g�ݍ��킹�ŏՓ˔�����s��
	for (size_t i = 0; i < m_pObjectCollision.size(); ++i) {
		for (size_t j = i + 1; j < m_pObjectCollision.size(); ++j) {

			// �Փ˔�����s���R���|�[�l���g���擾
			ComponentCollisionBase* collisionA = m_pObjectCollision.at(i);
			ComponentCollisionBase* collisionB = m_pObjectCollision.at(j);

			collisionA->UpdateCollision(collisionB);
			collisionB->UpdateCollision(collisionA); 
		}
	}

	// �Փˏ�ԃ}�b�v�X�V(��L�̏����ŏՓˏ�Ԃ��ς��������)
	for (size_t i = 0; i < m_pObjectCollision.size(); ++i) {
		for (size_t j = i + 1; j < m_pObjectCollision.size(); ++j) {

			// �Փ˔�����s���R���|�[�l���g���擾
			ComponentCollisionBase* collisionA = m_pObjectCollision.at(i);
			ComponentCollisionBase* collisionB = m_pObjectCollision.at(j);

			collisionA->UpdateCollisionMap(collisionB);
			collisionB->UpdateCollisionMap(collisionA);
		}
	}

}


/* ========================================
	���j�[�N���O�����֐�
	-------------------------------------
	���e�F���O���d�����Ă���ꍇ�ɁA
		�@�A�Ԃ��������O�𐶐�����
	-------------------------------------
	�����FsName	�I�u�W�F�N�g��
	-------------------------------------
	�ߒl�F������̖��O
=========================================== */
std::string SceneBase::CreateUniqueName(std::string sName)
{
	std::string sReName = sName;				// �Ԃ����O
	std::vector<ObjectBase*> pSelectObjects;	// ���O���܂܂�Ă���I�u�W�F�N�g�z��

	// ���O���܂܂�Ă���I�u�W�F�N�g������
	// ��F"Player"�̏ꍇ�A"CameraPlayer","PlayerStart","Player_1"�Ȃ�
	for (auto& pObject : m_pObjects)
	{
		if (pObject->GetName().find(sName) != std::string::npos)
		{
			pSelectObjects.push_back(pObject.get());
		}
	}
	// �ꎞ�ۑ��I�u�W�F�N�g�z��
	for (auto& pObject : m_pStandbyObjects)
	{
		if (pObject->GetName().find(sName) != std::string::npos)
		{
			pSelectObjects.push_back(pObject.get());
		}
	}
	// �d�����Ă��Ȃ��ꍇ�͂��̂܂ܕԂ�
	if (pSelectObjects.size() == 0) return sName;	

	int nDupCnt = 0;	// �d����
	// ���O���d�����Ă���ꍇ�͘A�Ԃ�t����(�d�����Ȃ��Ȃ�܂�)
	while (!CheckUniqueName(sReName, pSelectObjects))
	{
		nDupCnt++;
		sReName = sName + "_" + std::to_string(nDupCnt);
	}

	return sReName;

}

/* ========================================
	���j�[�N���OUI�����֐�
	-------------------------------------
	���e�F���O���d�����Ă���ꍇ�ɁA
		�@�A�Ԃ��������O�𐶐�����
	-------------------------------------
	�����FsName	UI�I�u�W�F�N�g��
	-------------------------------------
	�ߒl�F������̖��O
=========================================== */
std::string SceneBase::CreateUniqueUIName(std::string sName)
{
	std::string sReName = sName;			// �Ԃ����O
	std::vector<UIObjectBase*> pSelectUIs;	// ���O���܂܂�Ă���UI�I�u�W�F�N�g�z��

	// ���O���܂܂�Ă���UI�I�u�W�F�N�g������
	// ��F"Player"�̏ꍇ�A"CameraPlayer","PlayerStart","Player_1"�Ȃ�
	for (auto& pUI : m_pUIObjects)
	{
		if (pUI->GetName().find(sName) != std::string::npos)
		{
			pSelectUIs.push_back(pUI.get());
		}
	}
	// �d�����Ă��Ȃ��ꍇ�͂��̂܂ܕԂ�
	if (pSelectUIs.size() == 0) return sName;

	int nDupCnt = 0;	// �d����
	// ���O���d�����Ă���ꍇ�͘A�Ԃ�t����(�d�����Ȃ��Ȃ�܂�)
	while (!CheckUniqueUIName(sReName, pSelectUIs))
	{
		nDupCnt++;
		sReName = sName + "_" + std::to_string(nDupCnt);
	}

	return sReName;
}

/* ========================================
	���O�d���`�F�b�N�֐�
	-------------------------------------
	���e�F���O���d�����Ă��邩�`�F�b�N
		�@���O���܂܂�Ă���I�u�W�F�N�g�̔z���n��
	-------------------------------------
	����1�FsName	���O
	����2�FpObjects	�I�u�W�F�N�g�z��
	-------------------------------------
	�ߒl�F�d�����Ă��邩�ǂ���
=========================================== */
bool SceneBase::CheckUniqueName(std::string sName, std::vector<ObjectBase*> pObjects)
{
	for (auto& pObject : pObjects)
	{
		// �������O������ꍇ
		if (sName == pObject->GetName())
		{
			return false;
		}
	}

	return true;
}

/* ========================================
	���O�d���`�F�b�N(UI)�֐�
	-------------------------------------
	���e�F���O���d�����Ă��邩�`�F�b�N
		�@���O���܂܂�Ă���I�u�W�F�N�g�̔z���n��
	-------------------------------------
	����1�FsName	���O
	����2�FpUIs	UI�z��
	-------------------------------------
	�ߒl�F�d�����Ă��邩�ǂ���
=========================================== */
bool SceneBase::CheckUniqueUIName(std::string sName, std::vector<UIObjectBase*> pUIs)
{
	for (auto& pUI : pUIs)
	{
		// �������O������ꍇ
		if (sName == pUI->GetName())
		{
			return false;
		}
	}

	return true;
}

/* ========================================
	�V�[�����擾�֐�
	-------------------------------------
	�ߒl�F�V�[����
=========================================== */
std::string SceneBase::GetSceneName()
{
	return "SceneBase";
}

/* ========================================
	�S�I�u�W�F�N�g�擾�֐�
	-------------------------------------
	���e�F�V�[���ɏ�������S�ẴI�u�W�F�N�g���擾
	-------------------------------------
	�ߒl�F�擾�����I�u�W�F�N�g�̃|�C���^�z��
=========================================== */
std::vector<ObjectBase*> SceneBase::GetAllSceneObjects()
{
	std::vector<ObjectBase*> objects;

	for (const auto& pObject : m_pObjects)
	{
		objects.push_back(pObject.get());
	}

	return objects;
}

/* ========================================
	�SUI�I�u�W�F�N�g�擾�֐�
	-------------------------------------
	���e�F�V�[���ɏ�������S�Ă�UI�I�u�W�F�N�g���擾
	-------------------------------------
	�ߒl�F�擾����UI�I�u�W�F�N�g�̃|�C���^�z��
=========================================== */
std::vector<UIObjectBase*> SceneBase::GetAllSceneUIObjects()
{
	std::vector<UIObjectBase*> objects;

	for (const auto& pUIObject : m_pUIObjects)
	{
		objects.push_back(pUIObject.get());
	}

	return objects;
}

/* ========================================
	�^�O�ʃI�u�W�F�N�g���W�֐�
	-------------------------------------
	���e�F�V�[���ɏ����������̃^�O�̃I�u�W�F�N�g
		�@��S�Ď��W����
	-------------------------------------
	�ߒl�F�擾�����I�u�W�F�N�g�̃|�C���^�z��
========================================== */
std::vector<ObjectBase*> SceneBase::GetSceneObjectsTag(E_ObjectTag tag)
{
	// �擾�����I�u�W�F�N�g���i�[����z��
	std::vector<ObjectBase*> objects;

	// �V�[���ɏ�������I�u�W�F�N�g������
	for (const auto& pObject : m_pObjects)
	{
		// �I�u�W�F�N�g�̌^����v������z��ɒǉ�
		if (pObject->GetTag() == tag)
		{
			objects.push_back(pObject.get());
		}
	}

	return objects;	// �擾�����I�u�W�F�N�g�̔z���Ԃ�
}

/* ========================================
	�^�O�ʃI�u�W�F�N�g���W�֐�
	-------------------------------------
	���e�F�V�[���ɏ����������̃^�O�̃I�u�W�F�N�g
		�@����ԍŏ��Ɍ����������̂��擾����
	-------------------------------------
	�ߒl�F�擾�����I�u�W�F�N�g�̃|�C���^
========================================== */
ObjectBase* SceneBase::GetSceneObjectTag(E_ObjectTag tag)
{
	// �V�[���ɏ�������I�u�W�F�N�g������
	for (const auto& pObject : m_pObjects)
	{
		// ��ԍŏ��Ɍ��������I�u�W�F�N�g��Ԃ�
		if (pObject->GetTag() == tag)
		{
			return pObject.get();
		}
	}

	return nullptr;
}


// �f�o�b�O�p ========================================================
#ifdef _DEBUG

/* ========================================
	�E�B���h�E������(�I�u�W�F�N�g�ꗗ)�֐�
	-------------------------------------
	���e�F�I�u�W�F�N�g�ꗗ�̏��������s��
=========================================== */
void SceneBase::InitObjectList()
{
	using namespace DebugUI;


	// �I�u�W�F�N�g�폜�{�^��
	WIN_OBJ_LIST.AddItem(Item::CreateCallBack("Remove", Item::Kind::Command, [this](bool isWrite, void* arg)
	{
		if (m_nObjectListSelectNo == -1) return;					// �I������Ă��Ȃ��ꍇ�͏������Ȃ�
		// �V�[����̃J������1�̏ꍇ�A�J�����I�u�W�F�N�g�͍폜�s��
		if (dynamic_cast<ObjectCamera*>(m_pSelectObj) != nullptr && CAMERA_MNG_INST.GetCameraNum() == 1) return;
		// �J�����I�u�W�F�N�g���A�N�e�B�u�̏ꍇ�A�폜�s��
		if (CAMERA_MNG_INST.GetActiveCamera() == m_pSelectObj)	return;

		m_pSelectObj->Destroy();	// �I�u�W�F�N�g�폜

	}));

	// �I�u�W�F�N�g�t�H�[�J�X�{�^��
	WIN_OBJ_LIST.AddItem(Item::CreateCallBack("Focus", Item::Kind::Command, [this](bool isWrite, void* arg)
	{
		if (m_nObjectListSelectNo == -1) return;					// �I������Ă��Ȃ��ꍇ�͏������Ȃ�
		// �I������Ă��Ȃ��ꍇ�͏������Ȃ�
		if (m_nObjectListSelectNo == -1) return;
		// �A�N�e�B�u�J�����̓t�H�[�J�X�ړ��s��
		if (m_pSelectObj == CAMERA_MNG_INST.GetActiveCamera()) return;

		CAMERA_MNG_INST.FocusMoveCamera(m_pSelectObj);	// �J�������w��I�u�W�F�N�g�Ƀt�H�[�J�X�ړ�

	}, false, true));

	// �I�u�W�F�N�g�����{�^��
	WIN_OBJ_LIST.AddItem(Item::CreateCallBack("Copy", Item::Kind::Command, [this](bool isWrite, void* arg)
	{
		// �I������Ă��Ȃ��ꍇ�͏������Ȃ�
		if (m_nObjectListSelectNo == -1) return;
		// �I�u�W�F�N�g�𕡐�
		m_pSelectObj->Copy();

	}, false, true));

	// �I�u�W�F�N�g�I�����̃R�[���o�b�N�֐�
	Item::ConstCallback  FuncListClick = [this](const void* arg)
	{
		// �N���b�N���ꂽ�I�u�W�F�N�g�̏���\��
		std::string sObjName = reinterpret_cast<const char*>(arg);
		m_nObjectListSelectNo = ITEM_OBJ_LIST.GetListNo(sObjName.c_str());	// �I��ԍ����擾

		InitObjectInfo(sObjName);
	};

	// �I�u�W�F�N�g���X�g���쐬
	WIN_OBJ_LIST.AddItem(Item::CreateList(ITEM_OBJ_LIST_NAME.c_str(), FuncListClick, false, false, false, OBJECT_LIST_LINE_NUM));

}

/* ========================================
	�E�B���h�E������(�I�u�W�F�N�g���)�֐�
	-------------------------------------
	���e�F�I�u�W�F�N�g���̏��������s��
		�@���ꗗ�̃I�u�W�F�N�g�����N���b�N����x�Ă΂��
	-------------------------------------
	�����Fstring �I�u�W�F�N�g��
=========================================== */
void SceneBase::InitObjectInfo(std::string sName)
{
	using namespace DebugUI;

	WIN_OBJ_INFO.Clear();	// �\�����Z�b�g

	// ���O��"L"���܂܂�Ă���ꍇ(�q�I�u�W�F�N�g�̏ꍇ)
	if (sName.find(CHILD_HEAD_TEXT) != std::string::npos)
	{
		// "L"�������������O�ɕϊ�
		int nHeadTextCnt = sName.find(CHILD_HEAD_TEXT);							// L���܂܂��ʒu���擾
		sName = sName.substr(nHeadTextCnt + CHILD_HEAD_TEXT.size());	// L�ȍ~�̕�������擾
	}

	// ���O��"*"���܂܂�Ă���ꍇ(�e�I�u�W�F�N�g�̏ꍇ)
	if (sName.find(PARENT_END_TEXT) != std::string::npos)
	{
		// "*"�������������O�ɕϊ�
		int nEndTextCnt = sName.find(PARENT_END_TEXT);	// *���܂܂��ʒu���擾
		sName = sName.substr(0, nEndTextCnt);	// *�ȑO�̕�������擾
	}

	// ���O����v����I�u�W�F�N�g������
	for (auto& pObject : m_pObjects)
	{
		if (pObject->GetName() == sName)
		{
			// �I�u�W�F�N�g����\��
			pObject->Debug();			
			m_pSelectObj = pObject.get();	// �I�𒆂̃I�u�W�F�N�g��ێ�

			bool bIsFold = pObject->GetIsFold() ? false : true;
			pObject->SetIsFold(bIsFold);	// �܂肽���ݏ�Ԃ�ύX

			break;
		}
	}
}

/* ========================================
	�E�B���h�E������(UI�I�u�W�F�N�g�ꗗ)�֐�
	-------------------------------------
	���e�FUI�I�u�W�F�N�g�ꗗ�̏��������s��
=========================================== */
void SceneBase::InitUIList()
{

	using namespace DebugUI;

	// UI�폜�{�^��
	WIN_UI_LIST.AddItem(Item::CreateCallBack("Remove", Item::Kind::Command, [this](bool isWrite, void* arg)
	{
		if (m_nUISelectNo == -1) return;					// �I������Ă��Ȃ��ꍇ�͏������Ȃ�

		m_pSelectUI->SetState(UIObjectBase::E_State::STATE_DEAD);	// ���S��Ԃɐݒ�

	}));

	// UI�����{�^��
	WIN_UI_LIST.AddItem(Item::CreateCallBack("Copy", Item::Kind::Command, [this](bool isWrite, void* arg)
	{
		if (m_nUISelectNo == -1) return;	// �I������Ă��Ȃ��ꍇ�͏������Ȃ�

		UIObjectBase* pUI = m_pSelectUI->Copy();	// �I�𒆂�UI�I�u�W�F�N�g�𕡐�
	}, false, true));

	// �I�u�W�F�N�g�I�����̃R�[���o�b�N�֐�
	Item::ConstCallback  FuncListClick = [this](const void* arg)
	{
		// �N���b�N���ꂽ�I�u�W�F�N�g�̏���\��

		std::string sUIName = reinterpret_cast<const char*>(arg);
		m_nUISelectNo = ITEM_UI_LIST.GetListNo(sUIName.c_str());	// �I��ԍ����擾

		InitUIInfo(sUIName);
	};

	Item* pList = Item::CreateList(ITEM_UI_LIST_NAME.c_str(), FuncListClick, false);
	WIN_UI_LIST.AddItem(pList);
}

/* ========================================
	�E�B���h�E������(UI�I�u�W�F�N�g���)�֐�
	-------------------------------------
	���e�FUI�I�u�W�F�N�g���̏��������s��
		�@���ꗗ�̃I�u�W�F�N�g�����N���b�N����x�Ă΂��
	-------------------------------------
	�����Fstring UI�I�u�W�F�N�g��
=========================================== */
void SceneBase::InitUIInfo(std::string sName)
{
	using namespace DebugUI;

	WIN_UI_INFO.Clear();	// �\�����Z�b�g

	// ���O��"L"���܂܂�Ă���ꍇ(�q�I�u�W�F�N�g�̏ꍇ)
	if (sName.find(CHILD_HEAD_TEXT) != std::string::npos)
	{
		// "L"�������������O�ɕϊ�
		int nHeadTextCnt = sName.find(CHILD_HEAD_TEXT);							// L���܂܂��ʒu���擾
		sName = sName.substr(nHeadTextCnt + CHILD_HEAD_TEXT.size());	// L�ȍ~�̕�������擾
	}

	// ���O��"*"���܂܂�Ă���ꍇ(�e�I�u�W�F�N�g�̏ꍇ)
	if (sName.find(PARENT_END_TEXT) != std::string::npos)
	{
		// "*"�������������O�ɕϊ�
		int nEndTextCnt = sName.find(PARENT_END_TEXT);	// *���܂܂��ʒu���擾
		sName = sName.substr(0, nEndTextCnt);	// *�ȑO�̕�������擾
	}


	// ���O����v����I�u�W�F�N�g������
	for (auto& pUI : m_pUIObjects)
	{
		if (pUI->GetName() == sName)
		{
			// �I�u�W�F�N�g����\��
			pUI->Debug();
			m_pSelectUI = pUI.get();	// �I�𒆂̃I�u�W�F�N�g��ێ�

			bool bIsFold = pUI->GetIsFold() ? false : true;
			pUI->SetIsFold(bIsFold);	// �܂肽���ݏ�Ԃ�ύX

			break;
		}
	}
}


/* ========================================
	�f�o�b�O�p�I�u�W�F�N�g�ꗗ�ēǍ��֐�
	-------------------------------------
	���e�F�I�u�W�F�N�g�ꗗ���ēǂݍ��݂���
=========================================== */
void SceneBase::ReloadDebugObjectList()
{
	// �I�u�W�F�N�g�ꗗ���N���A
	ITEM_OBJ_LIST.RemoveListItemAll();

	// �I�u�W�F�N�g�𖼑O�̏����Ƀ\�[�g����(�I�u�W�F�N�g�ꗗ�����₷�����邽��)
	std::vector<ObjectBase*> pSortObjects = GetAllSceneObjects();	// �V�[���ɏ�������S�ẴI�u�W�F�N�g���擾
	std::sort(pSortObjects.begin(), pSortObjects.end(), [](const ObjectBase* a, const ObjectBase* b)
	{
		return a->GetName() < b->GetName();
	});

	// �S�ẴI�u�W�F�N�g�����X�g�ɒǉ�
	for (const auto& pObject : pSortObjects)
	{
		if (pObject->GetParentObject()) continue;	// �e�I�u�W�F�N�g������ꍇ�͔�΂�
		// �I�u�W�F�N�g�ꗗ�ɒǉ�
		ITEM_OBJ_LIST.AddListItem(pObject->GetListName().c_str());

		// �܂肽���ݏ�Ԃł͂Ȃ��ꍇ�͎q�I�u�W�F�N�g��\������
		if (!pObject->GetIsFold())
			AddObjectListChild(pObject);
	}

	// ���O�ύX��A�e�ύX�ȂǂŁA�I�u�W�F�N�g�ꗗ�̈ʒu������邽�߁A�I�𒆂̃I�u�W�F�N�g���đI������
	// �I�𒆂̃I�u�W�F�N�g������ꍇ
	if(m_pSelectObj)
	{
		int nSelectNo = ITEM_OBJ_LIST.GetListNo(m_pSelectObj->GetListName().c_str());	// �I�𒆂̃I�u�W�F�N�g�ԍ����擾

		if (m_nObjectListSelectNo != nSelectNo)
		{
			ITEM_OBJ_LIST.SetListNo(nSelectNo);		// �I�𒆂̃I�u�W�F�N�g��I����Ԃɂ���
			m_nObjectListSelectNo = nSelectNo;		// �I�𒆂̃I�u�W�F�N�g�ԍ���ێ�
		}
	}
}

/* ========================================
	�f�o�b�O�p�I�u�W�F�N�g�ꗗ�q�I�u�W�F�N�g�ǉ��֐�
	-------------------------------------
	���e�F�I�u�W�F�N�g�ꗗ�Ɏq�I�u�W�F�N�g��ǉ�
		�@���q���������ċA�I�ɌĂяo�����
	-------------------------------------
	�����FObjectBase* �e�I�u�W�F�N�g
=========================================== */
void SceneBase::AddObjectListChild(ObjectBase* pObject)
{
	// �q�I�u�W�F�N�g������ꍇ
	if (pObject->GetChildObjects().size() > 0)
	{
		if (pObject->GetIsFold()) return;	// �܂肽���ݏ�Ԃ̏ꍇ�͒ǉ����Ȃ�

		// �q�I�u�W�F�N�g�𖼑O�̏����Ƀ\�[�g����(�I�u�W�F�N�g�ꗗ�����₷�����邽��)
		std::vector<ObjectBase*> pSortChildObjects = pObject->GetChildObjects();	// �q�I�u�W�F�N�g���擾
		std::sort(pSortChildObjects.begin(), pSortChildObjects.end(), [](const ObjectBase* a, const ObjectBase* b)
		{
			return a->GetName() > b->GetName();
		});

		// �S�Ă̎q�I�u�W�F�N�g�����X�g�ɒǉ�
		for (auto& pChild : pSortChildObjects)
		{
			// �}���ʒu
			int nInsertNo = ITEM_OBJ_LIST.GetListNo(pObject->GetListName().c_str());
			// �I�u�W�F�N�g�ꗗ�ɒǉ�
			ITEM_OBJ_LIST.InsertListItem(pChild->GetListName().c_str(), nInsertNo + 1);
			// �q�I�u�W�F�N�g��ǉ�
			AddObjectListChild(pChild);	
		}
	}
	else
	{
		return;
	}
}

/* ========================================
	�f�o�b�O�pUI�I�u�W�F�N�g�ꗗ�ēǍ��֐�
	-------------------------------------
	���e�FUI�I�u�W�F�N�g�ꗗ���ēǂݍ��݂���
=========================================== */
void SceneBase::ReloadDebugUIList()
{
	// �I�u�W�F�N�g�ꗗ���N���A
	ITEM_UI_LIST.RemoveListItemAll();

	// �I�u�W�F�N�g�𖼑O�̏����Ƀ\�[�g����(�I�u�W�F�N�g�ꗗ�����₷�����邽��)
	std::vector<UIObjectBase*> pSortUIs = GetAllSceneUIObjects();	// �V�[���ɏ�������S�ẴI�u�W�F�N�g���擾
	std::sort(pSortUIs.begin(), pSortUIs.end(), [](const UIObjectBase* a, const UIObjectBase* b)
	{
		return a->GetName() < b->GetName();
	});

	// �S�Ă�UI�����X�g�ɒǉ�
	for (const auto& pUI : pSortUIs)
	{
		if (pUI->GetParentUI()) continue;	// �e�I�u�W�F�N�g������ꍇ�͔�΂�
		// �I�u�W�F�N�g�ꗗ�ɒǉ�
		ITEM_UI_LIST.AddListItem(pUI->GetListName().c_str());

		// �܂肽���ݏ�Ԃł͂Ȃ��ꍇ�͎q�I�u�W�F�N�g��\������
		if (!pUI->GetIsFold())
			AddUIListChild(pUI);
	}	
	
	// ���O�ύX��A�e�ύX�ȂǂŁA�I�u�W�F�N�g�ꗗ�̈ʒu������邽�߁A�I�𒆂̃I�u�W�F�N�g���đI������
	// �I�𒆂̃I�u�W�F�N�g������ꍇ
	if (m_pSelectUI)
	{
		int nSelectNo = ITEM_UI_LIST.GetListNo(m_pSelectUI->GetListName().c_str());	// �I�𒆂̃I�u�W�F�N�g�ԍ����擾

		if (m_nUISelectNo != nSelectNo)
		{
			ITEM_UI_LIST.SetListNo(nSelectNo);	// �I�𒆂̃I�u�W�F�N�g��I����Ԃɂ���
			m_nUISelectNo = nSelectNo;			// �I�𒆂̃I�u�W�F�N�g�ԍ���ێ�
		}
	}
}

/* ========================================
	�f�o�b�O�pUI�I�u�W�F�N�g�ꗗ�q�I�u�W�F�N�g�ǉ��֐�
	-------------------------------------
	���e�FUI�I�u�W�F�N�g�ꗗ�Ɏq�I�u�W�F�N�g��ǉ�
		�@���q���������ċA�I�ɌĂяo�����
	-------------------------------------
	�����FUIObjectBase* �eUI�I�u�W�F�N�g
=========================================== */
void SceneBase::AddUIListChild(UIObjectBase* pUIObject)
{
	// �q�I�u�W�F�N�g������ꍇ
	if (pUIObject->GetChildUIs().size() > 0)
	{
		if (pUIObject->GetIsFold()) return;	// �܂肽���ݏ�Ԃ̏ꍇ�͒ǉ����Ȃ�

		// �q�I�u�W�F�N�g�𖼑O�̏����Ƀ\�[�g����(�I�u�W�F�N�g�ꗗ�����₷�����邽��)
		std::vector<UIObjectBase*> pSortChildUIs = pUIObject->GetChildUIs();	// �q�I�u�W�F�N�g���擾
		std::sort(pSortChildUIs.begin(), pSortChildUIs.end(), [](const UIObjectBase* a, const UIObjectBase* b)
		{
			return a->GetName() > b->GetName();
		});

		// �S�Ă̎q�I�u�W�F�N�g�����X�g�ɒǉ�
		for (auto& pChild : pSortChildUIs)
		{
			// �}���ʒu
			int nInsertNo = ITEM_UI_LIST.GetListNo(pUIObject->GetListName().c_str());
			// �I�u�W�F�N�g�ꗗ�ɒǉ�
			ITEM_UI_LIST.InsertListItem(pChild->GetListName().c_str(), nInsertNo + 1);
			// �q�I�u�W�F�N�g��ǉ�
			AddUIListChild(pChild);
		}
	}
	else
	{
		return;
	}
}

#endif