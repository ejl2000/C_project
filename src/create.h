#ifndef CREATE_H
#define CREATE_H

#include <stdbool.h>
#include "common.h"



// Function to check if the subject already exists
bool doesSubjectExist(struct Subject subject);

// Function to add a new subject
void addSubject(struct Subject subject);

// Function to add a new quiz
void addQuiz(struct Subject subject, struct Quiz quiz);

#endif // CREATE_H
