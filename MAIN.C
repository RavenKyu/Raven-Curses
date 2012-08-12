#include "include/headers.h"

#define DEBUG 1                 // if the value is one, debugging mode is set.

/* Definition STRUCTURES for Raven Curses. */
typedef struct window
{
	int window_handle;
	int priority;
	int width;
	int height;
	int y;
	int x;
	char attribute;
	unsigned char far *next_word;
} DIALOG_BOX;

typedef struct a_word
{
	char a_word;
	char attribute;
	struct a_word far *previous;
	struct a_word far *next;
} A_WORD;

/* The end of definition of STRUCTURES for Raven Curses */

/* Definition of the Raven Curses */
/* Definition of low level function ----------------------------------------------------------------- */

/* #1 Low level functions for putting a text on screen  */
void put_a_character(int y, int x, char character, int attribute); // 문자 인자로 받아서 화면에 출력한다.
void put_a_character_as_ascii(int y, int x, char character, int attribute);
void put_a_string(int y, int x, char *string, int attribute);      // 문자열을 인자로 받아서 출력한다.

/* #2 Low level functions for making a box  */
void make_a_filled_box(int y, int x, int width, int height, int attribute, char option_flags); // 채워진 상자를 만든다.
void make_a_shadow(int y, int x, int width, int height, int attribute); // 상자에 그림자를 그린다.
void draw_a_quadrangle(int y, int x, int width, int height, int attribute, char option_flags); // 테두리를 그린다.

/* #3 Low level functions for filling the background with a extended ASCII */
void fill_background(char tile, int attribute); // 배경을 채운다.

/* #4 Low level functions for system */
int get_the_center_point(int width_of_base, int length_of_object);

void VGA_inverse_attrib(unsigned char far *attrib);
void VGA_inverse_bar(int y, int x, int length);

void VGA_inverse_attrib_shadow(unsigned char far *attrib);
void VGA_inverse_shadow(int y, int x, int length);

void exit_program()
{

	exit(-1);
}
/* Keyboard Proccessing. */
void get_keyboard_input(char *high_level, char *low_level); // 키보드의 입력을 받는다.
void move_cursor(int page, int y, int x); // 커서를 인자를 받아서 이동 시킨다.

void key_proccessing_for_text_editor_high_level(int *y, int *x, int width, int height,
												int *i_cursor_y, int *i_cursor_x,int high_level) // 텍스트 에디트 특수키 처리 함수
{
	if(45 == high_level)	// Alt + X, Exit.
	{
		clrscr();
		exit_program();
		return;
	}

	if(75 == high_level)	/* Left arrow key */
	{
		if((*i_cursor_y == *y) && (*i_cursor_x == *x))
		{
			return;
		}
		else if(*i_cursor_x == *x)
		{
			*i_cursor_y = *i_cursor_y - 1;
			*i_cursor_x = *x + width - 1;
			move_cursor(0, *i_cursor_y, *i_cursor_x);
		}
		*i_cursor_x = *i_cursor_x - 1;
		move_cursor(0, *i_cursor_y, *i_cursor_x);

	}
	if(77 == high_level)	/* Right arrow key */
	{
		if((*i_cursor_y == *y + height - 2) && (*i_cursor_x ==  *x + width - 2))	/* When the cursor is at the end of the line, cursor will be located at the next line. */
		{
			return ;
		}
		else if(*i_cursor_x == *x + width - 2)
		{
			*i_cursor_y = *i_cursor_y + 1;
			*i_cursor_x = *x;
			move_cursor(0, *i_cursor_y, *i_cursor_x);
		}
		else{
		*i_cursor_x = *i_cursor_x + 1;
		move_cursor(0, *i_cursor_y, *i_cursor_x);}
	}
	if(72 == high_level)	/* Up arrow key */
	{
		if(*i_cursor_y == *y)
		{
			/* Doing Nothing */
		}
		else
		{
			*i_cursor_y = *i_cursor_y - 1;
			move_cursor(0, *i_cursor_y, *i_cursor_x);
		}
	}
	if(80 == high_level)	/* Down arrow key */
	{
		if(*i_cursor_y == *y + height - 2)
		{
			/* Doing Nothing */
		}
		else
		{
			*i_cursor_y = *i_cursor_y + 1;
			move_cursor(0, *i_cursor_y, *i_cursor_x);
		}
	}
	if(13 == high_level)
	{
		if(*i_cursor_y == *y + height - 2)
		{
			/* Doing Nothing */
		}
		else
		{
			*i_cursor_y = *i_cursor_y + 1;
			*i_cursor_x = *x + 1;
			move_cursor(0, *i_cursor_y, *i_cursor_x);
		}
	}
	if(68 == high_level)
	{
	   //	make_a_main_menu(1, 2, 10, 10, TEXT_BLACK | BG_GRAY, 22);

	   put_a_string(5, 20, "Calling the menu", TEXT_WHITE | BG_BLUE);
	}

}

/* The end of definition of low level functions ------------------------------------------------------ */

/* Definition of high level function ----------------------------------------------------------------- */

/* #H1 High level functions for making a "Dialog Box"  */
void make_a_dialog_box(int y, int x, int width, int height,
					   int attribute, char option_flags,
					   char *tilte, char dialog_flags);

/* #H2 High level functions for making a "text editor" */
DIALOG_BOX make_a_text_editor(int y, int x, int width, int height,
						int attribute, char optionf_flags,
						char *title, char dialog_flags);

/* #H3 */
void make_a_main_menu(int y, int x, int width, int height, char attribute, char option_flags);


/* The end of definition of high level functions ----------------------------------------------------- */
/* The end of the Raven Curses. */


/* Functions for The online edito */
void initialize(void);
void prosseccing_for_text_editor(int y, int x, int width, int height, char attribute);

void make_a_menu(int y, int x, int width, int height, char attribute)
{
	#if DEBUG == 1
	attribute = 0xF0 & attribute;
	#define A "File"
	#endif


	 /* Top menu bar */
	make_a_filled_box(y, x, width, height, attribute, 0);


	/* Menu */
	put_a_character(0, 1, 0xF0, attribute);
	put_a_string(0, 4, A, attribute);
	put_a_string(0, 10, "Load", attribute);
	put_a_string(0, 16, "Save", attribute);
	put_a_string(0, 22, "Save as..", attribute);
	put_a_string(0, 34, "Exit", attribute);


}
/* -------------------------------------------------------------------------------------------------- */

int main()
{
	char far *high_level;       // For keyboard proccessing.
	char far *low_level;

	initialize();               // initiallizing.


	make_a_dialog_box(10, 15, 40, 13, TEXT_WHITE | BG_SKY, 22, " Raven ", 2);
	make_a_text_editor(3, 4, 15, 5, TEXT_WHITE | BG_BLUE, 22, " Hello ", 1);
	return 0;
}

/* Functions for The online editor */
void initialize(void)           // Initializing one line editor
{
	int i_count;

	clrscr();

	/* Background */
	fill_background(0xB0, BG_GRAY);
	make_a_menu(0, 0, 79, 0, BG_GRAY);

	return;
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

void put_a_character_as_ascii(int y, int x, char character, int attribute)
{
	unsigned char far *location;	/* Point where you put a word */
	int number = 0;

	location = (unsigned char far *)0xb8000000 + y * 160 + x * 2;

	number = '0' + character;

	*location++ = number;
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
				if((24 < y + i_count_y) || (79 < x + i_count_x) || (0 > y + i_count_y) || (0 > x + i_count_x))
				{

				}
				else
				{
					//put_a_character(y + i_count_y + 1, x + i_count_x + 1, ' ', BG_BLACK );
					VGA_inverse_shadow(y + i_count_y + 1, x + i_count_x + 1, 1);
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

	if((79 > (x + width)) || (0 < x + i_count_x))
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

/* #4 Low level functions for system */
int get_the_center_point(int width_of_base, int length_of_object)
{
	return ((width_of_base - length_of_object) / 2);
}

void VGA_inverse_attrib(unsigned char far *attrib)
{
	unsigned char origin_attrib;

	origin_attrib = *attrib;
	*attrib = *attrib >> 4;
	*attrib = *attrib & 0x0f;
	origin_attrib = origin_attrib << 4;
	*attrib = *attrib | origin_attrib;

	return;
}

void VGA_inverse_attrib_shadow(unsigned char far *attrib)
{
	*attrib = BG_BLACK;
	*attrib = *attrib | TEXT_GRAY | BG_BLACK;

	return;
}

void VGA_inverse_bar(int y, int x, int length)
{
	int i = 0;
	unsigned char far *attr_memory = (unsigned char far *)0xb8000001L;

	attr_memory = attr_memory + y * 160 + x * 2;

	for(i = 0; i < length; i++)
	{
		VGA_inverse_attrib(attr_memory);
		attr_memory = attr_memory + 2;
	}
}

void VGA_inverse_shadow(int y, int x, int length)
{
	int i = 0;
	unsigned char far *attr_memory = (unsigned char far *)0xb8000001L;

	attr_memory = attr_memory + y * 160 + x * 2;

	for(i = 0; i < length; i++)
	{
		VGA_inverse_attrib_shadow(attr_memory);
		attr_memory = attr_memory + 2;
	}
}

void move_cursor(int page, int y, int x)
{
	union REGS regs;
	regs.h.ah = 2;
	regs.h.dh = y;
	regs.h.dl = x;
	regs.h.bh = page;
	int86(0x10, &regs, &regs);

	return;
}

void get_keyboard_input(char *high_level, char *low_level)
{
	*low_level = getch();
	if(*low_level == 0)
	{
		*high_level = getch();
	}
	else
	{
		*high_level = 0;
	}
	return;
}

void prosseccing_for_text_editor(int y, int x, int width, int height, char attribute)
{
	char low_level;
	char high_level;

	int i_cursor_y = y;
	int i_cursor_x = x;

	while(1)
	{
		get_keyboard_input(&high_level, &low_level);

		if(high_level != 0)
		{
			key_proccessing_for_text_editor_high_level(&y, &x, width, height, &i_cursor_y, &i_cursor_x, high_level);

			#if DEBUG == 1	//	Watch
				make_a_dialog_box(2, 50, 15, 5, TEXT_WHITE | BG_BLUE, 22, " Watch ", 1);
				put_a_string(3, 51, "x_cursor : " , TEXT_WHITE | BG_BLUE);
				put_a_character_as_ascii(3, 65, i_cursor_x, TEXT_YELLOW | BG_BLUE);
#endif

		}
		else
		{
			if((97 < low_level) && (123 > low_level) || (65 < low_level) && (90 > low_level))
			{
				if('x' == low_level)
				{
					break;
				}



				put_a_character(i_cursor_y, i_cursor_x, low_level, TEXT_WHITE | BG_BLUE); /* put a text on the current window */
				if(i_cursor_x > (x + width - 3))
				{
					++i_cursor_y;
					i_cursor_x = x - 1;
					move_cursor(0, i_cursor_y, i_cursor_x);
				}
				move_cursor(0, i_cursor_y, ++i_cursor_x);
				fflush(stdin);

			}
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
	if(26 > width) /* if not, make the size fixed at 26. */
	{
		width = 20;
	}
	if(8 > height)
	{
		height = 5;
	}

	make_a_filled_box(y, x, width, height, attribute, option_flags);
	make_a_shadow(y, x, width, height, attribute);
	draw_a_quadrangle(y, x, width, height, attribute, option_flags);

	title_center = get_the_center_point(width, sizeof(title));
	put_a_string(y, x - 2 + (title_center), title, attribute);

	return;
}

DIALOG_BOX make_a_text_editor(int y, int x, int width, int height,
	int attribute, char option_flags,
	char *title, char dialog_flags)
{
	int title_center;

	/* Checking the minimum dialog box size */
	if(26 > width) /* if not, make the size fixed at 26. */
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

	move_cursor(0, y + 1, x + 1);

	prosseccing_for_text_editor(y + 1, x + 1, width, height, attribute);
	return;
}

void make_a_main_menu(int y, int x, int width, int height, char attribute, char option_flags)
{
	make_a_filled_box(y, x, width, height, attribute, option_flags);
	draw_a_quadrangle(y, x, width, height, attribute, option_flags);

	return;
}

