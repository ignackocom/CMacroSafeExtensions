/******************************************************************************
* \file      SafeString.h
* \author    Peter Potrok
* \copyright Copyright (c) 1994 - 2025
*            MIT License (see License.txt file)
* \brief     Safe String macros
* \details
*
* \see
*            and other resources
******************************************************************************/

#ifndef SAFESTRING_H
#define SAFESTRING_H		20250318L

#include <stdio.h>
#include <stdarg.h>


/* Returns the length of a string securely */
#define STRING_LENGTH(str) (str ? strlen(str) : 0)


/* Returns a safe string copy, ensuring null termination */
#define STRING_COPY(dest, src, dest_size) \
    do { \
        strncpy((dest), (src), (dest_size) - 1); \
        (dest)[(dest_size) - 1] = '\0'; \
    } while (0)


/* Returns a safe string concatenation, ensuring null termination */
#define STRING_CONCATENATE(dest, src, dest_size) \
    do { \
        strncat((dest), (src), (dest_size) - strlen(dest) - 1); \
        (dest)[(dest_size) - 1] = '\0'; \
    } while (0)


/* Safe string duplication */
#define STRING_DUPLICATE(dst, src) \
    do { \
        (dst) = NULL; \
        if (src) { \
            dst = malloc(strlen(src) + 1); \
            if (dst) { \
                strcpy((dst), (src)); \
            } \
        } \
    } while(0)


/* Free a string if not NULL */
#define STRING_FREE(str) \
    do { \
        if ((str) != NULL) { \
            free(str); \
            (str) = NULL; \
        } \
    } while (0)


#endif /* SAFESTRING_H */
