#include "game_menu.h"
#include "../graphic/framebf.h"
#include "../utils/utils.h"
#include "../graphic/game_graphic.h"

void home(int arrowPosition) {
    drawBackground();
    drawString(100, 100, "Battle Ship Adventure", 0x00ffffff, 5);
    drawString(180, 300, "Start", 0x00ffffff, 3);
    drawString(180, 400, "How to play", 0x00ffffff, 3);
    drawString(180, 500, "Choose ship", 0x00ffffff, 3);
    drawArrow(130, 295 + arrowPosition);
}

void howtoplay() {
    clearScreen();
    drawString(100, 100, "How to play", 0x00ffffff, 6);
    drawString(100, 200, "Objective: Shoot all monsters to win!", 0x00ffffff, 3);
    drawString(100, 250, "Press 'a' and the ship will go left.", 0x00ffffff, 3);
    drawString(100, 300, "Press 'd' and the ship will go right.", 0x00ffffff, 3);
    drawString(100, 350, "The ship will auto shot.", 0x00ffffff, 3);
    drawString(100, 500, "Press 'enter' to return.", 0x00ffffff, 4);
}

void chooseShip(int arrowPosition) {
    clearScreen();
    drawString(100, 100, "Choosing your ship", 0x00ffffff, 5);
    drawShip(180, 300, 0);
    drawShip(380, 300, 1);
    drawShip(580, 300, 2);
    drawArrow(130 + arrowPosition, 316);
    drawString(100, 500, "Press 'enter' to return", 0x00ffffff, 4);
}

void chooseLevel(int arrowPosition) {
    clearScreen();
    drawBackground();
    drawString(100, 100, "Choose Difficulty Level", 0x00ffffff, 5);
    drawString(180, 300, "Easy", 0x00ffffff, 3);
    drawString(180, 400, "Medium", 0x00ffffff, 3);
    drawString(180, 500, "Hard", 0x00ffffff, 3);
    drawArrow(130, 295 + arrowPosition);
}
