#include <gtest/gtest.h>

#include "analyzer.h"

TEST(AnalyzerTest, EmptyDirectoryReturnsZero)
{
    AnalyzerConfig analyzerConfig = {};
    analyzerConfig.projectPath = "../tests/no_files";

    Analyzer analyzer(analyzerConfig);
    AnalyzerResult analyzerResult = analyzer.analyze();

    EXPECT_EQ(analyzerResult.linesOfCode, 0);
    EXPECT_EQ(analyzerResult.totalLinesOfCode, 0);
    EXPECT_EQ(analyzerResult.javaFilesCount, 0);
    EXPECT_EQ(analyzerResult.javaClassesCount, 0);
    EXPECT_EQ(analyzerResult.javaMethodsCount, 0);
}

TEST(AnalyzerTest, SingleFileCountsCorrectly)
{
    AnalyzerConfig analyzerConfig = {};
    analyzerConfig.projectPath = "../tests/single_file";

    Analyzer analyzer(analyzerConfig);
    AnalyzerResult analyzerResult = analyzer.analyze();

    EXPECT_EQ(analyzerResult.linesOfCode, 5);
    EXPECT_EQ(analyzerResult.totalLinesOfCode, 11);
    EXPECT_EQ(analyzerResult.javaFilesCount, 1);
    EXPECT_EQ(analyzerResult.javaClassesCount, 1);
    EXPECT_EQ(analyzerResult.javaMethodsCount, 1);
}

TEST(AnalyzerTest, MixedFilesSearchCorrectly)
{
    AnalyzerConfig analyzerConfig = {};
    analyzerConfig.projectPath = "../tests/mixed_files";
    analyzerConfig.search = "public";

    Analyzer analyzer(analyzerConfig);
    AnalyzerResult analyzerResult = analyzer.analyze();

    EXPECT_EQ(analyzerResult.linesOfCode, 16);
    EXPECT_EQ(analyzerResult.totalLinesOfCode, 35);
    EXPECT_EQ(analyzerResult.javaFilesCount, 2);
    EXPECT_EQ(analyzerResult.javaClassesCount, 2);
    EXPECT_EQ(analyzerResult.javaMethodsCount, 3);
    EXPECT_EQ(analyzerResult.searchResults.size(), 2);
}
