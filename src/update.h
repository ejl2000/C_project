//
// Created by Tony on 11/26/2023.
//

#ifndef C_PROJECT_UPDATE_H
#define C_PROJECT_UPDATE_H

#include <stdbool.h>
#include "common.h"

void updateSubject();
void renderQuestions(char *quizFileName);
void updateQuestion(char *quizFileName, int questionNumber);

#endif //C_PROJECT_UPDATE_H
