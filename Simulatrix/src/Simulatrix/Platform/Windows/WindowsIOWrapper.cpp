#include <simixpch.h>
#include "WindowsIOWrapper.h"

namespace Simulatrix {
    template <typename TP>
    std::time_t to_time_t(TP tp)
    {
        using namespace std::chrono;
        auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now()
            + system_clock::now());
        return system_clock::to_time_t(sctp);
    }

    bool WindowsIOWrapper::Exists(const Path& path)
    {
        return std::filesystem::exists(path.PathString);
    }
    std::vector<Path> WindowsIOWrapper::GetDirectoryContent(const Path& path)
    {
        std::vector<Path> result;

        for (const auto& entry : std::filesystem::directory_iterator(path.PathString))
        {
            if (!entry.is_directory())
            {
                result.push_back(Path(entry.path().filename().string(), PathType::File));
            }
        }

        return result;
    }

    bool WindowsIOWrapper::CreateDir(const Path& path)
    {
        return std::filesystem::create_directory(path.PathString);
    }

    bool WindowsIOWrapper::Delete(const Path& path)
    {
        return std::filesystem::remove(path.PathString);
    }

    bool WindowsIOWrapper::Copy(const Path& src, const Path& dest)
    {
        try
        {
            std::filesystem::copy(src.PathString, dest.PathString);
            return true;
        }
        catch (...)
        {
            return false;
        }
    }

    bool WindowsIOWrapper::Move(const Path& src, const Path& dest)
    {
        try
        {
            std::filesystem::rename(src.PathString, dest.PathString);
            return true;
        }
        catch (...)
        {
            return false;
        }
    }

    std::uintmax_t WindowsIOWrapper::GetFileSize(const Path& path)
    {
        return std::filesystem::file_size(path.PathString);
    }

    std::time_t WindowsIOWrapper::GetLastModifiedTime(const Path& path)
    {
        return to_time_t(std::filesystem::last_write_time(path.PathString));
        
    }
    bool WindowsIOWrapper::IsDirectory(const Path& path)
    {
        return std::filesystem::is_directory(path.PathString);
    }
    Path WindowsIOWrapper::GetCurrentDir()
    {
        auto temp = std::filesystem::current_path().string();
        return Path(std::filesystem::current_path().string(), PathType::Directory);
    }
    Path WindowsIOWrapper::GetTempDirectory()
    {
        wchar_t buffer[MAX_PATH];
        GetTempPath(MAX_PATH, buffer);
        std::wstring ws(buffer);
        return Path(std::string(ws.begin(), ws.end()), PathType::Directory);
    }
    std::string WindowsIOWrapper::ReadText(const Path& path)
    {
        std::string result;

        std::ifstream input(path.PathString);
        if (input)
        {
            result = std::string((std::istreambuf_iterator<char>(input)),
                std::istreambuf_iterator<char>());
        }

        return result;
    }
    std::vector<std::string> WindowsIOWrapper::ReadTextLines(const Path& path) {
        std::vector<std::string> result;

        std::ifstream input(path.PathString);
        if (input)
        {
            std::string curline;
            while (std::getline(input, curline))
            {
                result.push_back(curline);
            }
        }

        return result;
    }

    bool WindowsIOWrapper::WriteText(const Path& path, const std::string& data)
    {
        std::ofstream output(path.PathString);
        if (!output)
        {
            return false;
        }

        output << data;
        return true;
    }

    std::vector<std::uint8_t> WindowsIOWrapper::ReadBinary(const Path& path)
    {
        std::vector<std::uint8_t> result;

        std::ifstream input(path.PathString, std::ios::binary);
        if (input)
        {
            input.unsetf(std::ios::skipws);
            result = std::vector<std::uint8_t>((std::istreambuf_iterator<char>(input)),
                std::istreambuf_iterator<char>());
        }

        return result;
    }

    bool WindowsIOWrapper::WriteBinary(const Path& path, const std::vector<std::uint8_t>& data)
    {
        std::ofstream output(path.PathString, std::ios::binary);
        if (!output)
        {
            return false;
        }

        output.write(reinterpret_cast<const char*>(data.data()), data.size());
        return true;
    }
}