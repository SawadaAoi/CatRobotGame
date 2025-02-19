/* ========================================
	DX22Base/
	------------------------------------
	�t�@�C�������Ǘ��pcpp
	------------------------------------
	FileManager.cpp
========================================== */

// =============== �C���N���[�h ===================
#include "FileManager.h"
// �t�@�C�������p
#include <iostream>		
#include <fstream>		

#include "SceneManager.h"
#include "SceneBase.h"
#include "ObjectBase.h"

#include "ComponentTransform.h"
#include "ObjectTypeRegistry.h"

#include "UIComponentTransform.h"
#include "UIComponentSprite.h"
#include "UITypeRegistry.h"

#include <unordered_map>	// �e�q�֌W�̐ݒ�p
#include "TextureManager.h"

/* ========================================
	�t�@�C���o��(�V�[���I�u�W�F�N�g)�֐�
	-------------------------------------
	���e�F�I�u�W�F�N�g�̏����t�@�C���ɏo�͂���
	-------------------------------------
	����1�F�t�@�C���p�X
========================================== */
void FileManager::StageObjectOutput(std::string sPath)
{
	// �t�@�C�����J��
	std::ofstream file(sPath, std::ios::out | std::ios::binary);

	if (!file.is_open())
	{
		std::cout << "�t�@�C�����J���܂���ł���" << std::endl;
		return;
	}

	// �V�[���ɑ��݂���I�u�W�F�N�g���擾
	for (auto& object : SceneManager::GetScene()->GetAllSceneObjects())
	{
		S_SaveDataObject data;

		// �I�u�W�F�N�g�̏����擾 ---------------------------------
		// �N���X��
		strncpy(data.cClassType, object->GetObjClassName().c_str(), sizeof(data.cClassType) - 1);
		data.cClassType[sizeof(data.cClassType) - 1] = '\0';

		// �ʒu�A��]�A�g��
		ComponentTransform* pTransform = object->GetComponent<ComponentTransform>();
		data.vPos	= pTransform->GetPosition();
		data.qRot	= pTransform->GetRotation();
		data.vScale = pTransform->GetScale();

		// �I�u�W�F�N�g��
		strncpy(data.cObjectName, object->GetName().c_str(), sizeof(data.cObjectName) - 1);
		data.cObjectName[sizeof(data.cObjectName) - 1] = '\0';

		// �e�I�u�W�F�N�g��
		ObjectBase* pParent = object->GetParentObject();
		if (pParent)
		{
			strncpy(data.cParentName, pParent->GetName().c_str(), sizeof(data.cParentName) - 1);
			data.cParentName[sizeof(data.cParentName) - 1] = '\0';
		}
		else
		{
			data.cParentName[0] = '\0';	// �e�I�u�W�F�N�g�����Ȃ��ꍇ�͋󕶎�
		}

		// �t�@�C���ɏ�������
		file.write((char*)&data, sizeof(S_SaveDataObject));
		// �I�u�W�F�N�g�ʂ̃f�[�^�o��
		object->OutPutLocalData(file);	
	}

	file.close();
}

/* ========================================
	�t�@�C������(�V�[���I�u�W�F�N�g)�֐�
	-------------------------------------
	���e�F�t�@�C������I�u�W�F�N�g�̏���ǂݍ���
	-------------------------------------
	����1�F�t�@�C���p�X
========================================== */
void FileManager::StageObjectInput(std::string sPath)
{
	// �e�I�u�W�F�N�g�̃}�b�v
	std::unordered_map<ObjectBase*, std::string> mapObjectParent;

	// �t�@�C�����J��
	std::ifstream file(sPath, std::ios::in | std::ios::binary);

	if (!file.is_open())
	{
		std::cout << "�t�@�C�����J���܂���ł���" << std::endl;
		return;
	}

	SceneBase* pScene = SceneManager::GetScene();	// �V�[���擾

	// �t�@�C���̏I�[�܂œǂݍ���
	while (!file.eof())
	{
		S_SaveDataObject data;
		file.read((char*)&data, sizeof(S_SaveDataObject));

		// �t�@�C���̏I�[�ɓ��B������I��
		if (file.eof())
		{
			break;
		}

		// �I�u�W�F�N�g�̐���(�n�����N���X�����琶��)
		ObjectBase* pObject = OBJ_TYPE_REGISTRY_INST.CreateObject(data.cClassType);

		if (pObject)
		{
			pObject->Init(pScene->CreateUniqueName(data.cObjectName));	// �I�u�W�F�N�g������(���O�d��������)

			// �ʒu�A��]�A�g��̐ݒ�
			ComponentTransform* pTransform = pObject->GetComponent<ComponentTransform>();
			pTransform->SetPosition(data.vPos);
			pTransform->SetRotation(data.qRot);
			pTransform->SetScale(data.vScale);

			// �V�[���ɒǉ�
			pScene->AddSceneObjectBase(pObject);
			// �I�u�W�F�N�g�ʂ̃f�[�^����
			pObject->InputLocalData(file);
			// �e�I�u�W�F�N�g�}�b�v�ɒǉ�
			mapObjectParent[pObject] = data.cParentName;
		}
	}

	// �e�q�֌W�̐ݒ�
	for (auto& object : mapObjectParent)
	{
		std::string sParentName = object.second;
		// �e�I�u�W�F�N�g�����Ȃ��ꍇ�̓X�L�b�v
		if (sParentName.empty()) continue;
		// �e�I�u�W�F�N�g�擾
		ObjectBase* pParent = pScene->FindSceneObject(sParentName);

		// �e�I�u�W�F�N�g�����݂��Ă�����e�q�֌W��ݒ�
		if (pParent)
		{
			object.first->SetParentObject(pParent);
		}
	}

	file.close();

}

/* ========================================
	�t�@�C���o��(�V�[��UI�I�u�W�F�N�g)�֐�
	-------------------------------------
	���e�FUI�I�u�W�F�N�g�̏����t�@�C���ɏo�͂���
	-------------------------------------
	����1�F�t�@�C���p�X
========================================== */
void FileManager::UIOutput(std::string sPath)
{
	// �t�@�C�����J��
	std::ofstream file(sPath, std::ios::out | std::ios::binary);

	if (!file.is_open())
	{
		std::cout << "�t�@�C�����J���܂���ł���" << std::endl;
		return;
	}

	// �V�[���ɑ��݂���I�u�W�F�N�g���擾
	for (auto& uiObj : SceneManager::GetScene()->GetAllSceneUIObjects())
	{
		S_SaveDataUI data;

		// �I�u�W�F�N�g�̏����擾 ---------------------------------
		// �N���X��
		strncpy(data.cClassType, uiObj->GetUIClassName().c_str(), sizeof(data.cClassType) - 1);
		data.cClassType[sizeof(data.cClassType) - 1] = '\0';

		// �ʒu�A��]�A�g��
		UIComponentTransform* pTransform = uiObj->GetComponent<UIComponentTransform>();
		data.vPos = pTransform->GetPosition();
		data.fRot = pTransform->GetRotation();
		data.vScale = pTransform->GetScale();

		UIComponentSprite* pSprite = uiObj->GetComponent<UIComponentSprite>();
		// �e�N�X�`��ID
		data.nTextureID = TEXTURE_MNG_INST.GetTextureKey(pSprite->GetTexture());
		// �\���t���O
		data.bIsVisible = pSprite->GetIsVisible();
		// �`��D��x
		data.nDrawPriority = uiObj->GetDrawPriority();

		// �I�u�W�F�N�g��
		strncpy(data.cUIName, uiObj->GetName().c_str(), sizeof(data.cUIName) - 1);
		data.cUIName[sizeof(data.cUIName) - 1] = '\0';

		// �e�I�u�W�F�N�g��
		UIObjectBase* pParent = uiObj->GetParentUI();
		if (pParent)
		{
			strncpy(data.cParentName, pParent->GetName().c_str(), sizeof(data.cParentName) - 1);
			data.cParentName[sizeof(data.cParentName) - 1] = '\0';
		}
		else
		{
			data.cParentName[0] = '\0';	// �e�I�u�W�F�N�g�����Ȃ��ꍇ�͋󕶎�
		}

		// �t�@�C���ɏ�������
		file.write((char*)&data, sizeof(S_SaveDataUI));
		// UI�ʂ̃f�[�^�o��
		uiObj->OutPutLocalData(file);
	}

	file.close();
}

/* ========================================
	�t�@�C������(�V�[��UI�I�u�W�F�N�g)�֐�
	-------------------------------------
	���e�F�t�@�C������UI�I�u�W�F�N�g�̏���ǂݍ���
	-------------------------------------
	����1�F�t�@�C���p�X
========================================== */
void FileManager::UIInput(std::string sPath)
{
	// �eUI�̃}�b�v
	std::unordered_map<UIObjectBase*, std::string> mapUIParent;

	// �t�@�C�����J��
	std::ifstream file(sPath, std::ios::in | std::ios::binary);

	if (!file.is_open())
	{
		std::cout << "�t�@�C�����J���܂���ł���" << std::endl;
		return;
	}

	SceneBase* pScene = SceneManager::GetScene();	// �V�[���擾

	// �t�@�C���̏I�[�܂œǂݍ���
	while (!file.eof())
	{
		S_SaveDataUI data;
		file.read((char*)&data, sizeof(S_SaveDataUI));

		// �t�@�C���̏I�[�ɓ��B������I��
		if (file.eof())
		{
			break;
		}

		// �I�u�W�F�N�g�̐���(�n�����N���X�����琶��)
		UIObjectBase* pUI = UI_TYPE_REGISTRY_INST.CreateUI(data.cClassType);

		if (pUI)
		{
			pUI->Init(pScene->CreateUniqueUIName(data.cUIName));	// �I�u�W�F�N�g������(���O�d��������)

			// �ʒu�A��]�A�g��̐ݒ�
			UIComponentTransform* pTransform = pUI->GetComponent<UIComponentTransform>();
			pTransform->SetPosition(data.vPos);
			pTransform->SetRotation(data.fRot);
			pTransform->SetScale(data.vScale);

			// �e�N�X�`���̐ݒ�
			UIComponentSprite* pSprite = pUI->GetComponent<UIComponentSprite>();
			// �e�N�X�`���ݒ�
			pSprite->SetTexture(GET_TEXTURE_DATA((TextureManager::E_TEX_KEY)data.nTextureID));
			// �e�N�X�`���\���t���O�ݒ�
			pSprite->SetIsVisible(data.bIsVisible);
			// �`��D��x�ݒ�
			pUI->SetDrawPriority(data.nDrawPriority);

			// �V�[���ɒǉ�
			pScene->AddSceneUI(pUI);
			// UI�ʂ̃f�[�^����
			pUI->InputLocalData(file);
			// �eUI�}�b�v�ɒǉ�
			mapUIParent[pUI] = data.cParentName;
		}
	}

	// �e�q�֌W�̐ݒ�
	for (auto& uiParent : mapUIParent)
	{
		std::string sParentName = uiParent.second;
		// �eUI�����Ȃ��ꍇ�̓X�L�b�v
		if (sParentName.empty()) continue;
		// �eUI�擾
		UIObjectBase* pParent = pScene->FindSceneUI(sParentName);

		// �eUI�����݂��Ă�����e�q�֌W��ݒ�
		if (pParent)
		{
			uiParent.first->SetParentUI(pParent);
		}
	}


	file.close();
}
