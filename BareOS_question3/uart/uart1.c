#include "uart1.h"

/**
 * Set baud rate and characteristics (115200 8N1) and map to GPIO
 */
void uart_init()
{
    unsigned int r;

    /* initialize UART */
    AUX_ENABLE |= 1;     //enable mini UART (UART1) 
    AUX_MU_CNTL = 0;	 //stop transmitter and receiver
    AUX_MU_LCR  = 3;     //8-bit mode (also enable bit 1 to be used for RPI3)
    AUX_MU_MCR  = 0;	 //clear RTS (request to send)
    AUX_MU_IER  = 0;	 //disable interrupts
    AUX_MU_IIR  = 0xc6;  //enable and clear FIFOs
    AUX_MU_BAUD = 270;   //configure 115200 baud rate [system_clk_freq/(baud_rate*8) - 1]

    /* Note: refer to page 11 of ARM Peripherals guide for baudrate configuration 
    (system_clk_freq is 250MHz by default) */

    /* map UART1 to GPIO pins 14 and 15 */
    r = GPFSEL1;
    r &=  ~( (7 << 12)|(7 << 15) ); //clear bits 17-12 (FSEL15, FSEL14)
    r |= (0b010 << 12)|(0b010 << 15);   //set value 0b010 (select ALT5: TXD1/RXD1)
    GPFSEL1 = r;

	/* enable GPIO 14, 15 */
#ifdef RPI3 //RPI3
	GPPUD = 0;            //No pull up/down control
	//Toogle clock to flush GPIO setup
	r = 150; while(r--) { asm volatile("nop"); } //waiting 150 cycles
	GPPUDCLK0 = (1 << 14)|(1 << 15); //enable clock for GPIO 14, 15
	r = 150; while(r--) { asm volatile("nop"); } //waiting 150 cycles
	GPPUDCLK0 = 0;        // flush GPIO setup

#else //RPI4
	r = GPIO_PUP_PDN_CNTRL_REG0;
	r &= ~((3 << 28) | (3 << 30)); //No resistor is selected for GPIO 14, 15
	GPIO_PUP_PDN_CNTRL_REG0 = r;
#endif

    AUX_MU_CNTL = 3;      //enable transmitter and receiver (Tx, Rx)
}

/**
 * Send a character
 */
void uart_sendc(char c) {
    // wait until transmitter is empty
    do {
    	asm volatile("nop");
    } while ( !(AUX_MU_LSR & 0x20) );

    // write the character to the buffer 
    AUX_MU_IO = c;
}

/**
 * Receive a character
 */
char uart_getc() {
    char c;

    // wait until data is ready (one symbol)
    do {
    	asm volatile("nop");
    } while ( !(AUX_MU_LSR & 0x01) );

    // read it and return
    c = (unsigned char)(AUX_MU_IO);

    // convert carriage return to newline character
    return (c == '\r' ? '\n' : c);
}

/**
 * Display a string
 */
void uart_puts(char *s) {
    while (*s) {
        // convert newline to carriage return + newline
        if (*s == '\n')
            uart_sendc('\r');
        uart_sendc(*s++);
    }
}


/**
* Display a value in hexadecimal format
*/
void uart_hex(unsigned int num) {
	uart_puts("0x");
	for (int pos = 28; pos >= 0; pos = pos - 4) {

		// Get highest 4-bit nibble
		char digit = (num >> pos) & 0xF;

		/* Convert to ASCII code */
		// 0-9 => '0'-'9', 10-15 => 'A'-'F'
		digit += (digit > 9) ? (-10 + 'A') : '0';
		uart_sendc(digit);
	}
}

/*
**
* Display a value in decimal format
*/
void uart_dec(int num)
{
	//A string to store the digit characters
	char str[33] = "";

	//Calculate the number of digits
	int len = 1;
	int temp = num;
	while (temp >= 10){
		len++;
		temp = temp / 10;
	}

	//Store into the string and print out
	for (int i = 0; i < len; i++){
		int digit = num % 10; //get last digit
		num = num / 10; //remove last digit from the number
		str[len - (i + 1)] = digit + '0';
	}
	str[len] = '\0';

	uart_puts(str);
}

//Check if the user has just inputted a new key
unsigned int uart_isReadByteReady(){
    return (AUX_MU_LSR & 0x01);
}

/* New function: Check and return if no new character, don't wait */
unsigned char getUart(){
    unsigned char ch = 0;
    if (uart_isReadByteReady())
        ch = uart_getc();
    return ch;
}

void itoa(int num, char* str) {
    int i = 0;
    int isNegative = 0;

    // Handle 0
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }
    if (num < 0) {
        isNegative = 1;
        num = -num;
    }
    while (num != 0) {
        int rem = num % 10;
        str[i++] = rem + '0';
        num = num / 10;
    }
    if (isNegative)
        str[i++] = '-';

    str[i] = '\0'; // Append null character

    // Reverse the string
    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}


volatile int start_game_flag = 0;
volatile int command_count = 0;

void cli() {
	static char cli_buffer[MAX_CMD_SIZE];
	static int index = 0;
    char count_str[10]; // Buffer to store the string representation of the command count

	//read and send back each char
    if (getUart() != '\n') { 
        char c = uart_getc();
	    uart_sendc(c);
        //put into a buffer until got new line character
	    if (c != '\n') {
            if (c == '\b' && index > 0) {
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
    	} else {
            cli_buffer[index] = '\0';
            command_count ++;
            if (compareStrings(cli_buffer, "playgame")) {
                uart_puts("\nACK: Starting the game\n");
                start_game_flag = 1;

            } else if (compareStrings(cli_buffer, "cls")) {
                uart_puts("\nACK: Clearing the screen\n");
                clearScreen();
            } else {
                uart_puts("\nNAK: Invalid command\n");
            }
            // Log the command counts for debug
            uart_puts("\n[DEBUG]: Number of commands received: ");
            itoa(command_count, count_str);
            uart_puts(count_str);
            uart_puts("\nBare0S:>");
            //Return to command line
            index = 0;
            for (int i = 0; i < 100; i++) {
                cli_buffer[i] = '\0';
            }
        }
	}
}