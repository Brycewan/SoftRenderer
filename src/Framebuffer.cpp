#include "Framebuffer.h"

Framebuffer::Framebuffer(int width, int height) {
  WIDTH = width;
  HEIGHT = height;
  frame_buffer = new Uint32[width * height];
}

Framebuffer::~Framebuffer() {
  delete[] frame_buffer;
}

void Framebuffer::clear() {
  for (int i = 0; i < WIDTH * HEIGHT; ++i) {
    frame_buffer[i] = 0;
  }
}

Uint32* Framebuffer::get_frame_buffer() {
  return frame_buffer;
}

void Framebuffer::drawPixel(int x, int y, Uint32 color) {
  if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
    frame_buffer[y * WIDTH + x] = color;
  }
}

void Framebuffer::draw_rectangle(int x, int y, int width, int height, Uint32 color) {
  int start_x = x - width / 2;
  int start_y = y - height / 2;
  for (int i = start_x; i < start_x + width; i++) {
    for (int j = start_y; j < start_y + height; j++) {
      drawPixel(i, j, color);
    }
  }
}

void Framebuffer::drawLineDDA(int x0, int y0, int x1, int y1, Uint32 color) {
  int dx = x1 - x0;
  int dy = y1 - y0;
  
  double length = abs(dx) >= abs(dy) ? abs(dx) : abs(dy);
  
  double x_inc = dx / length; 
  double y_inc = dy / length;
  
  double xi = x0;
  double yi = y0;

  for (int i = 0; i < length; i++) {
    drawPixel(round(xi), round(yi), color);
    xi += x_inc;
    yi += y_inc;
  }
}

void Framebuffer::drawLineBresenham(int x0, int y0, int x1, int y1, Uint32 color) {
  int dx = abs(x1 - x0); // Calculate the absolute distance in the x direction
  int dy = abs(y1 - y0); // Calculate the absolute distance in the y direction
  int sx = x0 < x1 ? 1 : -1; // Determine the step direction in the x-axis
  int sy = y0 < y1 ? 1 : -1; // Determine the step direction in the y-axis
  int err = dx - dy; // Initialize the error term

  while (true) {
    drawPixel(x0, y0, color); // Draw the pixel at the current point
    if (x0 == x1 && y0 == y1) break; // If the end point is reached, exit the loop
    int e2 = err * 2; // Calculate the doubled error term
    if (e2 > -dy) { // Check if the error is greater than -dy (2dx - 2dy > -dy  2dx > dy)
      err -= dy; // Adjust the error
      x0 += sx; // Move to the next pixel in the x direction
    }
    if (e2 < dx) { // Check if the error is less than dx (2dx - 2dy < dx  dx < 2dy)
      err += dx; // Adjust the error
      y0 += sy; // Move to the next pixel in the y direction
    }
  }
}


//void draw_gradient_colour_backgroud(int& WINDOW_WIDTH, int& WINDOW_HEIGHT, Uint32* frame_buffer) {
//  for (int y = 0; y < WINDOW_HEIGHT; ++y) {
//    for (int x = 0; x < WINDOW_WIDTH; ++x) {
//      Uint8 r = (Uint8)(x * 255 / WINDOW_WIDTH);
//      Uint8 g = (Uint8)(y * 255 / WINDOW_HEIGHT);
//      Uint8 b = 128;
//      frame_buffer[y * WINDOW_WIDTH + x] = (r << 16) | (g << 8) | b | (255 << 24);
//    }
//  }
//}