#ifndef __STRUCTURES_RCURSES__
#define __STRUCTURES_RCURSES__

typedef struct window_tag
{
	int window_number;
	int window_counter;

	int x;
	int y;
	int width;
	int height;
	char attribute;
	char *tilte;

	void *parents;
	void *child;

	struct window_tag *previous_window;
	struct window_tag *next_window;
} WINDOW_TAG;

typedef struct line_tag
{
	int line_number;
	int line_counter;

	struct line_tag *previous_line;
	struct line_tag *next_line;
	struct char_tag *character_point;
} LINE_TAG;

typedef struct char_tag
{
	char character;
	int char_number;
	struct char_tag *previous_char;
	struct char_tag *next_char;
} CHAR_TAG;


#endif // __STRUCTURES_RCURSES__
