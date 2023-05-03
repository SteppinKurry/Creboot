// 4-26-23
// A small program to quickly encrypt things from command line
// Uses the same charts file and key for everything(for now)

// 5-2-23
// Adding support for encrypting multiple files at a time

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "creboot.h"

// Default key and charts file
char* key = "put a default key here";
char* charts = "put the path to a default charts file here";


int file_path(char* filename, char* option)
{
	FILE* fh = fopen(filename, "r");

	if (!fh) { return -1; }

	int buffer_size = 999;
	char* buffer = malloc(sizeof(char*) * buffer_size);
	char c; // Individual characters from the file
	int x = 0;

	while ((c = fgetc(fh)) != EOF)
	{
		buffer[x] = c; // Loads characters from charts into numero
		x++;

		if (x >= buffer_size)   // Time to increase the buffer
		{
			buffer_size *= 10;
			buffer = realloc(buffer, sizeof(char*) * buffer_size);
		}
	}
	buffer[x] = '\0';
	fclose(fh);

	if (!strncmp(option, "e", 1)) { encrypt(buffer, key, charts); }
	if (!strncmp(option, "d", 1)) { decrypt(buffer, key, charts); }

	fh = fopen(filename, "w");
	fputs(buffer, fh);
	fclose(fh);
	free(buffer);

	return 0;

}

int main(int argc, char* argv[])
{
	if (argc < 3) { return 0; } // No argument supplied, do nothing

	FILE* op_file = fopen(argv[1], "r"); // If file exists, encrypt that

	if (argc > 3 || op_file)    // File exists, encrypt it
	{
		fclose(op_file);

		int e = 0;
		for (int x = 0; x < argc - 2; x++)
		{
			e = file_path(argv[x+1], argv[argc-1]);
			
			if (e == -1)
			{
				printf("Couldn't find: %s\n", argv[x+1]);
				continue;
			}
			if (!strncmp(argv[argc - 1], "e", 1)) { printf("Encrypted: %s\n", argv[x+1]); }
			if (!strncmp(argv[argc - 1], "d", 1)) { printf("Decrypted: %s\n", argv[x+1]); }
		}
		return 0;
	}

	// File doesn't exist, encrypt first argument

	if (!strncmp(argv[2], "e", 1)) 
	{ 
		encrypt(argv[1], key, charts); 
		printf("Encrypted: %s\n", argv[1]);
		return 0;
	}

	if (!strncmp(argv[2], "d", 1)) 
	{ 
		decrypt(argv[1], key, charts); 
		printf("Decrypted: %s\n", argv[1]);
		return 0;
	}

}
