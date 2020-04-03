#pragma once
#include "CSingleton.h"
class CPhysic
	: public CSingleton<CPhysic>
{
public:
	CPhysic();
	~CPhysic(); 

public:
	bool GetPixelCollision(CTexture * _pTexture, CRRect _Box, D3DXCOLOR _Color = D3DXCOLOR(1.f,1.f,1.f,1.f));

	bool GetPixelCollision(CTexture * _pTexture, CRVector2 _Pos, D3DXCOLOR _Color = D3DXCOLOR(1.f, 1.f, 1.f, 1.f));

	bool CheckCollision(const Circle& _Circle01, const Circle& _Circle02);

	bool CheckCollision(const Circle& _Circle01, const Vector2& _vPos);

	bool CheckCollision(const Rect& _reRect, const Vector2& _vPos);

	bool CheckCollision(const Vector2& _vPos, const Rect& _reRect);

	bool CheckCollision(const Rect& _reRect01, const Rect& _reRect02);

	bool CheckCollision(const Rect& _reRect01, float _fRot01, const Rect& _reRect02, float _fRot02);

	bool CheckCollision(const Box& _Box01, Vector3 _vRot01, const Box& _Box02, Vector3 _vRot02);

	bool CheckCollision( Box _Box01, Vector3 _fRot01, const Sphere& _Sphere);

	bool CheckCollision(Sphere _Sphere01, Sphere _Sphere02);
	
	bool CheckCollision(CRay _Ray, Sphere _Sphere, Vector3& _vIntersect = Vector3(0.f,0.f,0.f));

	bool CheckCollision(CRay _Ray, Box _Box,Vector3 _vRotation = Vector3(0,0,0), Vector3& _vIntersect = Vector3(0.f, 0.f, 0.f));
	
	CRaycastHit  RayCast(CRay _Ray);
	CRaycastHit  RayCast(CRay _Ray,ObjectTag _Tag);
	list<CRaycastHit > RayCastAll(CRay _Ray);
	list<CRaycastHit > RayCastAll(CRay _Ray, ObjectTag _Tag);
	//bool CheckCollision(const Box& _Box, float _fRot01, const Box& _Box02, float _fRot02);

//	bool CheckCollision()
};

#define Physic (*CPhysic::GetInstance())
 
