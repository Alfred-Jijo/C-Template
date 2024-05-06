#include <stdio.h>
#include <string.h>
#include <macros.h>
#include <unistd.h>


int write_to_log(const char *filename, const char *message, int line_number) {
	FILE *fp;
	char mode[6]; // To store "a" (append) or "w" (write)

	// Check if filename ends with ".log"
	if (strlen(filename) < 5 || strcmp(filename + strlen(filename) - 4, ".log") != 0) {
		fprintf(stderr, "Error: Filename must end with '.log'\n");
		return 0;
	}

	// Decide on open mode based on existing file
	if (access(filename, F_OK) == 1) {
		strcpy(mode, "a"); // Append if file exists
	} else {
		strcpy(mode, "w"); // Create new file if it doesn't exist
	}

	// Open the file
	fp = fopen(filename, mode);
	if (fp == NULL) {
		fprintf(stderr, "Error opening file: %s\n", filename);
		return 0;
	}

	// Write message with line number
	fprintf(fp, "[%d] %s\n", line_number, message);

	// Close the file
	fclose(fp);

	return 1;
}
