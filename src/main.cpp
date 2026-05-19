#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

#include "analyzer.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "[ERROR] Invalid arguments" << std::endl;
        return 1;
    }

    AnalyzerConfig analyzerConfig = {};
    analyzerConfig.root_path = argv[1];
    analyzerConfig.thread_count = 4;

    Analyzer analyzer(analyzerConfig);

    std::cout << analyzer.getLinesOfCode() << " total lines of java code found." << std::endl;

    return 0;
}
