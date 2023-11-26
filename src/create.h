#ifndef CREATE_H
#define CREATE_H

#include <stdbool.h>

#define MAX_SUBJECT_LENGTH 100
#define MAX_QUIZ_LENGTH 500

// Function to check if the subject already exists
bool doesSubjectExist(const char* subject);

// Function to add a new subject
void addSubject(const char* subject);


#endif // CREATE_H
