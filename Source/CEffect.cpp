#include "DXUT.h"
#include "CEffect.h"


CEffect::CEffect()
{
}


CEffect::~CEffect()
{
}

void CEffect::SetEffect(string _Res, float _fDelay)
{
	GetComponent<CAnimation2D>()->AddAnimator(_Res, _Res, _fDelay, false);
	GetComponent<CAnimation2D>()->SetHandleAnimator(_Res);
}

void CEffect::Awake()
{
	AddComponent<CSpriteRenderer>()->SetRenderMode(RenderMode::RM_Billboard);
	AddComponent<CAnimation2D>();
}

void CEffect::Start()
{
}

void CEffect::Update()
{
	if (GetComponent<CAnimation2D>()->GetHandleAnimator()->GetEnable() == false)
	{
		this->m_pObject->Destroy();
	}
}

void CEffect::LateUpdate()
{
}

void CEffect::OnDestroy()
{
}

void CEffect::OnRender()
{
}

void CEffect::OnEnable()
{
}

void CEffect::OnDisable()
{
}

void CEffect::OnCollisionEnter(CObject * _pObject)
{
}

void CEffect::OnCollisionStay(CObject * _pObject)
{
}

void CEffect::OnCollisionExit(CObject * _pObject)
{
}
