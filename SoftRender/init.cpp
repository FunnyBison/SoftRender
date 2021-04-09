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
	g_model.AddVertex({ -1, -1, -1 }, { 0, 0, 0 }, { 1, 1 });
	g_model.AddVertex({ -1,  1, -1 }, { 0, 0, 1 }, { 1, 1 });
	g_model.AddVertex({  1,  1, -1 }, { 0, 1, 0 }, { 1, 1 });
	g_model.AddVertex({  1, -1, -1 }, { 0, 1, 1 }, { 1, 1 });

	g_model.AddVertex({ -1, -1,  1 }, { 1, 0, 0 }, { 1, 1 });
	g_model.AddVertex({ -1,  1,  1 }, { 1, 0, 1 }, { 1, 1 });
	g_model.AddVertex({  1,  1,  1 }, { 1, 1, 0 }, { 1, 1 });
	g_model.AddVertex({  1, -1,  1 }, { 1, 1, 1 }, { 1, 1 });

	//
	g_model.AddTriangle(0, 1, 2);
	g_model.AddTriangle(0, 2, 3);

	g_model.AddTriangle(4, 6, 5);
	g_model.AddTriangle(4, 7, 6);

	g_model.AddTriangle(4, 5, 1);
	g_model.AddTriangle(4, 1, 0);

	g_model.AddTriangle(3, 2, 6);
	g_model.AddTriangle(3, 6, 7);

	g_model.AddTriangle(1, 5, 6);
	g_model.AddTriangle(1, 6, 3);

	g_model.AddTriangle(4, 0, 3);
	g_model.AddTriangle(4, 3, 7);
}

void Init()
{
	InitCamera();
	InitModel();
}