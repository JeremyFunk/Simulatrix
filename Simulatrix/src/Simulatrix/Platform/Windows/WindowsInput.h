#pragma once
#include "Simulatrix/Core/Input.h"

namespace Simulatrix {

	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;

		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
		virtual std::pair<float, float> GetMouseDeltaImpl() override;
		virtual float GetMouseDXImpl() override;
		virtual float GetMouseDYImpl() override;
		virtual void PollInputsImpl() override;
	private:
		float m_MouseX = 0.f, m_MouseY = 0.f, m_MouseDX = 0.f, m_MouseDY = 0.f;
		bool m_First = true;
	};

}