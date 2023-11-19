//
// Created by wifir on 2023-11-18.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SCREEN_CLEARING 0

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

void addQuestionMenu() {
    if (SCREEN_CLEARING) {
        system("cls");
    }
    printf("=============================\n");
    printf("=== Welcome To QuizMaster ===\n");
    printf("=============================\n\n");

    printf("");
}

void menu() {
    int running = 1;

    //Option Codes
    char addSubjectCode[2] = "1";
    char addQuestionCode[2] = "2";
    char EditQuestionCode[2] = "3";
    char deleteSubjectCode[2] = "4";
    char playQuizCode[2] = "5";
    char exitCode[2] = "6";
    char input[100];

    do {
        printf("<< input: '%s' >>\n\n", input);
        mainMenu();
        scanf("%s", input);
        if (strcmp(input, addSubjectCode) == 0) {
            addSubjectMenu();
            scanf("%s", input);
            printf("<< call to addSubject with '%s' as input >>\n", input);
        } else if (strcmp(input, addQuestionCode) == 0) {
            addQuestionMenu();
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