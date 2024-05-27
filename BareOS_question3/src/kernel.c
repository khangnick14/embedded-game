
#include "../uart/uart1.h"
#include "./game/game_menu.h"
#include "./game/game_logic.h"
#include "./graphic/framebf.h"

void display_information() {
 uart_puts("\n\n\n"
    "   ___                            _           _                                  _\n"
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
    );
    uart_puts("       Develop by Pham Hoang Thien An - s3818286  and  Nguyen Manh Khang - s3864131\n");
    uart_puts("Welcome to Bare0S!\n");
    uart_puts("Available commands:\n");
    uart_puts("  playgame - Start the game\n");
    uart_puts("  cls      - Clear the screen\n");
    uart_puts("Usage: Type a command and press Enter.\n\n");
}

void main()
{
    // set up serial console
    uart_init();
   
    // Display information
    display_information();

    // Initialize frame buffer
    framebf_init();

    uart_puts("\nBare0S:>");
    // echo everything back
    while(1) {
            // Handle UART input
        cli();
        if (start_game_flag) {
            // Clear the flag
            start_game_flag = 0;

            // Start the game loop
            game_start_menu();
            
            // Print CLI prompt after exiting the game
            uart_puts("\nBare0S:>");
        }
        wait_msec(10);
    }
}