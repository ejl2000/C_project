#include "create.h"
#include "update.h"
#include "delete.h"
#include "read.h"
#include <stdio.h>
#include <string.h>

void updateSubject() {
    char subject_name[MAX_SUBJECT_LENGTH];
    printf("Enter the subject to update: ");
    scanf("%s", subject_name);

    FILE *subjectsFile = fopen("resources/subjects.txt", "r");
    if (subjectsFile == NULL) {
        printf("Error opening subjects.txt\n");
        exit(1);
    }

    char quizFileName[MAX_QUIZ_LENGTH];
    char subjectFileName[MAX_SUBJECT_LENGTH];
    int found = 0;

    printf("Available subjects:\n");
    while (fscanf(subjectsFile, "%[^!]!%s", subjectFileName, quizFileName) == 2) {
        printf("- %s\n", subjectFileName);
        if (strcmp(subject_name, subjectFileName) == 0) {
            found = 1;
            break;
        }
    }

    fclose(subjectsFile);

    if (!found) {
        printf("Subject not found. Please check the subject name and try again.\n");
        return;
    }

    int questionNumber;
    printf("Enter the question number to update: ");
    scanf("%d", &questionNumber);

    renderQuestions(quizFileName, questionNumber);
}

void renderQuestions(char *quizFileName, int selectedQuestion) {
    char filePath[MAX_QUIZ_LENGTH + 20];
    snprintf(filePath, sizeof(filePath), "resources/quizzes/%s", quizFileName);
    FILE *quizFile = fopen(filePath, "r");
    if (quizFile == NULL) {
        printf("Error opening quiz file %s\n", quizFileName);
        exit(1);
    }

    struct Quiz currentQuiz;
    int questionNumber = 1;

    while (fscanf(quizFile, "%[^?!]?!%[^!\n]", currentQuiz.question, currentQuiz.answer) == 2) {
        if (questionNumber == selectedQuestion) {
            printf("Question %d: %s\n", questionNumber, currentQuiz.question);
            printf("Answer: %s\n", currentQuiz.answer);

            break;
        }

        questionNumber++;
    }

    fclose(quizFile);
}

void updateSpecificQuestion() {
    char subject_name[MAX_SUBJECT_LENGTH];
    printf("Enter the subject to update: ");
    scanf("%s", subject_name);

    FILE *subjectsFile = fopen("resources/subjects.txt", "r");
    if (subjectsFile == NULL) {
        printf("Error opening subjects.txt\n");
        exit(1);
    }

    char quizFileName[MAX_QUIZ_LENGTH];
    char subjectFileName[MAX_SUBJECT_LENGTH];
    int found = 0;

    printf("Available subjects:\n");
    while (fscanf(subjectsFile, "%[^!]!%s", subjectFileName, quizFileName) == 2) {
        printf("- %s\n", subjectFileName);
        if (strcmp(subject_name, subjectFileName) == 0) {
            found = 1;
            break;
        }
    }

    fclose(subjectsFile);

    if (!found) {
        printf("Subject not found. Please check the subject name and try again.\n");
        return;
    }

    int questionNumber;
    printf("Enter the question number to update: ");
    scanf("%d", &questionNumber);

    updateQuestion(quizFileName, questionNumber);
}

int main() {

    startQuiz();

    return 0;
}

