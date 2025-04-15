#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

#define _FILE_OFFSET_BITS 64

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

long long getFileSize(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        perror(filename);
        return 0;
    }
    fseeko(file, 0, SEEK_END);
    long long size = ftello(file);
    fclose(file);
    return size;
}

long long getDigitCount(const char* filelist[], int filecount) {
    long long total = 0;
    for (int i = 0; i < filecount; i++) {
        total += getFileSize(filelist[i]);
    }
    return total;
}

char** getFiles(const char *folderPath) {
    DIR *dir = opendir(folderPath);
    if (!dir) return NULL;

    struct dirent *entry;
    struct stat fileStat;
    char fullPath[4096];
    char **fileList = malloc(1000 * sizeof(char*)); 
    int count = 0;

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;
        if (entry->d_type == DT_REG) {
            fileList[count] = strdup(entry->d_name);
            count++;
        } else if (entry->d_type == DT_UNKNOWN) {
            snprintf(fullPath, sizeof(fullPath), "%s/%s", folderPath, entry->d_name);
            if (stat(fullPath, &fileStat) == 0 && S_ISREG(fileStat.st_mode)) {
                fileList[count] = strdup(entry->d_name);
                count++;
            }
        }
    }

    closedir(dir);
    return fileList;
}
