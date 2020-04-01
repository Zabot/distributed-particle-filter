#include "simulate/sensors.h"

int positionValid = 0;
vector3f currentPosition;

int sensePosition(vector3f* position) {
  *position = currentPosition;
  return positionValid;
}


void set_position(const vector3f* position) {
  currentPosition = *position;
  positionValid = 1;
}

void clear_position() {
  positionValid = 0;
}

