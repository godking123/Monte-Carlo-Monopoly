#include "Board.h"

Board::Board() {
    spaces.resize(40, nullptr);
    // Taxes
    spaces[4] = new IncomeTax(4);
    spaces[38] = new LuxuryTax(38);

    // Railroads
    spaces[5] = new Railroad("Reading Railroad", 5);
    spaces[15] = new Railroad("Pennsylvania Railroad", 15);
    spaces[25] = new Railroad("B. & O. Railroad", 25);
    spaces[35] = new Railroad("Short Line", 35);

    // Utilities
    spaces[12] = new Utility("Electric Company", 12);
    spaces[28] = new Utility("Water Works", 28);

    // Jail/GoToJail
    spaces[10] = new Jail(10);
    spaces[30] = new GoToJail(30);

    // Community Chest
    spaces[2]  = new CommunityChest(2);
    spaces[17] = new CommunityChest(17);
    spaces[33] = new CommunityChest(33);

    // Chance
    spaces[7]  = new Chance(7);
    spaces[22] = new Chance(22);
    spaces[36] = new Chance(36);

    // Brown
    spaces[1] = new Property("Mediterranean Avenue", 60, 1, {2, 10, 30, 90, 160, 250}, 50, "Brown");
    spaces[3] = new Property("Baltic Avenue", 60, 3, {4, 20, 60, 180, 320, 450}, 50, "Brown");


    // Light Blue
    spaces[6] = new Property("Oriental Avenue", 100, 6, {6, 30, 90, 270, 400, 550}, 50, "Light Blue");
    spaces[8] = new Property("Vermont Avenue", 100, 8, {6, 30, 90, 270, 400, 550}, 50, "Light Blue");
    spaces[9] = new Property("Connecticut Avenue", 120, 9, {8, 40, 100, 300, 450, 600}, 50, "Light Blue");

    // Pink
    spaces[11] = new Property("St. Charles Place", 140, 11, {10, 50, 150, 450, 625, 750}, 100, "Pink");
    spaces[13] = new Property("States Avenue", 140, 13, {10, 50, 150, 450, 625, 750}, 100, "Pink");
    spaces[14] = new Property("Virginia Avenue", 160, 14, {12, 60, 180, 500, 700, 900}, 100, "Pink");

    // Orange
    spaces[16] = new Property("St. James Place", 180, 16, {14, 70, 200, 550, 750, 950}, 100, "Orange");
    spaces[18] = new Property("Tennessee Avenue", 180, 18, {14, 70, 200, 550, 750, 950}, 100, "Orange");
    spaces[19] = new Property("New York Avenue", 200, 19, {16, 80, 220, 600, 800, 1000}, 100 , "Orange");

    // Red
    spaces[21] = new Property("Kentucky Avenue", 220, 21, {18, 90, 250, 700, 875, 1050}, 150, "Red");
    spaces[23] = new Property("Indiana Avenue", 220, 23, {18, 90, 250, 700, 875, 1050}, 150, "Red");
    spaces[24] = new Property("Illinois Avenue", 240, 24, {20, 100, 300, 750, 925, 1100}, 150, "Red");

    // Yellow
    spaces[26] = new Property("Atlantic Avenue", 260, 26, {22, 110, 330, 800, 975, 1150}, 150, "Yellow");
    spaces[27] = new Property("Ventnor Avenue", 260, 27, {22, 110, 330, 800, 975, 1150}, 150, "Yellow");
    spaces[29] = new Property("Marvin Gardens", 280, 29, {24, 120, 360, 850, 1025, 1200}, 150, "Yellow");

    // Green
    spaces[31] = new Property("Pacific Avenue", 300, 31, {26, 130, 390, 900, 1100, 1275}, 200, "Green");
    spaces[32] = new Property("North Carolina Avenue", 300, 32, {26, 130, 390, 900, 1100, 1275}, 200, "Green");
    spaces[34] = new Property("Pennsylvania Avenue", 320, 34, {28, 150, 450, 1000, 1200, 1400}, 200, "Green");

    // Dark Blue
    spaces[37] = new Property("Park Place", 350, 37, {35, 175, 500, 1100, 1300, 1500}, 200, "Dark Blue");
    spaces[39] = new Property("Boardwalk", 400, 39, {50, 200, 600, 1400, 1700, 2000}, 200, "Dark Blue");
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