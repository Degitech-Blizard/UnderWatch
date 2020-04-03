#pragma once
#include "CSingleton.h"
class FXManager :
	public CSingleton< FXManager>
{
public:
	FXManager();
	~FXManager();

	Shader * g_pShader;
};

//#define FXMANAGER (*FXManager::GetInstance())
#define FX (*FXManager::GetInstance()).g_pShader