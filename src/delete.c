#include <stdio.h>
#include <string.h>

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

    remove("resources/subjects.txt");
    rename("resources/temp.txt", "resources/subjects.txt");
}

int chooseSubject(FILE *file) {
    int count = 0;
    char line[100];
    int choice = 0;

    printf("Which Subject do you want to delete? \n");
    while (fgets(line, sizeof(line), file) != NULL) {
        sscanf(line, "%[^!]!", line);
        printf("%d. %s\n", count + 1, line);
        count++;
    }

    while (1) {
        printf("Enter the number of the subject to delete: ");
        if (scanf("%d", &choice) != 1 || choice < 1 || choice > count) {
            printf("Please enter a valid number between 1 and %d.\n", count);
            while (getchar() != '\n');
        } else {
            break;
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
            fclose(file);
            deleteLineFromSubjectFile("resources/subjects.txt", choice);
            printf("Successfully deleted.");
            break;
        }
    }

}

void deleteSubjectMain() {
    FILE *file = fopen("resources/subjects.txt", "r+");
    if (file == NULL) {
        printf("Subject file cannot be opened.\n");
        return;
    }

    int choice = chooseSubject(file);
    fclose(file);
    deleteSubject(choice);



}

