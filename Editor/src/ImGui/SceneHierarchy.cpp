#include "simixpch.h"
#include "SceneHierarchy.h"
#include <imgui.h>
#include <imgui_internal.h>
#include "Simulatrix/ResourceManager/ResourceManager.h"
#include "Simulatrix/Core/Core.h"
namespace Simulatrix {

	void SceneHierarchy::SetScene(const Ref<Scene>& context)
	{
		m_Scene = context;
		m_SelectionContext = {};
	}
	void SceneHierarchy::SetSelectedEntity(Entity entity)
	{
		m_SelectionContext = entity;
	}

    void SceneHierarchy::Render() {
        ImGui::Begin("Scene Hierarchy");
        //ImGui::TreeNodeEx("Camera", ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen, "Camera");
		m_Scene->m_Registry.each([&](auto entityID)
			{
				Entity entity{ entityID , m_Scene.get() };
				DrawEntityNode(entity);
			});

		/*if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
			m_SelectionContext = {};*/

		// Right-click on blank space
		/*if (ImGui::BeginPopupContextWindow(0, 1, false))
		{
			if (ImGui::MenuItem("Create Empty Entity"))
				m_Context->CreateEntity("Empty Entity");

			ImGui::EndPopup();
		}*/
        ImGui::End();


		ImGui::Begin("Properties");
		if (m_SelectionContext)
		{
			DrawComponents(m_SelectionContext);
		}

		ImGui::End();
    }

	void SceneHierarchy::DrawEntityNode(Entity entity) {
		auto& tag = entity.GetComponent<ComponentTag>().Tag;

		ImGuiTreeNodeFlags flags = ((m_SelectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		flags |= ImGuiTreeNodeFlags_SpanAvailWidth;
		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());
		if (ImGui::IsItemClicked())
		{
			m_SelectionContext = entity;
		}

		bool entityDeleted = false;
		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::MenuItem("Delete Entity"))
				entityDeleted = true;

			ImGui::EndPopup();
		}

		if (opened)
		{
			/*ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
			bool opened = ImGui::TreeNodeEx((void*)9817239, flags, tag.c_str());
			if (opened)
				ImGui::TreePop();*/
			ImGui::TreePop();
		}

		//if (entityDeleted)
		//{
		//	m_Scene->DestroyEntity(entity);
		//	if (m_SelectionContext == entity)
		//		m_SelectionContext = {};
		//}
	}


	static void DrawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f)
	{
		ImGuiIO& io = ImGui::GetIO();
		auto boldFont = io.Fonts->Fonts[0];

		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("X", buttonSize))
			values.x = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Y", buttonSize))
			values.y = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Z", buttonSize))
			values.z = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();

		ImGui::Columns(1);

		ImGui::PopID();
	}

	template<typename T, typename UIFunction>
	static void DrawComponent(const std::string& name, Entity entity, UIFunction uiFunction)
	{
		const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;
		if (entity.HasComponent<T>())
		{
			auto& component = entity.GetComponent<T>();
			ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
			float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
			ImGui::Separator();
			bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), treeNodeFlags, name.c_str());
			ImGui::PopStyleVar(
			);
			ImGui::SameLine(contentRegionAvailable.x - lineHeight * 0.5f);
			if (ImGui::Button("+", ImVec2{ lineHeight, lineHeight }))
			{
				ImGui::OpenPopup("ComponentSettings");
			}

			bool removeComponent = false;
			if (ImGui::BeginPopup("ComponentSettings"))
			{
				if (ImGui::MenuItem("Remove component"))
					removeComponent = true;

				ImGui::EndPopup();
			}

			if (open)
			{
				uiFunction(component);
				ImGui::TreePop();
			}

			if (removeComponent)
				entity.RemoveComponent<T>();
		}
	}

	void SceneHierarchy::DrawComponents(Entity entity)
	{
		if (entity.HasComponent<ComponentTag>())
		{
			auto& tag = entity.GetComponent<ComponentTag>().Tag;

			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			strncpy_s(buffer, sizeof(buffer), tag.c_str(), sizeof(buffer));
			if (ImGui::InputText("##Tag", buffer, sizeof(buffer)))
			{
				tag = std::string(buffer);
			}
		}

		ImGui::SameLine();
		ImGui::PushItemWidth(-1);

		if (ImGui::Button("Add Component"))
			ImGui::OpenPopup("AddComponent");

		if (ImGui::BeginPopup("AddComponent"))
		{

			ImGui::EndPopup();
		}

		ImGui::PopItemWidth();

		DrawComponent<ComponentTransform>("Transform", entity, [](auto& component){
			DrawVec3Control("Translation", component.Translation);
			glm::vec3 rotation = glm::degrees(component.Rotation);
			DrawVec3Control("Rotation", rotation);
			component.Rotation = glm::radians(rotation);
			DrawVec3Control("Scale", component.Scale, 1.0f);
		});

		DrawComponent<ComponentTextureMaterial>("Texture", entity, [](ComponentTextureMaterial& component) {
			ImGui::ImageButton((void*)(intptr_t)component.Diffuse->GetRendererID(), ImVec2(64, 64));

			if (ImGui::BeginDragDropTarget()) {
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM")) {
					const char* path = (const char*)payload->Data;

					component.Diffuse = ResourceManager::Get()->GetOrLoadTexture(Path(path, PathType::File));

					ImGui::EndDragDropTarget();
				}
			}

			ImGui::SameLine();
			ImGui::Text("Diffuse Texture");
		});

		//DrawComponent<CameraComponent>("Camera", entity, [](auto& component)
		//	{
		//		auto& camera = component.Camera;

		//		ImGui::Checkbox("Primary", &component.Primary);

		//		const char* projectionTypeStrings[] = { "Perspective", "Orthographic" };
		//		const char* currentProjectionTypeString = projectionTypeStrings[(int)camera.GetProjectionType()];
		//		if (ImGui::BeginCombo("Projection", currentProjectionTypeString))
		//		{
		//			for (int i = 0; i < 2; i++)
		//			{
		//				bool isSelected = currentProjectionTypeString == projectionTypeStrings[i];
		//				if (ImGui::Selectable(projectionTypeStrings[i], isSelected))
		//				{
		//					currentProjectionTypeString = projectionTypeStrings[i];
		//					camera.SetProjectionType((SceneCamera::ProjectionType)i);
		//				}

		//				if (isSelected)
		//					ImGui::SetItemDefaultFocus();
		//			}

		//			ImGui::EndCombo();
		//		}

		//		if (camera.GetProjectionType() == SceneCamera::ProjectionType::Perspective)
		//		{
		//			float perspectiveVerticalFov = glm::degrees(camera.GetPerspectiveVerticalFOV());
		//			if (ImGui::DragFloat("Vertical FOV", &perspectiveVerticalFov))
		//				camera.SetPerspectiveVerticalFOV(glm::radians(perspectiveVerticalFov));

		//			float perspectiveNear = camera.GetPerspectiveNearClip();
		//			if (ImGui::DragFloat("Near", &perspectiveNear))
		//				camera.SetPerspectiveNearClip(perspectiveNear);

		//			float perspectiveFar = camera.GetPerspectiveFarClip();
		//			if (ImGui::DragFloat("Far", &perspectiveFar))
		//				camera.SetPerspectiveFarClip(perspectiveFar);
		//		}

		//		if (camera.GetProjectionType() == SceneCamera::ProjectionType::Orthographic)
		//		{
		//			float orthoSize = camera.GetOrthographicSize();
		//			if (ImGui::DragFloat("Size", &orthoSize))
		//				camera.SetOrthographicSize(orthoSize);

		//			float orthoNear = camera.GetOrthographicNearClip();
		//			if (ImGui::DragFloat("Near", &orthoNear))
		//				camera.SetOrthographicNearClip(orthoNear);

		//			float orthoFar = camera.GetOrthographicFarClip();
		//			if (ImGui::DragFloat("Far", &orthoFar))
		//				camera.SetOrthographicFarClip(orthoFar);

		//			ImGui::Checkbox("Fixed Aspect Ratio", &component.FixedAspectRatio);
		//		}
		//	});

	}


	template<typename T>
	void SceneHierarchy::DisplayAddComponentEntry(const std::string& entryName) {
		if (!m_SelectionContext.HasComponent<T>())
		{
			if (ImGui::MenuItem(entryName.c_str()))
			{
				m_SelectionContext.AddComponent<T>();
				ImGui::CloseCurrentPopup();
			}
		}
	}
}