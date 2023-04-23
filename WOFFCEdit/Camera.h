#pragma once
#include "pch.h"
#include "DeviceResources.h"
#include "StepTimer.h"
#include "SceneObject.h"
#include "DisplayObject.h"
#include "DisplayChunk.h"
#include "ChunkObject.h"
#include <vector>
#include "InputCommands.h"





class Camera
{
public: 
	Camera();
	void Update(InputCommands inp);

	//functionality
	float								m_movespeed;

	//camera
	DirectX::SimpleMath::Vector3		m_camPosition;
	DirectX::SimpleMath::Vector3		m_camOrientation;
	DirectX::SimpleMath::Vector3		m_camLookAt;
	DirectX::SimpleMath::Vector3		m_camLookDirection;
	DirectX::SimpleMath::Vector3		m_camRight;
	float m_camRotRate;
	float m_PrevMouseX;
	float m_PrevMouseY;
};

