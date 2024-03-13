#ifndef UTIL_H
#define UTIL_H

#include "opengl_headers.hpp"
#include "headers.hpp"

void ResizeFunction(int Width, int Height);

void RenderFunction();

void TimerFunction(int Value);

void IdleFunction();

void KeyboardFunction(unsigned char Key, int X, int Y);

#endif