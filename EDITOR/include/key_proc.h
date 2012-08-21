#ifndef __KEY_PROC_EDITOR_H__
#define __KEY_PROC_EDITOR_H__

#include "rcurses/include/struct.h"

/* 에디터의 키 동작을 구현 해 준다. */
void key_proc_text_editor_low_level(int y, int x, int width, int height,
                                    int *i_cursor_y, int *i_cursor_x, int low_level, LINE_TAG *line_list);

void key_proc_text_editor_high_level(int y, int x, int width, int height,
                                     int *i_cursor_y, int *i_cursor_x,int high_level, LINE_TAG *line_list);

#endif //  __KEY_PROC_EDITOR_H__
