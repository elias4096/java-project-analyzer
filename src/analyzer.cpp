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
    return processJavaFiles([](std::ifstream &file) {
        AnalyzerResult result = {};
        result.javaFilesCount++;

        std::string line = {};
        bool inBlockComment = false;

        while (std::getline(file, line))
        {
            result.totalLinesOfCode++;

            line.erase(0, line.find_first_not_of(" \t\r\n"));

            if (line.empty())
                continue;

            // handle block comments
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

            // single line comment
            if (line.rfind("//", 0) == 0)
                continue;

            result.linesOfCode++;

            if (line.find("class ") != std::string::npos)
                result.javaClassesCount++;

            if (line.find("(") != std::string::npos && line.find(")") != std::string::npos &&
                line.find("{") != std::string::npos)
                result.javaMethodsCount++;
        }

        return result;
    });
}

template <typename Function> AnalyzerResult Analyzer::processJavaFiles(Function fn)
{
    AnalyzerResult result = {};
    std::mutex resultMutex;

    {
        ThreadPool pool(m_Config.threadCount);

        for (const auto &entry : std::filesystem::recursive_directory_iterator(m_Config.projectPath))
        {
            if (!entry.is_regular_file())
                continue;

            if (entry.path().extension() != ".java")
                continue;

            pool.enqueue([path = entry.path(), &result, &resultMutex, fn] {
                std::ifstream file(path);
                if (!file)
                {
                    std::cerr << "Warning: could not open " << path << std::endl;
                    return;
                }

                AnalyzerResult local = fn(file);
                std::lock_guard<std::mutex> lock(resultMutex);
                result += local;
            });
        }
    }

    return result;
}
