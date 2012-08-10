#include "include/headers.h"

/* #1 Low level functions for putting a text on screen  */
void put_a_character(int y, int x, char character, int attribute);
void put_a_string(int y, int x, char *string, int attribute);

/* #2 Low level functions for making a box  */
void make_a_filled_box(int y, int x, int width, int height, int attribute, char option_flags);
void make_a_shadow(int y, int x, int width, int height, int attribute);
void draw_a_quadrangle(int y, int x, int width, int height, int attribute, char option_flags);


/* #3 Low level functions for filling the background with a extended ASCII */
void fill_background(char tile, int attribute);

/* #4 Low level functions for getting the point where you want */
int get_the_center_point(int width_of_base, int length_of_object)
{
	return ((width_of_base - length_of_object) / 2);
}


/* #H1 High level functions for making a "Dialog Box"  */
void make_a_dialog_box(int y, int x, int width, int height,
	int attribute, char option_flags,
	char *tilte, char dialog_flags);


/* online editor functions */
void initialize(void)
{
	int i_count;

	clrscr();

	/* Background */
	fill_background(0xB0, BG_BLUE);

	/* Top menu bar */
	make_a_filled_box(0, 0, 79, 0, BG_GRAY, 0);


	return;
}

int main()
{
	initialize();

	make_a_dialog_box(9, 50, 50, 10, TEXT_WHITE | BG_BROWN, 22, " Hello ", 1);
	make_a_dialog_box(-3, -3, 40, 8, TEXT_WHITE | BG_BLUE, 22, " Raven ", 1);
	make_a_dialog_box(10, -3, 40, 8, TEXT_WHITE | BG_BLUE, 22, " Raven ", 1);

	make_a_dialog_box(3, 15, 15, 5, TEXT_WHITE | BG_BLUE, 22, " Chat ", 1);
	//make_a_dialog_box(4, 25, 30, 8, TEXT_WHITE | BG_RED, 22, "Raven", 1);
	//put_a_character(3, 3, 'A', TEXT_RED);
	//put_a_string(4, 3, "Hello World", TEXT_BLUE);
	//put_a_string(24, 1, "This is the first GUI program for me.", TEXT_YELLOW);

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
	for(i_count = 0; strlen(string) - 1 >= i_count; i_count++)
	{
		put_a_character(y, x + i_count, buffer[i_count], attribute);
	}
	return;
}

/* #2 Functions for making a box  */
void make_a_filled_box(int y, int x, int width, int height, int attribute, char option_flags)
{
	int i_count_x;
	int i_count_y;

	for(i_count_y = 0; height >= i_count_y; i_count_y++)
	{
		for(i_count_x = 0; width >= i_count_x; i_count_x++)
		{
			if((24 < y + i_count_y) || (79 < x + i_count_x) || (0 > y + i_count_y) || (0 > x + i_count_x))
			{
				/* This code is preventing to draw when the box is out of screen  */
			}
			else
			{
				put_a_character(y + i_count_y, x + i_count_x , ' ', attribute);
			}
		}
	}
	return;
}

void make_a_shadow(int y, int x, int width, int height, int attribute)
{
	int i_count_x;
	int i_count_y;

	for(i_count_y = 0; height >= i_count_y; i_count_y++)
	{
		for(i_count_x = 0; width >= i_count_x; i_count_x++)
		{
			if((i_count_x == width) || (i_count_y == height))
			{
				if((x < 0) || (24 < y + i_count_y) || (79 < x + i_count_x) || (0 > y + i_count_y) || (0 > x + i_count_x))
				{

				}
				else
				{
					put_a_character(y + i_count_y + 1, x + i_count_x + 1, ' ', BG_BLACK );
				}
			}
		}
	}

	return;
}

void draw_a_quadrangle(int y, int x, int width, int height, int attribute, char option_flags)
{
	int i_count_x;
	int i_count_y;

	for(i_count_y = 0; height >= i_count_y; i_count_y++)
	{
		for(i_count_x = 0; width >= i_count_x; i_count_x++)
		{
			//if((y == i_count_y) || (y == i_count_x)
			if((i_count_y == 0) || (i_count_y == height))
			{
				if((24 < y + i_count_y) || (79 < x + i_count_x) || (0 > y + i_count_y) || (0 > x + i_count_x))
				{

				}
				else
				{
					put_a_character(y + i_count_y, x + i_count_x, HORIZON_1_LINE, attribute);
				}
			}
			else if((i_count_x == 0) || (i_count_x = width))
			{
				if((24 < y + i_count_y) || (79 < x + i_count_x) || (0 > y + i_count_y) || (0 > x + i_count_x))
				{

				}
				else
				{
					put_a_character(y + i_count_y, x + i_count_x, VERTICAL_1_LINE, attribute);
				}
			}
		}
	}

	if((79 > x) && (x > 0))
	{
		put_a_character(y, x, TOP_LEFT_1_LINE, attribute);
	}

	if((79 > x + i_count_x) || (0 < x + i_count_x))
	{
		put_a_character(y, x + width, TOP_RIGHT_1_LINE, attribute);
	}
	if((24 > y + height) && (0 < x))
	{
		put_a_character(y + height, x, BOTTOM_LEFT_1_LINE, attribute);
	}
	if((79 > x + width))
	{
		put_a_character(y + height, x + width, BOTTOM_RIGHT_1_LINE, attribute);
	}
	return;
}

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

/* High */
void make_a_dialog_box(int y, int x, int width, int height,
	int attribute, char option_flags,
	char *title, char dialog_flags)
{
	int title_center;

	/* Checking the minimum dialog box size */
	if(26 > width) /* if not, make the size fixed as 26. */
	{
		width = 26;
	}
	if(8 > height)
	{
		height = 8;
	}
	make_a_filled_box(y, x, width, height, attribute, option_flags);
	make_a_shadow(y, x, width, height, attribute);
	draw_a_quadrangle(y, x, width, height, attribute, option_flags);

	title_center = get_the_center_point(width, sizeof(title));
	put_a_string(y, x - 2 + (title_center), title, attribute);

	return;
}
