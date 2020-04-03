#include "DXUT.h"
#include "CBox.h"


CBox::CBox()
{
}


CBox::CBox(Vector3 _vCenter, Vector3 _vRadius)
	: Center(_vCenter), Radius (_vRadius), Rotation(0,0,0)
{

}

CBox::~CBox()
{
}
