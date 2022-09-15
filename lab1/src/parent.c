#include "parent.h"
#include "utils.h"

#include <sys/wait.h>

void ParentRoutine(const char* pathToChild, FILE* stream) {
    char fileName[256];
    fscanf(stream, "%s\n", fileName);

    int parentPipe[2];
    CreatePipe(parentPipe);

    int pid = fork();

    if(pid == 0) {
        close(parentPipe[WRITE_END]);

        dup2(parentPipe[READ_END], 0);

        char* argv[3];
        argv[0] = "child";
        argv[1] = fileName;
        argv[2] = NULL;

        if(execv(pathToChild, argv) == -1) {
            printf("Failed to exec\n");
        }
    } else {
        close(parentPipe[READ_END]);
        char* input = NULL;

        while((input = ReadString(stream)) != NULL) {

            write(parentPipe[WRITE_END], input, strlen(input));

            free(input);
        }

        close(parentPipe[WRITE_END]);
        wait(NULL);
    }
}
