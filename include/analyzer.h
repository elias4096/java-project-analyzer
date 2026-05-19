#pragma once

#include <cstdint>
#include <string>

struct AnalyzerConfig
{
    std::string root_path;
    int thread_count = 4;
};

class Analyzer
{
public:
    explicit Analyzer(const AnalyzerConfig &config);

    // Ignores comments or empty lines.
    uint32_t getLinesOfCode();

    // Ignores nothing, every single line counts.
    uint32_t getTotalLinesOfCode();

private:
    AnalyzerConfig m_Config = {};

    template <typename Func>
    uint32_t processJavaFiles(Func fn);
};
