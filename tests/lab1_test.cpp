#include <gtest/gtest.h>

#include <fstream>

extern "C" {
    #include <parent.h>
}

TEST(FirstLabTests, SimpleTest) {
    const char* fileWithInput = "input.txt";
    const char* fileWithOutput = "output.txt";


    const char* input[] = {
            "1 2 3 4",
            "0 3 2",
            "-10 -10 -10",
            "1337"
    };

    const int expectedOutput[] = {
            10, 5, -30, 1337
    };

    {
        auto inFile = std::ofstream(fileWithInput);

        inFile << fileWithOutput << '\n';

        for(const auto& line : input) {
            inFile<< line << '\n';
        }
    }

    FILE* inFile = fopen(fileWithInput, "r");

    ParentRoutine(getenv("PATH_TO_CHILD"), inFile);

    fclose(inFile);

    auto outFile = std::ifstream(fileWithOutput);

    int result;

    for(int i : expectedOutput) {
        outFile >> result;
        EXPECT_EQ(result, i);
    }

}