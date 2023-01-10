#include "simixpch.h"
#include "WindowsInput.h"
#include "Simulatrix/Core/Input.h"

#include "Simulatrix/Core/Application.h"
#include <GLFW/glfw3.h>

namespace Simulatrix {

	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		return { m_MouseX, m_MouseY };
	}

	float WindowsInput::GetMouseXImpl()
	{
		return m_MouseX;
	}

	float WindowsInput::GetMouseYImpl()
	{
		return m_MouseY;
	}

	std::pair<float, float> WindowsInput::GetMouseDeltaImpl()
	{
		return { m_MouseDX, m_MouseDY };
	}

	float WindowsInput::GetMouseDXImpl()
	{
		return m_MouseDX;
	}

	float WindowsInput::GetMouseDYImpl()
	{
		return m_MouseDY;
	}

	void WindowsInput::PollInputsImpl() {
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		if (m_First) {
			m_First = false;
		}
		else {
			m_MouseDX = xpos - m_MouseX;
			m_MouseDY = ypos - m_MouseY;
		}

		m_MouseX = xpos;
		m_MouseY = ypos;
	}
}