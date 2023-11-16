#include <rogue.h>

Tile** createMapForCarve(void)	// To main (basic setup for carved maps)
{ 
	Tile** tiles = calloc(MAP_HEIGHT, sizeof(Tile*));
	
	for (int y = 0; y < MAP_HEIGHT; y++) { 
		tiles[y] = calloc(MAP_WIDTH, sizeof(Tile));
		for (int x = 0; x < MAP_WIDTH; x++) { 
			tiles[y][x].symbol = ' ';
			tiles[y][x].color = COLOR_PAIR(VISIBLE_COLOR);
			tiles[y][x].walkable = false;
			tiles[y][x].transparent = false;
			tiles[y][x].visible = false;
			tiles[y][x].seen = false;
		}
	} 
	
	return tiles;
}

bool roomOverlaps(Room *rooms, int roomsCounter, int y, int x, int height, int width)
{
	for (int i = 0; i < roomsCounter; i++) {
		if (x >= rooms[i].position.x + rooms[i].width || rooms[i].position.x >= x + width) {
			continue;
		}
		if (y + height <= rooms[i].position.y || rooms[i].position.y + rooms[i].height <= y) {
		continue;
		}
		
		return true;
	}
	
	return false;
} 

void freeMap(void)
{ 
	for (int y = 0; y < MAP_HEIGHT; y++) { 
		free(map[y]);
	} 
	free(map);
}
