#include "rcurses/include/rcurses.h"

/* 2단계 저수준 부터는 인수로 들어갈 변수명들을 통일한다. */

/* 채워진 박스를 화면에 출력한다. */
void make_a_filled_box(int y, int x, int width, int height, int attribute, char option_flags)
{ // 위치 좌표, 박스의 크기, 색 속성 그리고 아직 구현을 하지 않은 옵션 플래그를 인수로 받는다.
    int i_count_x;
    int i_count_y;

    for(i_count_y = 0; height >= i_count_y; i_count_y++) /* 반복문을 이용하여 원하는 크기의 박스를 그린다. */
    {
        for(i_count_x = 0; width >= i_count_x; i_count_x++)
        {
            if((24 < y + i_count_y) || (79 < x + i_count_x) || (0 > y + i_count_y) || (0 > x + i_count_x))
            {
                /* 화면을 벗어난 위치에 그리지 않게 한다. 위치를 벗어나면 다음 줄에 그리게 된다.  */
            }
            else
            {       /* 화면 해당 위치에 '빈칸' 한 문자씩 지정된 색 속성으로 출력을 한다. */
                put_a_character(y + i_count_y, x + i_count_x , ' ', attribute);
            }
        }
    }

    return;
}

/* 그림자를 지정된 위치에 출력한다. 따로 사용하는것 보다 고수준 함수를 이용하여 사용하면 편리하다. */
void make_a_shadow(int y, int x, int width, int height, int attribute) 
{
    int i_count_x;
    int i_count_y;

    for(i_count_y = 0; height >= i_count_y; i_count_y++)
    {
        for(i_count_x = 0; width >= i_count_x; i_count_x++)
        {
            if((i_count_x == width) || (i_count_y == height)) /* 현재위치가 오브젝트의 가로 또는 세로길이와 같다면 */
            {              
                if((24 < y + i_count_y) || (79 < x + i_count_x) || (0 > y + i_count_y) || (0 > x + i_count_x))
                {
                    /* 그림자가 화면의 영역을 벗어나며 그리지 않는다. */
                }
                else
                {
                    /* 그림자 처리가 아닌 단순 검은 그림자로 처리 */
                    //put_a_character(y + i_count_y + 1, x + i_count_x + 1, ' ', BG_BLACK );

                    /* 그림자 영역에 들어간 문자를 보이게 할 수 있게 바꾸었다. */
                    VGA_inverse_shadow(y + i_count_y + 1, x + i_count_x + 1, 1);
                }
            }
        }
    }

    return;
}

/* 선으로 이루어진 선을 그린다. */
/* 이 부분은 선을 선택 할 수 있게 option flags 등을 이용해서 바꿀 수 있게 해야 한다. */
void draw_a_quadrangle(int y, int x, int width, int height, int attribute, char option_flags)
{
    int i_count_x;
    int i_count_y;

    for(i_count_y = 0; height >= i_count_y; i_count_y++)
    {
        for(i_count_x = 0; width >= i_count_x; i_count_x++)
        {
            if((i_count_y == 0) || (i_count_y == height))
            {
                if((24 < y + i_count_y) || (79 < x + i_count_x) || (0 > y + i_count_y) || (0 > x + i_count_x))
                {
                    /* 화면 밖으로 벗어나는 부분은 출력하지 않는다. */
                }
                else
                {              
                    put_a_character(y + i_count_y, x + i_count_x, HORIZON_1_LINE, attribute); /* 가로 선을 출력 */
                }
            }
			else if((i_count_x == 0) || (i_count_x = width))
            {
                if((24 < y + i_count_y) || (79 < x + i_count_x) || (0 > y + i_count_y) || (0 > x + i_count_x))
                {
                    /* 화면 밖으로 벗어나는 부분은 출력하지 않는다. */
                } 
                else
                {
                    put_a_character(y + i_count_y, x + i_count_x, VERTICAL_1_LINE, attribute); /* 세로 선을 출력 */
                }
            }
        }
    }

    /* 각각의 모서리 부분을 출력할 코드 */
    if((79 > x) && (x > 0))
    {
        put_a_character(y, x, TOP_LEFT_1_LINE, attribute); /* 좌측 상단 */
    }

    if((79 > (x + width)) || (0 < x + i_count_x))
    {
        put_a_character(y, x + width, TOP_RIGHT_1_LINE, attribute); /* 우측 상단 */
    }
    if((24 > y + height) && (0 < x))
    {
        put_a_character(y + height, x, BOTTOM_LEFT_1_LINE, attribute); /* 좌측 하단 */
    }
    if((79 > x + width))
    {
        put_a_character(y + height, x + width, BOTTOM_RIGHT_1_LINE, attribute); /* 우측 상단 */
    }
    
    return;
}

