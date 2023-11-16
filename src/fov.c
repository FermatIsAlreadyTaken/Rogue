#include <rogue.h>

void makeFOV(Entity* player)
{ 
	int y, x, distance;
	int RADIUS = 15;
	Position target;
	
	map[player->position.y][player->position.x].visible = true;
	map[player->position.y][player->position.x].seen = true;
	
	for (y = player->position.y - RADIUS; y < player->position.y + RADIUS; y++) { 
		for (x = player->position.x - RADIUS; x < player->position.x + RADIUS; x++) { 
			target.y = y;
			target.x = x;
			distance = getDistance(player->position, target);
			
			if (distance < RADIUS) { 
				if (isInMap(y, x) && lineOfSight(player->position, target)) { 
					map[y][x].visible = true;
					map[y][x].seen = true;
				} 
			} 
		} 
	} 
} 

void clearFOV(Entity* player)
{ 
	int y, x;
	int RADIUS = 15;
	
	for (y = player->position.y - RADIUS; y < player->position.y + RADIUS; y++) { 
		for (x = player->position.x - RADIUS; x < player->position.x + RADIUS; x++) {
			if (isInMap(y, x)) {
				map[y][x].visible = false;
			}
		}
	}
}

int getDistance(Position origin, Position target)
{ 
	double dy, dx;
	int distance;
	dx = target.x - origin.x;
	dy = target.y - origin.y;
	distance = floor(sqrt((dx * dx) + (dy * dy)));
	
	return distance;
}

bool isInMap(int y, int x)
{ 
	if ((0 < y && y < MAP_HEIGHT - 1) && (0 < x && x < MAP_WIDTH - 1)) { 
		return true;
	}
	
	return false;
}

bool lineOfSight(Position origin, Position target)
{
	int t, x, y;
	int absDeltaX, absDeltaY;
	int signX, signY;
	int deltaX, deltaY;
	
	deltaX = origin.x - target.x;
	deltaY = origin.y - target.y;
	
	absDeltaX = abs(deltaX);
	absDeltaY = abs(deltaY);
	
	signX = getSign(deltaX);
	signY = getSign(deltaY);
	
	x = target.x;
	y = target.y;
	
	if (absDeltaX > absDeltaY) {
		t = absDeltaY * 2 - absDeltaX;
		
		do {
			if (t >= 0) {
				y += signY;
				t -= absDeltaX * 2;
			}
			
			x += signX;
			t += absDeltaY * 2;
			
			if (x == origin.x && y == origin.y) {
				return true;
			}
		} while (map[y][x].transparent);
		
		return false;
	} else {
		t = absDeltaX * 2 - absDeltaY;
		
		do {
			if (t >= 0) {
			x += signX;
			t -= absDeltaY * 2;
			}

			y += signY;
			t += absDeltaX * 2;

			if (x == origin.x && y == origin.y) {
				return true;
			}
		} while (map[y][x].transparent);
		
		return false;
	}
}

int getSign(int a)
{
	return (a < 0) ? -1 : 1;
}