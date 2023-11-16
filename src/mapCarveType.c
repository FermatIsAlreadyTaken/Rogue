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

/* Position setupMapForCarve(void)	// To main (a bit ugly generation)
{
	int y, x;
	int height, width;
	int numberOfRooms;
	Position startPosition;
	
	numberOfRooms =  (rand() % 11) + 5;
	Room* rooms = calloc(numberOfRooms, sizeof(Room));
	
	for (int i = 0; i < numberOfRooms; i++)  {
		y = (rand() % (MAP_HEIGHT - 11)) + 1;
		x = (rand() % (MAP_WIDTH - 19)) + 1;
		height = (rand() % 3)*2 + 5;	// only odd (5-9)
		width = (rand() % 7)*2 + 5;	// only odd (5-17)
		
		rooms[i] = createRoom(y, x, height, width);
		
		drawRoomForCarve(rooms[i]);
		if (i > 0) {
			connectRoomCenters(rooms[i - 1].center, rooms[i].center);
		}
	}
	
	startPosition.y = rooms[0].center.y;
	startPosition.x = rooms[0].center.x;
	
	free(rooms);
	
	return startPosition;
} 

Position setupMapForCarveNoOverlap(void)
{
	int y, x;
	int height, width;
	int numberOfRooms;
	int roomsCounter = 0;
	Position startPosition;
		
	numberOfRooms =  (rand() % 11) + 5;
	Room* rooms = calloc(numberOfRooms, sizeof(Room));
	
	for (int i = 0; i < numberOfRooms; )  {	// i++ <=> !roomOverlaps
		y = (rand() % (MAP_HEIGHT - 11)) + 1;
		x = (rand() % (MAP_WIDTH - 19)) + 1;
		height = (rand() % 3)*2 + 5;	// only odd (5-9)
		width = (rand() % 7)*2 + 5;	// only odd (5-17)
	
		if (!roomOverlaps(rooms, roomsCounter, y, x, height, width)) {
			rooms[roomsCounter] = createRoom(y, x, height, width);
			
			drawRoomForCarve(rooms[roomsCounter]);
			if (i > 0) {
				connectRoomCenters(rooms[i - 1].center, rooms[i].center);
			}
			
			roomsCounter++;
			i++;
		}
	}
	
	startPosition.y = rooms[0].center.y;
	startPosition.x = rooms[0].center.x;
	
	free(rooms);
	
	return startPosition;
} */

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