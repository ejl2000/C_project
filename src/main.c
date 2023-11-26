#include "create.h"
#include <stdio.h>
#include <string.h>


int main() {
    // Test adding a subject
    char subject[MAX_SUBJECT_LENGTH];
    printf("Enter a subject name to add: ");
    fgets(subject, MAX_SUBJECT_LENGTH, stdin);
    // Remove newline character if present
    if (subject[strlen(subject) - 1] == '\n') {
        subject[strlen(subject) - 1] = '\0';
    }

    addSubject(subject);


    return 0;
}
