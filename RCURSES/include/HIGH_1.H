#ifndef __HIGH_1_H__
#define __HIGH_1_H__

#include "rcurses\include\rcurses.h"

typedef struct dialog_box
{
	char number;
} DIALOG_BOX;

/* 완벽한 대화상자 한개를 만든다. */
void make_a_dialog_box(int y, int x, int width, int height,
					   int attribute, char option_flags,
					   char *tilte, char dialog_flags);

/* 글을 쓸 수 있는 에디터를 기본으로 가지는 대화 상자를 만든다. */
DIALOG_BOX make_a_text_editor(int y, int x, int width, int height,
						int attribute, char optionf_flags,
						char *title, char dialog_flags);

/* #H3 */
 

#endif  // __HIGH_1_H__
