#include "..\Include\CCamera.h"



CCamera::CCamera()
{
}


CCamera::~CCamera()
{
}

void CCamera::move(float deltaX, float deltaY)
{
	float values[3];
	pos.getValues(values);
	values[0] += deltaX;
	values[2] += deltaY;
	pos.setValues(values);
}

void CCamera::reset()
{

}
