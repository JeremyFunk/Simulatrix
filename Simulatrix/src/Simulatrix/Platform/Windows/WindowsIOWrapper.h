#pragma once
#include "Simulatrix/Core/IOWrapper.h"

namespace Simulatrix {
    class WindowsIOWrapper : public IOWrapper {
    public:
        WindowsIOWrapper() {

        }
        virtual Path OpenFile(const char* filter) override;
        virtual Path SaveFile(const char* filter) override;

        virtual bool Exists(const Path& path) override;
        virtual std::vector<Path> GetDirectoryContent(const Path& path) override;
        virtual bool CreateDir(const Path& path) override;
        virtual bool Delete(const Path& path) override;
        virtual bool Copy(const Path& src, const Path& dest) override;
        virtual bool Move(const Path& src, const Path& dest) override;
        virtual std::uintmax_t GetFileSize(const Path& path) override;
        virtual std::time_t GetLastModifiedTime(const Path& path) override;
        virtual bool IsDirectory(const Path& path) override;
        virtual Path GetCurrentDir() override;
        virtual Path GetTempDirectory() override;
        virtual std::string ReadText(const Path& path) override;
        virtual std::vector<std::string> ReadTextLines(const Path& path) override;
        virtual bool WriteText(const Path& path, const std::string& data) override;
        virtual std::vector<std::uint8_t> ReadBinary(const Path& path) override;
        virtual bool WriteBinary(const Path& path, const std::vector<std::uint8_t>& data) override;
    };
}