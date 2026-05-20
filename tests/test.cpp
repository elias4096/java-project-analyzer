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

TEST(AnalyzerTest, MixedFilesCountsCorrectly)
{
    AnalyzerConfig analyzerConfig = {};
    analyzerConfig.projectPath = "../tests/mixed_files";

    Analyzer analyzer(analyzerConfig);
    AnalyzerResult analyzerResult = analyzer.analyze();

    EXPECT_EQ(analyzerResult.linesOfCode, 12);
    EXPECT_EQ(analyzerResult.totalLinesOfCode, 23);
    EXPECT_EQ(analyzerResult.javaFilesCount, 2);
    EXPECT_EQ(analyzerResult.javaClassesCount, 2);
    EXPECT_EQ(analyzerResult.javaMethodsCount, 2);
}
