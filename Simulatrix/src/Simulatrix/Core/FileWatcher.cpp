#pragma once
#include "simixpch.h"
#include "FileWatcher.h"
#include <thread>
#include <Simulatrix/Util/StringUtil.h>

namespace Simulatrix {
    // Path has to end on backslash
    FileWatcher::FileWatcher(std::string pathToWatch, std::chrono::duration<int, std::milli> delay) : m_PathToWatch(pathToWatch), m_Delay(delay) {
        /*for (auto& file : std::filesystem::recursive_directory_iterator(pathToWatch)) {
            m_Paths[file.path().string()] = std::filesystem::last_write_time(file);
        }*/
    }

    void FileWatcher::Start() {
        int offset = 0;
        while (m_Running) {
            std::this_thread::sleep_for(m_Delay - std::chrono::milliseconds(offset));
            offset = RunIteration();
        }
    }

    int FileWatcher::RunIteration() {
        int offset = 0;
        std::vector<std::pair<Path, FileStatus>> toAdd;
        auto it = m_Paths.begin();
        while (it != m_Paths.end()) {
            if (!std::filesystem::exists(it->first)) {
                toAdd.push_back(std::pair<Path, FileStatus>(Path(it->first, std::filesystem::is_directory(it->first) ? PathType::Directory : PathType::File), FileStatus::Erased));
                it = m_Paths.erase(it);
            }
            else {
                it++;
            }
        }
        File root;
        root.SetName(m_PathToWatch.substr(0, m_PathToWatch.size() - 1));

        for (auto& file : std::filesystem::recursive_directory_iterator(m_PathToWatch)) {
            auto currentFileLastWriteTime = std::filesystem::last_write_time(file);

            if (!Contains(file.path().string())) {
                m_Paths[file.path().string()] = currentFileLastWriteTime;
                toAdd.push_back(std::pair<Path, FileStatus>(Path(file.path().string(), std::filesystem::is_directory(file.path().string()) ? PathType::Directory : PathType::File), FileStatus::Created));
            }
            else {
                if (m_Paths[file.path().string()] != currentFileLastWriteTime) {
                    m_Paths[file.path().string()] = currentFileLastWriteTime;
                    toAdd.push_back(std::pair<Path, FileStatus>(Path(file.path().string(), std::filesystem::is_directory(file.path().string()) ? PathType::Directory : PathType::File), FileStatus::Modified));
                }
            }

            auto relativePath = file.path().string().substr(m_PathToWatch.size());
            auto elements = Split(Replace(relativePath, '\\', '/'), '/');

            root.AddFile(elements, m_PathToWatch.substr(0, m_PathToWatch.size() - 1), file.is_directory());
        }
        while (!m_FileStructureMutex.try_lock()) {
            offset++;
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        m_FileStructure = root;
        m_FileStructure.SetParents();
        m_FileStructureMutex.unlock();

        while (!m_LastFileChangesMutex.try_lock()) {
            offset++;
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        m_LastFileChanges.insert(m_LastFileChanges.end(), toAdd.begin(), toAdd.end());
        m_LastFileChangesMutex.unlock();
        return offset;
    }
}