#ifndef ROGUE_H
#define ROGUE_H

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Map Dimensions
#define MAP_HEIGHT 40
#define MAP_WIDTH 150

// Color Pairs
#define VISIBLE_COLOR 1
#define SEEN_COLOR 2

// https://dev.to/ignaoya/the-c-roguelike-tutorial-part-2-the-map-2hg

typedef struct Position {
	int y;
	int x;
} Position;

typedef struct Entity {
	Position position;
	char symbol;
	int color;
} Entity;

typedef struct Tile {
	char symbol;
	int color;
	bool walkable;
	bool transparent;
	bool visible;
	bool seen;
} Tile;

typedef struct Room {
	int height; 
	int width;
	Position position;
	Position center;
} Room;

// const int MAP_HEIGHT = 40;
// const int MAP_WIDTH = 140;

/* Engine Functions (engine.c) */
bool cursesSetup(void);
void gameLoop(void);
void closeGame(void);

/* Player Functions (player.c) */
Entity* createPlayer(Position startPosition);
void handleInput(int input);
void movePlayer(Position newPosition);

/* Map Functions (mapCarveType.c) */
void freeMap(void);
/* Functions For Carve */
Tile** createMapForCarve(void);
// Position setupMapForCarve(void);
// Position setupMapForCarveNoOverlap(void)
bool roomOverlaps(Room *rooms, int roomsCounter, int y, int x, int height, int width);
/* mine map functions (check for Overlap-Carve) (mineCarveType.c) */
// Position setupMapForMineNoOverlap(void);
// Position setupMapForMineGridVersion(int NxN);
Position setupMapForMineBinarySpacePartitionVersion(int n, int m);

/* Room Functions (room.c) */
Room createRoom(int y, int x, int height, int width);
/* (for carve) */
void drawRoomForCarve(Room room);
void connectRoomCenters(Position centerOne, Position centerTwo);

/* Draw Functions (draw.c) */
void drawMap(void);
void drawEntity(Entity* entity);
void drawEverything(void);

/* Fov Functions (fov.c) */
void makeFOV(Entity* player);
void clearFOV(Entity* player);
int getDistance(Position origin, Position target);
bool isInMap(int y, int x);
bool lineOfSight(Position origin, Position target);
int getSign(int a);

/* Externs */
extern Entity *player;
// extern const int MAP_HEIGHT;
// extern const int MAP_WIDTH;
extern Tile **map;

#endif  