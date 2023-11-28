#include "common.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/stat.h>
#include <errno.h>
#endif

int create_directory(const char *path) {
#ifdef _WIN32
    // Windows-specific code
    if (CreateDirectory(path, NULL) || GetLastError() == ERROR_ALREADY_EXISTS) {
        return 0; // Success or directory already exists
    }
    return -1; // Error
#else
    // POSIX (Linux, UNIX) specific code
    if (mkdir(path, 0777) == -1) {
        if (errno == EEXIST) {
            return 0; // Directory already exists
        }
        return -1; // Error
    }
    return 0; // Success
#endif
}

