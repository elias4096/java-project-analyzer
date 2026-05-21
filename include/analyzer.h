#pragma once

#include <cstdint>
#include <filesystem>
#include <string>
#include <vector>

struct AnalyzerConfig
{
    size_t threadCount = 4;
    std::filesystem::path projectPath = {};
    std::string search = {};
};

struct SearchResult
{
    std::string filename = {};
    uint32_t lineNumber = {};
};

struct AnalyzerResult
{
    uint32_t linesOfCode = {};
    uint32_t totalLinesOfCode = {};
    uint32_t javaFilesCount = {};
    uint32_t javaClassesCount = {};
    uint32_t javaMethodsCount = {};
    std::vector<SearchResult> searchResults = {};

    AnalyzerResult &operator+=(const AnalyzerResult &other)
    {
        linesOfCode += other.linesOfCode;
        totalLinesOfCode += other.totalLinesOfCode;
        javaFilesCount += other.javaFilesCount;
        javaClassesCount += other.javaClassesCount;
        javaMethodsCount += other.javaMethodsCount;
        searchResults.insert(searchResults.end(), other.searchResults.begin(), other.searchResults.end());
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

    AnalyzerResult processJavaFile(std::filesystem::path filepath);
};
