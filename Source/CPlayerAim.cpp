#include "DXUT.h"
#include "CPlayerAim.h"


CPlayerAim::CPlayerAim()
{
}


CPlayerAim::~CPlayerAim()
{
}

void CPlayerAim::Hit()
{
	this->m_pHitAim->GetComponent<CSpriteRenderer>()->SetColor(D3DCOLOR_ARGB(255, 255, 255, 255));

}

void CPlayerAim::Kill()
{
	this->m_pKillAim->GetComponent<CSpriteRenderer>()->SetColor(D3DCOLOR_ARGB(255, 255, 255, 255));

}

void CPlayerAim::Awake()
{
	this->m_pCrossHairAim = OBJECT.AddObject("CrossHair", Tag::UI);
	this->m_pCrossHairAim->Transform->SetPosition(Vector3(Property::WinSize.x / 2.f, Property::WinSize.y / 2.f,0.f));
	this->m_pCrossHairAim->AddComponent<CSpriteRenderer>()->SetTexture(IMAGE["2D_PLAYER_AIM_CROSSHAIR"]);
	this->m_pCrossHairAim->GetComponent<CSpriteRenderer>()->SetRenderMode(RenderMode::RM_UI);

	this->m_pHitAim = OBJECT.AddObject("HitEffectAim", Tag::UI);
	this->m_pHitAim->Transform->SetPosition(Vector3(Property::WinSize.x / 2.f, Property::WinSize.y / 2.f, 0.f));
	this->m_pHitAim->AddComponent<CSpriteRenderer>()->SetTexture(IMAGE["2D_PLAYER_AIM_HIT"]);
	this->m_pHitAim->GetComponent<CSpriteRenderer>()->SetRenderMode(RenderMode::RM_UI);
	this->m_pHitAim->GetComponent<CSpriteRenderer>()->SetColor(D3DCOLOR_ARGB(0, 255, 255, 255));

	this->m_pKillAim = OBJECT.AddObject("HitEffectAim2", Tag::UI);
	this->m_pKillAim->Transform->SetPosition(Vector3(Property::WinSize.x / 2.f, Property::WinSize.y / 2.f, 0.f));
	this->m_pKillAim->AddComponent<CSpriteRenderer>()->SetTexture(IMAGE["2D_PLAYER_AIM_KILL"]);
	this->m_pKillAim->GetComponent<CSpriteRenderer>()->SetRenderMode(RenderMode::RM_UI);
	this->m_pKillAim->GetComponent<CSpriteRenderer>()->SetColor(D3DCOLOR_ARGB(0, 255, 255, 255));

}

void CPlayerAim::Start()
{
}

void CPlayerAim::Update()
{
	D3DXCOLOR col = this->m_pHitAim->GetComponent<CSpriteRenderer>()->GetColor();
	D3DXColorLerp(&col, &col, &D3DXCOLOR(1.f, 1.f, 1.f, 0.f), DeltaTime * 12.f);
	if (col.a  < 0.2f) col.a = 0.f;
	this->m_pHitAim->GetComponent<CSpriteRenderer>()->SetColor(col);

	D3DXCOLOR col2 = this->m_pKillAim->GetComponent<CSpriteRenderer>()->GetColor();
	D3DXColorLerp(&col2, &col2, &D3DXCOLOR(1.f, 1.f, 1.f, 0.f), DeltaTime * 8.f);
	if (col2.a < 0.2f) col2.a = 0.f;
	this->m_pKillAim->GetComponent<CSpriteRenderer>()->SetColor(col2);
}

void CPlayerAim::LateUpdate()
{
}

void CPlayerAim::OnDestroy()
{
}

void CPlayerAim::OnRender()
{

}

void CPlayerAim::OnEnable()
{
}

void CPlayerAim::OnDisable()
{
}

void CPlayerAim::OnCollisionEnter(CObject * _pObject)
{
}

void CPlayerAim::OnCollisionStay(CObject * _pObject)
{
}

void CPlayerAim::OnCollisionExit(CObject * _pObject)
{
}
