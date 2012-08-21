#ifndef __LNKL_EDT_H__
#define __LNKL_EDT_H__

#include "rcurses/include/struct.h"

LINE_TAG *line_insert(LINE_TAG *a_line, LINE_TAG **line_list);


CHAR_TAG *char_insert(CHAR_TAG *a_char, CHAR_TAG **char_list, LINE_TAG **line_list);
#endif  //      __LNKL_EDT_H__
