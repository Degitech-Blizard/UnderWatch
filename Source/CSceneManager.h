#pragma once
#include "CSingleton.h"
class CScene;
class CSceneManager :
	public CSingleton< CSceneManager>
{
	friend class CMainGame;
public:
	CSceneManager();
	~CSceneManager();

public:
	CScene * AddScene(CRString _Key, CScene*_pScene);
	CScene * ChangeScene(CRString _Key);
	CRString GetCurrentScene();
	map<string, CScene*> m_mapScene;
	int m_iScore;
private:
	void Update();

	void Render();
	CScene * m_pCurScene = nullptr;
	CScene * m_pNextScene = nullptr;
	
};

#define SCENE (*CSceneManager::GetInstance())