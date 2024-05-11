#include "dorm.h"
#include <string.h>
#include <stdio.h> 
#include <stdbool.h> // Include this to use bool

#include "dorm.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

DORM create_dorm(char *_name, unsigned short _capacity, enum gender_t _gender)
{
    DORM dorm_;

    strcpy(dorm_.name, _name);
    dorm_.capacity = _capacity;
    dorm_.gender = _gender;
    dorm_.residents_num = 0;

    return dorm_;
}

void print_dorm(DORM dorm_to_print)
{
    printf("%s|", dorm_to_print.name); // Tambahkan "|" setelah nama asrama
    (dorm_to_print.gender == GENDER_MALE) ? printf("|%d|male\n", dorm_to_print.capacity) : printf("|%d|female\n", dorm_to_print.capacity);
}

void print_DORMDetails(DORM dorm_to_print, bool print_capacity)
{
    printf("%s|%d", dorm_to_print.name, dorm_to_print.capacity); // Tambahkan "|" setelah nama asrama

    if (print_capacity)
    {
        printf("%d|", dorm_to_print.capacity); // Jika print_capacity true, cetak kapasitas
    }
    else
    {
        printf("%d|", dorm_to_print.residents_num); // Jika print_capacity false, cetak jumlah penghuni
    }

    (dorm_to_print.gender == GENDER_MALE) ? printf("male\n") : printf("female\n");
}

short findDORMInd(char *_name, DORM *daftar, int length)
{
    for (short i = 0; i < length; i++)
    {
        if (strcmp(daftar[i].name, _name) == 0)
            return i;
    }
    return -1;
}
