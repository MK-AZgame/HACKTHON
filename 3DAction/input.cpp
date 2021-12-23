//========================================================
//
//							����
//						AUTHIR:�z�{���V
//
//========================================================
#include "input.h"

//�}�N����`
#define NUM_KEY_MAX		(256)									//�L�[�̍ő吔

//�O���[�o���ϐ�
LPDIRECTINPUT8 g_pInput = NULL;									//DierectInput�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;						//���̓f�o�C�X�ւ̃|�C���^
BYTE g_aKeyState[NUM_KEY_MAX];									//�L�[�{�[�h�̃v���X���
BYTE g_aKeyStateTrigger[NUM_KEY_MAX];							//�L�[�{�[�h�̃g���K�[���
XINPUT_STATE g_joyKeyState;										//�W���C�p�b�h�̃v���X���
XINPUT_STATE g_joykeyStateTrigger;

//========================================================
//					�W���C�p�b�h�̏���������
//========================================================
HRESULT InitJoypad(void)
{
	//�������̃N���A
	memset(&g_joyKeyState, 0, sizeof(XINPUT_STATE));

	//xinput�̃X�e�[�g��ݒ�
	XInputEnable(true);

	return S_OK;
}

//========================================================
//				�W���C�p�b�h�̏I������
//========================================================
void UninitJoypad(void)
{
	//Xinput�̃X�e�[�g��ݒ�
	XInputEnable(false);
}

//========================================================
//					�W���C�p�b�h�̍X�V����
//========================================================
void UpdataJoypad(void)
{
	XINPUT_STATE joyKeyState;

	//�W���C�p�b�h�̏�Ԃ��擾
	if (XInputGetState(0, &joyKeyState) == ERROR_SUCCESS)
	{
		g_joykeyStateTrigger.Gamepad.wButtons = (g_joyKeyState.Gamepad.wButtons ^ joyKeyState.Gamepad.wButtons) & joyKeyState.Gamepad.wButtons;
		g_joyKeyState = joyKeyState;							//�W���C�p�b�h�̃v���X����ۑ�
	}
}

//========================================================
//				�W���C�p�b�h�̃v���X�����擾
//========================================================
bool GetJoypadPress(JOYKEY key)
{
	return (g_joyKeyState.Gamepad.wButtons & (0x01 << key)) ? true : false;
}

//========================================================
//				�W���C�p�b�h�̃g���K�[���̎擾
//========================================================
bool GetJoypadTrigger(JOYKEY key)
{
	return(g_joykeyStateTrigger.Gamepad.wButtons & (0x01 << key)) ? true : false;
}

//========================================================
//				�L�[�{�[�h�̏���������
//========================================================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	//���̓f�o�C�X�̐���
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//�������[�h�̐ݒ�
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�L�[�{�[�h�̃A�N�Z�X�����l��
	g_pDevKeyboard->Acquire();

	return S_OK;
}

//========================================================
//					�L�[�{�[�h�̏I������
//========================================================
void UninitKeyboard(void)
{
	//���̓f�o�C�X�̔j��
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();							//�A�N�Z�X���̔j��
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	//DirectInput�I�u�W�F�N�g�̔j��
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//========================================================
//					�L�[�{�[�h�̍X�V����
//========================================================
void UpdataKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];								//�L�[�{�[�h�̂̓��͏��
	int nCntKey;

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyStateTrigger[nCntKey] = (g_aKeyState[nCntKey]
				^ aKeyState[nCntKey]) & aKeyState[nCntKey];		//�g���K�[���̕ۑ�
			g_aKeyState[nCntKey] = aKeyState[nCntKey];			//�v���X���̕ۑ�
		}
	}
	else
	{
		//�A�N�Z�X���̎擾
		g_pDevKeyboard->Acquire();
	}
}

//========================================================
//					�v���X���̎擾
//========================================================
bool GetKeyboardPress(int nkey)
{
	return (g_aKeyState[nkey] & 0x80) ? true : false;
}

//========================================================
//					�g���K�[���̎擾
//========================================================
bool GetKeyboardTrigger(int nKey)
{
	return(g_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}