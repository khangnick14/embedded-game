
#include "../uart/uart1.h"
#include "mbox.h"
#include "framebf.h"
#include "utils.h"
#include "background.h"
#include "monster.h"
#include "ship.h"
#include "gameObject.h"

#define SIZE 64
#define MAX_CMD_SIZE 100
#define VIRTUAL_SCREEN_WIDTH 1024
#define VIRTUAL_SCREEN_HEIGHT 768
#define A 1664525
#define C 1013904223
#define M 4294967296 // 2^32


void clearScreen() {
    int count = 0;
    int count1 = 0;
    for(int i = 0; i < VIRTUAL_SCREEN_WIDTH * VIRTUAL_SCREEN_HEIGHT; i++){
        drawPixelARGB32(count, count1, 0x00000000);
        if(count < VIRTUAL_SCREEN_WIDTH - 1) {
            count++;
        } else {
            count = 0;
            count1++;
        }

    }
}


int compareStrings(const char *str1, const char *str2) {
    for (int i = 0; str1[i] != '\0' || str2[i] != '\0'; i++) {
        if (str1[i] != str2[i]) {
            return 0; // Strings are different
        }
    }
    return 1; // Strings are identical
}

void drawMonster(int x, int y, int num) {
    const unsigned long* monster = getMonster(num);
    int count = 0;
    int count1 = 0;
    for (int i = 0; i <= (SIZE * SIZE); i++) {
        drawPixelARGB32(x + count, y + count1, monster[i]);
        count++;
        if (count == 64) {
            count = 0;
            count1++;
        }
    }
}

void ereaseMonster(int x, int y) {
    int count = 0;
    int count1 = 0;
    for (int i = 0; i <= (SIZE * 2); i++) {
        drawPixelARGB32(x + count, y + count1, 0x00000000);
        count++;
        if (count == 64) {
            count = 0;
            count1++;
        }
    }
}

void erease64x64(int x, int y) {
    int count = 0;
    int count1 = 0;
    for (int i = 0; i <= (SIZE * SIZE); i++) {
        drawPixelARGB32(x + count, y + count1, 0x00000000);
        count++;
        if (count == 64) {
            count = 0;
            count1++;
        }
    }
}

void erease24x24(int x, int y) {
    int count = 0;
    int count1 = 0;
    for (int i = 0; i <= (24 * 24); i++) {
        drawPixelARGB32(x + count, y + count1, 0x00000000);
        count++;
        if (count == 24) {
            count = 0;
            count1++;
        }
    }
}

void drawShip(int x, int y, int num) {
    const unsigned long* ship = getship(num);
    int count = 0;
    int count1 = 0;
    for (int i = 0; i <= (SIZE * SIZE); i++) {
        drawPixelARGB32(x + count, y + count1, ship[i]);
        count++;
        if (count == 64) {
            count = 0;
            count1++;
        }
    }
}

void drawBackground() {
    const unsigned long* back = getBackground();
    int count = 0;
    int count1 = 0;
    for (int i = 0; i <= (VIRTUAL_SCREEN_HEIGHT * VIRTUAL_SCREEN_WIDTH); i++) {
        drawPixelARGB32(count, count1, back[i]);
        count++;
        if (count == VIRTUAL_SCREEN_WIDTH) {
            count = 0;
            count1++;
        }
    }
}

void drawArrow(int x, int y) {
    const unsigned long* ship = getArrow();
    int count = 0;
    int count1 = 0;
    for (int i = 0; i <= (SIZE * SIZE / 4); i++) {
        drawPixelARGB32(x + count, y + count1, ship[i]);
        count++;
        if (count == 32) {
            count = 0;
            count1++;
        }
    }
}

void drawHeart(int x, int y) {
    const unsigned long* heart = getHeart();
    int count = 0;
    int count1 = 0;
    for (int i = 0; i <= (SIZE * SIZE / 4); i++) {
        drawPixelARGB32(x + count, y + count1, heart[i]);
        count++;
        if (count == 32) {
            count = 0;
            count1++;
        }
    }
}

void drawAlien(int x, int y) {
    const unsigned long* alien = getAlien();
    int count = 0;
    int count1 = 0;
    for (int i = 0; i <= (SIZE * SIZE / 4); i++) {
        drawPixelARGB32(x + count, y + count1, alien[i]);
        count++;
        if (count == 32) {
            count = 0;
            count1++;
        }
    }
}

void drawBullet(int x, int y) {
    const unsigned long* bullet = getBullet();
    int count = 0;
    int count1 = 0;
    for (int i = 0; i <= (24 * 24); i++) {
        drawPixelARGB32(x + count, y + count1, bullet[i]);
        count++;
        if (count == 24) {
            count = 0;
            count1++;
        }
    }
}

void ereaseBullet(int x, int y){
    int count = 0;
    int count1 = 0;
    for (int i = 0; i <= (24 * 12); i++) {
        drawPixelARGB32(x + count, y + count1, 0x00000000);
        count++;
        if (count == 24) {
            count = 0;
            count1++;
        }
    }
}

void home(int num) {
    drawBackground();
    drawString(100, 100, "Battle Ship Adventure", 0x00ffffff, 5);
    drawString(180, 300, "Start", 0x00ffffff, 3);
    drawString(180, 400, "How to play", 0x00ffffff, 3);
    drawString(180, 500, "Choose ship", 0x00ffffff, 3);
    drawArrow(130, 295 + num);
}

void howtoplay() {
    clearScreen();
    drawString(100, 100, "How to play", 0x00ffffff, 6);
    drawString(100, 200, "Press 'a' and the ship will go left.", 0x00ffffff, 3);
    drawString(100, 250, "Press 'd' and the ship will go right.", 0x00ffffff, 3);
    drawString(100, 300, "The ship will auto shot.", 0x00ffffff, 3);
    drawString(100, 500, "Press 'enter' to return.", 0x00ffffff, 4);
}

void chooseShip(int num) {
    clearScreen();
    drawString(100, 100, "Choosing your ship", 0x00ffffff, 5);
    drawShip(180, 300, 0);
    drawShip(380, 300, 1);
    drawShip(580, 300, 2);
    drawArrow(130 + num, 316);
    drawString(100, 500, "Press 'enter' to return", 0x00ffffff, 4);
}

void clearShip(int x, int y) {
    int count = 0;
    int count1 = 0;
    for (int i = 1; i <= (SIZE * 10); i++) {
        drawPixelARGB32(x + count, y + count1, 0x00000000);
        count++;
        if (count == 10) {
            count = 0;
            count1++;
        }
    }
}

void drawline(){
    int count = 290;
    int count1 = 0;
    for (int i = 0; i <= (VIRTUAL_SCREEN_HEIGHT * 10); i++) {
        drawPixelARGB32(count, count1, 0x00ffffff);
        count++;
        if (count == 300) {
            count = 290;
            count1++;
        }
    }
}

void showalien(int num) {
    int ox2 = 20;
    int oy = 50;
    int y = num / 5;
    int x = num % 5;
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < 5; j++) {
            drawAlien(ox2, oy);
            ox2 = ox2 + 50;
        }
        oy = oy + 40;
        ox2 = 20;
    }
    for (int i = 0; i < x; i++) {
        drawAlien(ox2, oy);
        ox2 = ox2 + 50;
    }
}

void showheart(int num) {
    int ox = 20;
    for (int i = 0; i < num; i++) {
        drawHeart(ox, 700);
        ox = ox + 50;
    }
}

int randome(int min, int max){
    static unsigned int lcg_state = 1;
    lcg_state = (A * lcg_state + C) % M;
    return lcg_state % (max - min + 1) + min;
}

void erasebysize(int x, int y, int wight, int height) {
    int count = 0;
    int count1 = 0;
    for (int i = 0; i < (wight * height); i++) {
        drawPixelARGB32(x + count, y + count1, 0x00000000);
        count++;
        if (count == wight) {
            count = 0;
            count1++;
        }
    }
}

void playgame(int num, int heart, int monsters) {
    clearScreen();

    drawline();   
    showalien(monsters);
    showheart(heart);

    int ship = 0;
    if (num == 0) {
        ship = 0;
    } else if (num == 200) {
        ship = 1;
    } else {
        ship = 2;
    }

    int ox1 = 630;
    int oy1 = 650;

    unsigned char c = 0;
    int fy[3] = {600,600,600};
    int fx[3] = {630,630,630};
    int count[3] = {0,0,0};

    int mons[monsters][3];
    for (int i = 0; i < monsters; i++) {
        mons[i][0] = randome(300,1024-74);
        mons[i][1] = 0;
        mons[i][2] = randome(0,6);
    }
    int count1[monsters];
    for (int i = 0; i < monsters; i++) {
        count1[i] = 0;
    }
    int status3 = 0;
    int status[monsters];
    int status1[3] = {0,0,0};
    for (int i = 0; i < monsters; i++) {
        status[i] = 0;
    }
    int count3[monsters];
    for(int i = 0; i < monsters; i++) {
        count3[i] = i * randome(30, 45);
    }
    int lives = monsters;
    int lifes = heart;

    while (1)
    {
        drawShip(ox1, oy1, ship);

        for (int i = 0; i < monsters; i++) {
            if (count1[i] >= count3[i] && status[i] == 0) {
                drawMonster(mons[i][0], mons[i][1], mons[i][2]);
                erasebysize(mons[i][0], mons[i][1] - 2, 64, 2);
                mons[i][1] = mons[i][1] + 2;
            }
            if (mons[i][1] > 536 && status[i] == 0) {
                status[i] = 3;
            }
        }

        for (int i = 0; i < 3; i++) {
            if (count[i] >= i*38) {
                if (status1[i] == 0) {
                    drawBullet(fx[i] + 20, fy[i]);
                    erasebysize(fx[i] + 20, fy[i] + 24, 24, 12);
                }
                if (fy[i] > -100) {
                    fy[i] = fy[i] - 12;
                } else {
                    fy[i] = 600;
                    status1[i] = 0;
                }
            }
        }
        wait_msec(40000);

        for (int i = 0; i < monsters; i++) {
            if (status[i] == 1) {
                erease64x64(mons[i][0],mons[i][1] - 2);
                erasebysize(mons[i][0], mons[i][1] - 2 - 2, 64, 2);
                status[i] = 2;
                lives--;
                status3 = 1;
            }
            else if (status[i] == 3) {
                erease64x64(mons[i][0],mons[i][1] - 2);
                erasebysize(mons[i][0], mons[i][1] - 2 - 2, 64, 2);
                status[i] = 2;
                lifes--;
                lives--;
                status3 = 1;
            }
        }
        for (int i = 0; i < 3; i++){
            if (status1[i] == 1) {
                erease24x24(fx[i] + 20, fy[i] + 12);
                erasebysize(fx[i] + 20, fy[i] + 24 + 12, 24, 12);
                status1[i] = 2;
            }
        }

        for (int i = 0; i < 3; i++){
            for (int j = 0; j < monsters; j++){
                if (mons[j][1] + 64 > fy[i] && mons[j][1] + 64 - 16 < fy[i] && mons[j][1] > 30) {
                    if (fx[i] >= mons[j][0] - 16 - 20 && fx[i] <= mons[j][0] + 64 - 8 - 20 && status1[i] != 2 && status[j] != 2) {
                        status[j] = 1;
                        status1[i] = 1;
                    }
                }
            }
        }

        if (c = getUart()) {
            if (c == 'a') {
                if (ox1 > 300) {
                    ox1 = ox1 - 10;
                }
                drawShip(ox1, oy1, ship);
                clearShip(ox1 + 64, oy1);
            } else if (c == 'd') {
                if (ox1 < 1024 - 74) {
                    ox1 = ox1 + 10;
                }
                drawShip(ox1, oy1, ship);
                clearShip(ox1 - 10, oy1);
            }
        }
        for (int i = 0; i < 3; i++){
            if (fy[i] < -30) {
                fx[i] = ox1;
            }
        }
        count[0]++;
        count[1]++;
        count[2]++;
        for (int i = 0; i < monsters; i++) {
            count1[i]++;
        }
        if (status3) {
            erasebysize(0,0,300,VIRTUAL_SCREEN_HEIGHT);
            status3 = 0;
        }
        showalien(lives);
        showheart(lifes);
        drawline();
        
        if (lifes == 0 || lives == 0) {
            break;
        }
    }
    
    if (lives == 0) {
        drawString(450, 200, "You won!!", 0x00ffffff, 7);
        drawString(400, 500, "Press any key to return!!", 0x00ffffff, 3);
    }
    if (lifes == 0) {
        drawString(450, 200, "GameOver!!", 0x00ffffff, 7);
        drawString(400, 500, "Press any key to return!!", 0x00ffffff, 3);
    }
    while(!(c = getUart()));
}

void working(){
    static int count = 0;
    static int count1 = 0;

    while (1)
    {
        home(count);
        char c = uart_getc();

        while (1)
        {
            if (c == 's') {
                count = (count + 100) % 300;
                home(count);
                c = uart_getc();
            }

            if (c == 'w') {
                count = (count - 100) % 300;
                if (count < 0) {
                    count = 200;
                }
                home(count);
                c = uart_getc();
            }

            if (c == '\n'){ 
                break;
            }
        }

        if (count == 0) {
            playgame(count1, 5, 34);
        } else if (count == 100){
            howtoplay();
            c= uart_getc();
            while (1)
            {
                if (c == '\n') {
                    break;
                }
            }
            

        } else if (count == 200){
            chooseShip(count1);
            c = uart_getc();
            while (1) {
                if (c == 'd') {
                    count1 = (count1 + 200) % 600;
                    chooseShip(count1);
                    c = uart_getc();
                }

                if (c == 'a') {
                    count1 = (count1 - 200) % 600;
                    if (count1 < 0) {
                        count1 = 400;
                    }
                    chooseShip(count1);
                    c = uart_getc();
                }
                if (c == '\n'){ 
                    break;
                }
            }
        }
    }
}

void cli()
{
	static char cli_buffer[MAX_CMD_SIZE];
	static int index = 0;

	//read and send back each char
	char c = uart_getc();
	uart_sendc(c);

	//put into a buffer until got new line character
	if (c != '\n'){
        if (c == '\b' && index > 0){
            uart_sendc(' ');
            uart_sendc('\b');
            cli_buffer[index - 1] = ' ';
            index--;
        } else if (c != '\b'){
            cli_buffer[index] = c; //Store into the buffer
		    index++;
        } else {
            uart_sendc('>');
        }
		

	} else if (c == '\n'){
		cli_buffer[index] = '\0';

		
		//uart_puts(cli_buffer); uart_puts("\n");
        //uart_puts("BareOS:>");
        
		/* Compare with supported commands and execute
		* ........................................... */

        if (compareStrings(cli_buffer, "playgame")) {
            working();
        } else if (compareStrings(cli_buffer, "cls")) {
            clearScreen();
        }

        uart_puts("Bare0S:>");
        //Return to command line
        index = 0;
        for (int i = 0; i < 100; i++) {
                cli_buffer[i] = '\0';
        }
	}
}


void main()
{
    // set up serial console
    uart_init();
    // say hello
    uart_puts("\n\n\n"
    "   ___                           _           _                                  _\n"
    "  / _ \\_ __ ___  _   _ _ __     /_\\  ___ ___(_) __ _ _ __  _ __ ___   ___ _ __ | |_\n" 
    " / /_\\/ '__/ _ \\| | | | '_ \\   //_\\\\/ __/ __| |/ _` | '_ \\| '_ ` _ \\ / _ \\ '_ \\| __|\n"
    "/ /_\\\\| | | (_) | |_| | |_) | /  _  \\__ \\__ \\ | (_| | | | | | | | | |  __/ | | | |_\n"
    "\\____/|_|  \\___/ \\__,_| .__/  \\_/ \\_/___/___/_|\\__, |_| |_|_| |_| |_|\\___|_| |_|\\__|\n"
    "                      |_|                      |___/\n\n"                                
    "   ____                 _   _               _____\n"                                  
    "  /___ \\_   _  ___  ___| |_(_) ___  _ __   |___ /\n"                                   
    " //  / / | | |/ _ \\/ __| __| |/ _ \\| '_ \\    |_ \\\n"                                 
    "/ \\_/ /| |_| |  __/\\__ \\ |_| | (_) | | | |  ___) |\n"                             
    "\\___,_\\ \\__,_|\\___||___/\\__|_|\\___/|_| |_| |____/\n\n"                                  
    "       Develop by Pham Hoang Thien An - s3818286  and  Nguyen Manh Khang - s3864131"
    );
    // Initialize frame buffer
    framebf_init();
    uart_puts("\nBare0S:>");
    // echo everything back
    while(1) {
        cli();
    }
}