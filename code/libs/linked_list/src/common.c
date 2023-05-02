/**
 * @file common.c
 *
 * @author Samah A. SHAYYA
 *
 * @brief This file contains the common functions' implmentations.
 */

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "linked_list/common.h"

char *initialize(const char *stringLiteral) {
    // Assumes null-terrminated string that is not NULL
    char *str;
    size_t len = strlen(stringLiteral);
    str = malloc((len + 1) * sizeof(char));
    memcpy(str, stringLiteral, (len + 1) * sizeof(char));

    return str;
}

char *concatenate(const char *str_1, const char *str_2) {
    // // Assumes null-terrminated strings that are not NULL
    size_t len_1 = strlen(str_1);
    size_t len_2 =  strlen(str_2);
    char *result = malloc((len_1 + len_2 + 1) * sizeof(char));

    if(result) {
        // Successful allocation
        memcpy(result, str_1, len_1 * sizeof(char));
        memcpy(result + len_1 * sizeof(char), str_2, (len_2 + 1) * sizeof(char));
    }

    return result;
}

void freeCharPtrs(unsigned int count, ...) {
    // Assumes char * pointers as variable arguments
    char *ptr;
    va_list args;
    va_start(args, count);
    for (unsigned int i = 0; i < count; i++) {
        ptr = va_arg(args, char*);
        free(ptr);
    }
}
