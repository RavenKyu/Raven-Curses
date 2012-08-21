#include "rcurses/include/rcurses.h"

#if DEBUG == 3

WINDOW_TAG *insert(WINDOW_TAG *a_window, WINDOW_TAG *lastest_window)	/* just, make a line. */
{
	WINDOW_TAG *current_window;
	WINDOW_TAG *follow_window;
	WINDOW_TAG *new_window;

	current_window = lastest_window;
	follow_window = lastest_window;

	new_window = (WINDOW_TAG *)malloc(sizeof(WINDOW_TAG));
	if(new_window == NULL)
	{
		/*	Print error Message about what it failed to allocate. */
	}
	*new_window = *a_window;

	/* Insert a line between lines */
	if(current_window == NULL)
	{/* if cur_line is NULL, it means the line you are making is the first line of this document. */
		lastest_window = new_window;
	}
	else
	{/* if current_line has a address of line, the line will be the previous line for new line. */
		follow_window = current_window;
		new_window -> previous_window = follow_window;

		if(follow_window -> next_window != NULL)
		{
			follow_window -> next_window -> previous_window = new_window;
			new_window -> next_window = follow_window -> next_window;

		}
		lastest_window = new_window;
	}
	return lastest_window;
	/* The first line */

	/*   */
}

#endif