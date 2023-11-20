#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readQuizContents(FILE* quizFile) {
    int read;
    char *line;
    size_t initialSizeBytes = 1024;

    printf("\n\n");

    char* separator;
    line = (char *) malloc(initialSizeBytes);
    while ((read = getline(&line, &initialSizeBytes, quizFile)) != - 1) {
        separator = strchr(line, '!'); // find position of first occurrence of '!'
        if (separator != NULL) {
            *separator = '\0'; // replace '!' with null terminator
        }
        printf("Question: %s\n", line);
        printf("Answer: %s\n", ++separator);
    }
    free(line);
}


void getQuizPath(FILE* subjectsPtr, char* quizPath, int fileSize) {
    char quizFileName[100];

    while((fgetc(subjectsPtr)) != '!'); // get rid of preceding characters until first char after '!'
    fgets(quizFileName, fileSize, subjectsPtr);

    strcat(quizPath, quizFileName);
    printf("%s", quizPath);
}


int main() {
    FILE* subjectsFilePtr = fopen("resources/subjects.txt", "r");

    char quizPath[100] = "resources/quizzes/";
    getQuizPath(subjectsFilePtr, quizPath, sizeof(quizPath));

    FILE* quizFilePtr = fopen(quizPath, "r");
    readQuizContents(quizFilePtr);

    return 0;
}

