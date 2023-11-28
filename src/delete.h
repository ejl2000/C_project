//
// Created by Tony on 11/26/2023.
//

#ifndef C_PROJECT_DELETE_H
#define C_PROJECT_DELETE_H
#include <stdbool.h>
#include <stdio.h>
#include "common.h"


void deleteQuizQuestion(char *quizFileName);
void deleteLineFromSubjectFile(char *filename, int lineToDelete);
int chooseSubject(FILE *file);
void deleteSubject(int choice);
void deleteSubjectMain();

#endif //C_PROJECT_DELETE_H
