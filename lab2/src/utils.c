#include "utils.h"

void CreatePipe(int pipeFd[2])
{
    if(pipe(pipeFd) != 0) {
        printf("Couldn't create pipe\n");
        exit(EXIT_FAILURE);
    }
}

char* ReadString(FILE* stream) {
    if(feof(stream)) {
        return NULL;
    }

    const int chunkSize = 256;
    char* buffer = (char*)malloc(chunkSize);
    int bufferSize = chunkSize;

    if(!buffer) {
        printf("Couldn't allocate buffer");
        exit(EXIT_FAILURE);
    }

    int readChar;
    int idx = 0;
    while((readChar = getc(stream)) != EOF) {
        buffer[idx++] = readChar;

        if(idx == bufferSize) {
            buffer = realloc(buffer, bufferSize + chunkSize);
            bufferSize += chunkSize;
        }

        if(readChar == '\n') {
            break;
        }
    }

    buffer[idx] = '\0';

    return buffer;
}
