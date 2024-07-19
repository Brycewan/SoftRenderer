#pragma once

#include <iostream>
#include <SDL\SDL.h>
#include "Framebuffer.h"

class Window {
private:
  bool is_running;
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Texture* texture;
  int width, height;

public:
  Window(int w, int h);
  ~Window();
  void initialize_SDL(bool full_screen);
  void process_input();
  void render(Framebuffer* frame_buffer);
  bool get_running() const;
};