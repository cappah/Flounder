﻿#include "UiSelector.hpp"

#include "../devices/Mouse.hpp"
#include "../devices/Joysticks.hpp"

namespace Flounder
{
	UiSelector::UiSelector() :
		m_cursorX(0.0f),
		m_cursorY(0.0f),
		m_leftClick(false),
		m_rightClick(false),
		m_leftWasClick(false),
		m_rightWasClick(false),
		m_mouseLeft(new ButtonMouse({ GLFW_MOUSE_BUTTON_LEFT })),
		m_mouseRight(new ButtonMouse({ GLFW_MOUSE_BUTTON_RIGHT })),
		m_joysticksInitialized(false),
		m_selectedJoystick(0),
		m_joystickAxisX(nullptr),
		m_joystickAxisY(nullptr),
		m_joystickLeft(nullptr),
		m_joystickRight(nullptr)
	{
	}

	UiSelector::~UiSelector()
	{
		delete m_mouseLeft;
		delete m_mouseRight;

		delete m_joystickAxisX;
		delete m_joystickAxisY;
		delete m_joystickLeft;
		delete m_joystickRight;
	}

	void UiSelector::Load(const int &joystick, const int &joystickLeftClick, const int &joystickRightClick, const int &joystickAxisX, const int &joystickAxisY)
	{
		m_selectedJoystick = joystick;
		m_joystickAxisX = new AxisJoystick(joystick, { joystickAxisX });
		m_joystickAxisY = new AxisJoystick(joystick, { joystickAxisY });
		m_joystickLeft = new ButtonJoystick(joystick, { joystickLeftClick });
		m_joystickRight = new ButtonJoystick(joystick, { joystickRightClick });
		m_joysticksInitialized = true;
	}

	void UiSelector::Update(const bool &paused)
	{
		m_leftClick = m_mouseLeft->IsDown();
		m_rightClick = m_mouseRight->IsDown();
		m_leftWasClick = m_mouseLeft->WasDown();
		m_rightWasClick = m_mouseRight->WasDown();

		m_cursorX = Mouse::Get()->GetPositionX();
		m_cursorY = Mouse::Get()->GetPositionY();

		if (m_joysticksInitialized && Joysticks::Get()->IsConnected(m_selectedJoystick) && paused)
		{
			if (fabs(Maths::Deadband(0.1f, m_joystickAxisX->GetAmount())) > 0.0 || fabs(Maths::Deadband(0.1f, m_joystickAxisY->GetAmount())) > 0.0)
			{
				m_cursorX += m_joystickAxisX->GetAmount() * 0.75f * Engine::Get()->GetDelta();
				m_cursorY += -m_joystickAxisY->GetAmount() * 0.75f * Engine::Get()->GetDelta();
				m_cursorX = Maths::Clamp(m_cursorX, 0.0f, 1.0f);
				m_cursorY = Maths::Clamp(m_cursorY, 0.0f, 1.0f);
				Mouse::Get()->SetPosition(m_cursorX * Display::Get()->GetWidth(), m_cursorY * Display::Get()->GetHeight());
			}

			m_leftClick = m_leftClick || m_joystickLeft->IsDown();
			m_rightClick = m_rightClick || m_joystickRight->IsDown();
			m_leftWasClick = m_leftWasClick || m_joystickLeft->WasDown();
			m_rightWasClick = m_rightWasClick || m_joystickRight->WasDown();
		}
	}

	bool UiSelector::IsSelected(const UiObject &object) const
	{
		// TODO: Account for rotations.
		float positionX = object.GetRectangle()->m_position->m_x;
		float positionY = object.GetRectangle()->m_position->m_y;

		float width = 2.0f * object.GetRectangle()->m_dimensions->m_x * object.GetScreenTransform()->m_z / static_cast<float>(Display::Get()->GetAspectRatio());
		float height = 2.0f * object.GetRectangle()->m_dimensions->m_y * object.GetScreenTransform()->m_w;

		if (Mouse::Get()->IsDisplaySelected() && Display::Get()->IsFocused())
		{
			if (m_cursorX >= positionX - (width / 2.0f) && m_cursorX <= positionX + (width / 2.0f))
			{
				if (m_cursorY >= positionY - (height / 2.0f) && m_cursorY <= positionY + (height / 2.0f))
				{
					return true;
				}
			}
		}

		return false;
	}

	void UiSelector::CancelWasEvent()
	{
		m_leftWasClick = false;
		m_rightWasClick = false;
	}
}
