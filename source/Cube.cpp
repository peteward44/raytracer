
#include "Cube.h"
#include "Plane.h"


Cube::Cube()
{
}


Cube::Cube(const Vector3& centre, const Vector3& lookDirection, const Vector3& upDirection, float extentX, float extentY, float extentZ)
  : Centre(centre), AxisY(upDirection), AxisZ(lookDirection), ExtentX(extentX), ExtentY(extentY), ExtentZ(extentZ)
{
	AxisX = Vector3::Cross(lookDirection, upDirection);
}


bool Cube::Trace(const Ray& ray, float& distance) const
{
  float fWdU[3], fAWdU[3], fDdU[3], fADdU[3], fAWxDdU[3], fRhs;

  Vector3 kDiff = ray.Origin - Centre;

  fWdU[0] = Vector3::Dot(ray.Direction, GetAxis(0));
  fAWdU[0] = fabs(fWdU[0]);
  fDdU[0] = Vector3::Dot(kDiff, GetAxis(0));
  fADdU[0] = fabs(fDdU[0]);
  if ( fADdU[0] > GetExtent(0) && fDdU[0]*fWdU[0] >= 0.0f )
      return false;

  fWdU[1] = Vector3::Dot(ray.Direction, GetAxis(1));
  fAWdU[1] = fabs(fWdU[1]);
  fDdU[1] = Vector3::Dot(kDiff, GetAxis(1));
  fADdU[1] = fabs(fDdU[1]);
  if ( fADdU[1] > GetExtent(1) && fDdU[1]*fWdU[1] >= 0.0f )
      return false;

  fWdU[2] = Vector3::Dot(ray.Direction, GetAxis(2));
  fAWdU[2] = fabs(fWdU[2]);
  fDdU[2] = Vector3::Dot(kDiff, GetAxis(2));
  fADdU[2] = fabs(fDdU[2]);
  if ( fADdU[2] > GetExtent(2) && fDdU[2]*fWdU[2] >= 0.0f )
      return false;

  Vector3 kWxD = Vector3::Cross(ray.Direction, kDiff);

  fAWxDdU[0] = fabs(Vector3::Dot(kWxD, GetAxis(0)));
  fRhs = GetExtent(1)*fAWdU[2] + GetExtent(2)*fAWdU[1];
  if ( fAWxDdU[0] > fRhs )
      return false;

  fAWxDdU[1] = fabs(Vector3::Dot(kWxD, GetAxis(1)));
  fRhs = GetExtent(0)*fAWdU[2] + GetExtent(2)*fAWdU[0];
  if ( fAWxDdU[1] > fRhs )
      return false;

  fAWxDdU[2] = fabs(Vector3::Dot(kWxD, GetAxis(2)));
  fRhs = GetExtent(0)*fAWdU[1] + GetExtent(1)*fAWdU[0];
  if ( fAWxDdU[2] > fRhs )
      return false;

	distance = fRhs;

	return true;
}


Vector3 Cube::GetNormal(const Ray& ray, float distance) const
{
	return Vector3();
}

