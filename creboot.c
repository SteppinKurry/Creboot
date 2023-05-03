// Cal Tipton
// 4-25-23
// Remaking it again. Gonna be even faster now

#include "creboot.h"

#include <string.h>
#include <stdio.h>

// A list of already found characters in charts file
// A character's place in this list is its ascii value
// For example, the number corresponding to "A" would be 
// found in numero_list[65]
char numero_list[128];

int to_number_c(char c, char* numero)
{
	// 4-25-23
	// Converts a single character to a number 
	// and returns the value

	// 5-3-23
	// Updated to use numero_list where possible

	int ascii_c = c;

	int number_value = numero_list[ascii_c];
	if (number_value != -1)
	{
		return number_value;
	}

	int num_pos = 1;
	while (c != numero[num_pos])
	{
		num_pos += 1;
		if (num_pos >= numero[0])	// numero[0] is length
		{
			return -1;				// number isn't in the charts file
		}
	}

	numero_list[ascii_c] = num_pos;
	return num_pos;
}

char to_char_c(int n, char* numero)
{
	// 4-25-23
	// Converts a number to a character. Can't believe 
	// I didn't just do this the first time

	// Ensures that the number is in range
	if (n >= numero[0])	// numero[0] is length
	{
		return 'd';		// not particularly helpful, but should never happen
	}

	// Returns the correct character
	return numero[n];
}

int open_chart(char* chart_name, char* numero)
{
	// 4-25-23
	// Thought this might help make the code more readable
	// Opens a charts file and stores the contents into numero
	// Throws the overall length into numero[0] and also 
	// null terminates at the end

	FILE* chart_file = fopen(chart_name, "r"); // File handler

	if (!chart_file) return -1;			// File not found

	// Read charts file
	char c; // Individual characters from the file
	int x = 1;
	while ((c = fgetc(chart_file)) != EOF)
	{
		numero[x] = c; // Loads characters from charts into numero
		x++;
	}
	fclose(chart_file);
	numero[0] = x; // Store length of numero in numero[0]
	numero[x] = '\0';

	memset(numero_list, -1, 128);		// Initialize numero_list to -1s

	return 0;

}

int encrypt(char* mes, char* key, char* chart_name)
{

	// 4-25-23
	// A new encrypt method. I think it could be faster
	char numero[99]; // Chart file

	if (open_chart(chart_name, numero) == -1) {return -1;}

	// Avoids having to run strlen every iteration
	int mes_len = strlen(mes);
	int key_len = strlen(key);
	int current_num = 0;

	for (int x = 0; x < mes_len; x++)
	{
		// Convert char to number
		current_num = to_number_c(mes[x], numero);
		
		// Character wasn't found in the charts file; ignore it
		if (current_num == -1) { continue; }

		// Add key
		current_num += to_number_c(key[x % key_len], numero);

		// Get number into the correct range
		if (current_num >= numero[0]) { current_num -= (numero[0] - 1); }

		// Convert back
		mes[x] = to_char_c(current_num, numero);
	}
	
	return 0;
}

int decrypt(char* mes, char* key, char* chart_name)
{
	// 4-25-23
	// Follows the format of the new encrypt method
	// Pretty much exactly the same code

	char numero[99]; // Chart file

	if (open_chart(chart_name, numero) == -1) {return -1;}

	// Avoids having to run strlen every iteration
	int mes_len = strlen(mes);
	int key_len = strlen(key);
	int current_num = 0;

	for (int x = 0; x < mes_len; x++)
	{
		// Convert char to number
		current_num = to_number_c(mes[x], numero);

		// Character wasn't found in the charts file; ignore it
		if (current_num == -1) { continue; }

		// Subtract key
		current_num -= to_number_c(key[x % key_len], numero);

		// Get number into the correct range
		if (current_num <= 0) { current_num += (numero[0] - 1); }
		
		// Convert back
		mes[x] = to_char_c(current_num, numero);
	}
	
	return 0;

}
