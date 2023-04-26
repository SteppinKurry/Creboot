#include "creboot.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

typedef struct long_file
{
	int size; // In characters
	char* buffer;

} long_file;

int main(int argc, char *argv[])
{

	if ((argv[1] && strcmp(argv[1], "-h")) == 0 || argc == 1)
	{
		printf("\n");
		printf("Command: ./crencreboot [option] -k [key] -c [charts_file] [file]\n");
		printf("[option] can be -e (encrypt) or -d (decrypt)\n");
		printf("[key] is the key you want to use. If there are spaces, \"put it in quotes\"\n");
		printf("[file] is the file to be operated on. If there are spaces, \"put it in quotes\"\n");
		printf("[charts_file] is the name of the charts file. The program looks in the \"./Charts/\" directory.\n");
		printf("  If there are spaces, \"put it in quotes\"\n");
		printf("\n");
		return 1;
	}

	if (!argv[1] || (strcmp(argv[1], "-e") != 0 && strcmp(argv[1], "-d") != 0))
	{
		printf("You gotta specify to encrypt (-e) or decrypt (-d)!\n");
		return 1;
	}

	if (!argv[2] || strcmp(argv[2], "-k") != 0)
	{
		printf("You gotta specify what key (-k) to use!\n");
		return 1;
	}

	if (!argv[4] || strcmp(argv[4], "-c") != 0)
	{
		printf("You gotta specify what charts file (-c) to use!\n");
		return 1;
	}	

	long_file text_file;
	text_file.size = 450; // Default value, doesn't really matter
	text_file.buffer = malloc(sizeof(char*) * text_file.size);

	FILE* document = fopen("./md.txt", "r"); // File handler

	if (argv[6])
	{
		if (!(document = fopen(argv[6], "r")))
		{
			printf("'%s' doesn't seem to exist. Did you include the filename extension?\n", argv[6]);
			return 2;
		}
	}

	char c;
	int x = 0;
	while ((c = fgetc(document)) != EOF)
	{
		if (x >= text_file.size) // Time to make the buffer bigger
		{
			text_file.size *= 2;
			text_file.buffer = realloc(text_file.buffer, (sizeof(char*) * text_file.size));
		}

		text_file.buffer[x] = c;
		x++;
	}

	fclose(document);

	clock_t timer;
	timer = clock();

	text_file.size = x;
	text_file.buffer[x - 1] = '\0';
	text_file.buffer = realloc(text_file.buffer, sizeof(char*) * text_file.size); // Make buffer the exact size it needs to be

	FILE* charts_file;

	chdir("./Charts/");

	if (!(charts_file = fopen(argv[5], "r")))
	{
		printf("That charts file doesn't seem to exist :(\n");
		printf("name: %s\n", argv[5]);
		return 2;
	}
	else
	{
		fclose(charts_file);
		printf("Loaded: %s\n", argv[5]);
	}

	if (strcmp(argv[1], "-e") == 0)
		encrypt(text_file.buffer, argv[3], argv[5]);
	else
		decrypt(text_file.buffer, argv[3], argv[5]);

	chdir("../");

	if (argv[6])
	{
		document = fopen(argv[6], "w");
	}

	fputs(text_file.buffer, document);
	fclose(document);

	free(text_file.buffer);

	printf("Done\n");
	timer = clock() - timer;
	double time_taken = ((double)timer)/CLOCKS_PER_SEC;
	printf("Time: %f\n", time_taken);

	return 0;
}