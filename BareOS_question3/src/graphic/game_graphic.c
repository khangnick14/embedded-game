#include "game_graphic.h"
#include "framebf.h"
#include "../objects/monster.h"
#include "../objects/ship.h"
#include "../objects/gameObject.h"


void drawMonster(int x, int y, int num) {
    const unsigned long* monster = getMonster(num);
    int count = 0;
    int count1 = 0;
    for (int i = 0; i <= (ITEM_DEFAULT_SIZE * ITEM_DEFAULT_SIZE); i++) {
        drawPixelARGB32(x + count, y + count1, monster[i]);
        count++;
        if (count == ITEM_DEFAULT_SIZE) {
            count = 0;
            count1++;
        }
    }
}

void eraseMonster(int x, int y) {
    int count = 0;
    int count1 = 0;
    for (int i = 0; i <= (ITEM_DEFAULT_SIZE * 2); i++) {
        drawPixelARGB32(x + count, y + count1, 0x00000000);
        count++;
        if (count == ITEM_DEFAULT_SIZE) {
            count = 0;
            count1++;
        }
    }
}

void drawShip(int x, int y, int num) {
    const unsigned long* ship = getship(num);
    int count = 0;
    int count1 = 0;
    for (int i = 0; i <= (ITEM_DEFAULT_SIZE * ITEM_DEFAULT_SIZE); i++) {
        drawPixelARGB32(x + count, y + count1, ship[i]);
        count++;
        if (count == ITEM_DEFAULT_SIZE) {
            count = 0;
            count1++;
        }
    }
}

void clearShip(int x, int y) {
    int count = 0;
    int count1 = 0;
    for (int i = 1; i <= (ITEM_DEFAULT_SIZE * 10); i++) {
        drawPixelARGB32(x + count, y + count1, 0x00000000);
        count++;
        if (count == 10) {
            count = 0;
            count1++;
        }
    }
}

void drawArrow(int x, int y) {
    const unsigned long* ship = getArrow();
    int count = 0;
    int count1 = 0;
    for (int i = 0; i <= (ITEM_DEFAULT_SIZE * ITEM_DEFAULT_SIZE / 4); i++) {
        drawPixelARGB32(x + count, y + count1, ship[i]);
        count++;
        if (count == (ITEM_DEFAULT_SIZE / 2 )) {
            count = 0;
            count1++;
        }
    }
}

void drawHeart(int x, int y) {
    const unsigned long* heart = getHeart();
    int count = 0;
    int count1 = 0;
    for (int i = 0; i <= (ITEM_DEFAULT_SIZE * ITEM_DEFAULT_SIZE / 4); i++) {
        drawPixelARGB32(x + count, y + count1, heart[i]);
        count++;
        if (count == (ITEM_DEFAULT_SIZE / 2)) {
            count = 0;
            count1++;
        }
    }
}


void drawAlien(int x, int y) {
    const unsigned long* alien = getAlien();
    int count = 0;
    int count1 = 0;
    for (int i = 0; i <= (ITEM_DEFAULT_SIZE * ITEM_DEFAULT_SIZE / 4); i++) {
        drawPixelARGB32(x + count, y + count1, alien[i]);
        count++;
        if (count == (ITEM_DEFAULT_SIZE / 2)) {
            count = 0;
            count1++;
        }
    }
}

void drawBullet(int x, int y) {
    const unsigned long* bullet = getBullet();
    int count = 0;
    int count1 = 0;
    for (int i = 0; i <= (BULLET_DEFAULT_SIZE * BULLET_DEFAULT_SIZE); i++) {
        drawPixelARGB32(x + count, y + count1, bullet[i]);
        count++;
        if (count == BULLET_DEFAULT_SIZE) {
            count = 0;
            count1++;
        }
    }
}


void display_monster_alive(int num) {
    int ox = 20;
    int oy = 50;
    int y = num / 5;
    int x = num % 5;
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < 5; j++) {
            drawAlien(ox, oy);
            ox = ox + 50;
        }
        oy = oy + 40;
        ox = 20;
    }
    for (int i = 0; i < x; i++) {
        drawAlien(ox, oy);
        ox = ox + 50;
    }
}

void display_heart_left(int num) {
    int ox = 20;
    for (int i = 0; i < num; i++) {
        drawHeart(ox, 700);
        ox = ox + 50;
    }
}