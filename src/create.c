#include "create.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SUBJECT_LENGTH 100
#define FILE_NAME "resources/subjects.txt"

// Function to check if the subject already exists
bool doesSubjectExist(const char* subject) {
    FILE* file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        return false;
    }

    char line[MAX_SUBJECT_LENGTH*2 + 20]; // Extra space for filename and separator
    while (fgets(line, sizeof(line), file)) {
        char* token = strtok(line, "!");
        if (strcmp(token, subject) == 0) {
            fclose(file);
            return true;
        }
    }

    fclose(file);
    return false;
}

// Function to add a new subject
void addSubject(const char* subject) {
    // Check if the subject already exists
    if (doesSubjectExist(subject)) {
        printf("Subject '%s' already exists.\n", subject);
        return;
    }


    FILE* file = fopen(FILE_NAME, "r");
    if (file != NULL) {
        fseek(file, 0, SEEK_END);
        if (ftell(file) > 0) {
            fseek(file, -1, SEEK_END);
            char lastChar = fgetc(file);
            fclose(file);
            // Open again in append mode
            file = fopen(FILE_NAME, "a");
            if (lastChar != '\n') {
                fprintf(file, "\n");
            }
        } else {
            fclose(file);
            file = fopen(FILE_NAME, "a");
        }
    } else {
        // File doesn't exist, open in append mode to create it
        file = fopen(FILE_NAME, "a");
    }

    char quizFileName[MAX_SUBJECT_LENGTH];
    sprintf(quizFileName, "%s_quizzes.txt", subject);

    fprintf(file, "%s!%s\n", subject, quizFileName);
    fclose(file);

    char pathQuizFileName[MAX_SUBJECT_LENGTH + 25]; // Adjust size for path
    sprintf(pathQuizFileName, "resources/quizzes/%s", quizFileName);

    // Now handle the quiz file
    file = fopen(pathQuizFileName, "w");
    if (file == NULL) {
        printf("Error creating or clearing quiz file.\n");
        return;
    }
}


