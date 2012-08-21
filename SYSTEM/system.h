#ifndef __SYSTEM_H__
#define __SYSTEM_H__

void exit_program(void);
void initialize(void);
void file_menu(void);
void make_a_menu(int y, int x, int width, int height, char attribute);

void debugging_window(int *y, int *x, const char *item, int value);

void make_a_main_menu(int y, int x, int width, int height, char attribute, char option_flags);

void make_a_drop_menu(int y, int x, int width, int height, char attribute, char option_flags);
#endif  //      __SYSTEM_H__
