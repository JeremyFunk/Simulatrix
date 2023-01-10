#pragma once
#include "Simulatrix/Core/IOWrapper.h"
enum class FileStatus {Created, Modified, Erased};
namespace Simulatrix {
    class FileWatcher {
    public:
        FileWatcher() = default;
        FileWatcher(std::string pathToWatch, std::chrono::duration<int, std::milli> delay);

        void Stop() {
            m_Running = false;
        }

        bool Lock() {
            return m_LastFileChangesMutex.try_lock();
        }
        void Unlock() {
            m_LastFileChangesMutex.unlock();
        }
        void Start();
        // Make sure this object is locked before attempting a clear.
        void Clear() {
            m_LastFileChanges.clear();
        }
        std::vector<std::pair<Path, FileStatus>>::iterator begin() { return m_LastFileChanges.begin();}
        std::vector<std::pair<Path, FileStatus>>::iterator end() { return m_LastFileChanges.end(); }
    private:

        std::vector<std::pair<Path, FileStatus>> m_LastFileChanges;
        std::mutex m_LastFileChangesMutex;
        std::string m_PathToWatch;
        bool m_Running = true;
        std::chrono::duration<int, std::milli> m_Delay;
        std::unordered_map<std::string, std::filesystem::file_time_type> m_Paths;

        bool Contains(const std::string& key) {
            auto el = m_Paths.find(key);
            return el != m_Paths.end();
        }
    };
}