#pragma once

#include <iostream>
#include <SDL\SDL.h>

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
  void setup();
  void process_input();
  void update();
  void render(Uint32* frame_buffer);
  bool get_running() const;
};