//////////////////////////////////////////////////////////////////////////////////////////////////
// 
// File: d3dxcreate.cpp
// 
// Author: Frank D. Luna (C) All Rights Reserved
//
// System: AMD Athlon 1800+ XP, 512 DDR, Geforce 3, Windows XP, MSVC++ 7.0 
//
// Desc: Renders several D3DX shapes in wireframe mode and has the camera
//       fly around the scene.  Demonstrates the D3DXCreate* functions, and
//       demonstrates more complex transformations used to position the objects
//       in the world and move the camera around the world.
//          
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "d3dUtility.h"
#include <unordered_map>
#include <string>
#include "d3dUtility.h"
#include <iostream>
#include <any>

//
// Globals
//

IDirect3DDevice9*     Device = 0; 

const int Width  = 640;
const int Height = 480;

// Store 5 objects.
ID3DXMesh* human_Objects[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0}; 

D3DMATERIAL9 human_Mtrls[16];

// World matrices for each object.  These matrices
// specify the locations of the objects in the world.
D3DXMATRIX human_World[16];



//
// Framework Functions
//
bool Setup()
{	


	D3DXCreateBox(
		Device,
		2.0f, // width
		2.0f, // height
		1.5f, // depth
		&human_Objects[0],
		0);

	D3DXCreateBox(
		Device,
		3.0f, // width
		3.5f, // height
		2.0f, // depth
		&human_Objects[1],
		0);

	D3DXCreateBox(
		Device,
		0.75f, // width
		2.50f, // height
		0.75f, // depth
		&human_Objects[2],
		0);

	D3DXCreateBox(
		Device,
		0.75f, // width
		2.50f, // height
		0.75f, // depth
		&human_Objects[3],
		0);

	D3DXCreateBox(
		Device,
		0.75f, // width
		2.5f, // height
		0.75f, // depth
		&human_Objects[4],
		0);

	D3DXCreateBox(
		Device,
		0.75f, // width
		2.5f, // height
		0.75f, // depth
		&human_Objects[5],
		0);

	D3DXCreateBox(
		Device,
		0.26f, // width
		0.30f, // height
		0.05f, // depth
		&human_Objects[6],
		0);

	D3DXCreateBox(
		Device,
		0.26f, // width
		0.30f, // height
		0.05f, // depth
		&human_Objects[7],
		0);
	
	D3DXCreateBox(
		Device,
		0.24f, // width
		0.30f, // height
		0.05f, // depth
		&human_Objects[8],
		0);

	D3DXCreateBox(
		Device,
		0.24f, // width
		0.30f, // height
		0.05f, // depth
		&human_Objects[9],
		0);

	D3DXCreateBox(
		Device,
		1.0f, // width
		0.25f, // height
		0.05f, // depth
		&human_Objects[10],
		0);

	D3DXCreateBox(
		Device,
		0.75f, // width
		0.5f, // height
		0.75f, // depth
		&human_Objects[11],
		0);

	D3DXCreateBox(
		Device,
		0.75f, // width
		0.5f, // height
		0.75f, // depth
		&human_Objects[12],
		0);

	D3DXCreateBox(
		Device,
		0.75f, // width
		0.5f, // height
		0.75f, // depth
		&human_Objects[13],
		0);

	D3DXCreateBox(
		Device,
		0.75f, // width
		0.5f, // height
		0.75f, // depth
		&human_Objects[14],
		0);
	D3DXCreateBox(
		Device,
		50.0f, // width
		30.0f, // height
		1.0f, // depth
		&human_Objects[15],
		0);
	
	human_Mtrls[0] = d3d::SKIN_MTRL;
	human_Mtrls[1] = d3d::VIVID2_MTRL;
	human_Mtrls[2] = d3d::VIVID_MTRL;
	human_Mtrls[3] = d3d::VIVID_MTRL;
	human_Mtrls[4] = d3d::BLUE_MTRL;
	human_Mtrls[5] = d3d::BLUE_MTRL;
	human_Mtrls[6] = d3d::BLACK_MTRL;
	human_Mtrls[7] = d3d::BLACK_MTRL;
	human_Mtrls[8] = d3d::WHITE_MTRL;
	human_Mtrls[9] = d3d::WHITE_MTRL;
	human_Mtrls[10] = d3d::VIVID3_MTRL;
	human_Mtrls[11] = d3d::SKIN_MTRL;
	human_Mtrls[12] = d3d::SKIN_MTRL;
	human_Mtrls[13] = d3d::BLACK_MTRL;
	human_Mtrls[14] = d3d::BLACK_MTRL;
	human_Mtrls[15] = d3d::VIVID4_MTRL;

	

	D3DXVECTOR3 dir(5.0f, -0.0f, 10.0f);
	D3DXCOLOR   c = d3d::WHITE;
	D3DLIGHT9 dirLight = d3d::InitDirectionalLight(&dir, &c);


	//
	// Set and Enable the light.
	//

	Device->SetLight(0, &dirLight);
	Device->LightEnable(0, true);



	//
	// Build world matrices - position the objects in world space.
	// For example, ObjWorldMatrices[1] will position Objects[1] at
	// (-5, 0, 5).  Likewise, ObjWorldMatrices[2] will position
	// Objects[2] at (5, 0, 5).
	//

	D3DXMatrixTranslation(&human_World[0],  0.0f, 2.75f,  0.0f);
	D3DXMatrixTranslation(&human_World[1], 0.0f, 0.0f,  0.0f);
	D3DXMatrixTranslation(&human_World[2],  1.75f, 0.0f,  0.0f);
	D3DXMatrixTranslation(&human_World[3], -1.75f, 0.0f, 0.0f);
	D3DXMatrixTranslation(&human_World[4],  0.5f, -3.0f, 0.0f);
	D3DXMatrixTranslation(&human_World[5], -0.5f, -3.0f, 0.0f);
	D3DXMatrixTranslation(&human_World[6], 0.30f, 3.0f, -0.75f);
	D3DXMatrixTranslation(&human_World[7], -0.30f, 3.0f, -0.75f);
	D3DXMatrixTranslation(&human_World[8], 0.55f, 3.0f, -0.75f);
	D3DXMatrixTranslation(&human_World[9], -0.55f, 3.0f, -0.75f);
	D3DXMatrixTranslation(&human_World[10], 0.0f, 2.25f, -0.75f);
	D3DXMatrixTranslation(&human_World[11], 1.75f, -1.5f, -0.0f);
	D3DXMatrixTranslation(&human_World[12], -1.75f, -1.5f, -0.0f);
	D3DXMatrixTranslation(&human_World[13], 0.5f, -4.50f, -0.0f);
	D3DXMatrixTranslation(&human_World[14], -0.5f, -4.50f, -0.0f);

	D3DXMatrixTranslation(&human_World[15], -0.0f, -10.0f, 10.0f);
	

	//
	// Set the projection matrix.
	//


	Device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	Device->SetRenderState(D3DRS_SPECULARENABLE, false);

	//
	// Set the projection matrix.
	//

	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(
		&proj,
		D3DX_PI * 0.25f, // 45 - degree
		(float)Width / (float)Height,
		1.0f,
		1000.0f);
	Device->SetTransform(D3DTS_PROJECTION, &proj);

	//
	// Set the projection matrix.
	//


	return true;
}
void Cleanup()
{
	for(int i = 0; i < 16; i++)
		d3d::Release<ID3DXMesh*>(human_Objects[i]);
	
}

bool Display(float timeDelta)
{
	if( Device )
	{


		static float angle = (3.0f * D3DX_PI) / 2.0f;
		static float height = 5.0f;

		if (::GetAsyncKeyState(VK_LEFT) & 0x8000f)
			angle -= 0.5f * timeDelta;

		if (::GetAsyncKeyState(VK_RIGHT) & 0x8000f)
			angle += 0.5f * timeDelta;

		if (::GetAsyncKeyState(VK_UP) & 0x8000f)
			height += 5.0f * timeDelta;

		if (::GetAsyncKeyState(VK_DOWN) & 0x8000f)
			height -= 5.0f * timeDelta;

		if (::GetAsyncKeyState(VK_LEFT) & 0x8000f)
			angle -= 0.5f * timeDelta;

		// Animate the camera:
		// The camera will circle around the center of the scene.  We use the
		// sin and cos functions to generate points on the circle, then scale them
		// by 10 to further the radius.  In addition the camera will move up and down
		// as it circles about the scene.
		D3DXVECTOR3 position(cosf(angle) * 10.0f, height, sinf(angle) * 10.0f);
		D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
		D3DXMATRIX V;
		D3DXMatrixLookAtLH(&V, &position, &target, &up);

		Device->SetTransform(D3DTS_VIEW, &V);
		

		
		// compute the position for the next frame
		
		// compute the height of the camera for the next frame
		//cameraHeight += cameraHeightDirection * timeDelta;
		//if( cameraHeight >= 10.0f )
		//	cameraHeightDirection = -5.0f;

		//if( cameraHeight <= -10.0f )
		//	cameraHeightDirection = 5.0f;

		//
		// Draw the Scene:
		//

		Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0);
		Device->BeginScene();
		
		

		for(int i = 0; i < 16; i++)
		{
			// Set the world matrix that positions the object.
			Device->SetTransform(D3DTS_WORLD, &human_World[i]);
			Device->SetMaterial(&human_Mtrls[i]);

			// Draw the object using the previously set world matrix.
			human_Objects[i]->DrawSubset(0);
		}

		

		Device->EndScene();
		Device->Present(0, 0, 0, 0);
	}
	return true;
}

//
// WndProc
//
LRESULT CALLBACK d3d::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch( msg )
	{
	case WM_DESTROY:
		::PostQuitMessage(0);
		break;
		
	case WM_KEYDOWN:
		if( wParam == VK_ESCAPE )
			::DestroyWindow(hwnd);
		break;
	}
	return ::DefWindowProc(hwnd, msg, wParam, lParam);
}

//
// WinMain
//
int WINAPI WinMain(HINSTANCE hinstance,
				   HINSTANCE prevInstance, 
				   PSTR cmdLine,
				   int showCmd)
{
	if(!d3d::InitD3D(hinstance,
		Width, Height, true, D3DDEVTYPE_HAL, &Device))
	{
		::MessageBox(0,(LPCWSTR) "InitD3D() - FAILED", 0, 0);
		return 0;
	}
		
	if(!Setup())
	{
		::MessageBox(0, (LPCWSTR)"Setup() - FAILED", 0, 0);
		return 0;
	}

	d3d::EnterMsgLoop( Display );

	Cleanup();

	Device->Release();

	return 0;
}