#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SUBJECT_NAME 50
#define MAX_QUIZ_NAME 50
#define MAX_QUESTION 100
#define MAX_ANSWER 100
#define MAX_LINE 200

// Struct to represent a Quiz question
struct Quiz {
    char question[MAX_QUESTION];
    char answer[MAX_ANSWER];
};

// Struct to represent a Subject
struct Subject {
    char subjectName[MAX_SUBJECT_NAME];
    char quizFileName[MAX_QUIZ_NAME];
};

void updateSubject();
void renderQuestions(char *quizFileName);
void updateQuestion(char *quizFileName, int questionNumber);

int main() {
    updateSubject();

    return 0;
}

void updateSubject() {
    char subject[MAX_SUBJECT_NAME];
    printf("Enter the subject to update: ");
    scanf("%s", subject);

    // Open subjects.txt to find the corresponding quiz file
    FILE *subjectsFile = fopen("resources/subjects.txt", "r");
    if (subjectsFile == NULL) {
        printf("Error opening subjects.txt\n");
        exit(1);
    }

    char quizFileName[MAX_QUIZ_NAME];
    while (fscanf(subjectsFile, "%[^!]!%s", quizFileName, quizFileName) == 2) {
        if (strcmp(subject, quizFileName) == 0) {
            renderQuestions(quizFileName);
            fclose(subjectsFile);
            return;
        }
    }

    fclose(subjectsFile);
    printf("Subject not found. Please check the subject name and try again.\n");
}

void renderQuestions(char *quizFileName) {
    FILE *quizFile = fopen(strcat("resources/quizzes/", quizFileName), "r");
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
    FILE *quizFile = fopen(strcat("resources/quizzes/", quizFileName), "r+");
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
