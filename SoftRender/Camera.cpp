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
	rotate.Unit();
	rotate.Set(0, 0, right.x);
	rotate.Set(1, 0, right.y);
	rotate.Set(2, 0, right.z);

	rotate.Set(0, 1, m_up.x);
	rotate.Set(1, 1, m_up.y);
	rotate.Set(2, 1, m_up.z);

	rotate.Set(0, 2, m_dir.x);
	rotate.Set(1, 2, m_dir.y);
	rotate.Set(2, 2, m_dir.z);

	m_cameraTrans.Unit().Translate(-m_pos).TransformByOther(rotate);
}

void Camera::SetPerspective(float zn, float zf, float fovY, float aspect)
{
	m_zn = zn;
	m_zf = zf;
	m_fovY = fovY;
	m_aspect = aspect;
}

void Camera::ChangeAspect(float aspect)
{
	m_aspect = aspect;
	UpdateProject();
}

void Camera::UpdateProject()
{
	m_projTrans.Unit();
	float cotVy = 1 / tan(m_fovY * 0.5f);
	m_projTrans.Set(0, 0, cotVy / m_aspect);
	m_projTrans.Set(1, 1, cotVy);
	m_projTrans.Set(2, 2, m_zf / (m_zf - m_zn));
	m_projTrans.Set(3, 2, -m_zf * m_zn / (m_zf - m_zn));
	m_projTrans.Set(2, 3, 1);
	m_projTrans.Set(3, 3, 0);
}

Camera g_Camera;