#include "DXUT.h"
#include "CLoadScene.h"

#include "CMainGame.h"
#include "CMainScene.h"
#include "CGameOverScene.h"


CMainGame::CMainGame()
{

}


CMainGame::~CMainGame()
{
}

void CMainGame::Init()
{
	SCENE.AddScene("S_LOADING", new CLoadScene());

	SCENE.AddScene("S_MAIN", new CMainScene());

	SCENE.AddScene("S_GAMEOVER", new CGameOverScene());

	SCENE.ChangeScene("S_LOADING");

}

void CMainGame::Update()
{
	//TESK.EnqueueJob([&]()->void {INPUT.Update(); });



	 OBJECT.Update();
	//OBJECT.Update();
	
	CAMERA.Update();
	INPUT.Update();

	//TESK.EnqueueJob([&]()->void {	TIME.Update(); });

	TIME.Update();
	//if(SCENE.m_pCurScene == SCENE.m_mapScene["S_LOADING"])SCENE.Update();
	//else TESK.EnqueueJob([&]()->void {	SCENE.Update(); });

	SCENE.Update();
	//TESK.EnqueueJob([&]()->void {	SOUND.Update(); });

	SOUND.Update();

	if (INPUT.KeyDown('1'))
	{
		SCENE.ChangeScene("S_GAMEOVER");
	}
	if (INPUT.KeyDown('2'))
	{

	}
	if (INPUT.KeyDown('3'))
	{

	}
	m_fTime += DeltaTime;
	m_fFPS += 1.f;
	if (m_fTime > 1.f)
	{
		m_fTime -= 1.f;
		printf("%.f", m_fFPS);
		m_fFPS = 0.f;
	}
}

void CMainGame::Render()
{
	
	CAMERA.SetTransform();
	CAMERA.Render();
	IMAGE.Begin(RenderMode::RM_Normal);

	OBJECT.Render();
	
	SCENE.Render();

	IMAGE.End();



}

void CMainGame::Release()
{
	CThreadPool::ReleaseInstance();
	CPhysic::ReleaseInstance();
	CInputManager::ReleaseInstance();
	CImageManager::ReleaseInstance();
	CObjectManager::ReleaseInstance();
	CSceneManager::ReleaseInstance();
	CTimeManager::ReleaseInstance();
	CCameraManager::ReleaseInstance();
	CSoundManager::ReleaseInstance();
	CModelManager::ReleaseInstance();
	FXManager::ReleaseInstance();
}

void CMainGame::OnResetDevice()
{
	IMAGE.OnResetDevice();
}

void CMainGame::OnLostDevice()
{
	IMAGE.OnLostDevice();
}
