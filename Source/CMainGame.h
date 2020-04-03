#pragma once
class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void Init();
	void Update();
	void Render();
	void Release();

	void OnResetDevice();
	void OnLostDevice();

	float m_fTime = 0;
	float m_fFPS = 0;
};

