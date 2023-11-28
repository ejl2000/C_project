#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include <time.h>

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
    free(quizItems);
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

int loadQuizItems(FILE *quizFile, struct Quiz **quizItems) {
    int itemCount = 0, capacity = 10; // initial capacity for the array
    char buffer[MAX_QUESTION + MAX_ANSWER + 2]; // +2 for the delimiter and newline

    *quizItems = malloc(sizeof(struct Quiz) * capacity);

    while (fgets(buffer, sizeof(buffer), quizFile) != NULL) {
        // double array if full
        if (itemCount == capacity) {
            capacity *= 2;
            *quizItems = realloc(*quizItems, sizeof(struct Quiz) * capacity);
        }

        char *separator = strchr(buffer, '!');
        if (separator != NULL) {
            *separator = '\0'; // split the line into question and answer
            strncpy((*quizItems)[itemCount].question, buffer, MAX_QUESTION);
            (*quizItems)[itemCount].question[MAX_QUESTION - 1] = '\0'; // set last character to null terminator
            strncpy((*quizItems)[itemCount].answer, separator + 1, MAX_ANSWER);
            char *newline = strchr((*quizItems)[itemCount].answer, '\n');
            if (newline) *newline = '\0'; // remove newline if present
            itemCount++;
        }
    }
    return itemCount;
}

int displaySubjectsAndGetChoice(FILE *subjectsPtr, int numSubjects) {
    int choice;
    char subject[100];
    int i = 1;

    printf("Select a subject:\n");
    while (fscanf(subjectsPtr, "%[^!]", subject) == 1) {
        printf("%d) %s\n", i, subject);
        fscanf(subjectsPtr, "%*[^\n]");  // skip the rest of the line
        fgetc(subjectsPtr);
        i++;
    }

    numSubjects = i - 1;  // adjust for the last increment

    do {
        printf("Enter your choice (1-%d): ", numSubjects);
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            choice = -1;  // reset choice until user enters valid option
        } else if (choice < 1 || choice > numSubjects) {
            printf("Invalid choice. Please enter a valid option.\n");
            while (getchar() != '\n');
        }
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
    } while (choice < 1 || choice > numSubjects);

    return choice;
}

void getQuizFileName(FILE *subjectsPtr, int choice, char *quizFileName, int fileSize) {
    int i;
    rewind(subjectsPtr);

    for (i = 1; i <= choice; i++) {
        fscanf(subjectsPtr, "%*[^!]");  // skip subject name
        if (i == choice) {
            fgetc(subjectsPtr);  // skip '!' character
            fgets(quizFileName, fileSize, subjectsPtr);  // read the quiz file name
            quizFileName[strcspn(quizFileName, "\n")] = 0;
            break;
        }
        fscanf(subjectsPtr, "%*[^\n]");  // skip the rest of the line
        fgetc(subjectsPtr);
    }
}

void readSelectSubject(FILE *subjectsPtr, char *quizFileName, int fileSize) {
    int numSubjects = 0;
    int choice = displaySubjectsAndGetChoice(subjectsPtr, numSubjects);
    getQuizFileName(subjectsPtr, choice, quizFileName, fileSize);
}
void shuffleArray(struct Quiz *array, int size) {
    if (size > 1) {
        // Initialize random number generator
        srand(time(NULL));

        for (int i = size - 1; i > 0; i--) {
            // Generate a random index from 0 to i
            int j = rand() % (i + 1);

            // Swap array[i] with array[j]
            struct Quiz temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
}

void startQuiz() {
    FILE* subjectsFilePtr = fopen("resources/subjects.txt", "r");
    if (!subjectsFilePtr) {
        perror("Failed to open subjects file");
        exit(EXIT_FAILURE);
    }

    char quizFileName[100];
    readSelectSubject(subjectsFilePtr, quizFileName, sizeof(quizFileName));
    fclose(subjectsFilePtr);

    char quizPath[100] = "resources/quizzes/";
    strcat(quizPath, quizFileName);

    FILE* quizFilePtr = fopen(quizPath, "r");
    if (!quizFilePtr) {
        perror("Failed to open quiz file");
        exit(EXIT_FAILURE);
    }

    struct Quiz *quizItems;
    int itemCount = loadQuizItems(quizFilePtr, &quizItems);
    fclose(quizFilePtr);

    // Ask the user if they want to shuffle the quiz items
    printf("\nDo you want to shuffle the quiz questions? (y/n): ");
    char shuffleChoice[10];
    fgets(shuffleChoice, sizeof(shuffleChoice), stdin);
    shuffleChoice[strcspn(shuffleChoice, "\n")] = 0; // Remove newline character

    // If user chooses to shuffle
    if (strcmp(shuffleChoice, "y") == 0) {
        shuffleArray(quizItems, itemCount);
    }

    readQuizContents(quizItems, itemCount);
}



//int main() {
//    startQuiz();
//    return 0;
//}
