#ifndef CAMERA_H
#define CAMERA_H
#include "GraphDef.h"
#include "Transport.h"

class Matrix;
class Camera
{
public:
	Camera();
	~Camera();

	void SetPos(const Vector3d &pos);
	void SetDirAndUp(const Vector3d &dir, const Vector3d &up);
	void Update();		//根据已有信息更新矩阵

	Transport m_cameraTrans;
	Vector3d m_dir;
	Vector3d m_up;
	Vector3d m_pos;


	void SetPerspective(float zn, float zf, float fovY, float aspect);
	void UpdateProject();
	Transport m_projTrans;		//投影变换矩阵
	float m_zn;
	float m_zf;
	float m_fovY;
	float m_aspect;
};


#endif // !CAMERA_H


