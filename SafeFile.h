/******************************************************************************
* \file      SafeFile.h
* \author    Peter Potrok
* \copyright Copyright (c) 1994 - 2025
*            MIT License (see License.txt file)
* \brief     Safe File macros
* \details
*
* \see       
*            and other resources
******************************************************************************/

#ifndef SAFEFILE_H
#define SAFEFILE_H		20250318L


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


/* File Open Macro */
#define FILE_FOPEN(filePtr, fileName, mode, errorCode) \
    do { \
        filePtr = fopen(fileName, mode); \
        if (!filePtr) { \
            fprintf(stderr, "Error opening file %s: %s\n", filename, strerror(errno)); \
            if(errorCode == 0) exit(EXIT_FAILURE); \
            return(errorCode); \
        } \
    } while (0)

/* Check for File Errors */
#define FILE_CHECK_ERROR(filePtr, errorCode) \
    do { \
        if (ferror(filePtr)) { \
            fprintf(stderr, "Error: File operation error: %s\n", strerror(errno)); \
            fclose(filePtr); \
            if(errorCode == 0) exit(EXIT_FAILURE); \
            return(errorCode); \
        } \
    } while(0)

/* File Read Macro */
#define FILE_FREAD(filePtr, buffer, size, count, result, errorCode) \
    do { \
        result = fread(buffer, size, count, filePtr); \
        if (result != count) { \
            if (ferror(filePtr)) { \
                fprintf(stderr, "Error reading from file: %s\n", strerror(errno)); \
                fclose(filePtr); \
                if(errorCode == 0) exit(EXIT_FAILURE); \
                return(errorCode); \
            } else if (feof(filePtr)) { \
                fprintf(stderr, "End of file reached prematurely while reading\n"); \
            } \
        } \
    } while (0)

/* File Write Macro */
#define FILE_FWRITE(filePtr, buffer, size, count, result, errorCode) \
    do { \
        result = fwrite(buffer, size, count, filePtr); \
        if (result != count) { \
            fprintf(stderr, "Error writing to file: %s\n", strerror(errno)); \
            fclose(filePtr); \
            if(errorCode == 0) exit(EXIT_FAILURE); \
            return(errorCode); \
        } \
    } while (0)

/* File Seek Macro */
#define FILE_FSEEK(filePtr, offset, whence, errorCode) \
    do { \
        if (fseek(filePtr, offset, whence) != 0) { \
            fprintf(stderr, "Error seeking in file: %s\n", strerror(errno)); \
            fclose(filePtr); \
            if(errorCode == 0) exit(EXIT_FAILURE); \
            return(errorCode); \
        } \
    } while (0)

/* File Tell Macro */
#define FILE_FTELL(filePtr, position, errorCode) \
    do { \
        position = ftell(filePtr); \
        if (position == -1) { \
            fprintf(stderr, "Error telling file position: %s\n", strerror(errno)); \
            fclose(filePtr); \
            if(errorCode == 0) exit(EXIT_FAILURE); \
            return(errorCode); \
        } \
    } while (0)

// File Rewind
#define FILE_REWIND(filePtr) \
    rewind(filePtr)

/* File Flush Macro */
#define FILE_FFLUSH(filePtr, errorCode) \
    do { \
        if (fflush(filePtr) != 0) { \
            fprintf(stderr, "Error flushing file: %s\n", strerror(errno)); \
            fclose(filePtr); \
            if(errorCode == 0) exit(EXIT_FAILURE); \
            return(errorCode); \
        } \
    } while (0)

/* File Close Macro */
#define FILE_FCLOSE(filePtr, errorCode) \
    do { \
        if (filePtr) { \
            if (fclose(filePtr) != 0) { \
                fprintf(stderr, "Error closing file: %s\n", strerror(errno)); \
                if(errorCode == 0) exit(EXIT_FAILURE); \
                return(errorCode); \
            } \
            filePtr = NULL; /* Avoid dangling pointer */ \
        } \
    } while (0)

/* File Remove Macro */
#define FILE_REMOVE(fileName, errorCode) \
    do { \
        if (remove(fileName) != 0) { \
            fprintf(stderr, "Error removing file %s: %s\n", fileName, strerror(errno)); \
            if(errorCode == 0) exit(EXIT_FAILURE); \
            return(errorCode); \
        } \
    } while (0)

/* File Rename Macro */
#define FILE_RENAME(oldFileName, newFileName, errorCode) \
    do { \
        if (rename(oldFileName, newFileName) != 0) { \
            fprintf(stderr, "Error renaming file from %s to %s: %s\n", oldFileName, newFileName, strerror(errno)); \
            if(errorCode == 0) exit(EXIT_FAILURE); \
            return(errorCode); \
        } \
    } while (0)


#endif /* SAFEFILE_H */
