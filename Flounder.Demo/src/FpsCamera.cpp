#include "FpsCamera.hpp"

namespace Demo
{
	const float FpsCamera::NEAR_PLANE = 0.01f;
	const float FpsCamera::FAR_PLANE = 3072.0f;
	const float FpsCamera::FIELD_OF_VIEW = 70.0f;

	const float FpsCamera::ROTATE_AGILITY = 20.0f;
	const float FpsCamera::PITCH_AGILITY = 20.0f;

	const float FpsCamera::INFLUENCE_OF_JOYSTICK_DY = 4.5f;
	const float FpsCamera::INFLUENCE_OF_JOYSTICK_DX = 4.5f;

	const float FpsCamera::INFLUENCE_OF_MOUSE_DY = 10000.0f;
	const float FpsCamera::INFLUENCE_OF_MOUSE_DX = 10000.0f;

	const float FpsCamera::MAX_HORIZONTAL_CHANGE = 30.0f;
	const float FpsCamera::MAX_VERTICAL_CHANGE = 30.0f;

	const float FpsCamera::MAX_ANGLE_OF_ELEVATION = 85.0f;
	const float FpsCamera::MIN_ANGLE_OF_ELEVATION = -85.0f;

	FpsCamera::FpsCamera() :
		m_position(new Vector3()),
		m_velocity(new Vector3()),
		m_rotation(new Vector3()),
		m_viewMatrix(new Matrix4()),
		m_projectionMatrix(new Matrix4()),
		m_viewFrustum(new Frustum()),
		m_viewRay(new Ray(false, Vector2(0.5f, 0.5f))),
		m_angleOfElevation(25.0f),
		m_angleAroundPlayer(0.0f),
		m_targetPosition(new Vector3()),
		m_targetRotation(new Vector3()),
		m_targetElevation(m_angleOfElevation),
		m_targetRotationAngle(m_angleAroundPlayer),
		m_sensitivity(0.9f),
		m_reangleButton(GLFW_MOUSE_BUTTON_LEFT),
		m_joystickVertical(new AxisJoystick(0, { 3 })),
		m_joystickHorizontal(new AxisJoystick(0, { 2 })),
		m_joystickZoom(new ButtonJoystick(0, { 9 })),
		m_paused(false)
	{
	}

	FpsCamera::~FpsCamera()
	{
		delete m_position;
		delete m_velocity;
		delete m_rotation;

		delete m_viewMatrix;
		delete m_projectionMatrix;

		delete m_viewFrustum;
		delete m_viewRay;

		delete m_targetPosition;
		delete m_targetRotation;

		delete m_joystickVertical;
		delete m_joystickHorizontal;
		delete m_joystickZoom;
	}

	void FpsCamera::Update(IPlayer *player)
	{
		float delta = Maths::Min(1.0f / 60.0f, Engine::Get()->GetDelta());

		if (Uis::Get() != nullptr && Uis::Get()->GetManager() != nullptr)
		{
			const bool newPaused = Uis::Get()->GetManager()->IsGamePaused();

			if (m_paused != newPaused)
			{
				Mouse::Get()->SetCursorHidden(!newPaused);
			}

			m_paused = newPaused;
		}

		CalculateHorizontalAngle();
		CalculateVerticalAngle();

		if (player != nullptr)
		{
			Vector3::Subtract(*player->GetPosition(), *m_targetPosition, m_velocity); // TODO: Improve!

			m_targetPosition->Set(*player->GetPosition());
			m_targetRotation->Set(*player->GetRotation());
		}

		UpdateHorizontalAngle(delta);
		UpdatePitchAngle(delta);
		UpdatePosition();

		Matrix4::ViewMatrix(*m_position, *m_rotation, m_viewMatrix);
		Matrix4::PerspectiveMatrix(GetFov(), static_cast<float>(Display::Get()->GetAspectRatio()), GetNearPlane(), GetFarPlane(), m_projectionMatrix);

		m_viewFrustum->Update(*m_projectionMatrix, *m_viewMatrix);
		m_viewRay->Update(*m_position, Vector2(static_cast<float>(Mouse::Get()->GetPositionX()), static_cast<float>(Mouse::Get()->GetPositionY())), *m_viewMatrix, *m_projectionMatrix);

		// printf("Position: (%f, %f, %f). Rotation: (%f, %f, %f)\n", m_position->m_x, m_position->m_y, m_position->m_z, m_rotation->m_x, m_rotation->m_y, m_rotation->m_z);
	}

	void FpsCamera::CalculateHorizontalAngle()
	{
		float angleChange = 0.0f;

		if (!m_paused)
		{
			if (Maths::Deadband(0.05f, m_joystickHorizontal->GetAmount()) != 0.0f && !m_joystickZoom->IsDown())
			{
				angleChange = m_joystickHorizontal->GetAmount() * INFLUENCE_OF_JOYSTICK_DX * m_sensitivity;
			}
			else
			{
				if (Mouse::Get()->IsCursorDisabled() || Mouse::Get()->GetButton(m_reangleButton))
				{
					angleChange = -Mouse::Get()->GetDeltaX() * INFLUENCE_OF_MOUSE_DX * m_sensitivity;
				}
			}
		}

		if (angleChange > MAX_HORIZONTAL_CHANGE)
		{
			angleChange = MAX_HORIZONTAL_CHANGE;
		}
		else if (angleChange < -MAX_HORIZONTAL_CHANGE)
		{
			angleChange = -MAX_HORIZONTAL_CHANGE;
		}

		m_targetRotationAngle -= angleChange;

		if (m_targetRotationAngle >= DEGREES_IN_HALF_CIRCLE)
		{
			m_targetRotationAngle -= DEGREES_IN_CIRCLE;
		}
		else if (m_targetRotationAngle <= -DEGREES_IN_HALF_CIRCLE)
		{
			m_targetRotationAngle += DEGREES_IN_CIRCLE;
		}
	}

	void FpsCamera::CalculateVerticalAngle()
	{
		float angleChange = 0.0f;

		if (!m_paused)
		{
			if (Maths::Deadband(0.05f, m_joystickVertical->GetAmount()) != 0.0f && !m_joystickZoom->IsDown())
			{
				angleChange = m_joystickVertical->GetAmount() * INFLUENCE_OF_JOYSTICK_DY * m_sensitivity;
			}
			else
			{
				if (Mouse::Get()->IsCursorDisabled() || Mouse::Get()->GetButton(m_reangleButton))
				{
					angleChange = Mouse::Get()->GetDeltaY() * INFLUENCE_OF_MOUSE_DY * m_sensitivity;
				}
			}
		}

		if (angleChange > MAX_VERTICAL_CHANGE)
		{
			angleChange = MAX_VERTICAL_CHANGE;
		}
		else if (angleChange < -MAX_VERTICAL_CHANGE)
		{
			angleChange = -MAX_VERTICAL_CHANGE;
		}

		m_targetElevation -= angleChange;

		if (m_targetElevation >= MAX_ANGLE_OF_ELEVATION)
		{
			m_targetElevation = MAX_ANGLE_OF_ELEVATION;
		}
		else if (m_targetElevation <= MIN_ANGLE_OF_ELEVATION)
		{
			m_targetElevation = MIN_ANGLE_OF_ELEVATION;
		}
	}

	void FpsCamera::UpdateHorizontalAngle(const float &delta)
	{
		float offset = m_targetRotationAngle - m_angleAroundPlayer;

		if (fabs(offset) > DEGREES_IN_HALF_CIRCLE)
		{
			if (offset < 0.0f)
			{
				offset = m_targetRotationAngle + DEGREES_IN_CIRCLE - m_angleAroundPlayer;
			}
			else
			{
				offset = m_targetRotationAngle - DEGREES_IN_CIRCLE - m_angleAroundPlayer;
			}
		}

		m_angleAroundPlayer += offset * delta * ROTATE_AGILITY;

		if (m_angleAroundPlayer >= DEGREES_IN_HALF_CIRCLE)
		{
			m_angleAroundPlayer -= DEGREES_IN_CIRCLE;
		}
		else if (m_angleAroundPlayer <= -DEGREES_IN_HALF_CIRCLE)
		{
			m_angleAroundPlayer += DEGREES_IN_CIRCLE;
		}
	}

	void FpsCamera::UpdatePitchAngle(const float &delta)
	{
		float offset = m_targetElevation - m_angleOfElevation;

		if (fabs(offset) > DEGREES_IN_HALF_CIRCLE)
		{
			if (offset < 0.0f)
			{
				offset = m_targetElevation + DEGREES_IN_CIRCLE - m_angleOfElevation;
			}
			else
			{
				offset = m_targetElevation - DEGREES_IN_CIRCLE - m_angleOfElevation;
			}
		}

		m_angleOfElevation += offset * delta * PITCH_AGILITY;

		if (m_angleOfElevation >= DEGREES_IN_HALF_CIRCLE)
		{
			m_angleOfElevation -= DEGREES_IN_CIRCLE;
		}
		else if (m_angleOfElevation <= -DEGREES_IN_HALF_CIRCLE)
		{
			m_angleOfElevation += DEGREES_IN_CIRCLE;
		}
	}

	void FpsCamera::UpdatePosition()
	{
		m_position->m_x = m_targetPosition->m_x;
		m_position->m_y = m_targetPosition->m_y;
		m_position->m_z = m_targetPosition->m_z;

		m_rotation->m_x = m_angleOfElevation - m_targetRotation->m_z;
		m_rotation->m_y = m_angleAroundPlayer + m_targetRotation->m_y + DEGREES_IN_HALF_CIRCLE;
		m_rotation->m_z = 0.0f;
	}

	void FpsCamera::ReflectView(const float &waterHeight)
	{
		m_position->m_y -= 2.0f * (m_position->m_y - waterHeight);
		m_rotation->m_x = -m_rotation->m_x;
		Matrix4::ViewMatrix(*m_position, *m_rotation, m_viewMatrix);
	}
}
