#include <iomanip>
#include <iostream>

#include "analyzer.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Error: invalid arguments" << std::endl;
        return 1;
    }

    AnalyzerConfig analyzerConfig = {};
    analyzerConfig.projectPath = argv[1];
    analyzerConfig.threadCount = 4;

    Analyzer analyzer(analyzerConfig);
    AnalyzerResult analyzerResult = analyzer.analyze();

    std::cout << "\n<=== Java Project Analysis ===>\n\n";
    std::cout << std::left;
    std::cout << std::setw(20) << "Total java files:" << analyzerResult.javaFilesCount << "\n";
    std::cout << std::setw(20) << "Logical lines:" << analyzerResult.linesOfCode << "\n";
    std::cout << std::setw(20) << "Total lines:" << analyzerResult.totalLinesOfCode << "\n";
    std::cout << std::setw(20) << "Classes found:" << analyzerResult.javaClassesCount << "\n";
    std::cout << std::setw(20) << "Methods found:" << analyzerResult.javaMethodsCount << "\n";

    return 0;
}
