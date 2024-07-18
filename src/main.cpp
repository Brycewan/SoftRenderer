#include <iostream>
#include "window.h"
#include "draw.h"

int WINDOW_WIDTH = 1600;
int WINDOW_HEIGHT = 1200;
Uint32* frame_buffer = new Uint32[WINDOW_WIDTH * WINDOW_HEIGHT];

void clear_frame_buffer() {
  for (int i = 0; i < WINDOW_WIDTH * WINDOW_HEIGHT; ++i) {
    frame_buffer[i] = 0;
  }
}

int main(int argc, char* args[]) {
  Window window(WINDOW_WIDTH, WINDOW_HEIGHT);
  window.initialize_SDL(false);

//   setup();

  while (window.get_running()) {
    window.process_input();

    // update();

    // clear frame
    clear_frame_buffer();

    // draw frame
    // for (int i = 0; i < 9 * 9 * 9; i++) {
    //   draw_rectangle(frame_buffer, output_cube[i].x, output_cube[i].y, 5, 5, 0xffffff00);
    // }

    //// test draw function
    draw_pixel(frame_buffer, 100, 200, 0xffffffff);
    draw_rectangle(frame_buffer, 800, 600, 10, 10, 0xffffff00);
    DDA_line(frame_buffer, 100, 200, 800, 900, 0x00ffffff);
    Bresenham_line(frame_buffer, 800, 900, 100, 500, 0x00ffffff);

    // render frame
    window.render(frame_buffer);
  }

  // deacllocate
  window.~Window();
  delete[] frame_buffer;

  return 0;
}