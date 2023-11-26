#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"


void displayQuestionAndOptions(struct Quiz *quizItems, int index, int itemCount) {
    printf("-------------------------------------------");
    printf("\nQuestion: %s\n", quizItems[index].question);
    printf("Select one of the following options: \n");
    printf("(v) View Answer\n");

    if (index > 0) { // only display if not last question
        printf("(p) Previous Question\n");
    }
    if (index < itemCount - 1) { // only display if not first question
        printf("(n) Next Question\n");
    }

    printf("(e) Exit\n");
}


char getUserChoice() {
    char choice;
    scanf(" %c", &choice);
    return choice;
}


int processUserChoice(struct Quiz *quizItems, int itemCount, int *currentIndex, char userChoice) {
    switch (userChoice) {
        case 'v':
            printf("Answer: %s\n", quizItems[*currentIndex].answer);
            break;
        case 'p':
            if (*currentIndex > 0) {
                (*currentIndex)--;
            }
            break;
        case 'n':
            if (*currentIndex < itemCount - 1) {
                (*currentIndex)++;
            }
            break;
        case 'e':
            return 0; // User chose to exit
        default:
            printf("Invalid option. Please try again.\n");
            break;
    }
    return 1; // Continue the quiz
}

void cleanupQuizItems(struct Quiz *quizItems) {
    free(quizItems); // Only the array of structs needs to be freed now
}

void readQuizContents(struct Quiz *quizItems, int itemCount) {
    int currentIndex = 0, result;
    char userChoice;

    while (1) {
        displayQuestionAndOptions(quizItems, currentIndex, itemCount);
        userChoice = getUserChoice();
        result = processUserChoice(quizItems, itemCount, &currentIndex, userChoice);

        if (result == 0) {
            break; // Exit the loop if user chose to exit
        }
        // After viewing the answer, directly show the options again without repeating the question
        if (userChoice == 'v') {
            continue;
        }
    }

    cleanupQuizItems(quizItems);
}

void getQuizPath(FILE* subjectsPtr, char* quizPath, int fileSize) {
    char quizFileName[100];

    while((fgetc(subjectsPtr)) != '!'); // get rid of preceding characters until first char after '!'
    fgets(quizFileName, fileSize, subjectsPtr);

    strcat(quizPath, quizFileName);
}

int loadQuizItems(FILE *quizFile, struct Quiz **quizItems) {
    int itemCount = 0, capacity = 10; // initial capacity for the array
    char buffer[MAX_QUESTION + MAX_ANSWER + 2]; // +2 for the delimiter and newline

    *quizItems = malloc(sizeof(struct Quiz) * capacity);

    while (fgets(buffer, sizeof(buffer), quizFile) != NULL) {
        // Resize by doubling the array if it's full
        if (itemCount == capacity) {
            capacity *= 2;
            *quizItems = realloc(*quizItems, sizeof(struct Quiz) * capacity);
        }

        // Assuming each line is "question!answer\n"
        char *separator = strchr(buffer, '!');
        if (separator != NULL) {
            *separator = '\0'; // Split the line into question and answer
            strncpy((*quizItems)[itemCount].question, buffer, MAX_QUESTION);
            (*quizItems)[itemCount].question[MAX_QUESTION - 1] = '\0'; // Ensure null-termination
            strncpy((*quizItems)[itemCount].answer, separator + 1, MAX_ANSWER);
            char *newline = strchr((*quizItems)[itemCount].answer, '\n');
            if (newline) *newline = '\0'; // Remove newline if present
            itemCount++;
        }
    }
    return itemCount;
}

void startQuiz() {
    FILE* subjectsFilePtr = fopen("resources/subjects.txt", "r");
    if (!subjectsFilePtr) {
        perror("Failed to open subjects file");
        exit(EXIT_FAILURE);
    }

    char quizPath[100] = "resources/quizzes/";
    getQuizPath(subjectsFilePtr, quizPath, sizeof(quizPath));
    fclose(subjectsFilePtr);

    FILE* quizFilePtr = fopen(quizPath, "r");
    if (!quizFilePtr) {
        perror("Failed to open quiz file");
        exit(EXIT_FAILURE);
    }

    struct Quiz *quizItems;
    int itemCount = loadQuizItems(quizFilePtr, &quizItems);
    fclose(quizFilePtr);

    readQuizContents(quizItems, itemCount);
}


//int main() {
//    startQuiz();
//    return 0;
//}
