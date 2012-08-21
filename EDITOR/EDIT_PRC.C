#include "editor/include/editor.h"
#include "rcurses/include/rcurses.h"

void proc_for_text_editor(int y, int x, int width, int height, char attribute)
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
			key_proc_text_editor_high_level(y, x, width, height, &i_cursor_y, &i_cursor_x, high_level);
		}
		else
		{
			if((97 < low_level) && (123 > low_level) | (65 < low_level) && (90 > low_level))
			{
				if('x' == low_level)
				{
					break;
				}

				put_a_character(i_cursor_y, i_cursor_x, low_level, TEXT_WHITE | BG_BLUE);
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
