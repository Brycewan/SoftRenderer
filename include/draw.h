#pragma once
#include <SDL/SDL.h>

extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;

void draw_pixel(Uint32* frame_buffer, int x, int y, Uint32 color);

void draw_rectangle(Uint32* frame_buffer, int x, int y, int width, int height, Uint32 color);

void DDA_line(Uint32* frame_buffer, int x0, int y0, int x1, int y1, Uint32 color);

void Bresenham_line(Uint32* frame_buffer, int x0, int y0, int x1, int y1, Uint32 color);

void draw_gradient_colour_backgroud(int& WINDOW_WIDTH, int& WINDOW_HEIGHT, Uint32* frame_buffer);