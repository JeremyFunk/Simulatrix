#pragma once
#include "Simulatrix/Core/IOWrapper.h"
#include "Simulatrix/Core/UUID.h"
enum class FileStatus {Created, Modified, Erased};
namespace Simulatrix {
    class File {
    private:
        std::vector<File> m_Files;
        std::string m_Name;
        Path m_Path;
        File* m_Parent = nullptr;
        bool m_IsDirectory = true;
    public:
        UUID ID;

        void AddFile(std::vector<std::string> path, std::string fullPath, bool isDirectory, int index = 0) {
            m_Path = Path(fullPath, PathType::Directory);
            if (index == path.size() - 1) {
                File newFile;
                m_Files.push_back(newFile);
                m_Files[m_Files.size() - 1].m_Name = path[index];
                m_Files[m_Files.size() - 1].m_IsDirectory = isDirectory;
                m_Files[m_Files.size() - 1].m_Path = Path(fullPath + "\\" + path[index], isDirectory ?  PathType::Directory : PathType::File);
                return;
            }
            for (int i = 0; i < m_Files.size(); i++) {
                if (m_Files[i].m_Name == path[index]) {
                    m_Files[i].AddFile(path, fullPath + "\\" + path[index], isDirectory, index + 1);
                    return;
                }
            }
            File newFile;
            m_Files.push_back(newFile);
            m_Files[m_Files.size() - 1].m_Name = path[index];
            m_Files[m_Files.size() - 1].m_Path = Path(fullPath + "\\" + path[index], PathType::Directory);
        }

        Path& GetPath()  {
            return m_Path;
        }
        std::vector<File>& GetFiles()  {
            return m_Files;
        }
        std::string& GetName()  {
            return m_Name;
        }

        bool IsFile() const {
            return !m_IsDirectory;
        }
        bool IsDirectory() const {
            return m_IsDirectory;
        }

        File* GetParent() {
            return m_Parent;
        }

        void SetName(std::string name) {
            m_Name = name;
        }

        void SetParents() {
            for (int i = 0; i < m_Files.size(); i++) {
                m_Files[i].m_Parent = this;
                m_Files[i].SetParents();
            }
        }

        File Clone() const {
            File c;
            for (auto& f : m_Files) {
                c.m_Files.push_back(f.Clone());
            }
            c.m_Name = m_Name;
            c.m_IsDirectory = m_IsDirectory;
            c.m_Path = m_Path;
            return c;
        }
    };

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
        bool LockFileStructure() {
            return m_FileStructureMutex.try_lock();
        }
        void UnlockFileStructure() {
            m_FileStructureMutex.unlock();
        }
        void Start();
        int RunIteration();
        // Make sure this object is locked before attempting a clear.
        void Clear() {
            m_LastFileChanges.clear();
        }
        std::vector<std::pair<Path, FileStatus>>::iterator begin() { return m_LastFileChanges.begin();}
        std::vector<std::pair<Path, FileStatus>>::iterator end() { return m_LastFileChanges.end(); }

        const File& GetFileStructure() {
            return m_FileStructure;
        }

    private:

        std::vector<std::pair<Path, FileStatus>> m_LastFileChanges;
        File m_FileStructure;
        std::mutex m_LastFileChangesMutex;
        std::mutex m_FileStructureMutex;
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