
#include "../uart/uart1.h"
#include "./game/game_menu.h"
#include "./game/game_logic.h"

#define MAX_CMD_SIZE 100


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
            game_runner();
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