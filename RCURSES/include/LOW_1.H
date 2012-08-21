#ifndef __LOW_1_H__
#define __LOW_1_H__

// 화면 출력 담당
void put_a_character(int y, int x, char character, int attribute); // 문자 인자로 받아서 화면에 출력한다.
void put_a_character_as_ascii(int y, int x, char character, int attribute);
void put_a_string(int y, int x, char *string, int attribute);      // 문자열을 인자로 받아서 출력한다.

void fill_background(char tile, int attribute); // 배경을 채운다.

void VGA_inverse_attrib(unsigned char far *attrib); // 메뉴 선택바 역상처리를 한다.
void VGA_inverse_bar(int y, int x, int length);

void VGA_inverse_attrib_shadow(unsigned char far *attrib); // 뒤가 비치는 그림자를 처리한다.
void VGA_inverse_shadow(int y, int x, int length);

// 계산 담당
int get_the_center_point(int width_of_base, int length_of_object); // 객체의 가운데 부분을 계산한다.


#endif	//	__LOW_1_H__
