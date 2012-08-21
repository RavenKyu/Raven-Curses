#include "editor/include/editor.h"
#include "rcurses/include/rcurses.h"

/*Proccessinf Function for Text Editor
 * 문서 편집기의 동작처리를 수행하는 소스 */

void proc_for_text_editor(int y, int x, int width, int height, char attribute)
{
    char low_level;
    char high_level;

    int i_cursor_y = y;
    int i_cursor_x = x;

    static int cursor_y = 0;
    static int cursor_x = 0;
    
    LINE_TAG *line_list = NULL;
    CHAR_TAG *char_list = NULL;

    
    while(1)
    {
        get_keyboard_input(&high_level, &low_level); // 키보드 입력을 받는다.

        if(high_level != 0)     // 특수키 입력을 받았을 경우
        {
            key_proc_text_editor_high_level(y, x, width, height, &i_cursor_y, &i_cursor_x, high_level, &line_list);
        }
        else if(low_level != 0)                    // 특수키 입력을 받지 않았을 경우
        {
            key_proc_text_editor_low_level(y, x, width, height,
                                           &i_cursor_y, &i_cursor_x, &cursor_y, &cursor_x,
                                           low_level, line_list, char_list);
        }

        //테스트용 출력
        move_cursor(0, i_cursor_y, i_cursor_x+1);
        put_a_character(i_cursor_y, i_cursor_x, line_list -> character_point -> character, TEXT_WHITE | BG_BLUE);
        ++i_cursor_x;



    }
    
    return;
}
