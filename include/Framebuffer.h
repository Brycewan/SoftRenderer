#pragma once
#include <SDL/SDL.h>

extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;

class Framebuffer {
private:
  uint32_t* frame_buffer;
  int WIDTH;
  int HEIGHT;

public:
  Framebuffer(int width, int height);
  ~Framebuffer();
  void clear();
  Uint32* get_frame_buffer();
  void drawPixel(int x, int y, Uint32 color);
  void drawLineDDA(int x0, int y0, int x1, int y1, Uint32 color);
  void drawLineBresenham(int x0, int y0, int x1, int y1, Uint32 color);
  void draw_rectangle(int x, int y, int width, int height, Uint32 color);
};