#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "update.h"


void listQuestions(char *quizFileName);

void updateQuestion(char *quizFileName, int questionNumber);

bool checkQuizValid(struct Quiz quiz) {

// Check if the question is empty
    if (strlen(quiz.question) == 0 || strlen(quiz.answer) == 0) {
        printf("Error: Your Question or Answer is empty.\n");
        return false;

    }

// Check if the question ends with '?'
    if (quiz.question[strlen(quiz.question) - 1] != '?') {
        printf("Error: Question must end with '?'.\n");
        return false;
    }

// Check if the answer starts with '!'
    if (quiz.answer[0] == '!') {
        printf("Error: Answer cannot start with '!'.\n");
        return false;
    }

    return true;
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int selectSubject() {
    FILE *file = fopen("resources/subjects.txt", "r");
    if (file == NULL) {
        printf("Error: Unable to open subjects file.\n");
        exit(1);
    }

    printf("Available Subjects:\n");
    char subjectName[MAX_SUBJECT_LENGTH];
    char quizFileName[MAX_QUIZ_LENGTH];
    int count = 0;
    while (fscanf(file, "%[^!]!%s\n", subjectName, quizFileName) == 2) {
        printf("%d. %s\n", ++count, subjectName);
    }
    fclose(file);

    int choice;
    printf("Enter the number of the subject to update: ");
    scanf("%d", &choice);
    clearInputBuffer();
    return choice;
}

void updateSubject() {
    int choice = selectSubject();

    FILE *file = fopen("resources/subjects.txt", "r");
    if (file == NULL) {
        printf("Error: Unable to open subjects file.\n");
        exit(1);
    }

    char subjectName[MAX_SUBJECT_LENGTH];
    char quizFileName[MAX_QUIZ_LENGTH];
    int current = 1;
    while (fscanf(file, "%[^!]!%s\n", subjectName, quizFileName) == 2) {
        if (current == choice) {
            listQuestions(quizFileName);
            break;
        }
        current++;
    }
    fclose(file);
}

void listQuestions(char *quizFileName) {
    char filePath[MAX_QUIZ_LENGTH + 20];
    snprintf(filePath, sizeof(filePath), "resources/quizzes/%s", quizFileName);

    FILE *quizFile;
    struct Quiz currentQuiz;
    int questionNumber = 1;
    char option[10];

    while (1) {
        // Open the quiz file
        quizFile = fopen(filePath, "r");
        if (quizFile == NULL) {
            printf("Error: Unable to open quiz file %s.\n", quizFileName);
            exit(1);
        }

        // Skip to the current question
        for (int i = 0; i < questionNumber; i++) {
            if (fscanf(quizFile, "%[^?!]?!%[^!\n]", currentQuiz.question, currentQuiz.answer) != 2) {
                fclose(quizFile);
                printf("End of questions.\n");
                return;
            }
        }

        printf("\nQuestion %d: %s\n", questionNumber, currentQuiz.question);
        printf("Answer: %s\n", currentQuiz.answer);

        printf("Do you want to update this question? (y/n): ");
        scanf("%s", option);
        clearInputBuffer();

        if (strcmp(option, "y") == 0) {
            fclose(quizFile); // Close the file before updating
            updateQuestion(quizFileName, questionNumber);
            questionNumber--; // Stay on the same question number as it's now updated
        } else if (strcmp(option, "n") != 0) {
            fclose(quizFile);
            break;
        }

        questionNumber++;
        fclose(quizFile); // Close the file before the next iteration
    }
}

void updateQuestion(char *quizFileName, int questionNumber) {
    char filePath[MAX_QUIZ_LENGTH + 20];
    snprintf(filePath, sizeof(filePath), "resources/quizzes/%s", quizFileName);

    // Open the quiz file for reading
    FILE *quizFile = fopen(filePath, "r");
    if (quizFile == NULL) {
        printf("Error: Unable to open quiz file %s.\n", quizFileName);
        exit(1);
    }

    // Temporary file to store the updated questions
    char tempFilePath[MAX_QUIZ_LENGTH + 25];
    snprintf(tempFilePath, sizeof(tempFilePath), "%s.tmp", filePath);
    FILE *tempFile = fopen(tempFilePath, "w");
    if (tempFile == NULL) {
        printf("Error: Unable to create temporary file.\n");
        fclose(quizFile);
        exit(1);
    }

    struct Quiz currentQuiz;
    int currentQuestionNumber = 1;
    while (fscanf(quizFile, "%[^?!]?!%[^!\n]\n", currentQuiz.question, currentQuiz.answer) == 2) {
        if (currentQuestionNumber == questionNumber) {
            printf("\nCurrent Question: %s\n", currentQuiz.question);
            printf("Current Answer: %s\n", currentQuiz.answer);

            do{

                // Get new question and answer from user
                printf("\nEnter the new question: ");
                scanf(" %[^\n]", currentQuiz.question);
                printf("\nEnter the new answer: ");
                scanf(" %[^\n]", currentQuiz.answer);
            }while(checkQuizValid(currentQuiz)==false);


        }

        // Write to the temp file
        fprintf(tempFile, "%s!%s\n", currentQuiz.question, currentQuiz.answer);
        currentQuestionNumber++;
    }

    // Close both files
    fclose(quizFile);
    fclose(tempFile);

    // Replace the old quiz file with the updated one
    remove(filePath);
    rename(tempFilePath, filePath);

    printf("Question %d updated successfully.\n", questionNumber);
}