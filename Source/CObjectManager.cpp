#include "DXUT.h"
#include "CObjectManager.h"
#include <omp.h>
CObjectManager::CObjectManager()
	: m_iSplitCount(25000)
{
	for (INT i = ObjectTag::Start; i < ObjectTag::End; i++)
	{
		set<ObjectTag> list; 

		for (INT j = ObjectTag::Start; j < ObjectTag::End; j++)
		{
			list.insert((ObjectTag)j);
		}
		m_mapCollisionDetectlist[(ObjectTag)i] = list;
	}
	m_CollisionTimer.SetFramePerSec(60);

}


CObjectManager::~CObjectManager()
{
	for (auto& iter : m_ObjectList)
	{
		iter->Release();
		SAFE_DELETE(iter);
	}
	m_ObjectList.clear();
}



list<CObject*> CObjectManager::GetCotainObject(Vector3 _vPos, float Range)
{
	list<CObject*> listObject = this->m_ObjectList;
	
	for (auto iter : listObject)
	{
		float distance = abs(D3DXVec3Length(&(iter->Transform->GetPosition() - _vPos)));
		if (distance > Range) listObject.remove(iter);
	}
	
	return listObject;
}

list<CObject*> CObjectManager::GetCotainObject(Vector3 _vPos, float Range, Tag _Tag)
{
	list<CObject*> resultObjectList;

	for (auto iter : m_ObjectList)
	{
		float distance = abs(D3DXVec3Length(&(iter->Transform->GetPosition() - _vPos)));
		if (distance < Range && iter->m_Tag == _Tag)
			resultObjectList.push_back(iter);
		else
			continue;
	}

	return resultObjectList;
}

void CObjectManager::RegisterRenderer2D(CRenderer2D * _pRenderer2D)
{
	m_SortedRenderer2DList[_pRenderer2D->m_SortingLayer].push_back(_pRenderer2D);

	for (auto iter : m_SortedRenderer2DList)
	{
		iter.second.sort([&](CRenderer2D *  pPrev, CRenderer2D *  pNext)->bool { return pPrev->m_iOrderInLayer < pNext->m_iOrderInLayer; });
	}
}

void CObjectManager::UnRegisterRenderer2D(CRenderer2D * _pRenderer2D)
{
	m_SortedRenderer2DList[_pRenderer2D->m_SortingLayer].remove(_pRenderer2D);
}

void CObjectManager::RegisterRenderer3D(CRenderer3D * _pRenderer3D)
{
	m_listRender3D.push_back(_pRenderer3D);
}

void CObjectManager::UnRegisterRenderer3D(CRenderer3D * _pRenderer3D)
{
	m_listRender3D.remove(_pRenderer3D);
}

void CObjectManager::RegisterCollider2D(CCollider2D * _pCollider2D)
{
	m_listCollider2D.push_back(_pCollider2D);
}

void CObjectManager::UnRegisterCollider2D(CCollider2D * _pCollider2D)
{
	m_listCollider2D.remove(_pCollider2D);
}

void CObjectManager::RegisterCollider3D(CCollider3D * _pCollider3D)
{
	m_listCollider3D.push_back(_pCollider3D);
}

void CObjectManager::UnRegisterCollider3D(CCollider3D * _pCollider3D)
{
	for (auto iter : m_listCollider3D)
	{
			auto find = iter->m_listCollision.find(_pCollider3D);
			if (iter->m_listCollision.end() != find)
				iter->m_listCollision.erase(find);
	}
	
	m_listCollider3D.remove(_pCollider3D);
}



void CObjectManager::ClearAllObjects()
{
	for (auto& iter : m_ObjectList)
	{
		if(iter->GetIsStatic())
		{
			for (auto iter2 : iter->m_listChild)
			{
				iter2->SetIsStatic(true);
			}
		}

	}


	
	for (auto& iter : m_ObjectList)
	{
		if (!iter->GetIsStatic())
		{
			iter->Destroy();
		}
	}
}

void CObjectManager::DeleteCollisionDetect(ObjectTag Tag1, ObjectTag Tag2)
{
	auto find1 = m_mapCollisionDetectlist[Tag1].find(Tag2);
		
	if(find1 != m_mapCollisionDetectlist[Tag1].end())
		m_mapCollisionDetectlist[Tag1].erase(find1);
	
	auto find2 = m_mapCollisionDetectlist[Tag2].find(Tag1);

	if (find2 != m_mapCollisionDetectlist[Tag2].end())
		m_mapCollisionDetectlist[Tag2].erase(find2);
}

CObject * CObjectManager::FindObjectWithName(CRString _Name)
{
	CObject * Find = nullptr;
	for (auto iter : m_ObjectList)
	{
			if (iter->GetName() == _Name)
			{
				Find = iter;
				return Find;
			}
	}
	return Find;
	//for (auto& iter : m_Objects)
	//{
	//	if (iter->GetName() == _Name)
	//	{
	//		return iter;
	//	}
	//}
	//return nullptr;
}

list<CObject*> CObjectManager::FindObjectsWithName(CRString _Name)
{
	list<CObject*> listFind;

	for (auto& iter : m_ObjectList)
	{
		if (iter->GetName() == _Name)
		{
			listFind.push_back(iter);
		}
	}
	return listFind;
}

CObject * CObjectManager::FindObjectWithTag(ObjectTag _Tag)
{
	for (auto iter : m_ObjectList)
	{
			if (iter->GetObjectTag() == _Tag)
			{
				return iter;
			}	
	}
	return nullptr;
}

list<CObject*> CObjectManager::FindObjectsWithTags(ObjectTag _Tag)
{
	list<CObject*> listFind;

	for (auto& iter : m_ObjectList)
	{
		if (iter->GetObjectTag() == _Tag)
		{
			listFind.push_back(iter);
		}
	}
	return listFind;
}


void CObjectManager::Update()
{	

		for (auto& iter = m_ObjectList.begin(); iter != m_ObjectList.end(); iter++)
		{
			CObject * pObj = (*iter);
			{
				pObj->Update();

				for (auto& iter : pObj->GetComponents())
				{
					if (iter->m_bStart == FALSE)
					{
						iter->m_bStart = TRUE;
						iter->Start();
					}
					if (iter->GetIsEnable())
					{
						iter->Update();
					}
				}
			}
		}

#pragma region LateUpdate
	for (auto& iter = m_ObjectList.begin(); iter != m_ObjectList.end(); iter++)
		{
			CObject * pObj = (*iter);


			for (auto& iter : pObj->GetComponents())
			{
				if (iter->GetIsEnable())
				{
					iter->LateUpdate();
				}
			}
		}
#pragma endregion

	if(m_CollisionTimer.Update(DeltaTime))
	{

			for (auto& iter = m_listCollider3D.begin(); iter != m_listCollider3D.end(); iter++)
			{
				if (*iter == nullptr) continue;
				auto Collider01 = (*iter);

				if (Collider01->GetIsEnable() != false)
				{
					bool bIsCollide = FALSE;


					for (auto& iter2 = std::next(iter, 1); iter2 != m_listCollider3D.end(); iter2++)
					{
						if (*iter2 == nullptr) continue;
						if (m_mapCollisionDetectlist[(*iter)->m_pObject->GetObjectTag()].find((*iter2)->m_pObject->GetObjectTag()) == m_mapCollisionDetectlist[(*iter)->m_pObject->GetObjectTag()].end())
						{
							continue;
						}

						auto Collider02 = (*iter2);


						if (Collider02->GetIsEnable() == false) continue;


						bIsCollide = false;

						float Length = GetLength(Vector3((*iter)->Transform->m_vPosition), Vector3((*iter2)->Transform->m_vPosition));
						float w1, w2, h1, h2, d1, d2;
						switch (Collider01->m_Type)
						{
						case Collider3D_Type::SPHERE:
							w1 = ((CSphereCollider3D*)Collider01)->GetSphere().Radius;
							h1 = ((CSphereCollider3D*)Collider01)->GetSphere().Radius;
							d1 = ((CSphereCollider3D*)Collider01)->GetSphere().Radius;
							break;
						case Collider3D_Type::OBB:
							w1 = ((CBoxCollider3D*)Collider01)->GetBox().Radius.x;
							h1 = ((CBoxCollider3D*)Collider01)->GetBox().Radius.y;
							d1 = ((CBoxCollider3D*)Collider01)->GetBox().Radius.z;
							break;
						}

						switch (Collider02->m_Type)
						{
						case Collider3D_Type::SPHERE:
							w2 = ((CSphereCollider3D*)Collider02)->GetSphere().Radius;
							h2 = ((CSphereCollider3D*)Collider02)->GetSphere().Radius;
							d2 = ((CSphereCollider3D*)Collider02)->GetSphere().Radius;
							break;
						case Collider3D_Type::OBB:
							w2 = ((CBoxCollider3D*)Collider02)->GetBox().Radius.x;
							h2 = ((CBoxCollider3D*)Collider02)->GetBox().Radius.y;
							d2 = ((CBoxCollider3D*)Collider02)->GetBox().Radius.z;
							break;
						}

						float long2 = w2 > h2 ? w2 : h2;


						if (Length < (w1 + h1 + d1) + (w2 + h2 + d2))
						{
							switch (Collider01->m_Type)
							{
							case Collider3D_Type::SPHERE:
								switch (Collider02->m_Type)
								{
								case Collider3D_Type::SPHERE:

									bIsCollide = (Physic.CheckCollision(
										((CSphereCollider3D*)Collider01)->GetSphere(),
										((CSphereCollider3D*)Collider02)->GetSphere()));
									break;
								case Collider3D_Type::OBB:
									bIsCollide = (Physic.CheckCollision(
										((CBoxCollider3D*)Collider02)->GetBox(), Collider02->Transform->GetRotation(),
										((CSphereCollider3D*)Collider01)->GetSphere()));
									break;
								}
								break;
							case Collider3D_Type::OBB:
								switch (Collider02->m_Type)
								{
								case Collider3D_Type::SPHERE:

									bIsCollide = (Physic.CheckCollision(
										((CBoxCollider3D*)Collider01)->GetBox(), Collider01->Transform->GetRotation(),
										((CSphereCollider3D*)Collider02)->GetSphere()));
									break;
								case Collider3D_Type::OBB:
									bIsCollide = (Physic.CheckCollision(
										((CBoxCollider3D*)Collider01)->GetBox(), Collider01->Transform->GetRotation(),
										((CBoxCollider3D*)Collider02)->GetBox(), Collider02->Transform->GetRotation()));
									break;
								}
								break;
							}



						}
						else continue;
						auto& Collisionlist = (*iter)->m_listCollision;

						auto& find = Collisionlist.find((*iter2));

						if (find == Collisionlist.end())
						{
							if (bIsCollide == true)
							{
								Collisionlist.insert(*iter2);
								for (auto iter3 : (*iter)->m_pObject->GetComponents())
								{
									iter3->OnCollisionEnter((*iter2)->m_pObject);
								}
								for (auto iter4 : (*iter2)->m_pObject->GetComponents())
								{
									iter4->OnCollisionEnter((*iter)->m_pObject);
								}
							}
						}
						if (find != Collisionlist.end())
						{
							if (bIsCollide == true)
							{
								for (auto iter3 : (*iter)->m_pObject->GetComponents())
								{
									iter3->OnCollisionStay((*iter2)->m_pObject);
								}
								for (auto iter4 : (*iter2)->m_pObject->GetComponents())
								{
									iter4->OnCollisionStay((*iter)->m_pObject);
								}
							}
							if (bIsCollide == false)
							{
								for (auto iter3 : (*iter)->m_pObject->GetComponents())
								{
									iter3->OnCollisionExit((*iter2)->m_pObject);
								}
								for (auto iter4 : (*iter2)->m_pObject->GetComponents())
								{
									iter4->OnCollisionExit((*iter)->m_pObject);
								}
								Collisionlist.erase(find);
							}
						}
					}
				}

			}
	}

	for (auto iter = m_ObjectList.begin(); iter != m_ObjectList.end(); )
	{
		//BoxCollider 컴포넌트를 사용하는 오브젝트들은 충돌 검사를 진행하게 됩니다.
	//CollisionProcessing(*iter);
	// 오브젝트가 파괴되었다면
		if (TRUE == (*iter)->m_bDestroy)
		{
		//	DEBUG_LOG("Object Destroyed : %s", (*iter)->GetName().c_str());
			(*iter)->Release();
			SAFE_DELETE((*iter));
			iter = m_ObjectList.erase(iter);
		}
		else iter++;
	}
#pragma endregion

}


void CObjectManager::Render()
{
	for (auto& iter : m_listRender3D)
	{
		if(iter->m_bIsEnable)
		iter->Render();
	}
	IMAGE.End();

	RenderMode Mode = RenderMode::RM_Normal;
	IMAGE.Begin(RenderMode::RM_Normal);
	for (auto iter : m_SortedRenderer2DList)
	{
	
		
		for (auto iter2 : iter.second)
		{
			if (iter2->GetIsEnable())
			{
				if (iter2->GetRenderMode() != Mode)
				{
					Mode = iter2->GetRenderMode();
					IMAGE.ReBegin(Mode);
				}
				for (auto iter3 : iter2->m_pObject->GetComponents())
				{
					iter3->OnRender();
				}
				iter2->Render();
			}
		}
	}
	IMAGE.End();
	IMAGE.Begin(Mode);

}

