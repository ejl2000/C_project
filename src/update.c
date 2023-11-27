#include <stdio.h>
#include <string.h>

void updateSubjectName(char *oldSubjectName, char *newSubjectName) {
    FILE *file = fopen("resources/subjects.txt", "r+");
    if (file == NULL) {
        printf("Subject file cannot be opened.\n");
        return;
    }

    char line[100];
    int count = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        count++;
        if (strstr(line, oldSubjectName) != NULL) {
            fseek(file, -strlen(line), SEEK_CUR);
            fprintf(file, "%s!%s\n", newSubjectName, strchr(line, '!') + 1);
            break;
        }
    }

    fclose(file);
}

void updateSubjectNameMain() {
    char oldSubjectName[100];
    char newSubjectName[100];

    printf("Enter the subject name to update: ");
    scanf("%s", oldSubjectName);

    printf("Enter the new subject name: ");
    scanf("%s", newSubjectName);

    updateSubjectName(oldSubjectName, newSubjectName);
    printf("Subject name updated successfully.\n");
}

int main() {;
    menu();
    return 0;
}

