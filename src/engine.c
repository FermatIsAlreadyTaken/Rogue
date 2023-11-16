#include <rogue.h>

bool cursesSetup(void)
{ 
	initscr();
	noecho();
	curs_set(0);
	
	if (has_colors()) {
		start_color();
		
		init_pair(VISIBLE_COLOR, COLOR_WHITE, COLOR_BLACK);
		init_pair(SEEN_COLOR, COLOR_BLUE, COLOR_BLACK);
		
		return true;
	} else {
		mvprintw(20, 50, "Your system doesn't support color. Can't start game!");
		getch();
		return false;
	}
}

void gameLoop(void)
{ 
	int input;
	
	makeFOV(player);
	
	drawEverything();
	
	while (true) {
		input = getch();
		if (input == 27) {
			break;
		}
		handleInput(input);
		drawEverything();
	}
	
}

void closeGame(void)
{ 
  endwin();
  free(player);
} 