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

AnalyzerResult Analyzer::analyze()
{
    std::mutex resultMutex;
    AnalyzerResult result = {};

    {
        ThreadPool threadPool(m_Config.threadCount);

        // Recursively goes through all files
        for (const auto &entry : std::filesystem::recursive_directory_iterator(m_Config.projectPath))
        {
            // Ensure its a file
            if (!entry.is_regular_file())
                continue;

            // Ensure its a java file
            if (entry.path().extension() != ".java")
                continue;

            threadPool.enqueue([this, path = entry.path(), &result, &resultMutex] {
                std::ifstream file(path);
                if (!file)
                {
                    std::cerr << "Warning: could not open " << path << std::endl;
                    return;
                }

                AnalyzerResult local = this->processJavaFile(path);
                std::lock_guard<std::mutex> lock(resultMutex);
                result += local;
            });
        }
    }

    return result;
}

AnalyzerResult Analyzer::processJavaFile(std::filesystem::path filepath)
{
    AnalyzerResult result = {};
    result.javaFilesCount = 1;

    std::string line = {};
    bool inBlockComment = false;

    std::ifstream file(filepath);
    if (!file)
        return {};

    while (std::getline(file, line))
    {
        result.totalLinesOfCode++;

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

        result.linesOfCode++;

        if (!m_Config.search.empty())
        {
            if (line.find(m_Config.search) != std::string::npos)
            {
                SearchResult searchResult = {};
                searchResult.filename = filepath.filename().string();
                searchResult.lineNumber = result.totalLinesOfCode;
                result.searchResults.emplace_back(searchResult);
            }
        }

        if (line.find("class ") != std::string::npos)
            result.javaClassesCount++;

        if (line.find("(") != std::string::npos && line.find(")") != std::string::npos &&
            line.find("{") != std::string::npos)
            result.javaMethodsCount++;
    }

    return result;
}
