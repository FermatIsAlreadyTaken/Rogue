#include <rogue.h>

Position setupMapForMineBinarySpacePartitionVersion(int n, int m)	// To main (mine map better generator) [n <= 2 x m <= 7]
{
	int y, x;
	int i, j, k;
	int sector = 0;
	int height, width;
	int numberOfRooms;
	int roomsCounter;
	Position startPosition;
	Room *rooms;
	Room *rooms2;
	
	rooms2 = calloc(n*m, sizeof(Room));
	
	for (i = 0; i < n; i++) {		// y
		for (j = 0; j < m; j++) {	//x
			roomsCounter = 0;
			numberOfRooms =  (rand() % (5 - n)) + 2;
			rooms = calloc(numberOfRooms, sizeof(Room));
			
			for (k = 0; k < numberOfRooms; ) {	// k++ <=> !roomOverlaps
				height = (rand() % 3)*2 + 5;	// only odd (5-9)
				width = (rand() % 3)*2 + 5;		// only odd (5-9)
				
				if (j == 0) {
					x = (rand() % ((int)(MAP_WIDTH/m))) + ((int)(MAP_WIDTH/m))*j + 1;
				} else if (j == m - 1) {
					x = (rand() % ((int)(MAP_WIDTH/m) - width)) + ((int)(MAP_WIDTH/m))*j;
				} else { 
					x = (rand() % ((int)(MAP_WIDTH/m) + 1)) + ((int)(MAP_WIDTH/m))*j;
				}
				if (i == 0) {
					y = (rand() % ((int)(MAP_HEIGHT/n))) + ((int)(MAP_HEIGHT/n))*i + 1;
				} else if (i == n - 1) {
					y = (rand() % ((int)(MAP_HEIGHT/n) - height)) + ((int)(MAP_HEIGHT/n))*i;
				} else {
					y = (rand() % ((int)(MAP_HEIGHT/n) + 1)) + ((int)(MAP_HEIGHT/n))*i;
				}
				
				if (!roomOverlaps(rooms, roomsCounter, y, x, height, width)) {
					rooms[roomsCounter] = createRoom(y, x, height, width);
			
					drawRoomForCarve(rooms[roomsCounter]);
					if (k > 0) {
						connectRoomCenters(rooms[k - 1].center, rooms[k].center);
						if ((rand() % 1) == 0 && k > 1) {
							connectRoomCenters(rooms[k - 2].center, rooms[k].center);
						}
					}
					
					roomsCounter++;
					k++;
				}
			}
			rooms2[sector++] = createRoom(y, x, height, width);
			free(rooms);
		}
	}
	
	sector = 0;
	for (i = 0; i < n; i++) {
		for (j = 0; j < m - 1; j++) {
			connectRoomCenters(rooms2[sector + 1].center, rooms2[sector].center);
			sector++;
		}
		sector++;
		if (i < n - 1) {
			k = (rand() % m) + i*m;
			connectRoomCenters(rooms2[k + m].center, rooms2[k].center);
		}
	}
	
	startPosition.y = rooms2[n*m - 1].center.y;
	startPosition.x = rooms2[n*m - 1].center.x;
	
	free(rooms2);
	
	return startPosition;
}
