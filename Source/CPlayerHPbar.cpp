#include "DXUT.h"
#include "CPlayerHPbar.h"


CPlayerHPbar::CPlayerHPbar()
{
}


CPlayerHPbar::~CPlayerHPbar()
{
}

void CPlayerHPbar::Awake()
{
	this->m_pPlayerStatus = OBJECT.AddObject();
	this->m_pPlayerStatus->AddComponent<CSpriteRenderer>()->SetTexture(IMAGE["2D_PLAYER_STATUS"]);
	this->m_pPlayerStatus->GetComponent<CSpriteRenderer>()->SetRenderMode(RenderMode::RM_UI);
	this->m_pPlayerStatus->Transform->SetPosition(Vector3(300, WinSize.y - 100, 0.f));

	this->m_pHPbarEdge = OBJECT.AddObject();
	this->m_pHPbarEdge->AddComponent<CSpriteRenderer>()->SetTexture(IMAGE["2D_PLAYER_HPBAR_EMPTY"]);
	this->m_pHPbarEdge->GetComponent<CSpriteRenderer>()->SetRenderMode(RenderMode::RM_UI);
	this->m_pHPbarEdge->Transform->SetPosition(Vector3(400, WinSize.y - 80, 0.f));

	this->m_pHPbarFull = OBJECT.AddObject();
	this->m_pHPbarFull->AddComponent<CSpriteRenderer>()->SetTexture(IMAGE["2D_PLAYER_HPBAR_FILL"]);
	this->m_pHPbarFull->GetComponent<CSpriteRenderer>()->SetRenderMode(RenderMode::RM_UI);
	this->m_pHPbarFull->Transform->SetPosition(Vector3(400, WinSize.y - 80, 0.f));
}

void CPlayerHPbar::Start()
{
	this->m_pPlayer = OBJECT.FindObjectWithTag(Tag::Player)->GetComponent<CPlayer>();
}

void CPlayerHPbar::Update()
{
}

void CPlayerHPbar::LateUpdate()
{

	int MaxHp, CurHp;
	MaxHp = m_pPlayer->m_fMaxHp;
	CurHp = m_pPlayer->m_fCurHp;

	m_pHPbarFull->GetComponent<CSpriteRenderer>()->SetRect(Rect(0, 0, 227 * CurHp / MaxHp, 38));
}

void CPlayerHPbar::OnDestroy()
{
}

void CPlayerHPbar::OnRender()

{
	if (m_pPlayer)
	{
		IMAGE.ReBegin(RenderMode::RM_UI);
		TCHAR Msg[100];
		swprintf(Msg, L"%.f", m_pPlayer->m_fCurHp);
		IMAGE.PrintText(Msg, Vector2(330, WinSize.y - 100), 80, 0, true, D3DCOLOR_ARGB(255, 255, 255, 255));

		TCHAR Msg2[100];
		swprintf(Msg2, L"%.f", m_pPlayer->m_fMaxHp);
		IMAGE.PrintText(Msg2, Vector2(410, WinSize.y - 100), 80, 0, true, D3DCOLOR_ARGB(255, 255, 255, 255));

	}
}

void CPlayerHPbar::OnEnable()
{
}

void CPlayerHPbar::OnDisable()
{
}

void CPlayerHPbar::OnCollisionEnter(CObject * _pObject)
{
}

void CPlayerHPbar::OnCollisionStay(CObject * _pObject)
{
}

void CPlayerHPbar::OnCollisionExit(CObject * _pObject)
{
}
