#include "Camera.h"
#include "Matrix.h"
#include <cmath>
#include <utility>

Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::SetPos(const Vector3d & pos)
{
	m_pos = pos;
}

void Camera::SetDirAndUp(const Vector3d & dir, const Vector3d & up)
{
	m_dir = dir;
	m_up = up;
}

void Camera::Update()
{
	m_dir.Normalize();
	m_up.Normalize();
	Vector3d right = Vector3d::CrossProduct(m_up, m_dir);

	Transport rotate;
	rotate.Set(0, 0, right.x);
	rotate.Set(1, 0, right.y);
	rotate.Set(2, 0, right.z);

	rotate.Set(0, 1, m_up.x);
	rotate.Set(1, 1, m_up.x);
	rotate.Set(2, 1, m_up.x);

	rotate.Set(0, 2, m_dir.x);
	rotate.Set(1, 2, m_dir.x);
	rotate.Set(2, 2, m_dir.x);

	m_cameraTrans.Unit().Translate(-m_pos).TransformByOther(rotate);
}

void Camera::SetPerspective(float zn, float zf, float fovY, float aspect)
{
	m_zn = zn;
	m_zf = zf;
	m_fovY = fovY;
	m_aspect = aspect;
}

void Camera::UpdateProject()
{
	m_projTrans.Unit();
	float cotVy = 1 / tan(m_fovY * 0.5f);
}
