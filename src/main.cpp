#include <filesystem>
#include <iomanip>
#include <iostream>

#include "analyzer.h"

int main(int argc, char *argv[])
{
    std::string search = {};

    std::filesystem::path path = std::filesystem::canonical(argv[0]).parent_path();

    for (int i = 1; i < argc; i++)
    {
        std::string arg = argv[i];

        if (arg == "--path" && i + 1 < argc)
        {
            path = std::filesystem::path(argv[++i]);
        }
        else if (arg == "--search" && i + 1 < argc)
        {
            search = argv[++i];
        }
        else
        {
            std::cerr << "Error: invalid arguments\n";
            return EXIT_FAILURE;
        }
    }

    AnalyzerConfig analyzerConfig = {};
    analyzerConfig.threadCount = 4;
    analyzerConfig.projectPath = path;
    analyzerConfig.search = search;

    Analyzer analyzer(analyzerConfig);

    AnalyzerResult analyzerResult = analyzer.analyze();
    std::cout << "<=== Java Project Analysis ===>" << std::endl << std::endl;
    std::cout << std::left;
    std::cout << std::setw(26) << "Java files:" << analyzerResult.javaFilesCount << "\n";
    std::cout << std::setw(26) << "Lines of code:" << analyzerResult.linesOfCode << "\n";
    std::cout << std::setw(26) << "Total lines of code:" << analyzerResult.totalLinesOfCode << "\n";
    std::cout << std::setw(26) << "Classes:" << analyzerResult.javaClassesCount << "\n";
    std::cout << std::setw(26) << "Methods:" << analyzerResult.javaMethodsCount << "\n";

    if (!analyzerConfig.search.empty())
    {
        std::cout << std::endl;

        std::cout << "Found " << analyzerResult.searchResults.size() << " matches from search ("
                  << analyzerConfig.search << "):" << std::endl;

        for (size_t i = 0; i < analyzerResult.searchResults.size(); i++)
        {
            std::cout << i + 1 << ". " << analyzerResult.searchResults[i].filename << ":"
                      << analyzerResult.searchResults[i].lineNumber << std::endl;
        }
    }

    return EXIT_SUCCESS;
}
