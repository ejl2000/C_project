// common.h
#ifndef COMMON_H
#define COMMON_H
#define MAX_SUBJECT_LENGTH 100
#define MAX_QUIZ_LENGTH 120
#define MAX_QUESTION 100
#define MAX_ANSWER 100


// Struct to represent a Quiz question
struct Quiz {
    char question[MAX_QUESTION];
    char answer[MAX_ANSWER];
};

// Struct to represent a Subject
struct Subject {
    char subjectName[MAX_SUBJECT_LENGTH];
    char quizFileName[MAX_QUIZ_LENGTH];
};

#endif // COMMON_H
