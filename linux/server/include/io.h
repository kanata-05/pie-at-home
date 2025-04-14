#include <stdio.h>

int append(const char* filename, const char* str) {
    FILE* file = fopen(filename, "a"); // open file in append mode
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    fputs(str, file); // write string to file
    fclose(file); // close file
    return 0;
}

int appendRaw(const char* filename, const char* digits) {
    FILE* file = fopen(filename, "ab"); // open for appending in binary mode
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }
    if (fputs(digits, file) == EOF) {
        perror("Error writing to file");
        fclose(file);
        return -1;
    }
    fclose(file);
    return 0;
}
