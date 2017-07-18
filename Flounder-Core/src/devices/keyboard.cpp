#include "keyboard.h"

namespace flounder {
	void callbackKey(GLFWwindow *window, int key, int scancode, int action, int mods)
	{
		// TODO: Play with mods.

		if (key < 0 || key > GLFW_KEY_LAST)
		{
			std::cout << "Invalid action attempted with key " << key << std::endl;
		}
		else
		{
			keyboard::get()->m_keyboardKeys[key] = action;
		}
	}

	void callbackChar(GLFWwindow *window, unsigned int codepoint)
	{
		keyboard::get()->m_keyboardChar = codepoint;
	}

	keyboard::keyboard()
		: imodule()
	{
	}

	keyboard::~keyboard()
	{
		delete m_keyboardKeys;
	}

	void keyboard::init()
	{
		m_keyboardKeys = new int[GLFW_KEY_LAST + 1];
		m_keyboardChar = 0;

		// Sets the default state of the keys to released.
		for (unsigned int i = 0; i < GLFW_KEY_LAST + 1; i++) 
		{
			m_keyboardKeys[i] = GLFW_RELEASE;
		}

		// Sets the keyboards callbacks.
		glfwSetKeyCallback(display::get()->getWindow(), callbackKey);
		glfwSetCharCallback(display::get()->getWindow(), callbackChar);
	}

	void keyboard::update()
	{
	}

	bool keyboard::getKey(unsigned const int &key)
	{
		return m_keyboardKeys[key] != GLFW_RELEASE;
	}

	int keyboard::getKeyboardChar()
	{
		return m_keyboardChar;
	}
}