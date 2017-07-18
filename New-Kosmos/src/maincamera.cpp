#include "maincamera.h"

namespace flounder {
	maincamera::maincamera()
	{
		m_position = new vector3();
		m_rotation = new vector3();

		m_viewMatrix = new matrix4x4();
		m_projectionMatrix = new matrix4x4();

		m_viewFrustum = new frustum();
		m_viewRay = new ray(false, new vector2(0.5f, 0.5f));
	}

	maincamera::~maincamera()
	{
		delete m_position;
		delete m_rotation;

		delete m_viewMatrix;
		delete m_projectionMatrix;

		delete m_viewFrustum;
		delete m_viewRay;
	}

	float maincamera::getNearPlane()
	{
		return 0.1f;
	}

	float maincamera::getFarPlane()
	{
		return 1000.0f;
	}

	float maincamera::getFOV()
	{
		return 60.0f;
	}

	void maincamera::update(iplayer *player)
	{
		if (player != NULL)
		{
			m_position->set(*player->getPosition());
			m_rotation->set(*player->getRotation());
		}

		matrix4x4::viewMatrix(*m_position, *m_rotation, m_viewMatrix);
		matrix4x4::perspectiveMatrix(getFOV(), (float) display::get()->getAspectRatio(), getNearPlane(), getFarPlane(), m_projectionMatrix);

		m_viewFrustum->update(*m_projectionMatrix, *m_viewMatrix);
		m_viewRay->update(*m_position, vector2((float) mouse::get()->getPositionX(), (float) mouse::get()->getPositionY()), *m_viewMatrix, *m_projectionMatrix);
	}

	void maincamera::reflect(const float &waterHeight)
	{
		throw std::logic_error("Function maincamera::reflect not yet implemented!");
	}
}