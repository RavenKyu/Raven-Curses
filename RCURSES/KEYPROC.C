#include "rcurses/include/rcurses.h"
#include "editor/include/editor.h"

/* 키보드 입력을 처리 해주는 함수 모음 */
/* 키보드 입력을 사용할 윈도우는 커서 위치를 저장하고 통신을 할 수 있는 아래의 변수를 반드시 가져야 한다.
 * int i_cursor_y;
 * int i_cursor_x;
 * int high_level;
 * int low_level;
 * 위의 변수 값을 참고하여 키보드 입력을 받고 지정해둔 기능에 맞게 수행하게 된다. */


/* 커서를 지정된 위치에 이동 시켜 준다. */
void move_cursor(int page, int y, int x) /* 이 함수에 대해서는 공부가 더 필요하다. */
{
	union REGS regs;
	regs.h.ah = 2;
	regs.h.dh = y;
	regs.h.dl = x;
	regs.h.bh = page;
	int86(0x10, &regs, &regs);

	return;
}

/* 키보드에서 입력을 받는 함수
 * 호출하는 함수부에서 미리 아래의 변수들을 선언해 두어야 한다.
 * char high_level;
 * char low_level;
 * 각 키의 고유한 값을 받아 각 변수에 저장한다.*/
void get_keyboard_input(char *high_level, char *low_level)
{
	*low_level = getch();   /* low_level의 영역을 먼저 입력받고 */
	if(*low_level == 0)     /* 0이 아니면 그냥 low_level만 저장, 입력받은 값이 0일 경우에는 특수키를 입력했다 판단. */
	{
		*high_level = getch();
	}
	else
	{
		*high_level = 0;
	}
	return;
}


/* 커서를 지정된 방향으로 한 칸 이동 시킨다.
 * 커서는 지정된 범위를 벗어나지 못한다. */
void move_cursor_left(int y, int x, int width, int height, int **i_cursor_y, int **i_cursor_x, int high_level)
{
	if((**i_cursor_y == y) && (**i_cursor_x == x))
	{
		return;         /* 커서가 범위를 벗어나지 못하게 한다. */
	}
	else if(**i_cursor_x == x) /* 커서가 우측 첫 번째 칸에서 우측으로 이동 하려 한다면 */
	{
		**i_cursor_y = **i_cursor_y - 1; /* 커서를 위로 한칸 올리고 */
		**i_cursor_x = x + width - 1;    /* 좌측 가장 끝 부분으로 위치를 지정. */
		move_cursor(0, **i_cursor_y, **i_cursor_x); /* 커서를 해당 좌표에 옮긴다. */
	}

	**i_cursor_x = **i_cursor_x - 1; /* 좌측으로 한 칸 이동. */
	move_cursor(0, **i_cursor_y, **i_cursor_x);

	return;
}

void move_cursor_right(int y, int x, int width, int height, int **i_cursor_y, int **i_cursor_x, int high_level)
{
		if((**i_cursor_y == y + height - 2) && (**i_cursor_x ==  x + width - 2))	
		{
			return ;        /* 커서가 범위를 벗어나지 못하게 한다. */
		}
		else if(**i_cursor_x == x + width - 2) /* 커서가 우측 마지막 칸에서 우측으로 이동하려하면 */
		{
			**i_cursor_y = **i_cursor_y + 1; /* 아래로 한 칸 이동 */
			**i_cursor_x = x;                /* 좌측 첫 번째 칸으로 */
			move_cursor(0, **i_cursor_y, **i_cursor_x); /* 커서를 이동 시킨다. */
		}
		else{
		**i_cursor_x = **i_cursor_x + 1; /* 우측으로 한 칸 이동 */
		move_cursor(0, **i_cursor_y, **i_cursor_x);
		}

                return;
}

void move_cursor_up(int y, int x, int width, int height, int **i_cursor_y, int **i_cursor_x, int high_level)
{
	if(**i_cursor_y == y)
	{
            /* 커서가 범위를 벗어나지 못하게 한다. */
	}
	else
	{
		**i_cursor_y = **i_cursor_y - 1; /* 커서를 위로 한 칸 */
		move_cursor(0, **i_cursor_y, **i_cursor_x); /* 이동 */
	}

        return;
}

void move_cursor_down(int y, int x, int width, int height, int **i_cursor_y, int **i_cursor_x, int high_level)
{
	if(**i_cursor_y == y + height - 2)
	{
            /* 커서가 범위를 벗어나지 못하게 한다. */
	}
	else
	{
		**i_cursor_y = **i_cursor_y + 1; /* 커서를 아래로 한 칸 */
		move_cursor(0, **i_cursor_y, **i_cursor_x); /* 이동 */
	}
        
        return;
}

void move_cursor_new_line(int y, int x, int width, int height, int **i_cursor_y, int **i_cursor_x, int low_level)
{	
	if(**i_cursor_y == y + height - 2) 
	{
		/* 주어진 범위를 벗어나지 못하게 하지만, 텍스트 에디터와 연동하여 수정이 필요할 듯 */
	}
	else
	{
		**i_cursor_y = **i_cursor_y + 1;
		**i_cursor_x = x;
		move_cursor(0, **i_cursor_y, **i_cursor_x); /* 엔터 입력과 같은 동작을 한다. */
	}
}


void type_words(int y, int x, int width, int height, int **i_cursor_y, int **i_cursor_x, int low_level)
{
	/* put a alphabet on the screen */
	put_a_character(**i_cursor_y, **i_cursor_x, low_level, TEXT_WHITE | BG_BLUE); /* put a text on the current window */
	if(**i_cursor_x > (x + width - 3))	/* at the moment cursor come over the box, it will be moved at the first of next line.   */
	{
		++**i_cursor_y;
		**i_cursor_x = x - 1;
		move_cursor(0, **i_cursor_y, **i_cursor_x);
	}
	move_cursor(0, **i_cursor_y, ++**i_cursor_x);
	fflush(stdin);
}


