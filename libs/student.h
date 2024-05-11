#ifndef STUDENT_H
#define STUDENT_H

#include "gender.h"
#include "dorm.h"

/**
 * @brief define your structure, enums, globally accessible variables, and function prototypes here.
 * The actual function implementation should be defined in the corresponding source file.
 *
 */

typedef struct student_t
{
    char id[12];
    char name[40];
    char year[5];
    gender_t gender;
    DORM *dorm;
}STUDENT;

STUDENT create_student(char *_id, char *_name, char *_year,enum gender_t _gender);
void printSTUDENT (STUDENT student_to_print);
short findSTUDENTInd (char*_id, STUDENT *daftar, int length);
void assign (STUDENT *student_, DORM *dorm_);
void unassign ( STUDENT *student_, DORM* dorm_ );
void moveStudent ( STUDENT *migrasi, DORM *newResidence , DORM *oldResidence );
void printStudentDetails ( STUDENT student_to_print );
void emptyDorm ( DORM* residence, STUDENT** posibResidents, unsigned short totalPR );

#endif
