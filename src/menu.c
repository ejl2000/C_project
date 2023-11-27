//
// Created by Quinn Thompson on 2023-11-18.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"
#include "create.h"
#include "update.h"
#include "delete.h"
#include "read.h"
//#define SCREEN_CLEARING 1
#define MAX_INPUT_LENGTH 100


void mainMenu() {
//    if (SCREEN_CLEARING) {
//        system("cls");
//    }
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


    printf("====================\n");
    printf("=== Add Subjects ===\n");
    printf("====================\n\n");
    struct Subject new_subject;
    printf("Enter New Subject Name: \n");
    fgets(new_subject.subjectName, MAX_SUBJECT_LENGTH, stdin);
    // Remove newline character if present
    if (new_subject.subjectName[strlen(new_subject.subjectName) - 1] == '\n') {
        new_subject.subjectName[strlen(new_subject.subjectName) - 1] = '\0';
    }

    addSubject(new_subject);
}

bool boolAddQuestionMenu(struct Subject *new_subject) {



    printf("\n=====================\n");
    printf("=== Add Questions ===\n");
    printf("=====================\n\n");

    FILE *file = fopen("resources/subjects.txt", "r");
    int count = 0;
    char line[100];
    int choice = 0;

    printf("Which Subject do you want to add quiz to? \n");
    while (fgets(line, sizeof(line), file) != NULL) {
        sscanf(line, "%[^!]!", line);
        printf("%d. %s\n", count + 1, line);
        count++;
    }

    while (1) {
        printf("Enter the number of the subject: ");
        if (scanf("%d", &choice) != 1 || choice < 1 || choice > count) {
            printf("Please enter a valid number between 1 and %d.\n", count);
            while (getchar() != '\n');
        } else {
            break;
        }
    }

    count = 0;
    char scan_line[100];
    fseek(file, 0, SEEK_SET);

    while (fgets(scan_line, sizeof(scan_line), file) != NULL) {
        count++;
        if (count == choice) {
            sscanf(scan_line, "%[^!]", new_subject->subjectName);
            fclose(file);
            break;
        }
    }


    fflush(stdin);
    if (strchr(new_subject->subjectName, '!') != NULL) {
        printf("Error: Subject name cannot contain '!'.\n");
        return false;
    }
    // Check if subject exist
    printf("\nnewsubject: %s\n",new_subject->subjectName);
    if (doesSubjectExist(*new_subject)) {
        sprintf(new_subject->quizFileName, "%s_quizzes.txt", new_subject->subjectName);
        return true;
    } else {
        printf("Subject not found.\n");
        return false;
    }
}

struct Quiz getNewQuestion()


    {
        struct Quiz new_quiz;
        printf("\n\nEnter the Question (Please end with ?): \n");
        fgets(new_quiz.question, MAX_INPUT_LENGTH, stdin);


        if (new_quiz.question[strlen(new_quiz.question) - 1] == '\n') {
            new_quiz.question[strlen(new_quiz.question) - 1] = '\0';
        }


        printf("\nEnter the Question's Answer: \n");
        fgets(new_quiz.answer, MAX_INPUT_LENGTH, stdin);

        if (new_quiz.answer[strlen(new_quiz.answer) - 1] == '\n') {
            new_quiz.answer[strlen(new_quiz.answer) - 1] = '\0';
        }
        return new_quiz;
    }

void addQuestionMenu(){

    struct Subject new_subject;
    if (boolAddQuestionMenu(&new_subject)){
        char input[MAX_INPUT_LENGTH];
        do {
            struct Quiz new_quiz = getNewQuestion();
            printf("newsubject: %s",new_subject.subjectName);
            addQuiz(new_subject, new_quiz);

            printf("Would you like to add more?\n");
            printf("1. Yes\n");
            printf("2. No\n");
            fgets(input, MAX_INPUT_LENGTH, stdin); // Get user input

            // Remove newline character if present
            if (input[strlen(input) - 1] == '\n') {
                input[strlen(input) - 1] = '\0';
            }

            // Check if the user wants to exit the loop
            if (strcmp(input, "2") == 0) {
                break;
            }

        } while (strcmp(input, "1") == 0); // Continue if the user inputs "1"
    }
}



void deleteSubjectMenu() {


    deleteSubjectMain();
}

void editQuestionMenu() {

    updateSubject();

}


void quizMenu() {

    startQuiz();

}

void menu() {
    int running = 1;

    //Option Codes
    char addSubjectCode[3] = "1";
    char addQuestionCode[3] = "2";
    char editQuestionCode[3] = "3";
    char deleteSubjectCode[3] = "4";
    char playQuizCode[3] = "5";
    char exitCode[3] = "6";
    char input[3];

    do {
        printf("<< input: '%s' >>\n\n", input);
        mainMenu();
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
        int a = strcmp(input, addSubjectCode);
        if (strcmp(input, addSubjectCode) == 0) {
            addSubjectMenu();
        } else if (strcmp(input, addQuestionCode) == 0) {
            addQuestionMenu();
        } else if (strcmp(input, editQuestionCode) == 0) {
            editQuestionMenu();
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