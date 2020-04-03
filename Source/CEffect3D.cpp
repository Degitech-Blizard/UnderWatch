#include "DXUT.h"
#include "CEffect3D.h"


CEffect3D::CEffect3D()
{
}


CEffect3D::~CEffect3D()
{
}

void CEffect3D::SetEffect(string _Res, float _fDelay)
{
	GetComponent<CAnimation3D>()->AddAnimator(_Res, _Res, _fDelay, false);
	GetComponent<CAnimation3D>()->SetHandleAnimator(_Res);
}

void CEffect3D::Awake()
{
	AddComponent<CMeshRenderer>();
	AddComponent<CAnimation3D>();
}

void CEffect3D::Start()
{
}

void CEffect3D::Update()
{
	if (GetComponent<CAnimation3D>()->GetHandleAnimator()->GetEnable() == false)
	{
		this->m_pObject->Destroy();
	}
}

void CEffect3D::LateUpdate()
{
}

void CEffect3D::OnDestroy()
{
}

void CEffect3D::OnRender()
{
}

void CEffect3D::OnEnable()
{
}

void CEffect3D::OnDisable()
{
}

void CEffect3D::OnCollisionEnter(CObject * _pObject)
{
}

void CEffect3D::OnCollisionStay(CObject * _pObject)
{
}

void CEffect3D::OnCollisionExit(CObject * _pObject)
{
}
