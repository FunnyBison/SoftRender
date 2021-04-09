#include "Camera.h"
#include "Model.h"
#include "common.h"	

void InitCamera()
{
	g_Camera.SetPos({ 0, 0, -6 });
	g_Camera.SetDirAndUp({ 0, 0, 1 }, { 0, 1, 0 });
	g_Camera.Update();

	g_Camera.SetPerspective(1.0f, 1000.0f, DToR(90), 1);
	g_Camera.UpdateProject();
}

void InitModel()
{
	g_model.AddVertex({ -2, 0, 0 }, { 0, 1, 0 }, { 1, 1 });
	g_model.AddVertex({ 2, -1, 0 }, { 1, 0, 0 }, { 1, 1 });
	g_model.AddVertex({ 0, 2, 0 }, { 0, 0, 1 }, { 1, 1 });

	g_model.AddTriangle(0, 1, 2);
}

void Init()
{
	InitCamera();
	InitModel();
}