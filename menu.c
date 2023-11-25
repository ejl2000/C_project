//
// Created by Quinn Thompson on 2023-11-18.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SCREEN_CLEARING 0
#define MAX_INPUT_LENGTH 100

//Temporary Question Struct
struct Question {
    char content[100];
    char answer[100];
    int number;

};

void mainMenu() {
    if (SCREEN_CLEARING) {
        system("cls");
    }
    printf("=============================\n");
    printf("=== Welcome To QuizMaster ===\n");
    printf("=============================\n\n");

    printf("1) Create Subject\n");
    printf("2) Add New Question\n");
    printf("3) Edit Existing Question\n");
    printf("4) Delete Subject\n");
    printf("5) Take a Quiz\n");
    printf("6) Exit\n\n");

    printf("Option: ");
}

void addSubjectMenu() {
    if (SCREEN_CLEARING) {
        system("cls");
    }
    printf("====================\n");
    printf("=== Add Subjects ===\n");
    printf("====================\n\n");

    printf("Enter New Subject Name: \n");
}

struct Question addQuestionMenu() {
    if (SCREEN_CLEARING) {
        system("cls");
    }

    struct Question newQuestion;
    char subject[MAX_INPUT_LENGTH];

    printf("=====================\n");
    printf("=== Add Questions ===\n");
    printf("=====================\n\n");

    printf("Enter the Subject: \n");
    scanf("%s", subject);
    fflush(stdin);

    newQuestion.number = 0; //use subject to find end number

    printf("\n\nEnter the Question's Content: \n");
    fgets(newQuestion.content, MAX_INPUT_LENGTH, stdin);
    fflush(stdin);

    printf("\nEnter the Question's Answer: \n");
    fgets(newQuestion.answer, MAX_INPUT_LENGTH, stdin);
    fflush(stdin);

    return newQuestion;
}

struct Question getQuestion(char * subject) {
    struct Question newQuestion;
    newQuestion.number = 2;
    strcpy_s(newQuestion.content, 100, "What's one plus one?");
    strcpy_s(newQuestion.answer, 100, "Two.");

    return newQuestion;
}

void deleteSubjectMenu() {
    if (SCREEN_CLEARING) {
        system("cls");
    }

    char subject[MAX_INPUT_LENGTH];
    char input[MAX_INPUT_LENGTH];
    char confirmation[] = "confirm";

    printf("======================\n");
    printf("=== Delete Subject ===\n");
    printf("======================\n\n");

    printf("Subject: ");
    scanf("%s", subject);

    printf("\nType 'confirm' to confirm.\n");
    scanf("%s", input);

    if (strcmp(input, confirmation) == 0) {
        printf("Deleting %s...", subject);//call to delete subject
    }
}

struct Question editQuestionMenu() {
    if (SCREEN_CLEARING) {
        system("cls");
    }

    char subject[MAX_INPUT_LENGTH];
    char questionNumber[MAX_INPUT_LENGTH];
    char input[MAX_INPUT_LENGTH];

    printf("=====================\n");
    printf("=== Edit Question ===\n");
    printf("=====================\n\n");

    printf("Subject: ");
    scanf("%s", subject);
    printf("Question Number: ");
    scanf("%s", questionNumber);


    struct Question oldQuestion = getQuestion(subject);
    struct Question newQuestion;
    newQuestion.number = oldQuestion.number;

    printf("\n\n[ Question %d ]\n", oldQuestion.number);
    printf("%s --- Change[Y/N] ", oldQuestion.content);
    scanf("%s", input);

    fflush(stdin);

    if (strcmp(input, "Y") == 0) {
        printf("\nNew Content: \n");
        fgets(input, MAX_INPUT_LENGTH, stdin);
        strcpy(newQuestion.content, input);
    } else {
        strcpy(newQuestion.content, oldQuestion.content);
    }

    printf("\n%s --- Change[Y/N] ", oldQuestion.answer);
    scanf("%s", input);

    fflush(stdin);

    if (strcmp(input, "Y") == 0) {
        printf("\nNew Answer: \n");
        fgets(input, MAX_INPUT_LENGTH, stdin);
        strcpy(newQuestion.answer, input);
    } else {
        strcpy(newQuestion.answer, oldQuestion.answer);
    }

    return newQuestion;
}

void printQuestion(struct Question question) {
    if (SCREEN_CLEARING) {
        system("cls");
    }
    printf("[ Question %d ]\n", question.number);
    printf("%s\n\n", question.content);

    printf("1) View Answer\n");
    //placeholder; replace 100 with the number of questions for the current subject
    if (question.number > 1 && question.number < 100) {
        printf("2) Previous\n");
        printf("3) Next\n");
    } else if (question.number == 100) { //&& 1 != max question number
        printf("2) Previous\n");
    } else if (question.number == 1){ //&& 1 != max question number
        printf("2) Next\n");
    }

    printf("\nOption: ");
}

void printAnswer(struct Question question) {
    if (SCREEN_CLEARING) {
        system("cls");
    }
    printf("[ Answer %d ]\n", question.number);
    printf("%s\n\n", question.answer);

    printf("1) Hide Answer\n");

    //placeholder; replace 100 with the number of questions for the current subject
    if (question.number > 1 && question.number < 100) {
        printf("2) Previous\n");
        printf("3) Next\n");
    } else if (question.number == 100) { //&& 1 != max question number
        printf("2) Previous\n");
    } else if (question.number == 1){ //&& 1 != max question number
        printf("2) Next\n");
    }
    printf("\nOption: ");
}

void quizMenu() {
    if (SCREEN_CLEARING) {
        system("cls");
    }

    char subject[MAX_INPUT_LENGTH];
    int running = 1;
    int isAnswer = 0;

    printf("==================\n");
    printf("=== Quiz Mode! ===\n");
    printf("==================\n\n");

    printf("Subject: ");
    scanf("%s", subject);

    printf("\n\n");

    char input[MAX_INPUT_LENGTH];
    struct Question question = getQuestion(subject);

    char viewAnswerCode[2] = "1";
    char backCode[2] = "2";
    char nextCode[2] = "3";
    char exitCode[5] = "back";

    do {
        if (isAnswer) {
            printAnswer(question);
        } else {
            printQuestion(question);
        }
        scanf("%s", input);

        if (question.number == 1) {
            nextCode[0] = '2';
            backCode[0] = '\0';
        } else if (question.number == 100) {
            nextCode[0] = '\0';
            backCode[0] = '2';
        } else {
            nextCode[0] = '3';
            backCode[0] = '2';
        }

        if (strcmp(input, viewAnswerCode) == 0) {
            isAnswer = !isAnswer;
        } else if (strcmp(input, backCode) == 0) {
            //question = "previous question";
            printf("<< GET PREV QUESTION >>");
            question.number--;
        } else if (strcmp(input, nextCode) == 0) {
            //question = "next question";
            printf("<< GET NEXT QUESTION >>");
            question.number++;
        } else if (strcmp(input, exitCode) == 0) {
            running = 0;
        }
    } while (running);
}

void menu() {
    int running = 1;

    //Option Codes
    char addSubjectCode[2] = "1";
    char addQuestionCode[2] = "2";
    char editQuestionCode[2] = "3";
    char deleteSubjectCode[2] = "4";
    char playQuizCode[2] = "5";
    char exitCode[2] = "6";
    char input[MAX_INPUT_LENGTH];

    do {
        printf("<< input: '%s' >>\n\n", input);
        mainMenu();
        scanf("%s", input);
        if (strcmp(input, addSubjectCode) == 0) {
            addSubjectMenu();
            scanf("%s", input);
            printf("<< call to addSubject with '%s' as input >>\n", input);
        } else if (strcmp(input, addQuestionCode) == 0) {
            struct Question new = addQuestionMenu();
            //call to addQuestion(new); *NEEDS A SUBJECT
        } else if (strcmp(input, editQuestionCode) == 0) {
            struct Question newQuestion = editQuestionMenu();
            //update question with newQuestion
        } else if (strcmp(input, deleteSubjectCode) == 0) {
            deleteSubjectMenu();
        } else if (strcmp(input, playQuizCode) == 0) {
            quizMenu();
        } else if (strcmp(input, exitCode) == 0) {
            running = 0;
            printf("<< attempting to terminate program >>");
        }
    } while (running);
}

int main () {
    menu();
    return 0;
}