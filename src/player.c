#include <rogue.h>
#include <stdio.h>

Entity * createPlayer(Position startPosition)
{
	Entity *newPlayer = calloc(1, sizeof(Entity));
	
	newPlayer->position.y = startPosition.y;
	newPlayer->position.x = startPosition.x;
	newPlayer->color = COLOR_PAIR(VISIBLE_COLOR);
	newPlayer->symbol = '@';
	
	
	return newPlayer;
}

void handleInput(int input)
{
	Position newPosition = {player->position.y, player->position.x};
	Position startPosition;
	
	switch(input) {
		// Move Up
		case 'w':
		case 'W':
			newPosition.y--;
			break;
		// Move Down
		case 's':
		case 'S':
			newPosition.y++;
			break;
		// Move Left
		case 'a':
		case 'A':
			newPosition.x--;
			break;
		// Move Right
		case 'd':
		case 'D':
			newPosition.x++;
			break;
		// Restart Map Generation
		case '$':
			map = createMapForCarve();
			startPosition = setupMapForMineBinarySpacePartitionVersion(2, 4);
			player = createPlayer(startPosition);
			drawEverything();
			makeFOV(player);
			break;
		// Ping Map
		case '.':
			for (int y = 0; y < MAP_HEIGHT; y++) { 
				for (int x = 0; x < MAP_WIDTH; x++) { 
					map[y][x].seen = true;
				}
			}
			drawMap();
			break;
		default:
			break;
	}
	movePlayer(newPosition);
}

void movePlayer(Position newPosition)
{ 
	if (map[newPosition.y][newPosition.x].walkable) {
		clearFOV(player);
		player->position.y = newPosition.y;
		player->position.x = newPosition.x;
		makeFOV(player);
	}
}
