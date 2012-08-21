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


