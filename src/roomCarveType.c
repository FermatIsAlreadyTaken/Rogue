#include <rogue.h>

Room createRoom(int y, int x, int height, int width)
{
	Room newRoom;
	
	newRoom.position.y = y;
	newRoom.position.x = x;
	newRoom.height = height;
	newRoom.width = width;
	newRoom.center.y = y + (int)(height / 2);	// not "height + 1" because of "y +"
	newRoom.center.x = x + (int)(width / 2);	// not "width + 1" because of "x +"
	
	return newRoom;
}

void drawRoomForCarve(Room room)
{
	for (int y = room.position.y; y < room.position.y + room.height; y++) {
		for (int x = room.position.x; x < room.position.x + room.width; x++) {
			map[y][x].symbol = '.';
			map[y][x].walkable = true;
			map[y][x].transparent = true;
		}
	}
}

void connectRoomCenters(Position centerOne, Position centerTwo)
{ 
	Position temp;
	temp.x = centerOne.x;
	temp.y = centerOne.y;
	
	while (true) { 
		// West
		if (abs((temp.x - 1) - centerTwo.x) < abs(temp.x - centerTwo.x)) {
			temp.x--;
		// East
		} else if (abs((temp.x + 1) - centerTwo.x) < abs(temp.x - centerTwo.x)) {
			temp.x++;
		// South
		} else if (abs((temp.y + 1) - centerTwo.y) < abs(temp.y - centerTwo.y)) {
			temp.y++;
		// North
		} else if (abs((temp.y - 1) - centerTwo.y) < abs(temp.y - centerTwo.y)) {
			temp.y--;
		// End
		} else {
			break;
		}
		
		map[temp.y][temp.x].symbol = '.';
		map[temp.y][temp.x].walkable = true;
		map[temp.y][temp.x].transparent = true;
	}
}
