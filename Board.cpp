#include "Board.h"

Board::Board() {
    spaces.resize(40, nullptr);

    // Community Chest
    spaces[2] = new CommunityChest(2, 0, 200);   // Space 2: e.g., gain $200, don't move
    spaces[17] = new CommunityChest(17, -3, 0);  // Space 17: e.g., move back 3 spaces
    spaces[33] = new CommunityChest(33, 0, -50); // Space 33: e.g., pay $50, don't move

    // Brown
    spaces[1] = new Property("Mediterranean Avenue", 60, 1, 2);
    spaces[3] = new Property("Baltic Avenue", 60, 3, 4);

    // Railroad 1
    spaces[5] = new Property("Reading Railroad", 200, 5, 25);

    // Light Blue
    spaces[6] = new Property("Oriental Avenue", 100, 6, 6);
    spaces[8] = new Property("Vermont Avenue", 100, 8, 6);
    spaces[9] = new Property("Connecticut Avenue", 120, 9, 8);

    // Pink
    spaces[11] = new Property("St. Charles Place", 140, 11, 10);
    spaces[12] = new Property("Electric Company", 150, 12, 20); // simplified flat rent
    spaces[13] = new Property("States Avenue", 140, 13, 10);
    spaces[14] = new Property("Virginia Avenue", 160, 14, 12);

    // Railroad 2
    spaces[15] = new Property("Pennsylvania Railroad", 200, 15, 25);

    // Orange
    spaces[16] = new Property("St. James Place", 180, 16, 14);
    spaces[18] = new Property("Tennessee Avenue", 180, 18, 14);
    spaces[19] = new Property("New York Avenue", 200, 19, 16);

    // Red
    spaces[21] = new Property("Kentucky Avenue", 220, 21, 18);
    spaces[23] = new Property("Indiana Avenue", 220, 23, 18);
    spaces[24] = new Property("Illinois Avenue", 240, 24, 20);

    // Railroad 3
    spaces[25] = new Property("B. & O. Railroad", 200, 25, 25);

    // Yellow
    spaces[26] = new Property("Atlantic Avenue", 260, 26, 22);
    spaces[27] = new Property("Ventnor Avenue", 260, 27, 22);
    spaces[28] = new Property("Water Works", 150, 28, 20); // simplified flat rent
    spaces[29] = new Property("Marvin Gardens", 280, 29, 24);

    // Green
    spaces[31] = new Property("Pacific Avenue", 300, 31, 26);
    spaces[32] = new Property("North Carolina Avenue", 300, 32, 26);
    spaces[34] = new Property("Pennsylvania Avenue", 320, 34, 28);

    // Railroad 4
    spaces[35] = new Property("Short Line", 200, 35, 25);

    // Dark Blue
    spaces[37] = new Property("Park Place", 350, 37, 35);
    spaces[39] = new Property("Boardwalk", 400, 39, 50);
}

Board::~Board() {
    for (auto p : spaces) {
        delete p;
    }
}

Square* Board::getSquareAt(int position) const
{
    return spaces[position];
}