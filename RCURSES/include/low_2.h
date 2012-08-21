#ifndef __LOW_2_H__
#define __LOW_2_H__

/* 앞서 만들어진 1 단계 저레벨 함수들을 이용해서 필요한 것들을 구현한다. */

/* 화면에 박스를 출력해 줄 함수들 */
void make_a_filled_box(int y, int x, int width, int height, int attribute, char option_flags); // 채워진 상자를 만든다.
void make_a_shadow(int y, int x, int width, int height, int attribute); // 상자에 그림자를 그린다.
void draw_a_quadrangle(int y, int x, int width, int height, int attribute, char option_flags); // 테두리를 그린다.

#endif  // __LOW_2_H__
