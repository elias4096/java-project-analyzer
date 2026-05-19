#include "analyzer.h"

#include <fstream>
#include <filesystem>
#include <string>

Analyzer::Analyzer(const AnalyzerConfig &config)
{
    m_Config = config;
}

uint32_t Analyzer::getLinesOfCode()
{
    uint32_t result = 0;
    std::filesystem::recursive_directory_iterator it(m_Config.root_path);

    for (const auto &entry : it)
    {
        if (!entry.is_regular_file())
            continue;

        if (entry.path().extension() != ".java")
            continue;

        std::ifstream file(entry.path());
        if (!file)
        {
            return false;
        }

        std::string line;

        while (std::getline(file, line))
            result++;
    }

    return result;
}
