#include "Window.h"

Window::Window(int w, int h) : 
  width(w), 
  height(h), 
  window(nullptr), 
  renderer(nullptr), 
  texture(nullptr),
  is_running(false) {}

Window::~Window() {
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void Window::initialize_SDL(bool full_screen) {
  // initialize SDL subsystem
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    is_running = false;
  }

  // query full screen
  if (full_screen) {
    SDL_DisplayMode display_mode;
    SDL_GetCurrentDisplayMode(0, &display_mode);
    width = display_mode.w;
    height = display_mode.h;
  }
  
  // create SDL window
  window = SDL_CreateWindow(
    "SDL2 Window",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED, // set window in the centre of screen
    width,
    height,
    SDL_WINDOW_SHOWN);
  if (!window) {
    std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    is_running = false;
  }
  

  // create SDL renderer  
  renderer = SDL_CreateRenderer(window, -1, 0);
  if (!renderer) {
    std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(window);
    SDL_Quit();
    is_running = false;
  }


  // create SDL texture as the bridge of framebuffer and renderer, which use display texture on the window
  texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
  if (!texture) {
    std::cerr << "Texture could not be created! SDL_Error: " << SDL_GetError() << std::endl;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    is_running = false;
  }

  // // TODO: case 1 will have a bug!!!! dont know why
  //if (full_screen) {
  //  SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
  //}
  // // but this is ok????
  //SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);

  is_running = true;
}


void Window::process_input() {
  SDL_Event event;
  SDL_PollEvent(&event);

  switch (event.type) {
  case SDL_QUIT:
    is_running = false;
    break;
  case SDL_KEYDOWN:
    if (event.key.keysym.sym == SDLK_ESCAPE)
      is_running = false;
    break;
  }
}

void Window::render(Framebuffer* frame_buffer) {
  // Clear the current rendering target with the drawing color.
  //SDL_RenderClear(renderer);
  SDL_UpdateTexture(texture, nullptr, frame_buffer->get_frame_buffer(), width * sizeof(Uint32));
  // copy texture to renderer
  SDL_RenderCopy(renderer, texture, nullptr, nullptr);
  // display update
  SDL_RenderPresent(renderer);
}

bool Window::get_running() const {
  return is_running;
}