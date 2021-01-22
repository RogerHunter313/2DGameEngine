#ifndef CONSTANTS_H
#define CONSTANTS_H

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;

const unsigned int FPS = 60;
const unsigned int FRAME_TARGET_TIME = 1000 / FPS;   // for 60fps, one frame should last just .001666 seconds 16.6666 miliseconds.  the 1000 is just conversion to mili

#endif