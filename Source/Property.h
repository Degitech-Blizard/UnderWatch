#pragma once
#include "DXUT.h"
#include "Enum.h"
namespace Property
{
	static bool		UseVSync = TRUE; // ���� ����ȭ
	static double   FPSLimit = 144;
	static WINMODE	WinMode = WINMODE::FULLSCREEN;
	static Vector2	WinSize  = Vector2(1920	,1080);
	static wstring	WinTitle = L"EmptyProject";
}

using namespace Property;