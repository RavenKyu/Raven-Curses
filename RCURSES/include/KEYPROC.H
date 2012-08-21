#ifndef __GET_KEY_PROC_H__
#define __GET_KEY_PROC_H__

/* 키보드 입력을 처리 해주는 함수 모음 */
/* 키보드 입력을 사용할 윈도우는 커서 위치를 저장하고 통신을 할 수 있는 아래의 변수를 반드시 가져야 한다.
 * int i_cursor_y;
 * int i_cursor_x;
 * int high_level;
 * int low_level;
 * 위의 변수 값을 참고하여 키보드 입력을 받고 지정해둔 기능에 맞게 수행하게 된다. */

void get_keyboard_input(char *high_level, char *low_level); // 키보드의 입력을 받는다.
void move_cursor(int page, int y, int x); // 커서를 인자를 받아서 이동 시킨다.

/* 커서를 이동한다. 커서는 주어진 공간을 벗어나지 못 한다.*/
void move_cursor_left(int y, int x, int width, int height, int **i_cursor_y, int **i_cursor_x, int high_level);
void move_cursor_right(int y, int x, int width, int height, int **i_cursor_y, int **i_cursor_x, int high_level);
void move_cursor_up(int y, int x, int width, int height, int **i_cursor_y, int **i_cursor_x, int high_level);
void move_cursor_down(int y, int x, int width, int height, int **i_cursor_y, int **i_cursor_x, int high_level);

void move_cursor_new_line(int y, int x, int width, int height, int **i_cursor_y, int **i_cursor_x, int low_level);

void type_words(int y, int x, int width, int height, int **i_cursor_y, int **i_cursor_x, int low_level);

#endif // __GET_KEY_PROC_H__
