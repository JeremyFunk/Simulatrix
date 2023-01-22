#include "simixpch.h"
#include "ContentBrowser.h"
#include <ImGui/imgui.h>
#include "Simulatrix/ResourceManager/ResourceManager.h"
#include <Simulatrix/Util/StringUtil.h>

namespace Simulatrix {
	static std::string s_SelectedPath;
	File* DirectoryTreeViewRecursive(File* file)
	{
		ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_SpanFullWidth;

		bool any_node_clicked = false;
		int index = 0;
		File* SelectedFile = nullptr;
		for (File& entry : file->GetFiles())
		{
			ImGuiTreeNodeFlags node_flags = base_flags;
			const bool is_selected = s_SelectedPath == entry.GetPath().PathString;
			if (is_selected) {
				node_flags |= ImGuiTreeNodeFlags_Selected;
				auto temp = file->GetFiles();
				SelectedFile = &(file->GetFiles()[index]);
			}

			bool entryIsFile = entry.IsFile();
			if (entryIsFile)
				node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
			bool contains = s_SelectedPath.find(entry.GetPath().PathString) == 0;
			if (contains) {
				ImGui::SetNextItemOpen(true);
			}
			bool node_open = ImGui::TreeNodeEx(entry.GetPath().PathString.c_str(), node_flags, entry.GetName().c_str());

			if (ImGui::IsItemClicked())
			{
				s_SelectedPath = entry.GetPath().PathString;
				any_node_clicked = true;
			}

			if (!entryIsFile)
			{
				if (node_open)
				{
					auto clickState = DirectoryTreeViewRecursive(&entry);

					if (clickState != nullptr)
						SelectedFile = clickState;

					ImGui::TreePop();
				}
				else if(contains){
					s_SelectedPath = DirectoryUp(s_SelectedPath);
				}
			}
			index++;
		}

		return SelectedFile;
	}


    void ContentBrowser::Render() {

        auto fileStructure = ResourceManager::Get()->GetFileStructure();

        ImGui::Begin("Directories");

		auto SelectedFile = DirectoryTreeViewRecursive(&fileStructure);

		if (SelectedFile == nullptr) {
			SelectedFile = &fileStructure;
		}

        ImGui::End();

        ImGui::Begin("Content");
		float padding = 8.f;
		float thumbnailSize = 64.f;
		float cellSize = padding + thumbnailSize;
		float panelWidth = ImGui::GetContentRegionAvail().x;
		int columns = (int)(panelWidth / cellSize);
		if (columns < 1) {
			columns = 1;
		}
		File* relevantFile = SelectedFile;
		if (SelectedFile->IsFile()) {
			relevantFile = SelectedFile->GetParent();
		}
		if (ImGui::BeginTable("Files", columns, ImGuiTableFlags_SizingFixedFit, ImVec2(cellSize * columns, cellSize))) {
			int i = 0;
			for (File& file : relevantFile->GetFiles()) {
				ImGui::TableNextColumn();
				Ref<Texture2D> icon;
				Path& path = file.GetPath();
				bool isSelected = path.PathString == s_SelectedPath;
				if (file.IsDirectory()) {
					icon = m_IconLibrary->GetIconByName("folder");
				}
				else if (path.FileEnding == "bmp") {
					icon = m_IconLibrary->GetIconByName("bmp");
				}
				else if (path.FileEnding == "jpg") {
					icon = m_IconLibrary->GetIconByName("jpg");
				}
				else if (path.FileEnding == "mp3") {
					icon = m_IconLibrary->GetIconByName("mp3");
				}
				else if (path.FileEnding == "png") {
					icon = m_IconLibrary->GetIconByName("png");
				}
				else {
					icon = m_IconLibrary->GetIconByName("document");
				}
				auto cursor = ImGui::GetCursorScreenPos();

				ImVec4 bgColor = ImVec4(0.0, 0.0, 0.0, 0.0);
				if (isSelected) {
					bgColor = ImVec4(0.6f, 0.6f, 0.6f, 0.4f);
				}
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
				ImGui::ImageButton((void*)(intptr_t)icon->GetRendererID(), ImVec2(thumbnailSize, thumbnailSize), ImVec2(0, 1), ImVec2(1, 0), 0, bgColor);
				if (file.IsDirectory() && ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) {
					s_SelectedPath = path.PathString;
				}
				else if (file.IsFile() && ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
					s_SelectedPath = path.PathString;
				}
				ImGui::PopStyleColor();

				if (ImGui::IsItemHovered() && ImGui::BeginDragDropSource()) {
					const char* itemPath = path.PathString.c_str();
					ImGui::SetDragDropPayload("CONTENT_BROWSER_ITEM", itemPath, (strlen(itemPath) + 1) * sizeof(char), ImGuiCond_Once);
					ImGui::EndDragDropSource();
				}

				float currentWidth = ImGui::GetColumnWidth(i);
				ImGui::SetCursorPosX(ImGui::GetCursorPosX() + (thumbnailSize - ImGui::CalcTextSize(file.GetName().c_str()).x) / 2.f);
				ImGui::Text(file.GetName().c_str());

				i++;
			}
			ImGui::EndTable();
		}
		
        ImGui::End();

    }
}