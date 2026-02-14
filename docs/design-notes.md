# File Reader Design Decisions

**Date:** February 14, 2026
**Phase:** 1 - Basic File I/O

## Function Signature

**My Choice:**

```C
int read_settlement_file(const char* filepath, char** contents, size_t* file_size);

/*
Returns:
0 = success
1 = file not found
2 = permission denied
3 = file too large
4 = memory allocation failed
*/
// Allocates memory internally, returns pointer via parameter
```

**Reasoning:**

*Pros:*

- Separates success/failure (return code) from data (output parameeters)
- Returns file size explicitly (useful for later processing)
- Can return different error codes (1= file not found, 2=no permission, 3=too large)
- Industry standard pattern (used in POSIX, Windows APIs)

*Cons:*

- Pointer-to-pointer syntax is confusing for beginners
- Still requires call to free() the contents
- More parameters to pass

I am using this function signature as:

- I need detailed error reporting (PASS/FAIL with reasons)
- I need file size for validation logic later
- Its a professional pattern good for my portfolio
- I want to challenge myself with proper design

## Error Handling Strategy

### Possible Errors

1. File doesn't exist --> fopen() returns NULL, errno = ENOENT
2. No read permissions --> fopen() returns NULL, errno = EACCES
3. File is a directory (not a regular file) --> need to check the file type first
4. File path is NULL or empty string -> invalid input
5. File is too large (>10MB for security) --> check size before reading
6. Memory allocation fails (malloc() returns NULL) --> Out of RAM
7. Disk I/O error during read --> fread() returns less than expected
8. File path contains invalid characters (Windows: <>:"|?*) --> Path validation needed.

### Error Communication Strategy

1. Return Code (primary)

- Function returns integer status code
- 0 = success, positive numbers = specific error types

2. Output parameter for error message (optional, advanced)

```C
int read_settlement_file(const char* filepath, char** contents, size_t* file_size, char* error_msg);
```

- If error occurs, write human-readable message to error_msg buffer
- Example: "Error: File 'settlement.xml' exceeds 10MB limit (actual 15.2MB)"

## Memory Management

1. File Reading Strategy: Read entire file at once (files are <10MB)

**Reasoning:**

- Settlement files are typically 10KB-2MB (managable in RAM)
- The entire file needs to be parsed as can't parse partial data
- Simpler code (read one, then process)

2. Allocation Responsibility: Function calls malloc()

**Reasoning:**

- Function knows the exact file size (from fstat() or ftell())
- Allocates precisely what's needed (no waste)
- Caller doesn't need to guess buffer size

**Pattern:**

```C
// Inside read_settlement_file():
*contents = malloc(file_size + 1);  // +1 for null terminator
if (*contents == NULL) {
    return 4;  // Memory allocation failed
}
```

3. Deallocation Responsibility: Caller calls free()

**Reasoning:**

- Function doesn't know when caller is done with the data
- Caller might use the data across multiple function calls
- Standard C pattern" "whoever allocates, documents who frees"

README usage example should show:

```C
char* file_contents = NULL;
size_t file_size = 0;

if (read_settlement_file("test.xml", &file_contents, &file_size) == 0) {
    // Use file_contents here...
    free(file_contents);  // CALLER'S RESPONSIBILITY
}
```

3. Malloc Failure Handling

- If malloc() fails do not proceed, always return with an error code.

```C
*contents = malloc(file_size + 1);
if (*contents == NULL) {
    fclose(file);
    return 4;  // Error code: memory allocation failed
}
```

4. Security Limits: File Size Limits

Maximum file size is **10MB (10,485,760 bytes)**

```c
#define MAX_FILE_SIZE_MB 10
#define MAX_FILE_SIZE_BYTES (MAX_FILE_SIZE_MB * 1024 * 1024)
```

- PEXA xml files are typically <2MB
- 10MB provides headroom for edge cases
- Prevents denial of service attacks (attacker sends 5GB file)
- Protects against accidental misuse (user selects wrong file)

Check file size before reading

```c
if (file_size > MAX_FILE_SIZE_BYTES) {
    fclose(file);
    return 3;  // Error code: file too large
}
```

## Function Naming Convention

**My Choice**: read_settlement_file()

**Reasoning**:

- Matches my domain (settlement validation)
- Verb-first (good C style)
- Flexible (not tied to PEXA Brand)
- Professional naming convention

**Future related functions:**

- validate_settlement_format()
- calculate_settlement_checksum()
