// 12S23038 - Alya Triswani
// 12S23048 - Grace Caldera Situmorang

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./libs/dorm.h"
#include "./libs/student.h"

#define MAX_DORMS 50
#define MAX_STUDENTS 50
#define LINE_LENGTH 255
#define DELIMITER "#"

int main(int _argc, char **_argv)
{
    DORM dorms[MAX_DORMS];
    STUDENT students[MAX_STUDENTS];
    
    unsigned short totalDorm = 0;
    unsigned short totalStudent = 0;
    char line[LINE_LENGTH];
    char* token;
    char* _dorm_name; // Variabel yang digunakan
    int _capacity; // Variabel yang digunakan

    while (fgets(line, LINE_LENGTH, stdin) != NULL)
    {
        line[strcspn(line, "\r\n")] = '\0';

        if (strcmp(line, "---") == 0) break;
        else if (strcmp(line, "dorm-print-all") == 0) {
            for (size_t i = 0; i < totalDorm; i++) {
                print_dorm(dorms[i]);
            }
        }
        else if (strcmp(line, "student-print-all") == 0) {
            for (size_t i = 0; i < totalStudent; i++) {
                printStudentDetails(students[i]);
            }
        }
        else {
            token = strtok(line, DELIMITER);
            if (strcmp(token,"dorm-add") == 0) {
                _dorm_name = strtok(NULL, DELIMITER); // Menggunakan variabel yang sesuai
                _capacity = atoi(strtok(NULL, DELIMITER)); // Menggunakan variabel yang sesuai
                token = strtok(NULL, DELIMITER);
                enum gender_t _gender; // Variabel yang tidak digunakan
                if (strcmp(token, "male") == 0) {
                    _gender = GENDER_MALE;
                }
                else if (strcmp(token, "female") == 0) {
                    _gender = GENDER_FEMALE;
                }
                dorms[totalDorm] = create_dorm(_dorm_name, _capacity, _gender); // Menggunakan variabel yang sesuai
                totalDorm++;
            }
            else if (strcmp(token,"student-add") == 0) {
                char* _student_id = strtok(NULL, DELIMITER); // Variabel yang digunakan
                char* _student_name = strtok(NULL, DELIMITER); // Variabel yang digunakan
                int _student_year = atoi(strtok(NULL, DELIMITER)); // Variabel yang digunakan
                char str_year[5];
                sprintf(str_year, "%d", _student_year);
                token = strtok(NULL, DELIMITER);
                enum gender_t _gender; // Variabel yang tidak digunakan
                if (strcmp(token, "male") == 0) {
                    _gender = GENDER_MALE;
                }
                else if (strcmp(token, "female") == 0) {
                    _gender = GENDER_FEMALE;
                }
                students[totalStudent] = create_student(_student_id, _student_name, str_year, _gender); // Menggunakan variabel yang sesuai
                totalStudent++;
            }
            else if (strcmp(token,"assign-student") == 0) {
                char* _student_id = strtok(NULL, DELIMITER); // Variabel yang digunakan
                char* _dorm_name = strtok(NULL, DELIMITER); // Variabel yang digunakan
                short studentInd = findSTUDENTInd(_student_id, students, totalStudent);
                short dormInd = findDORMInd(_dorm_name, dorms, totalDorm);
                if (studentInd >= 0 && dormInd >= 0) {
                    assign(&students[studentInd], &dorms[dormInd]);
                }
            }
            else if (strcmp(token,"dorm-empty") == 0) {
                _dorm_name = strtok(NULL, DELIMITER); // Menggunakan variabel yang sesuai
                short dormInd = findDORMInd(_dorm_name, dorms, totalDorm);
                if (dormInd >= 0) {
                    // Mengalokasikan array pointer ke STUDENT
                    STUDENT *residentPtrs[MAX_STUDENTS];
                    int residentCount = 0;
                    for (size_t i = 0; i < totalStudent; i++) {
                        if (students[i].dorm == &dorms[dormInd]) {
                            residentPtrs[residentCount++] = &students[i];
                        }
                    }
                    // Memanggil emptyDorm dengan parameter yang sesuai
                    emptyDorm(&dorms[dormInd], residentPtrs, residentCount);
                    dorms[dormInd].residents_num = 0;
                }
            }
            else if (strcmp(token,"student-print-all-detail") == 0) {
                for (size_t i = 0; i < totalStudent; i++) {
                    printStudentDetails(students[i]);
                }
            }
            else if (strcmp(token,"dorm-print-all-detail") == 0) {
                for (size_t i = 0; i < totalDorm; i++) {
                    print_DORMDetails(dorms[i], true);
                }
            }
        }
    }

    // Tambahkan logika tambahan di sini untuk mencetak detail setelah dorm-empty
    // Cek apakah student unassigned dan print detailnya
    printf("student-print-all-detail\n");
    for (size_t i = 0; i < totalStudent; i++) {
        if (students[i].dorm == NULL) {
            printStudentDetails(students[i]);
        }
    }
    // Cetak detail dorm setelah dorm-empty
    printf("dorm-print-all-detail\n");
    for (size_t i = 0; i < totalDorm; i++) {
        print_DORMDetails(dorms[i], true);
    }

    return 0;
}
