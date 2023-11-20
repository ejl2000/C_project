#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void deleteQuizQuestion(char *quizFileName) {
    char filePath[150] = "resources/quizzes/";
    strcat(filePath, quizFileName);
    remove(filePath);
}

void deleteLineFromSubjectFile(char *filename, int lineToDelete) {
    FILE *file = fopen(filename, "r");
    FILE *tempFile = fopen("resources/temp.txt", "w");
    int count = 0;
    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        count++;
        if (count != lineToDelete) {
            fprintf(tempFile, "%s", line);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(filename);
    rename("resources/temp.txt", filename);
}

void displaySubjects() {
    FILE *file = fopen("resources/subjects.txt", "r");
    int count = 0;
    char line[100];

    printf("Which Subject do you want to delete? \n");
    while (fgets(line, sizeof(line), file) != NULL) {
        sscanf(line, "%[^!]!", line);
        printf("%d. %s\n", count + 1, line);
        count++;
    }
    fclose(file);
}

int askUserForSubject(int count) {
    int choice;
    bool validChoice = false;

    while (!validChoice) {
        printf("Enter the number of the subject to delete: ");
        if (scanf("%d", &choice) != 1 || choice < 1 || choice > count) {
            printf("Please enter a valid number.\n");
            while (getchar() != '\n'); // Clear input buffer
        } else {
            validChoice = true;
        }
    }

    return choice;
}

void deleteSubject(int choice) {
    FILE *file = fopen("resources/subjects.txt", "r");
    int count = 0;
    char line[100];

    while (fgets(line, sizeof(line), file) != NULL) {
        count++;
        if (count == choice) {
            sscanf(line, "%*[^!]!%s", line);
            deleteQuizQuestion(line);
            deleteLineFromSubjectFile("resources/subjects.txt", choice);
            printf("Deleted subject: %s\n", line);
            break;
        }
    }
    fclose(file);
}

int main() {
    displaySubjects();

    FILE *file = fopen("resources/subjects.txt", "r");
    int count = 0;
    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        count++;
    }
    fclose(file);

    int choice = askUserForSubject(count);
    deleteSubject(choice);

    return 0;
}
