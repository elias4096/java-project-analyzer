#include "analyzer.h"

#include <atomic>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "thread_pool.h"

Analyzer::Analyzer(const AnalyzerConfig &config)
{
    m_Config = config;
}

uint32_t Analyzer::getLinesOfCode()
{
    return processJavaFiles([](std::ifstream &file) {
        uint32_t count = 0;
        std::string line = {};
        bool inBlockComment = false;

        while (std::getline(file, line))
        {
            line.erase(0, line.find_first_not_of(" \t\r\n"));

            if (line.empty())
                continue;

            if (inBlockComment)
            {
                if (line.find("*/") != std::string::npos)
                    inBlockComment = false;
                continue;
            }

            if (line.rfind("/*", 0) == 0)
            {
                inBlockComment = true;
                continue;
            }

            if (line.rfind("//", 0) == 0)
                continue;

            count++;
        }

        return count;
    });
}

uint32_t Analyzer::getTotalLinesOfCode()
{
    return processJavaFiles([](std::ifstream &file) {
        uint32_t count = 0;
        std::string line = {};
        while (std::getline(file, line))
            count++;

        return count;
    });
}

template <typename Function> uint32_t Analyzer::processJavaFiles(Function fn)
{
    std::atomic<uint32_t> result = 0;

    {
        ThreadPool pool(m_Config.thread_count);

        for (const auto &entry : std::filesystem::recursive_directory_iterator(m_Config.root_path))
        {
            if (!entry.is_regular_file())
                continue;

            if (entry.path().extension() != ".java")
                continue;

            pool.enqueue([path = entry.path(), &result, fn] {
                std::ifstream file(path);
                if (!file)
                {
                    std::cerr << "Warning: could not open " << path << std::endl;
                    return;
                }

                result += fn(file);
            });
        }
    }

    return result;
}
