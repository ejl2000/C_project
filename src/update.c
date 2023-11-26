#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "update.h"



void updateSubject();
void renderQuestions(char *quizFileName);
void updateQuestion(char *quizFileName, int questionNumber);


void updateSubject() {
    char subject_name[MAX_SUBJECT_LENGTH];
    printf("Enter the subject to update: ");
    scanf("%s", subject_name);

    // Open subjects.txt to find the corresponding quiz file
    FILE *subjectsFile = fopen("resources/subjects.txt", "r");
    if (subjectsFile == NULL) {
        printf("Error opening subjects.txt\n");
        exit(1);
    }

    char quizFileName[MAX_QUIZ_LENGTH];
    char subjectFileName[MAX_SUBJECT_LENGTH];
    while (fscanf(subjectsFile, "%[^!]!%s", subjectFileName, quizFileName) == 2) {
        if (strcmp(subject_name, subjectFileName) == 0) {
            renderQuestions(quizFileName);
            fclose(subjectsFile);
            return;
        }
    }

    fclose(subjectsFile);
    printf("Subject not found. Please check the subject name and try again.\n");
}

void renderQuestions(char *quizFileName) {
    char filePath[MAX_QUIZ_LENGTH+20];  // Ensure this is large enough
    snprintf(filePath, sizeof(filePath), "resources/quizzes/%s", quizFileName);
    FILE *quizFile = fopen(filePath, "r");
    if (quizFile == NULL) {
        printf("Error opening quiz file %s\n", quizFileName);
        exit(1);
    }

    struct Quiz currentQuiz;
    int questionNumber = 1;

    while (fscanf(quizFile, "%[^?!]?!%[^!\n]", currentQuiz.question, currentQuiz.answer) == 2) {
        printf("Question %d: %s\n", questionNumber, currentQuiz.question);
        printf("Answer: %s\n", currentQuiz.answer);

        printf("Previous or Next or Exit\n");
        char option[10];
        scanf("%s", option);

        if (strcmp(option, "Next") == 0) {
            questionNumber++;
        } else if (strcmp(option, "Previous") == 0) {
            if (questionNumber > 1) {
                questionNumber--;
            } else {
                printf("Already at the first question.\n");
            }
        } else if (strcmp(option, "Exit") == 0) {
            fclose(quizFile);
            return;
        } else {
            printf("Invalid option. Please enter 'Next', 'Previous', or 'Exit'.\n");
        }
    }

    fclose(quizFile);
    printf("End of questions.\n");
}

void updateQuestion(char *quizFileName, int questionNumber) {
    char filePath[MAX_QUIZ_LENGTH+20];  // Ensure this is large enough
    snprintf(filePath, sizeof(filePath), "resources/quizzes/%s", quizFileName);
    FILE *quizFile = fopen(filePath, "r+");
    if (quizFile == NULL) {
        printf("Error opening quiz file %s\n", quizFileName);
        exit(1);
    }

    struct Quiz currentQuiz;
    int currentQuestionNumber = 1;

    while (fscanf(quizFile, "%[^?!]?!%[^!\n]", currentQuiz.question, currentQuiz.answer) == 2) {
        if (currentQuestionNumber == questionNumber) {
            printf("Old question: %s\n", currentQuiz.question);

            // Update the question
            printf("Please enter the new question: ");
            scanf(" %[^\n]", currentQuiz.question);
            printf("Please enter the new answer: ");
            scanf(" %[^\n]", currentQuiz.answer);

            // Write the updated question back to the file
            fseek(quizFile, -strlen(currentQuiz.question) - strlen(currentQuiz.answer) - 3, SEEK_CUR);
            fprintf(quizFile, "%s?!%s\n", currentQuiz.question, currentQuiz.answer);

            printf("Done.\n");
            break;
        }

        currentQuestionNumber++;
    }

    fclose(quizFile);
}
