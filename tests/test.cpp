#include <gtest/gtest.h>

#include "analyzer.h"

TEST(AnalyzerTest, EmptyDirectoryReturnsZero)
{
    AnalyzerConfig analyzerConfig = {};
    analyzerConfig.root_path = "../tests/no_files";

    Analyzer analyzer(analyzerConfig);

    EXPECT_EQ(analyzer.getLinesOfCode(), 0);
    EXPECT_EQ(analyzer.getTotalLinesOfCode(), 0);
}

TEST(AnalyzerTest, SingleFileCountsCorrectly)
{
    AnalyzerConfig analyzerConfig = {};
    analyzerConfig.root_path = "../tests/single_file";

    Analyzer analyzer(analyzerConfig);

    EXPECT_EQ(analyzer.getLinesOfCode(), 5);
    EXPECT_EQ(analyzer.getTotalLinesOfCode(), 11);
}

TEST(AnalyzerTest, MixedFilesCountsCorrectly)
{
    AnalyzerConfig analyzerConfig = {};
    analyzerConfig.root_path = "../tests/mixed_files";

    Analyzer analyzer(analyzerConfig);

    EXPECT_EQ(analyzer.getLinesOfCode(), 11);
    EXPECT_EQ(analyzer.getTotalLinesOfCode(), 22);
}
