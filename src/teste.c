#include <stdlib.h>
#include <ncurses.h>

void end_curses()
{
	endwin();
}

int main()
{
	atexit(end_curses);
	initscr();
	WINDOW* win = newwin(10 , 10 , 0 , 0);
	keypad(win , true);
	box(win , 0 , 0);

	wmove(win, 5 , 5);
	wprintw(win , "X");

	refresh();
	wrefresh(win);
	getch();
}
