#pragma once
#include "simixpch.h"
#include "SceneSerializer.h"
#include "Simulatrix/Core/Core.h"
#include "yaml-cpp/yaml.h"
#include "Simulatrix/ResourceManager/ResourceManager.h"
#include "Simulatrix/Scene/Entity.h"
#include "Simulatrix/Scene/Components.h"
#include "Simulatrix/Scene/SceneData.h"
namespace YAML {

	template<>
	struct convert<glm::vec2>
	{
		static Node encode(const glm::vec2& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, glm::vec2& rhs)
		{
			if (!node.IsSequence() || node.size() != 2)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			return true;
		}
	};

	template<>
	struct convert<glm::vec3>
	{
		static Node encode(const glm::vec3& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, glm::vec3& rhs)
		{
			if (!node.IsSequence() || node.size() != 3)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			return true;
		}
	};

	template<>
	struct convert<glm::vec4>
	{
		static Node encode(const glm::vec4& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, glm::vec4& rhs)
		{
			if (!node.IsSequence() || node.size() != 4)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			rhs.w = node[3].as<float>();
			return true;
		}
	};

	template<>
	struct convert<Simulatrix::UUID>
	{
		static Node encode(const Simulatrix::UUID& uuid)
		{
			Node node;
			node.push_back((uint64_t)uuid);
			return node;
		}

		static bool decode(const Node& node, Simulatrix::UUID& uuid)
		{
			uuid = node.as<uint64_t>();
			return true;
		}
	};
}

namespace Simulatrix {
	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec2& v)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << YAML::EndSeq;
		return out;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec3& v)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
		return out;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec4& v)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;
		return out;
	}


    SceneSerializer::SceneSerializer(const Ref<Scene>& scene) : m_Scene(scene) {

    }

    static void SerializeEntity(YAML::Emitter& out, Entity entity) {
        out << YAML::BeginMap;
        out << YAML::Key << "Entity" << YAML::Value << entity.GetUUID();

		//if (entity.HasComponent<ComponentColorMaterial>()) {
		//	auto& component = entity.GetComponent<ComponentColorMaterial>();
		//	out << YAML::Key << "ComponentColorMaterial";
		//	out << YAML::BeginMap;
		//	out << YAML::Key << "Color" << YAML::Value << component.Color;
		//	out << YAML::EndMap;
		//}

		if (entity.HasComponent<ComponentRenderable>()) {
			auto& component = entity.GetComponent<ComponentRenderable>();
			out << YAML::Key << "ComponentRenderable";
			out << YAML::BeginMap;
			out << YAML::Key << "ModelID" << YAML::Value << component.Model->ID;
			out << YAML::Key << "PipelineID" << YAML::Value << component.RenderPipeline->GetID();
			if (component.Model->IsPrimitive) {
				out << YAML::Key << "IsPrimitive" << YAML::Value << true;
			}
			out << YAML::EndMap;
		}

		if (entity.HasComponent<ComponentTag>()) {
			auto& component = entity.GetComponent<ComponentTag>();
			out << YAML::Key << "ComponentTag";
			out << YAML::BeginMap;
			out << YAML::Key << "Tag" << YAML::Value << component.Tag;
			out << YAML::EndMap;
		}

		/*if (entity.HasComponent<ComponentTextureMaterial>()) {
			auto& component = entity.GetComponent<ComponentTextureMaterial>();
			out << YAML::Key << "ComponentTextureMaterial";
			out << YAML::BeginMap;
			out << YAML::Key << "TextureID" << YAML::Value << component.Diffuse->GetID();
			out << YAML::EndMap;
		}*/

		if (entity.HasComponent<ComponentTransform>()) {
			out << YAML::Key << "ComponentTransform";
			out << YAML::BeginMap;
			auto& component = entity.GetComponent<ComponentTransform>();

			out << YAML::Key << "Translation" << YAML::Value << component.Translation;
			out << YAML::Key << "Rotation" << YAML::Value << component.Rotation;
			out << YAML::Key << "Scale" << YAML::Value << component.Scale;

			out << YAML::EndMap;
		}

		out << YAML::EndMap;
	}


	void SceneSerializer::Serialize(const Path& filepath) {
		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "Scene" << YAML::Value << "Untitled";

		out << YAML::Key << "Textures" << YAML::Value << YAML::BeginSeq;
		for (auto& t : ResourceManager::GetLoadedTextures()) {
			out << YAML::BeginMap;
			out << YAML::Key << "Texture" << YAML::Value << t->GetID();

			out << YAML::Key << "Path" << YAML::Value << t->GetPath().to_string();
			out << YAML::EndMap;
		}
		out << YAML::EndSeq;


		out << YAML::Key << "Shaders" << YAML::Value << YAML::BeginSeq;
		for (auto& t : ResourceManager::GetLoadedShaders()) {
			out << YAML::BeginMap;
			out << YAML::Key << "Shader" << YAML::Value << t->GetID();

			out << YAML::Key << "Path" << YAML::Value << t->GetPath().to_string();
			out << YAML::EndMap;
		}
		out << YAML::EndSeq;


		out << YAML::Key << "Models" << YAML::Value << YAML::BeginSeq;
		for (auto& t : ResourceManager::GetLoadedModels()) {
			out << YAML::BeginMap;
			out << YAML::Key << "Model" << YAML::Value << t->ID;

			out << YAML::Key << "Path" << YAML::Value << t->Path.to_string();
			out << YAML::EndMap;
		}
		out << YAML::EndSeq;

		out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;
        m_Scene->m_Registry.each([&](auto entityID) {
            Entity entity = { entityID, m_Scene.get() };
            if (!entity || entity.HasComponent<ComponentInternal>()) return;

            SerializeEntity(out, entity);
        });
		
        out << YAML::EndSeq;
        out << YAML::EndMap;

        ResourceManager::GetIO()->WriteText(filepath, out.c_str());
    }

	bool SceneSerializer::Deserialize(const Path& filepath)
	{
		YAML::Node data;
		try
		{
			data = YAML::LoadFile(filepath.PathString);
		}
		catch (YAML::ParserException e)
		{
			//SIMIX_CORE_ERROR("Failed to load .hazel file '{0}'\n     {1}", filepath, e.what());
			return false;
		}

		if (!data["Scene"])
			return false;

		std::string sceneName = data["Scene"].as<std::string>();
		//SIMIX_CORE_TRACE("Deserializing scene '{0}'", sceneName);

		auto textures = data["Textures"];
		if (textures) {
			for (auto texture : textures) {
				UUID uuid = texture["Texture"].as<UUID>();
				ResourceManager::GetOrLoadTexture(Path(texture["Path"].as<std::string>(), PathType::File), uuid);
			}
		}

		auto shaders = data["Shaders"];
		if (shaders) {
			for (auto shader : shaders) {
				UUID uuid = shader["Shader"].as<UUID>();
				ResourceManager::GetOrLoadShader(Path(shader["Path"].as<std::string>(), PathType::File), uuid);
			}
		}

		auto models = data["Models"];
		if (models) {
			for (auto model : models) {
				UUID uuid = model["Model"].as<UUID>();
				ResourceManager::GetOrLoadModel(Path(model["Path"].as<std::string>(), PathType::File), uuid);
			}
		}

		auto entities = data["Entities"];
		if (entities)
		{
			for (auto entity : entities)
			{
				UUID uuid = entity["Entity"].as<UUID>();

				//SIMIX_CORE_TRACE("Deserialized entity with ID = {0}", uuid);
				Entity deserializedEntity = m_Scene->CreateEntityWithUUID(uuid);

				auto tagComponent = entity["ComponentTag"];
				if (tagComponent) {
					std::string name;
					deserializedEntity.AddComponent<ComponentTag>(tagComponent["Tag"].as<std::string>());
				}

				auto transformComponent = entity["ComponentTransform"];
				if (transformComponent)
				{
					// Entities always have transforms
					auto& tc = deserializedEntity.AddComponent<ComponentTransform>();
					tc.Translation = transformComponent["Translation"].as<glm::vec3>();
					tc.Rotation = transformComponent["Rotation"].as<glm::vec3>();
					tc.Scale = transformComponent["Scale"].as<glm::vec3>();
				}

				//auto colorMaterialComponent = entity["ComponentColorMaterial"];
				//if (colorMaterialComponent) {
				//	auto& tc = deserializedEntity.AddComponent<ComponentColorMaterial>();
				//	tc.Color = colorMaterialComponent["Color"].as<glm::vec3>();
				//}

				////auto shaderComponent = entity["ComponentShader"];
				////if (shaderComponent) {
				////	auto& tc = deserializedEntity.AddComponent<ComponentShader>();
				////	tc.ShaderRef = ResourceManager::GetShader(shaderComponent["ShaderID"].as<UUID>());
				////}

				//auto textureComponent = entity["ComponentTextureMaterial"];
				//if (textureComponent) {
				//	auto& tc = deserializedEntity.AddComponent<ComponentTextureMaterial>();
				//	tc.Diffuse = ResourceManager::GetTexture(textureComponent["TextureID"].as<UUID>());
				//}

				//auto modelComponent = entity["ComponentModel"];
				//if (modelComponent) {
				//	auto& tc = deserializedEntity.AddComponent<ComponentModel>();
				//	auto isPrimitive = modelComponent["IsPrimitive"];

				//	if (isPrimitive) {
				//		tc.Model = ResourceManager::GetPrimitive(modelComponent["ModelID"].as<UUID>());
				//	}
				//	else {
				//		tc.Model = ResourceManager::GetModel(modelComponent["ModelID"].as<UUID>());
				//	}
				//}
			}
		}

		return true;
	}

    /*bool SceneSerializer::Deserialize(const Path& filepath) {

    }*/
}