/* RCURSES (Raven Curses)를 이용한 문서 편집기
 * 2012년 8월.*/

#include "include/headers.h"

int main()
{
    char high_level;        // 키보드 입력을 받기 위한 변수 선언
    char low_level;

    WINDOW_TAG *main_window = NULL;

    char screen_buffer;

    initialize();           // 화면 초기화.

    main_window = (WINDOW_TAG *)malloc(sizeof(WINDOW_TAG));
    if(main_window == NULL)
    {
        //fatal_error_memory();
    }

    make_a_dialog_box(10, 13, 40, 13, TEXT_WHITE | BG_SKY, 22, " Raven ", 2);
    make_a_text_editor(3, 4, 15, 5, TEXT_WHITE | BG_BLUE, 22, " Hello ", 1);

    free(main_window);
    return 0;
}
