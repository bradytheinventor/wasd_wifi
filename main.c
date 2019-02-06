
#include <stdbool.h>

#include "timer.h"
#include "uart.h"
#include "lcd.h"
#include "open_interface.h"

#include "driverlib/interrupt.h"

//#define LIN_S 750
//#define ROT_S 250

typedef enum {
    LIN_SLOW = 100,
    LIN_STANDARD = 400,
    LIN_FAST = 750
} lin_speed_t;

typedef enum {
    ROT_SLOW = 100,
    ROT_STANDARD = 250,
    ROT_FAST = 350
} rot_speed_t;

uint8_t isRunning = 1;
char prevCommand = ' ';
lin_speed_t linSpeed = LIN_STANDARD;
rot_speed_t rotSpeed = ROT_STANDARD;

void setLinSpeed(lin_speed_t speed);
void setRotSpeed(rot_speed_t speed);
void updateDriveSpeeds(void);

int main() {
    uart_init();
    lcd_init();

    lcd_printf("I'm alive!");

    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);

    while(isRunning) {
        //wait for uart
        char msg = uart_receive();
        lcd_printf("%c", msg);

        //determine character
        switch(msg) {
        case 'w':
            oi_setWheels(linSpeed, linSpeed);
            prevCommand = 'w';
            break;

        case 's':
            oi_setWheels(-linSpeed, -linSpeed);
            prevCommand = 's';
            break;

        case 'a':
            oi_setWheels(rotSpeed, -rotSpeed);
            prevCommand = 'a';
            break;

        case 'd':
            oi_setWheels(-rotSpeed, rotSpeed);
            prevCommand = 'd';
            break;

        case 'y':
            setLinSpeed(LIN_FAST);
            setRotSpeed(ROT_FAST);
            updateDriveSpeeds();
            break;

        case 'h':
            setLinSpeed(LIN_STANDARD);
            setRotSpeed(ROT_STANDARD);
            updateDriveSpeeds();
            break;

        case 'n':
            setLinSpeed(LIN_SLOW);
            setRotSpeed(ROT_SLOW);
            updateDriveSpeeds();
            break;

        case 'q':
            oi_setWheels(0, 0);
            isRunning = 0;
            break;

        case ' ':
        default:
            oi_setWheels(0, 0);
            prevCommand = ' ';
            break;
        }
    }

    lcd_printf("Done.");

    oi_setWheels(0, 0);
    oi_free(sensor_data);
    return 0;
}

void setLinSpeed(lin_speed_t speed) {
    linSpeed = speed;
}

void setRotSpeed(rot_speed_t speed) {
    rotSpeed = speed;
}

void updateDriveSpeeds(void) {
    //immediately apply changes
    switch(prevCommand) {
    case 'w':
        oi_setWheels(linSpeed, linSpeed);
        break;

    case 's':
        oi_setWheels(-linSpeed, -linSpeed);
        break;

    case 'a':
        oi_setWheels(rotSpeed, -rotSpeed);
        break;

    case 'd':
        oi_setWheels(-rotSpeed, rotSpeed);
        break;

    case ' ':
    default:
        oi_setWheels(0, 0);
        break;
    }
}
