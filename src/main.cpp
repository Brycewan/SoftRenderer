#include <iostream>
#include "Window.h"
#include "Framebuffer.h"
#include "Shader.h"
#include "Scene.h"
#include "Object.h"

int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 800;

int main(int argc, char* args[]) {
  Window window(WINDOW_WIDTH, WINDOW_HEIGHT);
  window.initialize_SDL(false);
  Framebuffer framebuffer(WINDOW_WIDTH, WINDOW_HEIGHT);

  Shader shader;

  // set scene parameters
  Vec3 cameraPos(0.0f, 0.0f, 3.0f);
  Vec3 target(0.0f, 0.0f, 0.0f);
  Vec3 up(0.0f, 1.0f, 0.0f);
  Camera camera(cameraPos, target, up, 45.0f, (float)WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 100.0f);

  // 创建场景并设置相机
  Scene scene(&camera);

  // 创建一个三角形对象
  Object triangle;
  triangle.addVertex(Vertex(Vec3(-0.5f, -0.5f, 0.0f), 0xFF0000FF)); // Red
  triangle.addVertex(Vertex(Vec3(0.5f, -0.5f, 0.0f), 0xFF00FF00)); // Green
  triangle.addVertex(Vertex(Vec3(0.0f, 0.5f, 0.0f), 0xFFFF0000)); // Blue

  // 将三角形对象添加到场景中
  scene.addObject(&triangle);


  while (window.get_running()) {
    window.process_input();

    // clear frame
    //clear_frame_buffer();
    framebuffer.clear();

    shader.wireframe(&scene, framebuffer);
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