#include "editor/include/editor.h"
#include "rcurses/include/rcurses.h"

/* 연결리스트와 함께 구현 하게 했을 땐 대폭 수정이 불 가피하다. */

/* 일반 키 입력을 받았을 때, 동작 구현 */
void key_proc_editor_low_level(int y, int x, int width, int height, int *i_cursor_y, int *i_cursor_x, int low_level)
{
	if(13 == low_level)	/* 리턴 키 */
	{
		move_cursor_new_line(y, x, width, height, &i_cursor_y, &i_cursor_x, low_level);
	}

	if(32 == low_level)	/* 스페이스 키 */
	{
		move_cursor_right(y, x, width, height, &i_cursor_y, &i_cursor_x, low_level);
	}

		/* 일반적인 알파벳 입력 */
	if((96 < low_level) && (123 > low_level) || (64 < low_level) && (90 > low_level))
	{
		type_words(y, x, width, height, &i_cursor_y, &i_cursor_x, low_level);
	}

	return;
}

/* 특수키 입력을 받았을 때 동작 구현 */
void key_proc_text_editor_high_level(int y, int x, int width, int height, int *i_cursor_y, int *i_cursor_x,int high_level) // 텍스트 에디트 특수키 처리 함수
{

	if(45 == high_level)	// Alt + X, Exit.
	{
		clrscr();
		exit_program();
		return;
	}

	if(75 == high_level)	/* Left arrow key */
	{
		move_cursor_left(y, x, width, height, &i_cursor_y, &i_cursor_x, high_level);
	}
	if(77 == high_level)	/* Right arrow key */
	{
		move_cursor_right(y, x, width, height, &i_cursor_y, &i_cursor_x, high_level);
	}
	if(72 == high_level)	/* Up arrow key */
	{
		move_cursor_up(y, x, width, height, &i_cursor_y, &i_cursor_x, high_level);
	}
	if(80 == high_level)	/* Down arrow key */
	{
		move_cursor_down(y, x, width, height, &i_cursor_y, &i_cursor_x, high_level);
	}
        return;
}