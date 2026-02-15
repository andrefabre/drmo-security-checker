#ifndef FILE_READER_H
#define FILE_READER_H

#include <stdio.h> // for file operations
#include <stdlib.h> // for memory allocation (malloc, free)
#include <stddef.h> // for size_t type)

// Define security constant
#define MAX_FILE_SIZE_MB 10
#define MAX_FILE_SIZE_BYTES (MAX_FILE_SIZE_MB * 1024 * 1024)

// Define error code constants for readability
#define FILE_READ_SUCCESS 0
#define FILE_READ_NOT_FOUND 1
#define FILE_READ_PERMISSION_DENIED 2
#define FILE_READ_TOO_LARGE 3
#define FILE_READ_MEMORY_ERROR 4

/*
 * Reads a settlement file into memory.
 * 
 * Parameters:
 *   - filepath: Path to the settlement file to be read
 *   - contents: Pointer to char pointer where file contents will be stored (caller must free)
 *   - file_size: Pointer to size_t where file size in bytes will be stored
 * 
 * Returns:
 *   FILE_READ_SUCCESS (0) - File read successfully
 *   FILE_READ_NOT_FOUND (1) - File does not exist
 *   FILE_READ_PERMISSION_DENIED (2) - No permission to read file
 *   FILE_READ_TOO_LARGE (3) - File exceeds MAX_FILE_SIZE_BYTES
 *   FILE_READ_MEMORY_ERROR (4) - Memory allocation failed
 * 
 * Note: Caller is responsible for freeing *contents using free() after use.
 */

int read_settlement_file(const char* filepath, char** contents, size_t* file_size);

#endif