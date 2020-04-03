#include "DXUT.h"
#include "CMainScene.h"
#include "CTileMap.h"
#include "CPlayer.h"
#include "CGun.h"
#include "CEnemy01.h"
#include "CMonsterSpawner.h"
#include "CPlayerAim.h"
#include "CPlayerHPbar.h"
#include "CPlayerUltimate.h"
#include "CCastle.h"
#include "CPlayerSkill.h"


CMainScene::CMainScene()
{
	
}


CMainScene::~CMainScene()
{
}

void CMainScene::Init()
{
	CAMERA.SetSkyBox(new CSkyBox(
		IMAGE["2D_SKYBOX_UP"], 
		IMAGE["2D_SKYBOX_DN"], 
		IMAGE["2D_SKYBOX_LF"], 
		IMAGE["2D_SKYBOX_RT"], 
		IMAGE["2D_SKYBOX_FT"], 
		IMAGE["2D_SKYBOX_BK"]));

	SCENE.m_iScore = 0;
	ShowCursor(false);
	INPUT.SetCenterFixCursor(true);

	OBJECT.DeleteCollisionDetect(Tag::Untagged, Tag::Map);
	OBJECT.DeleteCollisionDetect(Tag::Untagged, Tag::Enemy);
	OBJECT.DeleteCollisionDetect(Tag::Untagged, Tag::Player);
	OBJECT.DeleteCollisionDetect(Tag::Untagged, Tag::PlayerBullet);
	OBJECT.DeleteCollisionDetect(Tag::Untagged, Tag::EnemyBullet);

	OBJECT.DeleteCollisionDetect(Tag::Map, Tag::Map);
	OBJECT.DeleteCollisionDetect(Tag::Enemy, Tag::Enemy);
	OBJECT.DeleteCollisionDetect(Tag::Enemy, Tag::Player);
	OBJECT.DeleteCollisionDetect(Tag::PlayerBullet, Tag::Map);
	OBJECT.DeleteCollisionDetect(Tag::Player, Tag::PlayerBullet);
	OBJECT.DeleteCollisionDetect(Tag::PlayerBullet, Tag::PlayerBullet);
	OBJECT.DeleteCollisionDetect(Tag::Enemy, Tag::EnemyBullet);
	OBJECT.DeleteCollisionDetect(Tag::EnemyBullet, Tag::EnemyBullet);
	SOUND.Play("SND_MAIN_BG2", FALSE);

	
	//auto TestTilemap = OBJECT.AddObject();
	//TestTilemap->AddComponent<CTileMap>();

	//auto Map = OBJECT.AddObject("Map");
	//Map->Transform->SetPosition(Vector3(0, 0, 0));
	//Map->AddComponent<CMeshRenderer>()->SetModel(MODEL["TREE_01"]);
	//auto mapcollision = OBJECT.AddObject();
	//mapcollision->AddComponent<CBoxCollider3D>()->SetBox(Box(Vector3(10,10,10),Vector3(1,1,1))

	INPUT.SetCenterFixCursor(true);
	auto Gun = OBJECT.AddObject("Gun", Tag::Fall);
	Gun->AddComponent<CGun>();

	auto Player = OBJECT.AddObject("Player",Tag::Player);
	Player->AddComponent<CPlayer>();

	auto Aim = OBJECT.AddObject("Aim");
	Aim->AddComponent<CPlayerAim>();

	auto PlayerHPbar = OBJECT.AddObject();
	m_pPlayerHPbar = PlayerHPbar->AddComponent<CPlayerHPbar>();
	
	auto PlayerUltimate = OBJECT.AddObject();
	m_pPlayerUltimate = PlayerUltimate->AddComponent<CPlayerUltimate>();

	auto MAP = OBJECT.AddObject();
	MAP->AddComponent<CMeshRenderer>()->SetModel(MODEL["3D_MAP"]);

	auto Castle = OBJECT.AddObject("Castle");
	Castle->AddComponent<CCastle>();
	//ULTIMATEUI->Transform->SetPosition(Vector3(WinSize.x / 2.f, WinSize.y - 100, 0.f));

	auto PlayerSkill = OBJECT.AddObject("PlayerSkill");
	PlayerSkill->AddComponent<CPlayerSkill>();


	auto Spawner = OBJECT.AddObject();
	m_iPhase =  &Spawner->AddComponent<CMonsterSpawner>() ->m_iPhase;
	

	for (int i = 0; i < 20; i++)
	{
		auto Sphere = OBJECT.AddObject("Collider", Tag::Collider);
		Sphere->Transform->SetPosition(Vector3(-2200, 120, 500 + (i * 120)));
	
		Sphere->AddComponent<CSphereCollider3D>()->SetSphere(CSphere(Sphere->Transform->GetPosition(), 100.f));
	}
	for (int i = 0; i < 25; i++)
	{
		auto Sphere = OBJECT.AddObject("Collider", Tag::Collider);
		Sphere->Transform->SetPosition(Vector3(700 - (i * 120), 120, 2830));
		Sphere->AddComponent<CSphereCollider3D>()->SetSphere(CSphere(Sphere->Transform->GetPosition(), 100.f));
	}
	for (int i = 0; i < 2; i++)
	{
		auto Sphere = OBJECT.AddObject("Collider", Tag::Collider);
		Sphere->Transform->SetPosition(Vector3(870, 120, 2800 - (i * 120)));
		Sphere->AddComponent<CSphereCollider3D>()->SetSphere(CSphere(Sphere->Transform->GetPosition(), 100.f));
	}
	for (int i = 0; i < 8; i++)
	{
		auto Sphere = OBJECT.AddObject("Collider", Tag::Collider);
		Sphere->Transform->SetPosition(Vector3(980 + (i * 120), 120, 2620));
		Sphere->AddComponent<CSphereCollider3D>()->SetSphere(CSphere(Sphere->Transform->GetPosition(), 100.f));
	}


}

void CMainScene::Update()
{
}

void CMainScene::Render()
{
	m_pPlayerHPbar->OnRender();
	m_pPlayerUltimate->OnRender();
	IMAGE.ReBegin(RenderMode::RM_UI);
	TCHAR Msg[100];
	swprintf(Msg, L"SCORE : %d", SCENE.m_iScore);
	IMAGE.PrintText(Msg, Vector2(100, 50), 80, 0, false, D3DCOLOR_ARGB(255, 255, 255, 255));

	IMAGE.ReBegin(RenderMode::RM_UI);
	TCHAR Msg2[100];
	swprintf(Msg2, L"WAVE : %d", *m_iPhase);
	IMAGE.PrintText(Msg2, Vector2(100, 100), 80, 0, false, D3DCOLOR_ARGB(255, 255, 255, 255));

	IMAGE.ReBegin(RenderMode::RM_UI);
	TCHAR Msg3[100];
	swprintf(Msg3, L"FPS : %.f", TIME.m_fFPS);
	IMAGE.PrintText(Msg3, Vector2(100, 0), 80, 0, false, D3DCOLOR_ARGB(255, 255, 255, 255));



	//IMAGE.ReBegin(RenderMode::RM_UI);
	//TCHAR Msg3[100];
	//swprintf(Msg3, L"X : %.f Y : %.f Z : %.f", OBJECT.FindObjectWithTag(Tag::Player)->Transform->GetPosition().x, OBJECT.FindObjectWithTag(Tag::Player)->Transform->GetPosition().y, OBJECT.FindObjectWithTag(Tag::Player)->Transform->GetPosition().z);
	//IMAGE.PrintText(Msg3, Vector2(100, 150), 80, 0, false, D3DCOLOR_ARGB(255, 255, 255, 255));
	//if (INPUT.KeyDown('2'))
	//{
	//	wprintf(L"%s", Msg3);
	//}
}

void CMainScene::Release()
{
	ShowCursor(true);
}
