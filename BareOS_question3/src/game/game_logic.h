/* USe LCG constant
A: multiplier
C: increment
M: modulus
*/
#define A 1664525
#define C 1013904223
#define M 4294967296 // 2^32
#define SHIP_DEFAULT_OX 630
#define SHIP_DEFAULT_OY 650

#define EASY_SPAWN_RATE 45 
#define MEDIUM_SPAWN_RATE 30 
#define HARD_SPAWN_RATE 20 

int randomize(int min, int max);
void navigate_home_menu(int *menu_selected_option, char *user_input);
void execute_home_option(int menu_selected_option, int *ship_selected_option, char *user_input, int *level_selected_option);
void navigate_ship_selection(int *ship_selected_option, char *user_input);
void display_how_to_play(char *user_input);
void gameloop();
void spawnMonsters(int monsters, int mons[][3], int count1[], int count3[], int status[], int level);
void shootBullets(int fx[], int fy[], int count[], int status1[]);
void checkCollisions(int monsters, int mons[][3], int status[], int fx[], int fy[], int status1[]);
void eraseEntities(int monsters, int mons[][3], int status[], int status1[], int fy[], int fx[], int *status3, int *lives, int *lifes);
void handleInput(int *ox1, int oy1, int ship);
void updateBulletPositions(int fx[], int fy[], int ox1);
void startGame(int num, int heart, int monsters, int level);