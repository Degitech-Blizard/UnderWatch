#include "DXUT.h"
#include "CCastle.h"


CCastle::CCastle()
{
}


CCastle::~CCastle()
{
}

void CCastle::Awake()
{
	m_pCastleUI = OBJECT.AddObject("UI", Tag::UI);
	m_pCastleUI->AddComponent<CSpriteRenderer>()->SetTexture(IMAGE["2D_CASTLE_CASTLEUI"]);
	m_pCastleUI->GetComponent<CSpriteRenderer>()->SetRenderMode(RenderMode::RM_UI);
	m_pCastleUI->Transform->SetPosition(Vector3(WinSize.x / 2.f, 85, 0.f));


	m_pCastleHPEdge = OBJECT.AddObject("UI", Tag::UI);
	m_pCastleHPEdge->AddComponent<CSpriteRenderer>()->SetTexture(IMAGE["2D_CASTLE_HPBAR_EDGE"]);
	m_pCastleHPEdge->GetComponent<CSpriteRenderer>()->SetRenderMode(RenderMode::RM_UI);
	m_pCastleHPEdge->Transform->SetPosition(Vector3(WinSize.x / 2.f + 100, 105, 0.f));

	m_pCastleHPFull = OBJECT.AddObject("UI", Tag::UI);
	m_pCastleHPFull->AddComponent<CSpriteRenderer>()->SetTexture(IMAGE["2D_CASTLE_HPBAR"]);
	m_pCastleHPFull->GetComponent<CSpriteRenderer>()->SetRenderMode(RenderMode::RM_UI);
	m_pCastleHPFull->Transform->SetPosition(Vector3(WinSize.x / 2.f + 100, 105, 0.f));

}

void CCastle::Start()
{
}

void CCastle::Update()
{
	if (INPUT.KeyPress('1'))
	{
		m_fCurHp -= 10;
	}

	m_pCastleHPFull->GetComponent<CSpriteRenderer>()->SetRect(Rect(0, 0, 483 * m_fCurHp / m_fMaxHp, 24));
}

void CCastle::LateUpdate()
{
	if (m_fCurHp <= 0)
	{
		INPUT.SetCenterFixCursor(false);
		SCENE.ChangeScene("S_GAMEOVER");
	}
}

void CCastle::OnDestroy()
{
}

void CCastle::OnRender()
{
}

void CCastle::OnEnable()
{
}

void CCastle::OnDisable()
{
}

void CCastle::OnCollisionEnter(CObject * _pObject)
{
}

void CCastle::OnCollisionStay(CObject * _pObject)
{
}

void CCastle::OnCollisionExit(CObject * _pObject)
{
}
