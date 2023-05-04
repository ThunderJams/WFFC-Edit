#include "Camera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

using Microsoft::WRL::ComPtr;

 Camera::Camera() {
	////functional
	m_movespeed = 0.30;
	m_camRotRate = 1.0;

	//camera
	m_camPosition.x = 0.0f;
	m_camPosition.y = 3.7f;
	m_camPosition.z = -3.5f;

	m_camOrientation.x = 0;
	m_camOrientation.y = 0;
	m_camOrientation.z = 0;

	m_camLookAt.x = 0.0f;
	m_camLookAt.y = 0.0f;
	m_camLookAt.z = 0.0f;

	m_camLookDirection.x = 0.0f;
	m_camLookDirection.y = 0.0f;
	m_camLookDirection.z = 0.0f;

	m_camRight.x = 0.0f;
	m_camRight.y = 0.0f;
	m_camRight.z = 0.0f;

	m_camOrientation.x = 0.0f;
	m_camOrientation.y = 0.0f;
	m_camOrientation.z = 0.0f;
}

void Camera::Update(InputCommands inp)
{
	//camera motion is on a plane, so kill the 7 component of the look direction
	Vector3 planarMotionVector = m_camLookDirection;
	planarMotionVector.y = 0.0;

	

	if (inp.mouse_RB_Down)
	{
		float deltaX = inp.mouse_X - m_PrevMouseX;
		float deltaY = inp.mouse_Y - m_PrevMouseY;

		m_camOrientation.y -= deltaX * m_camRotRate;
		m_camOrientation.x -= deltaY * m_camRotRate;

		if (m_camOrientation.x > 89.0f)
		{
			m_camOrientation.x = 89.0f;
		}
		if (m_camOrientation.x < -89.0f)
		{
			m_camOrientation.x = -89.0f;
		}
	}

	//create look direction from Euler angles in m_camOrientation
	m_camLookDirection.x = Lerp(m_camLookDirection.x, sin((m_camOrientation.y) * 3.1415 / 180), 0.5);
	m_camLookDirection.y = Lerp(m_camLookDirection.y, sin((m_camOrientation.x) * 3.1415 / 180), 0.5);
	m_camLookDirection.z = Lerp(m_camLookDirection.z, cos((m_camOrientation.y) * 3.1415 / 180), 0.5);
	m_camLookDirection.Normalize();

	//create right vector from look Direction
	m_camLookDirection.Cross(Vector3::UnitY, m_camRight);

	//process input and update stuff
	if (inp.forward)
	{
		m_camPosition += m_camLookDirection * m_movespeed;
	}
	if (inp.back)
	{
		m_camPosition -= m_camLookDirection * m_movespeed;
	}
	if (inp.right)
	{
		m_camPosition += m_camRight * m_movespeed;
	}
	if (inp.left)
	{
		m_camPosition -= m_camRight * m_movespeed;
	}
	if (inp.up) {
		m_camPosition.y += m_movespeed;
	}
	if (inp.down) {
		m_camPosition.y -= m_movespeed;
	}

	//update lookat point
	m_camLookAt = m_camPosition + m_camLookDirection;

	//update previous mouse position
	m_PrevMouseX = inp.mouse_X;
	m_PrevMouseY = inp.mouse_Y;
}

float Camera::Lerp(float start, float end, float t)
{
	return start + t * (end - start);
}
