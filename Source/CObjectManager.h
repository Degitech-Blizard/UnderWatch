#pragma once
#include "CSingleton.h"




class CObjectManager :
	public CSingleton<CObjectManager>
{
	friend class CMainGame;
	friend class CPhysic;
public:
	CObjectManager();
	~CObjectManager();
public:
	list<CObject*> listObject;
	int m_iSplitCount; // 컨테이너 하나당 List가 가지고있을 개수 
	list<CObject *> m_ObjectList;
	list<CRenderer3D *> m_listRender3D;
	list<CCollider2D*> m_listCollider2D;
	list<CCollider3D*> m_listCollider3D;
	map<SortingLayer, list<CRenderer2D * >> m_SortedRenderer2DList;

	map<ObjectTag, set<ObjectTag>> m_mapCollisionDetectlist;

	CFrameSkip m_CollisionTimer;

public:
	list<CObject *> GetCotainObject(Vector3 _vPos, float Range);
	list<CObject *> GetCotainObject(Vector3 _vPos, float Range, Tag _Tag);
	void RegisterRenderer2D(CRenderer2D * _pRenderer2D);
	void UnRegisterRenderer2D(CRenderer2D * _pRenderer2D);

	void RegisterRenderer3D(CRenderer3D * _pRenderer3D);
	void UnRegisterRenderer3D(CRenderer3D * _pRenderer3D);

	void RegisterCollider2D(CCollider2D * _pCollider2D);
	void UnRegisterCollider2D(CCollider2D * _pCollider2D);

	void RegisterCollider3D(CCollider3D * _pCollider3D);
	void UnRegisterCollider3D(CCollider3D * _pCollider3D);

	void ClearAllObjects();
	void DeleteCollisionDetect(ObjectTag Tag1, ObjectTag Tag2);

	CObject * FindObjectWithName(CRString _Name);
	list<CObject *> FindObjectsWithName(CRString _Name);
	CObject * FindObjectWithTag(ObjectTag _Tag);
	list<CObject *> FindObjectsWithTags(ObjectTag _Tag);

	CObject * AddObject(CRString _ObjectName = "GameObject",ObjectTag _ObjectTag = Untagged)  // 디폴트 파라미터
	{
		CObject * pObject = new CObject();
		
		pObject->Transform = pObject->AddComponent<CTransform>();
		pObject->m_Tag = _ObjectTag;
		pObject->m_iDepth = 0;
		pObject->m_Name = _ObjectName;
		pObject->Init();
		m_ObjectList.push_back(pObject);
		return pObject;
	}

	

	
private:
	void Update();
	void Render();

};

#define OBJECT (*CObjectManager::GetInstance())