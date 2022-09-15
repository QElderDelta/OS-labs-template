#include "utils.h"

#include <ctype.h>

int main(const int argc, const char* argv[]) {
    if(argc != 2) {
        printf("Necessary arguments were not provided\n");
        exit(EXIT_FAILURE);
    }

    FILE* out = fopen(argv[1], "w");
    if(!out) {
        printf("Failed to open file\n");
        exit(EXIT_FAILURE);
    }

    char* input = NULL;

    int strLength;
    int result;
    char flag;

    while((input = ReadString(stdin)) != NULL) {
        strLength = strlen(input);
        result = 0;
        int start = 0;

        flag = 0;

        for(int end = 0; end < strLength; ++end) {
            if(isspace(input[end])) {
                flag = 1;
                input[end] = '\0';
                result += atoi(input + start);
                start = end + 1;
            }
        }

        if(start != strLength) {
            result += atoi(input + start);
        }

        if(flag == 1) {
            fprintf(out, "%d\n", result);
        }

        free(input);
    }

    fclose(out);

    return 0;
}
