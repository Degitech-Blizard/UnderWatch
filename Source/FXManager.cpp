#include "DXUT.h"
#include "FXManager.h"


FXManager::FXManager()
{
	DWORD dwShaderFlags = D3DXFX_NOT_CLONEABLE;

	LPD3DXBUFFER errBuffer;

	if (FAILED(D3DXCreateEffectFromFile(g_Device, L"./Shader/OutlineShader.fx", NULL, NULL, dwShaderFlags,

		NULL, &g_pShader, &errBuffer)))

	{

		MessageBoxA(DXUTGetHWND(), (LPCSTR)errBuffer->GetBufferPointer(), "ERROR", MB_OK);

		SAFE_RELEASE(errBuffer);
	}
}


FXManager::~FXManager()
{
	SAFE_RELEASE(g_pShader);
}
