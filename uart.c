/*
*
*   uart.c
*
*
*
*
*
*   @author
*   @date
*/

#include "uart.h"

void uart_init(void){
	SYSCTL_RCGCUART_R |= 0x02;
	SYSCTL_RCGCGPIO_R |= 0x02;

	timer_waitMillis(1);

	//setup GPIO
	GPIO_PORTB_AFSEL_R |= 0x03;
	GPIO_PORTB_PCTL_R &= 0x11;
	GPIO_PORTB_PCTL_R |= 0x11;
	GPIO_PORTB_DEN_R |= 0x03;
	GPIO_PORTB_DIR_R &= 0x11;
	GPIO_PORTB_DIR_R |= 0x11;

	//disable UART
    UART1_CTL_R &= ~0x01;

    //set baud
    //UART1_IBRD_R = 104;
    //UART1_FBRD_R = 11;
    UART1_IBRD_R = 8;
    UART1_FBRD_R = 44;

    //set # data bits, parity, FIFO, clock source
    UART1_LCRH_R = 0x60;
    UART1_CC_R &= ~0x0F;

    //enable UART
    UART1_CTL_R |= 0x300;
    UART1_CTL_R |= 0x01;
}

void uart_sendChar(char data){
    while(UART1_FR_R & 0x20)
        ;

    UART1_DR_R = data;
}

int uart_receive(void){
    char data = 0;

    while(UART1_FR_R & 0x10)
        ;

    data = (char) (UART1_DR_R & 0xFF);

    return data;
}

void uart_sendStr(const char *data) {
    //while not equal to null
    while(*data != '\0')
    {
        uart_sendChar(*data);
        data++;
    }
}
