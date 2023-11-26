#include "create.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "common.h"

#define MAX_SUBJECT_LENGTH 100
#define MAX_QUIZ_LENGTH 120
#define MAX_QUESTION 100
#define MAX_ANSWER 100
#define FILE_NAME "resources/subjects.txt"



// Function to check if the subject already exists
bool doesSubjectExist(struct Subject subject) {
    FILE* file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        return false;
    }

    char line[MAX_SUBJECT_LENGTH*2 + 20]; // Extra space for filename and separator
    while (fgets(line, sizeof(line), file)) {
        char* token = strtok(line, "!");
        if (strcmp(token, subject.subjectName) == 0) {
            fclose(file);
            return true;
        }
    }

    fclose(file);
    return false;
}

// Function to add a new subject
void addSubject(struct Subject subject) {
    // Check if the subject already exists
    if (doesSubjectExist(subject)) {
        printf("Subject '%s' already exists.\n", subject.subjectName);
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

    sprintf(subject.quizFileName, "%s_quizzes.txt", subject.subjectName);

    fprintf(file, "%s!%s\n", subject.subjectName, subject.quizFileName);
    fclose(file);

    char pathQuizFileName[MAX_SUBJECT_LENGTH + 25]; // Adjust size for path
    sprintf(pathQuizFileName, "resources/quizzes/%s", subject.quizFileName);
//    printf("\n%s\n",pathQuizFileName);
    // Now handle the quiz file
    FILE* quizFile = fopen(pathQuizFileName, "w+");
    if (quizFile == NULL) {
        printf("Error creating or clearing quiz file.\n");
        return;
    }
    // Write an empty string to the file
    fflush(quizFile);
    fclose(quizFile);

}

void addQuiz(struct Subject subject, struct Quiz quiz) {
    // Check if the question is empty
    if(strlen(quiz.question)==0 || strlen(quiz.answer)==0){
        printf("Error: Your Question or Answer is empty.\n");
        return;

    }

    // Check if the question ends with '?'
    if (quiz.question[strlen(quiz.question) - 1] != '?') {
        printf("Error: Question must end with '?'.\n");
        return;
    }

    // Check if the answer starts with '!'
    if (quiz.answer[0] == '!') {
        printf("Error: Answer cannot start with '!'.\n");
        return;
    }

    char pathQuizFileName[MAX_SUBJECT_LENGTH + 25];
    printf("quiz name: %s\n",subject.quizFileName);
    sprintf(pathQuizFileName, "resources/quizzes/%s", subject.quizFileName);
    printf("quiz path: %s",pathQuizFileName);
    FILE* file = fopen(pathQuizFileName, "r");

    if (file != NULL) {
        fseek(file, 0, SEEK_END);
        if (ftell(file) > 0) {
            fseek(file, -1, SEEK_END);
            char lastChar = fgetc(file);
            fclose(file);
            // Open again in append mode
            file = fopen(pathQuizFileName, "a");
            if (lastChar != '\n') {
                fprintf(file, "\n");
            }
        } else {
            fclose(file);
            file = fopen(pathQuizFileName, "a");
        }
    } else {
        // File doesn't exist, open in append mode to create it
        file = fopen(pathQuizFileName, "a");
    }

    fprintf(file, "%s!%s\n", quiz.question, quiz.answer);
    fclose(file);
    printf("Quiz added successfully.\n");
}



