#pragma once

#include <cstdint>
#include <string>

struct AnalyzerConfig
{
    std::string projectPath;
    size_t threadCount = 4;
};

struct AnalyzerResult
{
    uint32_t linesOfCode = {};
    uint32_t totalLinesOfCode = {};
    uint32_t javaFilesCount = {};
    uint32_t javaClassesCount = {};
    uint32_t javaMethodsCount = {};

    AnalyzerResult &operator+=(const AnalyzerResult &other)
    {
        linesOfCode += other.linesOfCode;
        totalLinesOfCode += other.totalLinesOfCode;
        javaFilesCount += other.javaFilesCount;
        javaClassesCount += other.javaClassesCount;
        javaMethodsCount += other.javaMethodsCount;
        return *this;
    }
};

class Analyzer
{
  public:
    explicit Analyzer(const AnalyzerConfig &config);

    AnalyzerResult analyze();

  private:
    AnalyzerConfig m_Config = {};

    template <typename Function> AnalyzerResult processJavaFiles(Function fn);
};
