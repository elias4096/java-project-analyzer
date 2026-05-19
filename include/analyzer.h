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

    uint32_t getLinesOfCode();

private:
    AnalyzerConfig m_Config = {};
};
