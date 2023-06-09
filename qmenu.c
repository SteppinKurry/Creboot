// 4-26-23
// A small program to quickly encrypt things from command line
// Uses the same charts file and key for everything(for now)

// 5-2-23
// Adding support for encrypting multiple files at a time
// Also switching around order of arguments a little

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "creboot.h"
#include "config.h"

// The key and path to charts file are kept in "config.h" now. 
// Look there to change them

int file_path(char* filename, char* option)
{
	FILE* fh = fopen(filename, "r+");

	if (!fh) { return -1; }

	int buffer_size = 999;
	char* buffer = malloc(sizeof(char*) * buffer_size);
	char c; // Individual characters from the file
	int x = 0;

	// Read the file; resizes if file is larger than buffer
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

	// Encryption
	int e = 0; // Error
	if (option[0] == 'e') { e = encrypt(buffer, key, charts); }
	if (option[0] == 'd') { e = decrypt(buffer, key, charts); }

	// The only thing that could've gone wrong is the charts file
	if (e == -1) { printf("'%s' not found >:(\n", charts); }

	fh = fopen(filename, "w");
	fputs(buffer, fh);
	fclose(fh);
	free(buffer);

	return 0;

}

int main(int argc, char* argv[])
{	
	if (argc < 3) { return 0; } // No argument supplied, do nothing

	FILE* op_file = fopen(argv[2], "r"); // If file exists, encrypt that

	if (argc > 3 || op_file)    // File exists, encrypt it
	{
		int e_addr;				// stores the index of the files in argv
		fclose(op_file);
		int e = 0;

		for (int x = 0; x < argc - 2; x++)
		{
			e_addr = x + 2; 
			e = file_path(argv[e_addr], argv[1]);
			
			if (e == -1)
			{
				printf("Couldn't find: %s\n", argv[e_addr]);
				continue;
			}
			if (argv[1][0] == 'e') { printf("Encrypted: %s\n", argv[e_addr]); }
			if (argv[1][0] == 'd') { printf("Decrypted: %s\n", argv[e_addr]); }
		}
		return 0;
	}

	// File doesn't exist, encrypt first argument

	if (argv[1][0] == 'e') 
	{ 
		encrypt(argv[2], key, charts); 
		printf("Encrypted: %s\n", argv[2]);
		return 0;
	}

	if (argv[1][0] == 'd') 
	{ 
		decrypt(argv[2], key, charts); 
		printf("Decrypted: %s\n", argv[2]);
		return 0;
	}

}
