#ifndef _MOVEMENT_H
#define _MOVEMENT_H

#include <stdbool.h>
#include "open_interface.h"

int16_t movement_moveForward(oi_t *sensor_data, uint16_t distance, uint16_t velocity, bool stopForBumpers);
int16_t movement_moveBackward(oi_t *sensor_data, uint16_t distance, uint16_t velocity, bool stopForBumpers);
int16_t turn_clockwise(oi_t *sensor_data, uint16_t degrees, uint16_t velocity);
int16_t turn_counter_clockwise(oi_t *sensor_data, uint16_t degrees, uint16_t velocity);

#endif
