#include "rcurses/include/rcurses.h"
#include "editor/include/editor.h"

/* 고수준 1단계
 * 저수준의 함수들을 이용하여 윈도우등을 손쉽게 만든다.*/

/* 대화상자를 하나 그린다. */
void make_a_dialog_box(int y, int x, int width, int height, 
	int attribute, char option_flags,
	char *title, char dialog_flags) 
{
	int title_center;

	/* 대화상자가 가질 수 있는 최대 크기를 고정 */
	if(26 > width) 
	{
		width = 20;
	}
	if(15 > height)
	{
		height = 10;
	}

        /* 저수준 상자구현 함수를 이용하여 그린다. */
	make_a_filled_box(y, x, width, height, attribute, option_flags);
	make_a_shadow(y, x, width, height, attribute);
	draw_a_quadrangle(y, x, width, height, attribute, option_flags);

        /* 제목을 가진다. */
	title_center = get_the_center_point(width, sizeof(title)); /* 제목을 상단 가운데에 놓는다. */
	put_a_string(y, x - 2 + (title_center), title, attribute);

	return;
}

/* 글을 편집할 수 있는 텍스트 에디터를 만든다. */

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

	move_cursor(0, y + 1, x + 1); /* 커서를 대화상자 안으로 넣는다. */

	proc_for_text_editor(y + 1, x + 1, width, height, attribute); /* 텍스트 에디터를 동작 시킨다 */

	return;
}

/* 메뉴를 선택할 수 있는 드랍메뉴를 만든다. */
void make_a_drop_menu(int y, int x, int width, int height, char attribute, char option_flags)
{
	make_a_filled_box(y, x, width, height, attribute, option_flags);
	make_a_shadow(y, x, width, height, attribute);
	draw_a_quadrangle(y, x, width, height, attribute, option_flags);

	return;
}




