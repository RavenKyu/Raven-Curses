#include "include/headers.h"

/* #1 Functions for putting a text on screen  */
void put_a_character(int y, int x, char character, int attribute);
void put_a_string(int y, int x, char * string, int attribute);

/* #2 Functions for making a box  */

/* #3 Functions for filling the background with a extended ASCII */
void fill_background(char tile, int attribute);

int main()
{
	clrscr();

	fill_background(0xB0, TEXT_YELLOW);

	put_a_character(3, 3, 'A', TEXT_RED);
	put_a_string(4, 3, "Hello World", TEXT_RED);

	return 0;
}

/* #1 Functions for putting a text on screen  */
void put_a_character(int y, int x, char character, int attribute)
{

	unsigned char far *location;	/* Point where you put a word */

	location = (unsigned char far *)0xb8000000 + y * 160 + x * 2;

	*location++ = character;
	*location = attribute;

	return;
}

void put_a_string(int y, int x, char *string, int attribute)
{
	int i_count;
	char buffer[255];

	strcpy(buffer, string);

	/* Sending a word in buffer step over and over  */
	for(i_count = 0; strlen(string) >= i_count; i_count++)
	{
		put_a_character(y, x + i_count, buffer[i_count], attribute);
	}
	return;
}

/* #2 Functions for making a box  */

/* #3 Functions for filling the background with a extended ASCII */
void fill_background(char tile, int attribute)
{
	int y;
	int x;

	for(y = 0; 25 >= y; y++)
	{
		for(x = 0; 80 >= x; x++)
		{
			put_a_character(y, x, tile, attribute);
		}
	}
	return;
}