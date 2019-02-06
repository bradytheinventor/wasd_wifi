
#include <stdbool.h>
#include "movement.h"
#include "open_interface.h"

//moves the robot 'distance' mm forwards at 'velocity' mm / s
//  if 'respectBumpers' is set, the robot will stop moving if it encounters an obstacle
//  returns the number of millimeters moved
int16_t movement_moveForward(oi_t *sensor_data, uint16_t distance, uint16_t velocity, bool respectBumpers) {
    int16_t distanceTravelled = 0;

    //start the wheels
    oi_setWheels(velocity, velocity);

    //wait until the target is reached
    while(distanceTravelled < distance) {
        oi_update(sensor_data);

        distanceTravelled += sensor_data->distance;

        //stop driving if an obstacle is encountered
        if(respectBumpers && (sensor_data->bumpLeft || sensor_data->bumpRight)) {
            break;
        }
    }

    //stop the wheels and return how far the robot travelled
    oi_setWheels(0, 0);
    return distanceTravelled;
}

//moves the robot 'distance' mm backwards at 'velocity' mm / s
//  if 'respectBumpers' is set, the robot will stop moving if it encounters an obstacle
//  returns the number of millimeters moved
int16_t movement_moveBackward(oi_t *sensor_data, uint16_t distance, uint16_t velocity, bool respectBumpers) {
    int16_t distanceTravelled = 0;

    //start the wheels
    oi_setWheels(-velocity, -velocity);

    //todo use the error between distance and distance travelled
    //wait until the target is reached
    while(distanceTravelled > -distance) {
        oi_update(sensor_data);

        distanceTravelled += sensor_data->distance;

        //stop driving if an obstacle is encountered
        if(respectBumpers && (sensor_data->bumpLeft || sensor_data->bumpRight)) {
            break;
        }
    }

    //stop the wheels and return how far the robot travelled
    oi_setWheels(0, 0);
    return distanceTravelled;
}

//rotates the robot 'degrees' degrees clockwise (right) with a wheel speed of 'velocity' mm / s
//  returns the number of degrees rotated by
int16_t turn_clockwise(oi_t *sensor_data, uint16_t degrees, uint16_t velocity) {
    int16_t degreesRotated = 0;

    //start the wheels
    oi_setWheels(-velocity, velocity);

    //wait until the target is reached
    while(degreesRotated > -degrees) {
        oi_update(sensor_data);

        degreesRotated += sensor_data->angle;
    }

    //stop the wheels and return how far the robot rotated
    oi_setWheels(0, 0);
    return degreesRotated;
}

//rotates the robot 'degrees' degrees counterclockwise (left) with a wheel speed of 'velocity' mm / s
//  returns the number of degrees rotated by
int16_t turn_counter_clockwise(oi_t *sensor_data, uint16_t degrees, uint16_t velocity) {
    int16_t degreesRotated = 0;

    //start the wheels
    oi_setWheels(velocity, -velocity);

    //wait until the target is reached
    while(degreesRotated < degrees) {
        oi_update(sensor_data);

        degreesRotated += sensor_data->angle;
    }

    //stop the wheels and return how far the robot rotated
    oi_setWheels(0, 0);
    return degreesRotated;
}
