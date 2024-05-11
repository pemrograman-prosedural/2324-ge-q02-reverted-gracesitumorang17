// 12S23038 - Alya Triswani
// 12S23048 - Grace Caldera Situmorang

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "./libs/dorm.h"
#include "./libs/student.h"

int main(int _argc, char **_argv)
{
     DORM *dorms = (DORM*) malloc(1 * sizeof(DORM));
    STUDENT *students = (STUDENT*) malloc(1 * sizeof(STUDENT));
    unsigned short totalDorm;
    unsigned short totalStudent;
    char line[255];
    char delim[2] = "#";


    while ( 1 ) {
        line[0] = '\0';
        fgets(line, 255, stdin);

        {
            int len = strlen(line);
            for (short a = 0; a < len; a++) {
                if(line[a] == '\r' || line[a] == '\n') {
                    for(short b = a; b < len; b++) { line[b] = line[b + 1]; }
                    len--;
                    a--;
                }
            }
        }

        if ( strcmp(line, "---") == 0 ) break;

        else if ( strcmp(line, "student-print-all") == 0 ) {
            for (short i=0; i<totalStudent; i++) {
                printSTUDENT(students[i]);
            }
        }

        else if ( strcmp(line, "dorm-print-all") == 0 ) {
            for (short i=0; i<totalDorm; i++) {
                print_dorm(dorms[i]);
            }
        }

        else if ( strcmp(line, "student-print-all-detail") == 0 ) {
            for (short i=0; i<totalStudent; i++) {
                printStudentDetails(students[i]);
            }
            
        }

        else if ( strcmp(line, "dorm-print-all-detail") == 0 ) {
            for (short i=0; i<totalDorm; i++) {
                print_DORMDetails(dorms[i], true);
            }
        }

        else {
            char *token = strtok(line, delim);

            if ( strcmp(token, "student-add") == 0 ) {
                token = strtok(NULL, delim); char *_id = token;
                token = strtok(NULL, delim); char *_name = token;
                token = strtok(NULL, delim); char *_year = token;
                
                token = strtok(NULL, delim);
                if ( totalStudent > 0 ) {
                    students = (STUDENT*) realloc(students, (totalStudent+1) * sizeof(STUDENT));
                }
                if ( strcmp(token, "male") == 0 ) {
                    students[totalStudent] = create_student(_id, _name, _year, GENDER_MALE);
                    totalStudent++;
                }
                else if ( strcmp(token, "female") == 0 ) {
                    students[totalStudent] = create_student(_id, _name, _year, GENDER_FEMALE);
                    totalStudent++;
                }
            }

            else if ( strcmp(token, "dorm-add") == 0 ) {
                token = strtok(NULL, delim); char *_name = token;
                token = strtok(NULL, delim); unsigned short _capacity = atoi(token);
                token = strtok(NULL, delim);
                if ( totalDorm > 0 ) {
                    dorms = (DORM*) realloc(dorms, (totalDorm+1) * sizeof(DORM));
                }
                if ( strcmp(token, "male") == 0 ) {
                    dorms[totalDorm] = create_dorm(_name, _capacity, GENDER_MALE);
                    totalDorm++;
                }
                else if ( strcmp(token, "female") == 0 ) {
                    dorms[totalDorm] = create_dorm(_name, _capacity, GENDER_FEMALE);
                    totalDorm++;
                }
            }

            else if ( strcmp(token, "assign-student") == 0 ) {
                token = strtok(NULL, delim); char *_id = token;
                token = strtok(NULL, delim); char *dorm_name = token;

                short studentInd = findSTUDENTInd(_id, students, totalStudent);
                short dormInd = findDORMInd(dorm_name, dorms, totalDorm);

                if ( studentInd>=0 && dormInd>=0 ) {
                    assign(&students[studentInd], &dorms[dormInd]);
                }
            }

            else if ( strcmp(token, "move-student") == 0 ) {
                token = strtok(NULL, delim); char *_id = token;
                token = strtok(NULL, delim); char *dorm_name = token;

                short studentInd = findSTUDENTInd(_id, students, totalStudent);
                short newDormInd = findDORMInd(dorm_name, dorms, totalDorm);
                char *_name = students[studentInd].dorm->name;
                if (_name != NULL) {
                    short oldDormInd = findDORMInd( _name, dorms, totalDorm );

                    if ( studentInd>=0 && newDormInd>=0 && oldDormInd>=0 ) {
                        moveStudent(&students[studentInd], &dorms[newDormInd] , &dorms[oldDormInd]);
                    }
                } else {
                    assign(&students[studentInd], &dorms[newDormInd]);
                }
            }

            else if ( strcmp(token, "dorm-empty") == 0 ) {
                token = strtok(NULL, delim);
                char *dorm_name = token;
                short target = findDORMInd(dorm_name, dorms, totalDorm);
                

                for (short i=0; i<totalStudent; i++) {
                    if (students[i].dorm != NULL) { 
                        if ( strcmp(students[i].dorm->name, dorm_name) == 0 ) {
                            unassign(&students[i], &dorms[target]);
                        }
                    }
                }
            }
        }
    }
    

    return 0;
}
