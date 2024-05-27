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
void navigate_level_selection(int *level_selected_option, char *user_input);
void execute_home_option(int menu_selected_option, int *ship_selected_option, char *user_input, int *level_selected_option);
void navigate_ship_selection(int *ship_selected_option, char *user_input);
void display_how_to_play(char *user_input);
void game_start_menu();
int randomize(int min, int max);
void spawnMonsters(int monsters, int monster_details[][3], int moveCount[], int moveThreshold[], int monster_status[], int level);
void shootBullets(int fx[], int fy[], int bulletCooldowns[], int bullet_status[]);
void checkCollisions(int monsters, int monster_details[][3], int monster_status[], int fx[], int fy[], int bullet_status[]);
void eraseEntities(int monsters, int monster_details[][3], int monster_status[], int bullet_status[], int fy[], int fx[], int *shouldUpdateInterface, int *num_monster_alive, int *num_heart_left);
void handleInput(int *ox, int oy, int ship);
void updateBulletPositions(int fx[], int fy[], int ox);
void game_loop(int num, int heart, int monsters, int level);
