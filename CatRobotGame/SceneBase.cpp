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

/* ========================================
	�R���X�g���N�^�֐�
	-------------------------------------
	���e�F������
========================================== */
SceneBase::SceneBase()
	: m_bIsUpdating(false)	// �X�V���t���O��������
	, m_pObjects()			// �V�[���ɏ�������I�u�W�F�N�g�ꗗ
	, m_pStandbyObjects()	// �I�u�W�F�N�g���ꎞ�I�ɕۑ����Ă����z��
	, m_pUIObjects()		// �V�[���ɏ�������UI�I�u�W�F�N�g�ꗗ
	, m_pObjectCollision()	// �e�I�u�W�F�N�g�����Փ˔���R���|�[�l���g
#ifdef _DEBUG
	, m_pSelectObj(nullptr)	// �ꗗ�őI�𒆂̃I�u�W�F�N�g
	, m_nObjectListSelectNo(-1)
	, m_pSelectUI(nullptr)	// �ꗗ�őI�𒆂�UI�I�u�W�F�N�g
	, m_nUISelectNo(-1)
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

}

/* ========================================
	�X�V�֐�
	-------------------------------------
	���e�F�X�V����
=========================================== */
void SceneBase::Update()
{
	UpdateObject();	// �I�u�W�F�N�g�X�V
	UpdateUI();		// UI�X�V

#ifdef _DEBUG
	// ���X�g���I�����͑I���I�u�W�F�N�g���N���A
	if (m_nObjectListSelectNo == -1) m_pSelectObj = nullptr;
	// UI���X�g���I�����͑I��UI�I�u�W�F�N�g���N���A
	if (m_nUISelectNo == -1) m_pSelectUI = nullptr;

	ReloadDebugObjectList();	// �I�u�W�F�N�g���X�g�ēǂݍ���
	ReloadDebugUIList();		// UI�I�u�W�F�N�g���X�g�ēǂݍ���
#endif // _DEBUG
}

/* ========================================
	�`��֐�
	-------------------------------------
	���e�F�`�揈��
=========================================== */
void SceneBase::Draw()
{
	// �����I�u�W�F�N�g�z��̑S�v�f��`��
	for (auto& pObject : m_pObjects)
	{
		pObject->Draw();	
	}

	// ����UI�I�u�W�F�N�g�z��̑S�v�f��`��
	for (auto& pUIObject : m_pUIObjects)
	{
		pUIObject->Draw();
	}

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
	// ����UI�I�u�W�F�N�g�z��̑S�v�f���X�V
	for (auto& pObject : m_pUIObjects)
	{
		pObject->Update();
	}
	RemoveDeadUIObjects();	// ���S��Ԃ�UI�I�u�W�F�N�g���폜
	UpdateLocal();			// �ʍX�V����
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
		if (pObjectStateMap.at(pObject) == ObjectBase::E_State::STATE_DEAD)
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
{	// �V�[����UI�I�u�W�F�N�g�z��Ƀ��j�[�N�|�C���^���ړ����܂�
	m_pUIObjects.push_back(std::unique_ptr<UIObjectBase>(pUIObject));
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

	pObject->RemoveParentObject();						// �e�I�u�W�F�N�g����폜
	pObject->SetState(ObjectBase::E_State::STATE_DEAD);	// ���S��Ԃɐݒ�

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
	// ���O���d�����Ă���ꍇ�͘A�Ԃ�t����
	int nDupCnt = 0;	// �d����
	for (auto& pObject : m_pObjects)
	{
		// ���O���܂܂�Ă���ꍇ(���ɘA�Ԃ����Ă���ꍇ��z�肵��)
		if (pObject->GetName().find(sName) != std::string::npos)
		{
			nDupCnt++;
		}
	}

	if (nDupCnt > 0)
	{
		sName += "_" + std::to_string(nDupCnt);	
		return sName = CreateUniqueName(sName);	// �I�u�W�F�N�g���Əd���`�F�b�N
	}
	else
	{
		return sName;
	}

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
	// ���O���d�����Ă���ꍇ�͘A�Ԃ�t����
	int nDupCnt = 0;	// �d����
	for (auto& pUIObject : m_pUIObjects)
	{
		// ���O���܂܂�Ă���ꍇ(���ɘA�Ԃ����Ă���ꍇ��z�肵��)
		if (pUIObject->GetName().find(sName) != std::string::npos)
		{
			nDupCnt++;
		}
	}

	if (nDupCnt > 0)
	{
		sName += "_" + std::to_string(nDupCnt);
		return sName = CreateUniqueUIName(sName);	// UI�I�u�W�F�N�g���Əd���`�F�b�N
	}
	else
	{
		return sName;
	}
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

		m_pSelectObj->SetState(ObjectBase::E_State::STATE_DEAD);	// ���S��Ԃɐݒ�

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

	// �I�u�W�F�N�g�I�����̃R�[���o�b�N�֐�
	Item::ConstCallback  FuncListClick = [this](const void* arg)
	{
		// �N���b�N���ꂽ�I�u�W�F�N�g�̏���\��
		std::string sObjName = reinterpret_cast<const char*>(arg);
		m_nObjectListSelectNo = ITEM_OBJ_LIST.GetListNo(sObjName.c_str());	// �I��ԍ����擾

		InitObjectInfo(sObjName);
	};

	Item* pList = Item::CreateList(ITEM_OBJ_LIST_NAME.c_str(), FuncListClick, false, false, false, 10);
	WIN_OBJ_LIST.AddItem(pList);

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


	Item::ConstCallback  FuncListClick = [this](const void* arg) {
		// �N���b�N���ꂽ�I�u�W�F�N�g�̏���\��

		std::string sUIName = reinterpret_cast<const char*>(arg);
		m_nUISelectNo = WIN_UI_LIST[ITEM_UI_LIST_NAME.c_str()].GetListNo(sUIName.c_str());	// �I��ԍ����擾

		// ���O��"L"���܂܂�Ă���ꍇ(�q�I�u�W�F�N�g�̏ꍇ)
		if (sUIName.find(DebugUI::CHILD_HEAD_TEXT) != std::string::npos)
		{
			// "L"�������������O�ɕϊ�
			int nHeadTextCnt = sUIName.find(DebugUI::CHILD_HEAD_TEXT);
			sUIName = sUIName.substr(nHeadTextCnt + DebugUI::CHILD_HEAD_TEXT.size());
		}

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

	// ���O����v����I�u�W�F�N�g������
	for (auto& pUI : m_pUIObjects)
	{
		if (pUI->GetName() == sName)
		{
			// �I�u�W�F�N�g����\��
			pUI->Debug();
			m_pSelectUI = pUI.get();	// �I�𒆂̃I�u�W�F�N�g��ێ�
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
	WIN_UI_LIST[ITEM_UI_LIST_NAME.c_str()].RemoveListItemAll();

	// �V�[���ɏ�������S�ẴI�u�W�F�N�g���擾
	for (const auto& pUI : m_pUIObjects)
	{
		if (pUI->GetParentUI()) continue;	// �e�I�u�W�F�N�g������ꍇ�͔�΂�
		// �I�u�W�F�N�g�ꗗ�ɒǉ�
		ITEM_UI_LIST.AddListItem(pUI->GetName().c_str());
		AddUIListChild(pUI.get());
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
		for (auto& pChild : pUIObject->GetChildUIs())
		{
			// �}���ʒu
			int nInsertNo = WIN_UI_LIST[ITEM_UI_LIST_NAME.c_str()].GetListNo(pUIObject->GetListName().c_str());
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