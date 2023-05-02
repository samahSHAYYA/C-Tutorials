/**
 * @file common.h
 *
 * @author Samah A. SHAYYA
 *
 * @brief This file contains common functions used by both unidirectional and
 *        bidirectional linked lists.
 */

#ifndef COMMON_H
#define COMMON_H


// Note in the documentation, "@fn" is explicitly required if you add @example
// or add the example below withot @exmaple and within @code and @endcode.
/**
 * @fn char *initialize(const char *stringLiteral)
 *
 * @brief A function to initialize char * pointer with string literal by using
 *        malloc, and therefore assuring it can be freed by the free function.
 *
 * The purpose is to avoid writing char *s = "string-literal", and later you do
 * not know if "s" is still string literal or reused by applying malloc. In the
 * first case, you should not free but in case malloc was used, it should be
 * freed. To avoid having to track how char *s was used, always use initialize
 * with string literal, and thus you should always free it.
 *
 * @param stringLiteral A string literal or any other string as long as it is
 *                      null-terrminated and its value is not NULL. Otherwise,
 *                      undefined behaviour.
 *
 * @return The initialized char * pointer.
 *
 * @attention You always need to free the char * pointer as this is the
 *            intention. Use in case your pointer might be first initialized
 *            by string literal but later set by malloc function.
 *
 * @example initialize
 *          @code
 *          char *s = initialize("some-string");
 *          :
 *          free(s);
 *          @endcode
 */
char *initialize(const char *stringLiteral);

/**
 * @fn char *concatenate(char *str_1, char *str_2)
 *
 * @brief A function to concatenate two strings (two char * pointers).
 *
 * @param str_1 The first string (const char * pointer). It should be
 *              null-terminated and not NULL. Otherwise, we have undefined
 *              behaviour.
 *
 * @param str_2 The second string (const char * pointer). It should be
 *              null-terminated and not NULL. Otherwise, we have undefined
 *              behaviour.
 *
 * @return The concatenation result.
 *
 * @attention Passed string should be null-terminated and not NULL. Otherwise,
 *            the behaviour is undefined.
 *
 * @example concatenate
 *          @code
 *          char *s1 = ...;
 *          char *s2 = ...;
 *          char *s = concatenate(s1, s2);
 *          :          :
 *          free(s);
 *          @endcode
 */
char *concatenate(const char *str_1, const char *str_2);

/**
 * @fn void freeCharPtrs(unsigned int count, ...)
 *
 * @brief A function to free a varaiable list of char * pointers.
 *
 * @param count The count of list of arguments.
 *
 * @param ... The list of char * pointers to free.
 *
 * @attention
 *      To use freeCharPtrs, you should have used malloc to allocate them
 *      directly or indirectly (via initialize / concatenate, etc.).
 *
 * @example freeCharPtrs
 *          @code
 *          char *s1 = malloc(...);
 *          char *s2 = initialize("some-string");
 *          char *s3 = concatenate(..., ...);
 *          :
 *          freeCharPtrs(3, s1, s2, s3);
 *          @endcode
*/
void freeCharPtrs(unsigned int count, ...);

/**
 * @def FREE_PTR
 *
 * @brief Frees a non-null pointer and sets it to NULL to assure non-dangling
 *        pointer.
 *
 * @example FREE_PTR
 *          @code
 *          char *s = malloc(...);
 *          int *p = malloc(...);
 *          :
 *          FREE_PTR(s);
 *          FREE_PTR(p);
 *          @code
*/
#define FREE_PTR(ptr) { \
    if(ptr) { \
        free(ptr); \
        ptr = NULL; \
    } \
}

#endif
