#include "DXUT.h"
#include "CCircle.h"


CCircle::CCircle()
{
}

CCircle::CCircle(Vector2 _Center, float _Radius)
	: Center(_Center), Radius(_Radius)
{
}


CCircle::~CCircle()
{
}

bool CCircle::IntersectPoint(Vector2 _Point)
{
	return true;
}
bool CCircle::IntersectRect(CRect _Rect)
{
	return true;
}

bool CCircle::IntersectCircle(CCircle _Circle)
{
	return true;
}


