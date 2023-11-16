#include <rogue.h>

void drawMap(void)
{ 
	for (int y = 0; y < MAP_HEIGHT; y++) { 
		for (int x = 0; x < MAP_WIDTH; x++) { 
			if (map[y][x].visible) {
				mvaddch(y, x, map[y][x].symbol | map[y][x].color);
			} else if (map[y][x].seen) {
				mvaddch(y, x, map[y][x].symbol | COLOR_PAIR(SEEN_COLOR));
			} else {
				mvaddch(y, x, ' ');
			}
		} 
	} 
} 

void drawEntity(Entity *entity)
{ 
	mvaddch(entity->position.y, entity->position.x, entity->symbol | entity->color);
} 

void drawEverything(void)
{
	clear();
	drawMap();
	drawEntity(player);
} 