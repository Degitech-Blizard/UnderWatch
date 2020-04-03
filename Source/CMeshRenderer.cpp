#include "DXUT.h"
#include "CMeshRenderer.h"


CMeshRenderer::CMeshRenderer()
{
	OBJECT.RegisterRenderer3D(this);
}


CMeshRenderer::~CMeshRenderer()
{
	OBJECT.UnRegisterRenderer3D(this);
}

void CMeshRenderer::Awake()
{
}

void CMeshRenderer::Start()
{
}

void CMeshRenderer::Update()
{
}

void CMeshRenderer::LateUpdate()
{
}

void CMeshRenderer::Render()
{
	if (this->m_pModel && this->GetIsEnable())
	{
		Matrix matWorld;
		matWorld = IMAGE.GetWorldMatrix(this->m_pObject->Transform);
		auto handle = this->m_pObject;
		while (handle->m_pParent != nullptr)
		{
			handle = handle->m_pParent;
			matWorld *= IMAGE.GetWorldMatrix(handle->Transform);
		}
		MODEL.Render(this->m_pModel, matWorld);
	}
}

void CMeshRenderer::OnRender()
{
}

void CMeshRenderer::OnDestroy()
{
}

void CMeshRenderer::OnEnable()
{
}

void CMeshRenderer::OnDisable()
{
}


void CMeshRenderer::OnCollisionEnter(CObject * _pObject)
{
}

void CMeshRenderer::OnCollisionStay(CObject * _pObject)
{
}

void CMeshRenderer::OnCollisionExit(CObject * _pObject)
{
}
