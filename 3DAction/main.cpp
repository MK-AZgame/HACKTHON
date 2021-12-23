//===============================================================================================
//
//�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@	 3DGame
//�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@Author:�z�{���V
//
//===============================================================================================
#include "main.h"
#include "light.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "wall.h"
#include "billboard.h"
#include "meshfield.h"
#include "meshcylinder.h"
#include "sphere.h"
#include "bullet.h"
#include "effect.h"
#include "player.h"
#include "line.h"
#include "model.h"

//�}�N����`
#define CLASS_NAME		 "WindowsClass"								//�E�B���h�E�N���X�̖��O
#define Window_NAME		 "3DGame"									//�E�B���h�E�̖��O

//�v���g�^�C�v�錾
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

//�O���[�o���ϐ�
LPDIRECT3D9          g_pD3D = NULL;									//Direct3D�I�u�W�F�N�g�̃|�C���^
LPDIRECT3DDEVICE9    g_pD3DDevice = NULL;							//Direct3D�f�o�C�X�ւ̃|�C���^
MODE g_mode = MODE_TITLE;											//���݂̃��[�h

//===============================================================================================
//									���C���֐�
//===============================================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstanceprev, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),											//WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC,													//�E�B���h�E�̃X�^�C��
		WindowProc,													//�E�B���h�E�v���V�[�W��
		0,															//
		0,															//
		hInstance,													//�C���X�^���X�n���h��
		LoadIcon(NULL,IDI_APPLICATION),								//�^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL,IDC_ARROW),									//�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),									//�N���C�A���g�̈�̔w�i�F
		NULL,														//���j���[�o�[
		CLASS_NAME,													//�E�B���h�E�N���X�̖��O
		LoadIcon(NULL,IDI_APPLICATION)								//�t�@�C���̃A�C�R��
	};

	HWND hWnd;														//�E�B���h�E�n���h��
	MSG msg;														//���b�Z�[�W�̊i�[

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };					//��ʂ̃T�C�Y

	//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//�E�B���h�E�𐶐�
	hWnd = CreateWindowEx(0,										//�g���E�B���h�E�X�^�C��
		CLASS_NAME,													//�E�B���h�E�N���X�̖��O
		Window_NAME,												//�E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,										//�E�B���h�E�X�^�C��
		CW_USEDEFAULT,												//�E�B���h�E�̍���X���W
		CW_USEDEFAULT,												//�E�B���h�E�̍���Y���W
		(rect.right - rect.left),									//�E�B���h�E�̕�
		(rect.bottom - rect.top),									//�E�B���h�E�̍���
		NULL,														//�e�E�B���h�E�̃n���h��
		NULL,														//���j���[�n���h�����͎q�E�B���h�EID
		hInstance,													//�C���X�^���X�n���h��
		NULL);														//�E�B���h�E�쐬�f�[�^

	DWORD dwCurrentTime;											//���ݎ���
	DWORD dwExecLastTime;											//�Ō�ɏ�����������

																	//����������
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{//�����������s�����ꍇ
		return -1;
	}

	//����\��ݒ�
	timeBeginPeriod(1);
	dwCurrentTime = 0;												//����������
	dwExecLastTime = timeGetTime();									//���ݎ����̎擾

	//�E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);										//�E�B���h�E�̕\����Ԃ̐ݒ�
	UpdateWindow(hWnd);												//�N���C�A���g�̈���X�V

	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//Windows�̏���
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				//���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);								//���z���b�Z�[�W�𕶎����b�Z�[�W�֕ϊ�
				DispatchMessage(&msg);								//�E�B���h�E�v���V�[�W���փ��b�Z�[�W�𑗏o
			}
		}
		else
		{//DirectX�̏���
			dwCurrentTime = timeGetTime();							//���ݎ������擾

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{//60����1�b�o��
				dwExecLastTime = dwCurrentTime;						//�����J�n������ۑ�

				//�X�V����
				Update();

				//�`�揈��
				Draw();
			}
		}
	}

	//�I������
	Uninit();

	//����\��߂�
	timeEndPeriod(1);

	//�E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return(int)msg.wParam;
}

//===============================================================================================
//									�E�B���h�E�v���V�[�W��
//===============================================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;														//�Ԃ�l���i�[
	const RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };			//�E�B���h�E�̗̈�

	switch (uMsg)
	{
	case WM_DESTROY:
		//WM_QUIT���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:												//�L�[�����̃��b�Z�[�W
		switch (wParam)
		{
		case VK_ESCAPE:												//[ESC]�L�[�������ꂽ
			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO|MB_TOPMOST);

			if (nID == IDYES)
			{
				//�E�B���h�E��j������(WM_DESTOROY���b�Z�[�W�𑗂�j
				DestroyWindow(hWnd);
			}
			break;
		}
		break;

	case WM_CLOSE:													//����{�^�������̃��b�Z�[�W
		nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);

		if (nID == IDYES)
		{
			//�E�B���h�E��j������(WM_DESTOROY���b�Z�[�W�𑗂�j
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;
		}
		break;

	case WM_LBUTTONDOWN:											//�}�E�X���N���b�N�̃��b�Z�[�W
																	//�E�B���h�E�Ƀt�H�[�J�X�����킹��
		SetFocus(hWnd);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);				//����̏�����Ԃ�
}

//===============================================================================================
//									����������
//===============================================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;											//�f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;									//�v���[���e�[�V�����p�����[�^

																	//Direct3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//���݂̃f�B�X�v���C���[�h���擾
	if (g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm))
	{
		return E_FAIL;
	}

	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));								//�p�����[�^�̃[���N���A

	d3dpp.BackBufferWidth = SCREEN_WIDTH;							//�Q�[����ʃT�C�Y�i���j
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;							//�Q�[����ʃT�C�Y�i�����j
	d3dpp.BackBufferFormat = d3ddm.Format;							//�o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;										//�o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						//�_�u���o�b�t�@�̐؂�ւ�
	d3dpp.EnableAutoDepthStencil = TRUE;							//�f�v�X�o�b�t�@�ƃX�e���V���o�b�t�@���`��
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;						//�f�v�X�o�b�t�@�Ƃ��ĂP�Ubit���g��
	d3dpp.Windowed = bWindow;										//�E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		//���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		//�C���^�[�o��

																	//Direct3D�f�o�C�X�̐����i�`�揈���ƒ��_�������n�[�h�E�F�A�ōs���j
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		//Direct3D�f�o�C�X�̐����i�`�揈���̓n�[�h�E�F�A�A���_������CPU�ōs���j
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			//Direct3D�f�o�C�X�̐���(�`�揈���ƒ��_������CPU�ōs��)
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//�����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�T���v���[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
	
	//���C���[�t���[��
	//g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	//�L�[�{�[�h�̏�����
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	////�e��I�u�W�F�N�g�̏���������
	////�T�E���h�̏�����
	//InitSound(hWnd);
	////�t�F�[�h�̏�����
	//InitFade(g_mode);
	InitMeshfield();
	InitShadow();
	InitModel();
	InitPlayer();
	InitBillboard();
	InitCamera();
	InitLight();
	InitWall();
	InitMeshCylinder();
	InitSphere();
	Initbullet();
	InitEffect();
	InitLine();

	return S_OK;
}

//===============================================================================================
//									�I������
//===============================================================================================
void Uninit(void)
{
	////�e��I�u�W�F�N�g�̏I������
	UninitMeshfield();
	UninitPlayer();
	UninitLight();
	UninitCamera();
	UninitShadow();
	UninitWall();
	UninitBillboard();
	UninitMeshCylinder();
	UninitSphere();
	Uninitbullet();
	UninitEffect();
	UninitModel();
	UninitLine();
	////�t�F�[�h�̏I��
	//UninitFade();
	////�^�C�g����ʂ̏I��
	//UninitTitle();
	////�Q�[����ʂ̏I��
	//UninitGame();
	////���U���g��ʂ̏I��
	//UninitResult();
	////�`���[�g���A���̏I��
	//UninitTutorial();
	////�����L���O���I��
	//UninitRanking();
	////�T�E���h�̏I������
	//UninitSound();
	//�L�[�{�[�h�̏I��
	UninitKeyboard();
	////�W���C�p�b�h�̏I������
	//UninitJoypad();

	//Direct3D�f�o�C�X�̔j��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}
	//Direct3D�I�u�W�F�N�g�̔j��
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//===============================================================================================
//									�X�V����
//===============================================================================================
void Update(void)
{
	UpdataMeshfield();
	UpdataPlayer();
	UpdataCamera();
	UpdataShadow();
	UpdataLight();
	UpdataWall();
	UpdataBillboard();
	UpdataMeshCylinder();
	UpdataSphere();
	Updatabullet();
	UpdataEffect();
	UpdataModel();
	UpdataLine();

	//�L�[�{�[�h�̍X�V
	UpdataKeyboard();
	////�W���C�p�b�h�̍X�V����
	//UpdataJoypad();
	////�e��I�u�W�F�N�g�̍X�V����
	//switch (g_mode)
	//{
	//case MODE_TITLE:
	//	UpdataTitle();
	//	break;
	//case MODE_GAME:
	//	UpdataGame();
	//	break;
	//case MODE_RESULT:
	//	UpdataResult();
	//	break;
	//case MODE_TUTORIAL:
	//	UpdataTutorial();
	//	break;
	/*case MODE_RANKING:
		UpdataRanking();
		break;*/

	////�t�F�[�h�̍X�V
	//UpdataFade();
}

//===============================================================================================
//									�`�揈��
//===============================================================================================
void Draw(void)
{
	//��ʃN���A
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//�`��J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//�`��J�n�����������ꍇ
	 //�e��I�u�W�F�N�g�̕`�揈��
		//DrawPolygon();
		DrawMeshfield();
		DrawWall();
		DrawBillboard();
		DrawPlayer();
		SetCamera();
		DrawShadow();
		DrawMeshCylinder();
		DrawSphere();
		Drawbullet();
		DrawEffect();
		DrawModel();
		DrawLine();
		
		//switch (g_mode)
		//{
		//case MODE_TITLE:
		//	DrawTitle();
		//	break;
		//case MODE_GAME:
		//	DrawGame();
		//	break;
		//case MODE_RESULT:
		//	DrawResult();
		//	break;
		//case MODE_TUTORIAL:
		//	DrawTutorial();
		//	break;
		///*case MODE_RANKING:
		//	DrawRanking();
		//	break;*/

		////�t�F�[�h�̕`��
		//DrawFade();

		//�`��I��
		g_pD3DDevice->EndScene();
	}
	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//================================================================================================
//									���[�h�̐ݒ�
//================================================================================================
void SetMode(MODE mode)
{
	//���݂̃��[�h�̏I������
	/*switch (g_mode)
	{
	case MODE_TITLE:
		UninitTitle();
		break;
	case MODE_GAME:
		UninitGame();
		break;
	case MODE_RESULT:
		UninitResult();
		break;
	case MODE_TUTORIAL:
		UninitTutorial();
		break;*/
	/*case MODE_RANKING:
		UninitRanking();
		break;*/
	//}

	////�V������ʂ̏���������
	//switch (mode)
	//{
	//case MODE_TITLE:
	//	InitTitle();
	//	break;
	//case MODE_GAME:
	//	InitGame();
	//	break;
	//case MODE_RESULT:
	//	InitResult();
	//	break;
	//case MODE_TUTORIAL:
	//	InitTutorial();
	//	break;
	/*case MODE_RANKING:
		InitRanking();
		break;*/
	/*}

	g_mode = mode;*/
}

//==============================================================================================
//									�f�o�C�X�̎擾
//==============================================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}