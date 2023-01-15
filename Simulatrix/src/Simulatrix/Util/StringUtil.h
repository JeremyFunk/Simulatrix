#pragma once

namespace Simulatrix {
    std::vector<std::string> Split(const std::string& s, char delimiter);
    std::string Replace(const std::string& s, char find, char replace);
    std::string DirectoryUp(const std::string& path);
}