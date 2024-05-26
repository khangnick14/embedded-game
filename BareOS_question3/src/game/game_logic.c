#include "game_logic.h"
#include "game_menu.h"
#include "../graphic/framebf.h"
#include "../utils/utils.h"
#include "../graphic/game_graphic.h"
#include "../../uart/uart1.h"



void navigate_home_menu(int *menu_selected_option, char *user_input) {
    while (1) {
        switch (*user_input) {
            case 's':
                *menu_selected_option = (*menu_selected_option + 100) % 300;
                home(*menu_selected_option);
                *user_input = uart_getc();
                break;
            case 'w': 
                *menu_selected_option = (*menu_selected_option - 100) % 300;
                if (*menu_selected_option < 0) {
                    *menu_selected_option = 200;
                }
                home(*menu_selected_option);
                *user_input = uart_getc();
                break;
            case '\n':
                return;
            default:
                *user_input = uart_getc();
                break;
        }
    }
}

void navigate_level_selection(int *level_selected_option, char *user_input) {
    while (1) {
        chooseLevel(*level_selected_option);
        *user_input = uart_getc();
        switch (*user_input) {
            case 's':
                *level_selected_option = (*level_selected_option + 100) % 300;
                break;
            case 'w': 
                *level_selected_option = (*level_selected_option - 100) % 300;
                if (*level_selected_option < 0) {
                    *level_selected_option = 200;
                }
                break;
            case '\n':
                return;
            default:
                break;
        }
    }
}

void execute_home_option(int menu_selected_option, int *ship_selected_option, char *user_input, int *level_selected_option) {
    if (menu_selected_option == 0) {
        *level_selected_option = 0; // Reset level selected option
        navigate_level_selection(level_selected_option, user_input); // Navigate level selection screen
        startGame(*ship_selected_option, 5, 34, *level_selected_option / 100); // Start the game with selected level
    } else if (menu_selected_option == 100) {
        display_how_to_play(user_input);
    } else if (menu_selected_option == 200) {
        navigate_ship_selection(ship_selected_option, user_input);
    }
}

void navigate_ship_selection(int *ship_selected_option, char *user_input) {
    while (1) {
        chooseShip(*ship_selected_option);
        *user_input = uart_getc();
        switch (*user_input) {
            case 'd':
                *ship_selected_option = (*ship_selected_option + 200) % 600;
                break;
            case 'a':
                *ship_selected_option = (*ship_selected_option - 200) % 600;
                if (*ship_selected_option < 0) {
                    *ship_selected_option = 400;
                }
                break;
            case '\n':
                return;
            default:
                break;
        }
    }
}

void display_how_to_play(char *user_input) {
    while (1) {
        howtoplay();
        *user_input = uart_getc();
        if (*user_input == '\n') {
            return;
        }
    }
}

void gameloop(){
    static int menu_selected_option = 0;
    static int ship_selected_option = 0;
    static int level_selected_option = 0;

    while (1)
    {
        home(menu_selected_option);
        char user_input = uart_getc();

        // Display the home menu + arrow position
        navigate_home_menu(&menu_selected_option, &user_input);
        execute_home_option(menu_selected_option, &ship_selected_option, &user_input, &level_selected_option);
        menu_selected_option = 0; // Reset menu selected option
    }
}


int randomize(int min, int max){
    static unsigned int lcg_state = 1;
    lcg_state = (A * lcg_state + C) % M;
    return (lcg_state % (max - min + 1)) + min;
}

void spawnMonsters(int monsters, int monster_details[][3], int moveCount[], int moveThreshold[], int monster_status[], int level) {
    for (int i = 0; i < monsters; i++) {
        int spawnRate = 0;
        int descentSpeed = 1; // Default descent speed
        switch (level) {
            case 0: // Easy
                spawnRate = i * randomize(80, 100);
                break;
            case 1: // Medium
                spawnRate = i * randomize(60, 80);
                descentSpeed = 3;
                break;
            case 2: // Hard
                spawnRate = i * randomize(50, 60);
                descentSpeed = 4;
                break;
            default:
                break;
        }
        // Check if it's time for this monster to move and it is still active
        if (moveCount[i] >= spawnRate && monster_status[i] == 0) {
            // Draw the monster
            drawMonster(monster_details[i][0], monster_details[i][1], monster_details[i][2]);
            // Erase the screen when the monster moves down
            eraseBySize(monster_details[i][0], monster_details[i][1] - descentSpeed, 64, descentSpeed);
            // Move the monster down
            monster_details[i][1] += descentSpeed;
        }
        if (monster_details[i][1] > 536 && monster_status[i] == 0) {
            monster_status[i] = 3;
        }        
    }
}

void shootBullets(int fx[], int fy[], int bulletCooldowns[], int bullet_status[]) {
    for (int i = 0; i < 3; i++) {
        if (bulletCooldowns[i] >= i * 38) {
            if (bullet_status[i] == 0) {
                drawBullet(fx[i] + 20, fy[i]);
                eraseBySize(fx[i] + 20, fy[i] + 24, 24, 12);
            }
            if (fy[i] > -100) {
                fy[i] -= 12;
            } else {
                fy[i] = 600;
                bullet_status[i] = 0;
            }
        }
    }
}

void checkCollisions(int monsters, int monster_details[][3], int monster_status[], int fx[], int fy[], int bullet_status[]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < monsters; j++) {
            if (monster_details[j][1] + 64 > fy[i] && monster_details[j][1] + 64 - 16 < fy[i] && monster_details[j][1] > 30) {
                if (fx[i] >= monster_details[j][0] - 16 - 20 && fx[i] <= monster_details[j][0] + 64 - 8 - 20 && bullet_status[i] != 2 && monster_status[j] != 2) {
                    monster_status[j] = 1;
                    bullet_status[i] = 1;
                }
            }
        }
    }
}

void eraseEntities(int monsters, int monster_details[][3], int monster_status[], int bullet_status[], int fy[], int fx[], int *shouldUpdateInterface, int *num_monster_alive, int *num_heart_left) {
    for (int i = 0; i < monsters; i++) {
        if (monster_status[i] == 1) { // Monster was hit by a bullet
            erease64x64(monster_details[i][0], monster_details[i][1] - 2);
            eraseBySize(monster_details[i][0], monster_details[i][1] - 4, 64, 2);
            monster_status[i] = 2; // Set to erased state
            (*num_monster_alive)--;
            *shouldUpdateInterface  = 1;
        } else if (monster_status[i] == 3) { // Monster reached the bottom
            erease64x64(monster_details[i][0], monster_details[i][1] - 2);
            eraseBySize(monster_details[i][0], monster_details[i][1] - 4, 64, 2);
            monster_status[i] = 2; // Set to erased state
            (*num_heart_left)--;
            (*num_monster_alive)--;
            *shouldUpdateInterface  = 1;
        }
    }

    for (int i = 0; i < 3; i++) {
        if (bullet_status[i] == 1) { // Bullet hit a monster
            erease24x24(fx[i] + 20, fy[i] + 12);
            eraseBySize(fx[i] + 20, fy[i] + 24 + 12, 24, 12);
            bullet_status[i] = 2; // Set to erased state
        }
    }
}

void handleInput(int *ox, int oy, int ship) {
    unsigned char c = getUart();
    if (c == 'a' && *ox > 300) {
        *ox -= 10;
        drawShip(*ox, oy, ship);
        clearShip(*ox + 64, oy);
    } else if (c == 'd' && *ox < 1024 - 74) {
        *ox += 10;
        drawShip(*ox, oy, ship);
        clearShip(*ox - 10, oy);
    }
}

void updateBulletPositions(int fx[], int fy[], int ox) {
    for (int i = 0; i < 3; i++) {
        if (fy[i] < -30) {
            fx[i] = ox;
        }
    }
}

void startGame(int num, int heart, int monsters, int level) {
    clearScreen();  // Clear screen first

    // Left sections: show number of aliens and current hearts
    drawline();   
    showalien(monsters);
    showheart(heart);

    int ship = (num == 0) ? 0 : (num == 200) ? 1 : 2;
    int ox = 630, oy = 650;
    int fx[3] = {630, 630, 630}, fy[3] = {600, 600, 600};
    
    // Store monster details: ox, oy, monster img
    int monster_details[monsters][3];
    
    // Store count to define when a monster is spawned
    int moveCount[monsters]; 
    int moveThreshold[monsters];

    /* Store the current monster status
    0: Active
    1: Hit my bullet
    2: Erased
    3: Reached Bottom
    */
    int monster_status[monsters];

    /* Store the bullet status
    0: Active - ready the shoot
    1: Hit my monsters
    2: Erased
    */
    int bullet_status[3] = {0, 0, 0};
    
    /* Store the bullet cooldown */
    int bulletCooldowns[3] = {0,0,0};
   
    int num_monster_alive = monsters, num_heart_left = heart, shouldUpdateInterface  = 0;

    for (int i = 0; i < monsters; i++) {
        // Random a monster details
        // Random the x coordinate
        monster_details[i][0] = randomize(300, 1024 - 74);
        // y = 0
        monster_details[i][1] = 0;
        // random monster image
        monster_details[i][2] = randomize(0, 6);

        moveCount[i] = 0;
        monster_status[i] = 0;

        // random a time when monster is spawned
        moveThreshold[i] = i * randomize(30, 45);
    }

    while (num_heart_left > 0 && num_monster_alive > 0) {
        drawShip(ox, oy, ship);

        spawnMonsters(monsters, monster_details, moveCount, moveThreshold, monster_status, level);
        shootBullets(fx, fy, bulletCooldowns, bullet_status);

        wait_msec(40000);
        eraseEntities(monsters, monster_details, monster_status, bullet_status, fy, fx, &shouldUpdateInterface, &num_monster_alive, &num_heart_left);

        checkCollisions(monsters, monster_details, monster_status, fx, fy, bullet_status);
        handleInput(&ox, oy, ship);
        updateBulletPositions(fx, fy, ox);

        bulletCooldowns[0]++;
        bulletCooldowns[1]++;
        bulletCooldowns[2]++;
        for (int i = 0; i < monsters; i++) {
            moveCount[i]++;
        }

        if (shouldUpdateInterface) {
            eraseBySize(0, 0, 300, VIRTUAL_SCREEN_HEIGHT);
            shouldUpdateInterface = 0;
        }

        showalien(num_monster_alive);
        showheart(num_heart_left);
        drawline();
    }

    // Display end message
    if (num_monster_alive == 0) {
        drawString(450, 200, "You won!!", 0x00ffffff, 7);
    } else if (num_heart_left == 0) {
        drawString(450, 200, "GameOver!!", 0x00ffffff, 7);
    }
    drawString(400, 500, "Press any key to return!!", 0x00ffffff, 3);
    while (uart_getc() != '\n');
}