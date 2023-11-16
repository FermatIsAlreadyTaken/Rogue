#include <rogue.h>
#include <ncurses.h>

Entity *player;
Tile **map;

int main(void)
{
	Position startPosition;
	bool compatibleTerminal;
	
	compatibleTerminal = cursesSetup();
	if (compatibleTerminal) {
		srand(time(NULL));
		
		map = createMapForCarve();
		startPosition = setupMapForMineBinarySpacePartitionVersion(2, 4);
		player = createPlayer(startPosition);
		
		gameLoop();
		
		closeGame();
	} else {
		endwin();
	}
	
	return 0;
}