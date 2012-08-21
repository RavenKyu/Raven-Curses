#include "rcurses/include/rcurses.h"

// 저레벨 1단계. 
// 가장 밑 바닥에서 상위 함수들을 도와줄 기본이 되는 함수들.

void put_a_character(int y, int x, char character, int attribute) // 한 글자를 화면에 출력한다.
{
    unsigned char far *location;	/* 글자와 속성값이 들어갈 포인터 변수 선언 */

    location = (unsigned char far *)0xb8000000 + y * 160 + x * 2; // 글자가 들어갈 주소를 대입

    *location++ = character; // 지정된 주소 한 바이트 앞에 글자가 들어간다.
    *location = attribute;   // 속성값을 넣어준다.

    return;
}

void put_a_character_as_ascii(int y, int x, char character, int attribute) // 미완성 코드
{
    unsigned char far *location;	/* Point where you put a word */
    int number = 0;

    location = (unsigned char far *)0xb8000000 + y * 160 + x * 2;

    number = '0' + character;

    *location++ = number;
    *location = attribute;

    return;
}

void put_a_string(int y, int x, char *string, int attribute) // 화면에 문자열을 출력한다.
{
    int i_count;
    char buffer[255];       // 문자열을 만들 때 사용할 Buffer Memory.

    strcpy(buffer, string); // Buffer에 인자로 받은 문자열을 복사한다.

    // 한 글자씩 주소를 옮겨 가며 put_a_character를 이용하여 화면에 출력한다.
    for(i_count = 0; strlen(string) - 1 >= i_count; i_count++)
    {                       
        put_a_character(y, x + i_count, buffer[i_count], attribute);
    }

    return;
}

// 배경화면을 지정된 타일로 채워준다.
void fill_background(char tile, int attribute) // 반복문을 화면 크기 만큼 수행해서 배경을 채워간다.
{
    int y;
    int x;
    
    for(y = 0; 25 >= y; y++) // 세로 크기
    {
        for(x = 0; 80 >= x; x++) // 가로 크기
        {
            put_a_character(y, x, tile, attribute); // 화면에 출력한다.
        }
    }
    
    return;
}


// 메뉴 선택바를 역상 시켜 준다
void VGA_inverse_bar(int y, int x, int length) // 위치 좌표와 길이를 인수로 받는다.
{
    int i = 0;
    unsigned char far *attr_memory = (unsigned char far *)0xb8000001L; 
    
    attr_memory = attr_memory + y * 160 + x * 2; // 문자를 찍을 수 있는 메모리에 접근
    
    for(i = 0; i < length; i++) // 반복문으로 지정된 길이만큼 수행
    {
        VGA_inverse_attrib(attr_memory); // 역상처리를 해주는 함수로 해당 주소를 인수로 보낸다.
        attr_memory = attr_memory + 2;   // 다음 글자를 위해 메모리 위치를 전진.
    }
    
    return;
}

// 역상처리를 하는 함수
void VGA_inverse_attrib(unsigned char far *attrib) // 메모리 위치를 받는다.
{
    unsigned char origin_attrib; // 원래 속성값을 저장할 변수.
    
    origin_attrib = *attrib;    // 가지고 있던 속성값은 따로 저장.
    *attrib = *attrib >> 4;
    *attrib = *attrib & 0x0f;
    origin_attrib = origin_attrib << 4;
    *attrib = *attrib | origin_attrib;
    
    return;
}

// 뒤가 비치는 그림자를 만들어 줄 함수
// VGA_inverse_bar 소스와 한 줄을 제외하고 중복되는 소스라 옵션을 주고 합치려다가 명확성을 위해 나누었다.
void VGA_inverse_shadow(int y, int x, int length) 
{
    int i = 0;
    unsigned char far *attr_memory = (unsigned char far *)0xb8000001L;

    attr_memory = attr_memory + y * 160 + x * 2;

    for(i = 0; i < length; i++)
    {
        VGA_inverse_attrib_shadow(attr_memory);
        attr_memory = attr_memory + 2;
    }

    return;
}

void VGA_inverse_attrib_shadow(unsigned char far *attrib) // 인자로 받은 메모리 부분을 해당 배경색으로 바꾸어 준다.
{
    *attrib = BG_BLACK;
    *attrib = *attrib | TEXT_GRAY | BG_BLACK; // 그림자 부분에 들어간 글자등은 검은 배경에 회색 글씨를 가진다.

    return;
}


// 객체의 중앙이 어디인지 계산해 준다.
// 현재 정확한 위치를 출력하지 않기 때문에 좀 더 수정을 필요로 하는 코드
int get_the_center_point(int width_of_base, int length_of_object)
{
	return ((width_of_base - length_of_object) / 2);
}

