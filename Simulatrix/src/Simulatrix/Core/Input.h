#pragma once

#include "Simulatrix/Core/KeyCode.h"
#include "Simulatrix/Core/MouseCodes.h"

#include <glm/glm.hpp>

namespace Simulatrix {

	class Input
	{
	public:
		inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }

		inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }
		inline static std::pair<float, float> GetMouseDelta() { return s_Instance->GetMouseDeltaImpl(); }
		inline static float GetMouseDX() { return s_Instance->GetMouseDXImpl(); }
		inline static float GetMouseDY() { return s_Instance->GetMouseDYImpl(); }
		inline static void PollInputs() { s_Instance->PollInputsImpl(); }
	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;

		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
		virtual std::pair<float, float> GetMouseDeltaImpl() = 0;
		virtual float GetMouseDXImpl() = 0;
		virtual float GetMouseDYImpl() = 0;
		virtual void PollInputsImpl() = 0;
	private:
		static Input* s_Instance;
	};
}