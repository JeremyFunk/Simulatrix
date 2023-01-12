#pragma once
#include <string>
#include <vector>

namespace Simulatrix {
    enum class PathType{
        File, Directory
    };
    struct Path {
        std::string PathString;
        std::string FileEnding;
        std::string FileName;
        std::string FileNameNoEnding;
        std::string Directory;
        PathType Type;

        Path(const std::string& path, PathType type) {
            PathString = path;
            Type = type;
            if (type == PathType::File) {
                FileName = path.substr(path.find_last_of("\\") + 1);
                FileEnding = FileName.substr(FileName.find_last_of(".") + 1);
                FileNameNoEnding = FileName.substr(0, FileName.size() - FileEnding.size() - 1   );
                Directory = path.substr(0, path.find_last_of("\\") + 1);
            }
            else {
                Directory = path;
            }
        }
        Path() {

        }
        std::ostream& operator<<(std::ostream& os) {
            return os << PathString;
        }
        std::string to_string() const {
            return PathString;
        }
    };


    class IOWrapper {
    public:
        virtual bool Exists(const Path& path) = 0;
        virtual std::vector<Path> GetDirectoryContent(const Path& path) = 0;
        virtual bool CreateDir(const Path& path) = 0;
        virtual bool Delete(const Path& path) = 0;
        virtual bool Copy(const Path& src, const Path& dest) = 0;
        virtual bool Move(const Path& src, const Path& dest) = 0;
        virtual std::uintmax_t GetFileSize(const Path& path) = 0;
        virtual std::time_t GetLastModifiedTime(const Path& path) = 0;
        virtual bool IsDirectory(const Path& path) = 0;
        virtual Path GetCurrentDir() = 0;
        virtual Path GetTempDirectory() = 0;
        virtual std::string ReadText(const Path& path) = 0;
        virtual std::vector<std::string> ReadTextLines(const Path& path) = 0;
        virtual bool WriteText(const Path& path, const std::string& data) = 0;
        virtual std::vector<std::uint8_t> ReadBinary(const Path& path) = 0;
        virtual bool WriteBinary(const Path& path, const std::vector<std::uint8_t>& data) = 0;
    };
}