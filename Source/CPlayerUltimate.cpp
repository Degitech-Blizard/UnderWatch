#include "DXUT.h"
#include "CPlayerUltimate.h"


CPlayerUltimate::CPlayerUltimate()
{
}


CPlayerUltimate::~CPlayerUltimate()
{
}

void CPlayerUltimate::Awake()
{
	m_pUltimateUI = OBJECT.AddObject();
	m_pUltimateUI->AddComponent<CSpriteRenderer>()->SetTexture(IMAGE["2D_PLAYER_ULTIMATE_GAUGE"]);
	m_pUltimateUI->GetComponent<CSpriteRenderer>()->SetRenderMode(RenderMode::RM_UI);
	m_pUltimateUI->Transform->SetPosition(Vector3(WinSize.x / 2.f, WinSize.y - 100, 0.f));

	m_pUltimateBackground = OBJECT.AddObject();
	m_pUltimateBackground->AddComponent<CSpriteRenderer>()->SetTexture(IMAGE["2D_PLAYER_ULTIMATE_BACKGROUND"]);
	m_pUltimateBackground->GetComponent<CSpriteRenderer>()->SetRenderMode(RenderMode::RM_UI);
	m_pUltimateBackground->Transform->SetPosition(Vector3(WinSize.x / 2.f, WinSize.y /2.f, 0.f));
	m_pUltimateBackground->GetComponent<CSpriteRenderer>()->SetIsEnable(false);

	m_pUltimateDuractionMax = OBJECT.AddObject();
	m_pUltimateDuractionMax->AddComponent<CSpriteRenderer>()->SetTexture(IMAGE["2D_PLAYER_ULTIMATE_DURACTION_GAUGE_MAX"]);
	m_pUltimateDuractionMax->GetComponent<CSpriteRenderer>()->SetRenderMode(RenderMode::RM_UI);
	m_pUltimateDuractionMax->Transform->SetPosition(Vector3(WinSize.x / 2.f, WinSize.y - 300, 0.f));
	m_pUltimateDuractionMax->GetComponent<CSpriteRenderer>()->SetIsEnable(false);

	m_pUltimateDuractionEdge = OBJECT.AddObject();
	m_pUltimateDuractionEdge->AddComponent<CSpriteRenderer>()->SetTexture(IMAGE["2D_PLAYER_ULTIMATE_DURACTION_GAUGE"]);
	m_pUltimateDuractionEdge->GetComponent<CSpriteRenderer>()->SetRenderMode(RenderMode::RM_UI);
	m_pUltimateDuractionEdge->Transform->SetPosition(Vector3(WinSize.x / 2.f, WinSize.y - 300, 0.f));
	m_pUltimateDuractionEdge->GetComponent<CSpriteRenderer>()->SetIsEnable(false);
}

void CPlayerUltimate::Start()
{
	this->m_pPlayer = OBJECT.FindObjectWithTag(Tag::Player)->GetComponent<CPlayer>();


}

void CPlayerUltimate::Update()
{
	if (m_pPlayer->m_bUltimateEnable)
	{
		m_pUltimateUI->GetComponent<CSpriteRenderer>()->SetTexture(IMAGE["2D_PLAYER_ULTIMATE_GAUGE_MAX"]);
		m_pUltimateBackground->GetComponent<CSpriteRenderer>()->SetIsEnable(true);
		m_pUltimateDuractionMax->GetComponent<CSpriteRenderer>()->SetIsEnable(true);
		m_pUltimateDuractionEdge->GetComponent<CSpriteRenderer>()->SetIsEnable(true);

		m_pUltimateDuractionMax->GetComponent<CSpriteRenderer>()->SetRect(Rect(0, 0, 286 * m_pPlayer->m_fUltimateDuraction / 12.f, 22));

		m_pUltimateDuractionMax->GetComponent<CSpriteRenderer>()->SetRenderMode(RenderMode::RM_UI);

	}
	else
	{
		m_pUltimateUI->GetComponent<CSpriteRenderer>()->SetTexture(IMAGE["2D_PLAYER_ULTIMATE_GAUGE"]);
		m_pUltimateBackground->GetComponent<CSpriteRenderer>()->SetIsEnable(false);
		m_pUltimateDuractionMax->GetComponent<CSpriteRenderer>()->SetIsEnable(false);
		m_pUltimateDuractionEdge->GetComponent<CSpriteRenderer>()->SetIsEnable(false);
		if (m_pPlayer->m_fCurUltimate >= m_pPlayer->m_fMaxUltimate)
		{
			m_pUltimateUI->GetComponent<CSpriteRenderer>()->SetTexture(IMAGE["2D_PLAYER_ULTIMATE_GAUGE_MAX"]);

		}
		else m_pUltimateUI->GetComponent<CSpriteRenderer>()->SetTexture(IMAGE["2D_PLAYER_ULTIMATE_GAUGE"]);

	}
}

void CPlayerUltimate::LateUpdate()
{
}

void CPlayerUltimate::OnDestroy()
{
}

void CPlayerUltimate::OnRender()
{
	if (m_pPlayer )
	{
		if (!m_pPlayer->m_bUltimateEnable && m_pPlayer->m_fCurUltimate < m_pPlayer->m_fMaxUltimate)
		{
			IMAGE.ReBegin(RenderMode::RM_UI);
			TCHAR Msg[100];
			swprintf(Msg, L"%d", (int)((m_pPlayer->m_fCurUltimate / m_pPlayer->m_fMaxUltimate) * 100));
			IMAGE.PrintText(Msg, Vector2(WinSize.x / 2.f+20, WinSize.y - 80), 100, 0, true, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}
}

void CPlayerUltimate::OnEnable()
{
}

void CPlayerUltimate::OnDisable()
{
}

void CPlayerUltimate::OnCollisionEnter(CObject * _pObject)
{
}

void CPlayerUltimate::OnCollisionStay(CObject * _pObject)
{
}

void CPlayerUltimate::OnCollisionExit(CObject * _pObject)
{
}
