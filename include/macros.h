#ifndef WRITE_TO_LOG_H
#define WRITE_TO_LOG_H

#include <stdio.h>

/**
 * Function: WRITE_TO_LOG
 * 
 * Description: Writes a message with a line number to a file ending in ".log".
 *              Creates a new file if it doesn't exist or appends to 
 *              an existing one.
 * 
 * Params:
 *  - filename (const char*): The name of the file to write to (must end with ".log").
 *  - message (const char*): The message to write to the file.
 *  - line_number (int): The line number where the message is written.
 * 
 * Returns:
 *  - int: 0 on success, -1 on error (prints error message to stderr).
 */
#define WRITE_TO_LOG(filename, message, line_number) \
    int result = write_to_log(filename, message, line_number); \
    if (result != 0) { \
        return result; \
    }

/**
 * Function: array_size
 * 
 * Description: Calculates and returns the size of an array in bytes.
 * 
 * Params:
 *  - arr (any array type): The array whose size needs to be determined.
 * 
 * Returns:
 *  - size_t: The size of the array in bytes.
 */
size_t array_size(const void *arr);

#endif
