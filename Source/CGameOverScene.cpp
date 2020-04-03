#include "DXUT.h"
#include "CGameOverScene.h"


CGameOverScene::CGameOverScene()
{
}


CGameOverScene::~CGameOverScene()
{
}

void CGameOverScene::Init()
{
	auto Background = OBJECT.AddObject();
	Background->AddComponent<CSpriteRenderer>()->SetTexture(IMAGE["2D_GAMEOVER_AIM_BACKGORUND"]);
	Background->GetComponent<CSpriteRenderer>()->SetRenderMode(RenderMode::RM_UI);
	Background->Transform->SetPosition(Vector3(WinSize.x / 2.f, WinSize.y / 2.f, 0.f));

	auto Retry = OBJECT.AddObject();
	Retry->AddComponent<CSpriteRenderer>()->SetTexture(IMAGE["2D_GAMEOVER_AIM_RETRY"]);
	Retry->AddComponent<CButton>()->SetType(ButtonType::BT_COLORING);
	Retry->GetComponent<CButton>()->SetOnClickFunc([&]() {SCENE.ChangeScene("S_MAIN"); });
	Retry->GetComponent<CSpriteRenderer>()->SetRenderMode(RenderMode::RM_UI);
	Retry->Transform->SetPosition(Vector3(WinSize.x / 2.f , WinSize.y / 2.f + 100, 0.f));
	Retry->GetComponent<CButton>()->SetRect(Retry->GetComponent<CSpriteRenderer>()->GetRect());

	auto Exit = OBJECT.AddObject();
	Exit->AddComponent<CSpriteRenderer>()->SetTexture(IMAGE["2D_GAMEOVER_AIM_EXIT"]);
	Exit->AddComponent<CButton>()->SetType(ButtonType::BT_COLORING);
	Exit->GetComponent<CButton>()->SetOnClickFunc([&]() {PostQuitMessage(0); });
	Exit->GetComponent<CSpriteRenderer>()->SetRenderMode(RenderMode::RM_UI);
	Exit->Transform->SetPosition(Vector3(WinSize.x / 2.f , WinSize.y / 2.f + 250, 0.f));
	Exit->GetComponent<CButton>()->SetRect(Exit->GetComponent<CSpriteRenderer>()->GetRect());

	INPUT.SetCenterFixCursor(false);


}

void CGameOverScene::Update()
{
}

void CGameOverScene::Render()
{
	IMAGE.ReBegin(RenderMode::RM_UI);
	TCHAR Msg[100];
	swprintf(Msg, L"SCORE : %d", SCENE.m_iScore);
	IMAGE.PrintText(Msg, Vector2(WinSize.x / 2.f, WinSize.y / 2.f + 400), 160, 0, false, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CGameOverScene::Release()
{
}
