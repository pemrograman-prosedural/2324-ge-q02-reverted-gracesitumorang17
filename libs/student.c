#include "student.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/**
 * @brief Define the complete function definition here. Be sure to enlist the prototype of each function
 * defined here in the corresponding header file.
 *
 */

STUDENT create_student(char *_id, char *_name, char *_year,enum gender_t _gender)
{
    STUDENT student_;

    strcpy (student_.id, _id);
    strcpy (student_.name, _name);
    strcpy (student_.year, _year);
    student_.gender = _gender;
    student_.dorm = NULL;

    return student_;

}

void printSTUDENT (STUDENT student_to_print)
{
    if (strcmp(student_to_print.name, "") != 0){
        printf("%s|%s|%s", student_to_print.id);
        printf("%s|%s|%s", student_to_print.name);
        printf("%s|%s|%s", student_to_print.year);
    }
    switch (student_to_print.gender)
    {
        case GENDER_MALE:
        printf("|male");
        break;

        case GENDER_FEMALE:
        printf("|female");
        break;
    }
}
short findSTUDENTInd (char*_id, STUDENT *daftar, int length)
{
    for(short i = 0; i<length; i++){
        if(strcmp(daftar[i].id, _id) == 0)
        return i;
    }
    return -1;
}

void assign (STUDENT *student_, DORM *dorm_)
{
    if (student_ ->gender == dorm_->gender && dorm_->residents_num < dorm_->capacity)
    {
        student_ ->dorm = dorm_;
        dorm_ ->residents_num++;
        }
    else {
        student_->dorm = NULL;
    }
}

void unassign ( STUDENT *student_, DORM* dorm_ )
{
    if ( student_->dorm == dorm_ ) {
        student_->dorm = NULL;
        dorm_->residents_num--;
    }
}

void moveStudent ( STUDENT *migrasi, DORM *newResidence , DORM *oldResidence )
{
    if ( migrasi->dorm != NULL ) {
        unassign ( migrasi, oldResidence );
    }
    assign ( migrasi, newResidence );
}

void printStudentDetails ( STUDENT student_to_print )
{
    if ( strcmp(student_to_print.name, "") != 0 ) {
        printf( "%s|%s|%s", student_to_print.id);
        printf( "%s|%s|%s", student_to_print.name);
        printf( "%s|%s|%s", student_to_print.year);
      

        switch ( student_to_print.gender ) {
            case GENDER_MALE:
                ( student_to_print.dorm != NULL ) ?
                    printf("|male|%s\n", student_to_print.dorm->name) : printf("|male|unassigned\n");
                break;
            
            case GENDER_FEMALE:
                ( student_to_print.dorm != NULL ) ?
                    printf("|female|%s\n", student_to_print.dorm->name) : printf("|female|unassigned\n");
                break;
        }
    }
   
}

void emptyDorm ( DORM* residence, STUDENT** posibResidents, unsigned short totalPR )
{
    for (size_t i=0; i<totalPR; i++) {
        if (posibResidents[i]->dorm != NULL) {
            if (posibResidents[i]->dorm == residence)
                unassign(posibResidents[i], residence);
        }
    }
}

