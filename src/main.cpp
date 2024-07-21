#include <iostream>
#include "Window.h"
#include "Framebuffer.h"
#include "Scene.h"
#include "Shader.h"

int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 800;

int main(int argc, char* args[]) {
  Window window(WINDOW_WIDTH, WINDOW_HEIGHT);
  window.initialize_SDL(false);

  Framebuffer framebuffer(WINDOW_WIDTH, WINDOW_HEIGHT);

  Shader shader;

  Scene scene;

  while (window.get_running()) {
    window.process_input();

    // clear frame
    //clear_frame_buffer();
    framebuffer.clear();

    shader.direct(&scene, framebuffer);
    //// test draw function
    framebuffer.drawPixel(100, 200, 0xffffffff);
    framebuffer.draw_rectangle(400, 300, 10, 10, 0xffffff00);
    framebuffer.drawLineDDA(100, 200, 400, 450, 0x00ffffff);
    framebuffer.drawLineBresenham(400, 450, 50, 250, 0x00ffffff);

    // render frame
    window.render(&framebuffer);
  }
  
  return 0;
}