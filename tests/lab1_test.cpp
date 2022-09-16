#include <gtest/gtest.h>

#include <array>
#include <filesystem>
#include <fstream>
#include <memory>

namespace fs = std::filesystem;

extern "C" {
    #include <parent.h>
}

TEST(FirstLabTests, SimpleTest) {
    const char* fileWithInput = "input.txt";
    const char* fileWithOutput = "output.txt";

    constexpr int inputSize = 4;

    std::array<const char*, inputSize> input = {
            "1 2 3 4",
            "0 3 2",
            "-10 -10 -10",
            "1337"
    };

    std::array<int, inputSize> expectedOutput = {
            10, 5, -30, 1337
    };

    {
        auto inFile = std::ofstream(fileWithInput);

        inFile << fileWithOutput << '\n';

        for(const auto& line : input) {
            inFile<< line << '\n';
        }
    }

    auto deleter = [](FILE* file) {
        fclose(file);
    };

    std::unique_ptr<FILE, decltype(deleter)> inFile(fopen(fileWithInput, "r"), deleter);

    ParentRoutine(getenv("PATH_TO_CHILD"), inFile.get());

    auto outFile = std::ifstream(fileWithOutput);

    ASSERT_TRUE(outFile.good());

    int result;

    for(int i : expectedOutput) {
        outFile >> result;
        EXPECT_EQ(result, i);
    }

    auto removeIfExists = [](const char* path) {
        if(fs::exists(path)) {
            fs::remove(path);
        }
    };

    removeIfExists(fileWithInput);
    removeIfExists(fileWithOutput);
}