#include "mouse.h"

namespace flounder {
	mouse::mouse()
	{
		m_mouseButtons = new int[GLFW_MOUSE_BUTTON_LAST];
		m_displaySelected = true;
		m_mousePositionX = 0.5;
		m_mousePositionY = 0.5;	
		
		m_cursorDisabled = false;
		m_lastCursorDisabled = false;

		// Sets the default state of the buttons to released.
		for (int i = 0; i < GLFW_MOUSE_BUTTON_LAST + 1; i++) {
			m_mouseButtons[i] = GLFW_RELEASE;
		}

		// Sets the mouses callbacks.
		glfwSetScrollCallback(display::get()->getWindow(), callbackScroll);
		glfwSetMouseButtonCallback(display::get()->getWindow(), callbackMouseButton);
		glfwSetCursorPosCallback(display::get()->getWindow(), callbackCursorPos);
		glfwSetCursorEnterCallback(display::get()->getWindow(), callbackCursorEnter);
	}

	mouse::~mouse()
	{
		delete m_mouseButtons;
	}

	void mouse::update()
	{
		// Updates the mouses delta.
		m_mouseDeltaX = framework::get()->getDelta() * (m_lastMousePositionX - m_mousePositionX);
		m_mouseDeltaY = framework::get()->getDelta() * (m_lastMousePositionY - m_mousePositionY);

		// Sets the last position of the current.
		m_lastMousePositionX = m_mousePositionX;
		m_lastMousePositionY = m_mousePositionY;

		// Fixes snaps when toggling cursor.
		if (m_cursorDisabled != m_lastCursorDisabled) 
		{
			m_mouseDeltaX = 0.0;
			m_mouseDeltaY = 0.0;

			m_lastCursorDisabled = m_cursorDisabled;
		}

		// Updates the mouse wheel using a smooth scroll technique.
		if (m_mouseDeltaWheel != 0.0) 
		{
			m_mouseDeltaWheel -= framework::get()->getDelta() * ((m_mouseDeltaWheel < 0.0) ? -1.0 : 1.0);
			m_mouseDeltaWheel = maths::deadband(0.1, m_mouseDeltaWheel);
		}
	}

	void mouse::setCursorHidden(bool disabled)
	{
		if (m_cursorDisabled != disabled) {
			glfwSetInputMode(display::get()->getWindow(), GLFW_CURSOR, (disabled ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL));

			if (!disabled && m_cursorDisabled) {
				glfwSetCursorPos(display::get()->getWindow(), m_mousePositionX * display::get()->getWidth(), m_mousePositionY * display::get()->getHeight());
			}
		}

		m_cursorDisabled = disabled;
	}

	bool mouse::getButton(int button)
	{
		return m_mouseButtons[button] != GLFW_RELEASE;
	}

	double mouse::getPositionX()
	{
		return m_mousePositionX;
	}

	double mouse::getPositionY()
	{
		return m_mousePositionY;
	}

	void mouse::setPosition(double cursorX, double cursorY)
	{
		glfwSetCursorPos(display::get()->getWindow(), cursorX, cursorY);
	}

	double mouse::getDeltaX()
	{
		return m_mouseDeltaX;
	}

	double mouse::getDeltaY()
	{
		return m_mouseDeltaY;
	}

	double mouse::getDeltaWheel()
	{
		return m_mouseDeltaWheel;
	}

	bool mouse::isDisplaySelected()
	{
		return m_displaySelected;
	}

	bool mouse::isCursorDisabled()
	{
		return m_cursorDisabled;
	}

	void callbackScroll(GLFWwindow *window, double xoffset, double yoffset)
	{
		mouse::get()->m_mouseDeltaWheel = (float)yoffset;
	}

	void callbackMouseButton(GLFWwindow *window, int button, int action, int mods)
	{
		mouse::get()->m_mouseButtons[button] = action;
	}

	void callbackCursorPos(GLFWwindow *window, double xpos, double ypos)
	{
		mouse::get()->m_mousePositionX = (float)(xpos / display::get()->getWidth());
		mouse::get()->m_mousePositionY = (float)(ypos / display::get()->getHeight());
	}

	void callbackCursorEnter(GLFWwindow *window, int entered)
	{
		mouse::get()->m_displaySelected = entered;
	}
}