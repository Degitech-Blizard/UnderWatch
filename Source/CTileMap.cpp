#include "DXUT.h"
#include "CTileMap.h"


CTileMap::CTileMap()
{
}


CTileMap::~CTileMap()
{
}



void CTileMap::Awake()
{
	for (int i = 0; i < 250; i++)
	{
		for (int j = 0; j < 250; j++)
		{

			m_pTilePool[make_tuple(j, 0, i)] = OBJECT.AddObject("MAP", Tag::Map);

			m_pTilePool[make_tuple(j, 0, i)]->AddComponent<CMeshRenderer>()->SetModel(MODEL["BOX"]);
			m_pTilePool[make_tuple(j, 0, i)]->Transform->SetScale(Vector3(1, 1, 1));
			m_pTilePool[make_tuple(j, 0, i)]->Transform->SetPosition(Vector3(j * 32, 0, i * 32));
			//	m_pTilePool[make_tuple(j, 0, i)]->AddComponent<CBoxCollider3D>()->SetBox(Box(m_pTilePool[make_tuple(j, 0, i)]->Transform->GetPosition(), Vector3(16, 16, 16)));
		}
	}
}

void CTileMap::Start()
{
}

void CTileMap::Update()
{
	//DEBUG_LOG("%d", m_pTilePool.size());
}

void CTileMap::LateUpdate()
{
}

void CTileMap::OnDestroy()
{
}

void CTileMap::OnRender()
{
}

void CTileMap::OnEnable()
{
}

void CTileMap::OnDisable()
{
}


void CTileMap::OnCollisionEnter(CObject * _pObject)
{
}

void CTileMap::OnCollisionStay(CObject * _pObject)
{
}

void CTileMap::OnCollisionExit(CObject * _pObject)
{
}
