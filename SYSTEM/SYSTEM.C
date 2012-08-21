#include "rcurses/include/rcurses.h"
#include "system/system.h"

void file_menu()
{
	char low_level;
	char high_level;

	char buffer[80*25];
	char buffer2[30*20];

	int y = 2;
	gettext(3, 1, 25, 9, buffer);

	make_a_drop_menu(1, 2, 21, 6, TEXT_BLACK | BG_GRAY, 22);

	VGA_inverse_shadow(0, 3, 6);
	put_a_string(2, 4, "New         Ctrl+N", TEXT_BLACK | BG_GRAY);
		VGA_inverse_bar(2, 4, 1);
	put_a_string(3, 4, "Open...     Ctrl+O", TEXT_BLACK | BG_GRAY);
		VGA_inverse_bar(3, 4, 1);
	put_a_string(4, 4, "Save        Ctrl+S", TEXT_BLACK | BG_GRAY);
		VGA_inverse_bar(4, 4, 1);
	put_a_string(5, 4, "Save as...", TEXT_BLACK | BG_GRAY);
		VGA_inverse_bar(5, 5, 1);
	put_a_string(6, 4, "Quit         Alt+X", TEXT_BLACK | BG_GRAY);
		VGA_inverse_bar(6, 4, 1);

	gettext(3, 1, 25, 9, buffer2);

	VGA_inverse_shadow(2, 3, 20);

	while(1)
	{
		get_keyboard_input(&high_level, &low_level);
		if(low_level != 0)
		{
			if(13 == low_level)
			{

			}
		}
		else if(high_level != 0)
		{
			if((68 == high_level) || (27 == low_level))
			{	/* Escape Key and F10 */
				puttext(3, 1, 25, 9, buffer);
				return;
			}
			if(80 == high_level)
			{
				if(y == 6)
				{
					y = 1;
				}
				puttext(3, 1, 25, 9, buffer2);
				VGA_inverse_shadow(++y, 3, 20);
			}
			if(72 == high_level)
			{
				if(y == 2)
				{
					y = 7;
				}
				puttext(3, 1, 25, 9, buffer2);
				VGA_inverse_shadow(--y, 3, 20);
			}

			//key_proccessing_for_text_editor_high_level(y, x, width, height, &i_cursor_y, &i_cursor_x, high_level);
		}
	}
	puttext(3, 1, 25, 9, buffer);
}



void edit_menu()
{

}

void search_menu()
{

}
void application_menu()
{

}
void help_menu()
{

}


void exit_program()
{
	exit(-1);
}
/*
void debugging_window(int *y, int *x, const char *item, int value)
{
	int	temp_y = *y;
	int temp_x = *x;

	make_a_dialog_box(2, 50, 15, 3, TEXT_WHITE | BG_BLUE, 22, " Watch ", 1);
	put_a_string(3, 51, "File", TEXT_WHITE | BG_BLUE);
	move_cursor(0, 3, 56);
	printf("%5d\n", value);

	*y = temp_y;
	*x = temp_x;

	return;
}
*/
void initialize(void)           // Initializing one line editor
{
	int i_count;

	clrscr();

	/* Background */
	fill_background(0xB0, BG_GRAY);
	make_a_menu(0, 0, 79, 0, BG_GRAY);

	return;
}

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
	put_a_string(0, 4, "A", attribute);
	put_a_string(0, 10, "Load", attribute);
	put_a_string(0, 16, "Save", attribute);
	put_a_string(0, 22, "Save as..", attribute);
	put_a_string(0, 34, "Exit", attribute);

	return;

}

