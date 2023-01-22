#pragma once

#include "Simulatrix/Core/IOWrapper.h"
#include "Scene.h"

namespace Simulatrix {

	class SceneSerializer
	{
	public:
		SceneSerializer(const Ref<Scene>& scene);

		void Serialize(const Path& filepath);

		bool Deserialize(const Path& filepath);
	private:
		Ref<Scene> m_Scene;
	};

}
