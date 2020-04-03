#include "DXUT.h"
#include "CLineRenerer.h"


CLineRenerer::CLineRenerer()
{
	OBJECT.RegisterRenderer2D(this);

}


CLineRenerer::~CLineRenerer()
{
	OBJECT.UnRegisterRenderer2D(this);

}


void CLineRenerer::Awake()
{
}

void CLineRenerer::Start()
{
}

void CLineRenerer::Update()
{
}

void CLineRenerer::LateUpdate()
{
}

void CLineRenerer::Render()
{
}

void CLineRenerer::OnRender()
{
}

void CLineRenerer::OnDestroy()
{
}

void CLineRenerer::OnEnable()
{
}

void CLineRenerer::OnDisable()
{
}

void CLineRenerer::OnCollisionEnter(CObject * _pObject)
{
}

void CLineRenerer::OnCollisionStay(CObject * _pObject)
{
}

void CLineRenerer::OnCollisionExit(CObject * _pObject)
{
}
