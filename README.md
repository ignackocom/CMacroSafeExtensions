# CMacroSafeExtensions
C Macro Safe Extensions, a library collection of commonly used safe macros in the C language.

Example of use

```c
#include <stdio.h>


#ifdef _MSC_VER
#pragma warning(disable:4464)
#endif /* _MSC_VER */

#include "../CMacroSafeExtensions/CMacroSafeExtensions.h"

#ifdef _MSC_VER
#pragma warning(default:4464)
#endif /* _MSC_VER */


#pragma warning(disable : 4996)

int SafeFile(void);

int SafeFile(void)
{
    const char* filename = "example.txt";
    const char* newfilename = "new_example.txt";
    const char* data = "Hello, World!";
    FILE* file;
    char buffer[100];
    long position;
    size_t result;
    int iret;

    iret = 0;

    /* Open file for writing */
    FILE_FOPEN(file, filename, "w", iret);

    /* Write to file */
    FILE_FWRITE(file, data, sizeof(char), strlen(data), result, iret);

    /* Flush the file to ensure data is written */
    FILE_FFLUSH(file, iret);

    /* Close file */
    FILE_FCLOSE(file, iret);

    /* Open file for reading */
    FILE_FOPEN(file, filename, "r", iret);

#if defined(__clang__)
#pragma clang unsafe_buffer_usage begin
#endif /* defined(__clang__) */

    /* Read from file */
    FILE_FREAD(file, buffer, sizeof(char), sizeof(buffer) - 1, result, iret);
    buffer[sizeof(buffer) - 1] = '\0'; /* Ensure null - termination - buffer */
    if (result < sizeof(buffer)) buffer[result] = 0; /* Ensure null - termination - string */

#if defined(__clang__)
#pragma clang unsafe_buffer_usage end
#endif /* defined(__clang__) */

    /* Print read data */
    printf("Read from file: %s\n", buffer);

    /* Check position in file */
    FILE_FTELL(file, position, iret);
    printf("Current file position: %ld\n", position);

    /* Seek to the beginning of the file */
    FILE_FSEEK(file, 0, SEEK_SET, iret);

    /* Close file */
    FILE_FCLOSE(file, iret);

    /* Example of renaming a file */
    FILE_RENAME(filename, newfilename, iret); /* This will output an error since the file doesn't exist */

    /* Optionally remove the file */
    FILE_REMOVE(newfilename, iret);

    printf("\n\n");

    return(0);
}

int SafeMemory(void);

int SafeMemory(void)
{
    int* array;
    int i;
    int iret;

    iret = 0;
    
#if defined(__clang__)
#pragma clang unsafe_buffer_usage begin
#endif /* defined(__clang__) */

    /* Calloc */
    MEMORY_CALLOC(int, 10, array, iret);

    for (i = 0; i < 10; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    MEMORY_FREE(array);

    /* Malloc */
    MEMORY_MALLOC(int, 10, array, iret);

    for (i = 0; i < 10; i++) {
        array[i] = i;
    }

    for (i = 0; i < 10; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    MEMORY_FREE(array);

    /* Realloc */
    MEMORY_REALLOC(int, 20, array, iret);

    MEMORY_ALLOCATION_CHECK(array, iret);

    MEMORY_INIT(20, array);

    for (i = 0; i < 20; i++) {
        array[i] = i;
    }

    for (i = 0; i < 20; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    MEMORY_FREE(array);

#if defined(__clang__)
#pragma clang unsafe_buffer_usage end
#endif /* defined(__clang__) */

    printf("\n\n");

    return(0);
}

int SafeString(void);

int SafeString(void)
{
    char buffer[20];
    char* dynamicString;

#if defined(__clang__)
#pragma clang unsafe_buffer_usage begin
#endif /* defined(__clang__) */

    /* Safe copy */
    STRING_COPY(buffer, "Hello, World!", sizeof(buffer));
    printf("Buffer after STRING_COPY: %s\n", buffer);

    /* Safe concatenation */
    STRING_CONCATENATE(buffer, " Test", sizeof(buffer));
    printf("Buffer after STRING_CONCATENATE: %s\n", buffer);

    /* Safe string duplication */
    STRING_DUPLICATE(dynamicString, buffer);
    if (dynamicString) {
        printf("Dynamic String: %s\n", dynamicString);
    }

    printf("STRING_LENGTH(dynamicString) = %zu\n",STRING_LENGTH(dynamicString));

    /* Freeing safely */
    STRING_FREE(dynamicString);

#if defined(__clang__)
#pragma clang unsafe_buffer_usage end
#endif /* defined(__clang__) */

    printf("\n\n");

    return(0);
}


int main(int argc, char* argv[])
{
    printf("Hello World!\n");

    SafeFile();
    SafeMemory();
    SafeString();

    return(0);
}
```

# History of changes ...
