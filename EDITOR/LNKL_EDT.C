#include "editor/include/editor.h"
#include "rcurses/include/rcurses.h"
#include "rcurses/include/struct.h"

#define DEBUG  1

LINE_TAG *line_insert(LINE_TAG *a_line, LINE_TAG **line_list)	/* 문자를 연결에 추가한다. */
{
    LINE_TAG *current_line;     /* 현재 커서가 위치한 줄 */
    LINE_TAG *follow_line;      /* 바로 윗 줄 */
    LINE_TAG *new_line;         /* 추가할 새로운 줄 */

    current_line = line_list;   /* 위치했던 줄의 연결 리스트 정보를 대입  */
    follow_line = line_list;

    new_line = (LINE_TAG *)malloc(sizeof(LINE_TAG));
    if(new_line == NULL)
    {
        /*	Print error Message about what it failed to allocate. */
    }
    *new_line = *a_line;        /* 새로운 라인의 값들을 연결 리스트에 넣는다. */

    /* 줄과 줄 사이에 새로운 줄을 추가  */
    if(current_line == NULL)
    {/* 새로운 문서를 열게되면 Current_Line은 NULL이다. */
        line_list = new_line;   /* 새로 만든 라인의 주소를 line_list에 대입 */
    }
    else
    {/* current_line 에 주소가 존재한다면, current_line이 바로 윗 줄이 된다. */
        follow_line = current_line; /* 위치했던 줄은 따라오는 줄, 즉 윗 줄이 된다. */
        new_line -> previous_line = follow_line; /* 새 줄의 연결 리스트의 멤버 previous_line에 앞 줄에 잇는다. */

        if(follow_line -> next_line != NULL) /* 줄과 줄 사이에 넣는 것이라면 */
        {
            follow_line -> next_line -> previous_line = new_line; /* 아랫줄과 새로운 줄을 잇고 */
            new_line -> next_line = follow_line -> next_line; /* 새로운 줄과 아랫 줄을 서로 잇는다. */
        }
        line_list = new_line;
    }

#if DEBUG == 1
    put_a_string(4, 5, "Succeed!", TEXT_WHITE | BG_BLUE);
#endif
    return line_list;
}



/* 문자를 위한 연결 리스트 */

CHAR_TAG *char_insert(CHAR_TAG *a_char, CHAR_TAG **char_list, LINE_TAG **line_list)	/* 문자를 연결에 추가한다. */
{
    CHAR_TAG *current_char;     /* 현재 커서가 위치한 문자 */
    CHAR_TAG *previous_char;      /* 앞 문자 */
    CHAR_TAG *new_char;         /* 추가할 새로운 문자 */
       
    current_char = *char_list;
    previous_char = *char_list;

    new_char = (CHAR_TAG *)malloc(sizeof(CHAR_TAG));
    if(new_char == NULL)
    {
        /*	Print error Message about what it failed to allocate. */
        put_a_character(1, 1, a_char -> character, TEXT_WHITE | BG_BLUE);                
    }
    *new_char = *a_char;        /* 새로운 문자 값들을 연결 리스트에 넣는다. */

/* 문자와 문자 사이에 새 문자를 삽입  */
    if(current_char == NULL)
    {
        new_char -> previous_char = NULL;
        new_char -> next_char = NULL;

        (*line_list) -> character_point = *char_list;
        
        **char_list = *new_char;   /* 새로 만든 char 주소에 char_list에 대입 */
    }
    else
    {/* current_char 에 주소가 존재한다면, current_char이 바로 앞 문자가 된다. */
        previous_char = current_char; /* 인수로 받은 문자는 바로 앞 문자가 된다. */
        new_char -> previous_char = previous_char; /* 새 문자의 연결 리스트의 멤버 previous_char에 앞 문자를 잇는다. */

        if(previous_char -> next_char != NULL) /* 문자와 문자 사이에 넣는 것이라면 */
        {
            previous_char -> next_char -> previous_char = new_char; /* 다음 문자와 새로운 문자를 잇고 */
            new_char -> next_char = previous_char -> next_char; /* 새로운 문자와 다음 문자를 서로 잇는다. */
        }
        **char_list = *new_char;
    }

    return *char_list;
}
