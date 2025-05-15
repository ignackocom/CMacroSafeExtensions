/******************************************************************************
* \file      SafeMemory.h
* \version   2025.03.18
* \author    Peter Potrok ( @ignackocom )
*            ignacko.com@outlook.com
*            https://github.com/ignackocom
* \copyright Copyright (c) 1994 - 2025
*            MIT License (see License.txt file)
* \brief     Safe Memory macros
* \details
*
* \see       https://github.com/ignackocom
*            and other resources
******************************************************************************/

#ifndef SAFEMEMORY_H
#define SAFEMEMORY_H		20250318L

#include <stdio.h>
#include <stdlib.h>


/* Macro to allocate memory of given type and size */
#define MEMORY_MALLOC(type, size, ptr, errorCode) \
    do { \
        (ptr) = malloc(((size_t)(size)) * sizeof(type)); \
        if ((ptr) == NULL) { \
            fprintf(stderr, "Memory allocation failed for size: %zu\n", (size_t)size); \
            if(errorCode == 0) exit(EXIT_FAILURE); \
            return(errorCode); \
        } \
    } while(0)

/* Macro to allocate memory of given type and size and initialize to zero */
#define MEMORY_CALLOC(type, size, ptr, errorCode) \
    do { \
        (ptr) = calloc((size_t)(size), (size_t)sizeof(type)); \
        if ((ptr) == NULL) { \
            fprintf(stderr, "Memory allocation failed for size: %zu\n", (size_t)size); \
            if(errorCode == 0) exit(EXIT_FAILURE); \
            return(errorCode); \
        } \
    } while(0)

/* Macro to reallocate memory */
#define MEMORY_REALLOC(type, size, ptr, errorCode) \
    do { \
        void *tmp_ptr = realloc((void*)(ptr), (((size_t)(size)) * sizeof(type))); \
        if (tmp_ptr == NULL) { \
            fprintf(stderr, "Memory reallocation failed for size: %zu\n", (size_t)size); \
            free(ptr); \
            if(errorCode == 0) exit(EXIT_FAILURE); \
            return(errorCode); \
        } \
        (ptr) = tmp_ptr; \
    } while(0)


/* Macro to check if memory allocation was successful */
#define MEMORY_ALLOCATION_CHECK(ptr, errorCode) \
    do { \
        if ((ptr) == NULL) { \
            fprintf(stderr, "Memory allocation failed at %s:%ld\n", __FILE__, (long)__LINE__); \
            if(errorCode == 0) exit(EXIT_FAILURE); \
            return(errorCode); \
        } \
    } while(0)


/* Macro to initialize memory to 0 */
#define MEMORY_INIT(len, ptr) \
    (memset((ptr), '\0', (len)))


/* Macro to free memory and set pointer to NULL */
#define MEMORY_FREE(ptr) \
    do { \
        if ((ptr) != NULL) { \
            free(ptr); \
            (ptr) = NULL; \
        } \
    } while(0)


#endif /* SAFEMEMORY_H */
