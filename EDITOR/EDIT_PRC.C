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

    LINE_TAG line_list;
    
    while(1)
    {
        get_keyboard_input(&high_level, &low_level); // 키보드 입력을 받는다.

        if(high_level != 0)     // 특수키 입력을 받았을 경우
        {
            key_proc_text_editor_high_level(y, x, width, height, &i_cursor_y, &i_cursor_x, high_level, &line_list);
        }
        else if(low_level != 0)                    // 특수키 입력을 받지 않았을 경우
        {
            key_proc_text_editor_low_level(y, x, width, height, &i_cursor_y, &i_cursor_x, low_level, &line_list);
        }
    }

    return;
}
