#ifndef DORM_H
#define DORM_H

#include "gender.h"
#include <stdbool.h>

/**
 * @brief define your structure, enums, globally accessible variables, and function prototypes here.
 * The actual function implementation should be defined in the corresponding source file.
 *
 */

typedef struct dorm_t
{
  char name[20];
  unsigned short capacity;
  enum gender_t gender;
  unsigned short residents_num;
} DORM;

DORM create_dorm(char *_name, unsigned short _capacity, enum gender_t _gender);
void print_dorm (DORM dorm_to_print);
void print_DORMDetails (DORM dorm_to_print, bool print_capacity);
short findDORMInd (char*_name, DORM *daftar, int length);

#endif
