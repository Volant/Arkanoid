#include "util.h"

#include "arkanoid.hpp"
#include "image.hpp"
#include "config.hpp"

int main() {

#if USE_VIDEO_MODE == 1
    if (SDL_Init (SDL_INIT_VIDEO) < 0) {
        printf("Error while initializing SDL: %sn",SDL_GetError());
        exit(1);
    }
#endif

#if USE_VIDEO_MODE == 1
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 6);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
#endif

    SDL_Window *sdlWindow;
    SDL_Renderer *sdlRenderer;

#if USE_VIDEO_MODE == 1
    SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL, &sdlWindow, &sdlRenderer);

    SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255);
    SDL_RenderClear(sdlRenderer);
    SDL_RenderPresent(sdlRenderer);

    if (sdlRenderer == NULL) {
        printf("Error while setting up video mode: %sn", SDL_GetError());
        exit(1);
    }
#endif

#if USE_VIDEO_MODE == 1
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glClearDepth(1.0f);
     
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
     
    glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 1, -1);
     
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
#endif

    Arkanoid engine (sdlWindow);

#if USE_VIDEO_MODE == 1
    SDL_GL_SwapWindow(sdlWindow);
#endif

    engine.game_loop ();

//    SDL_ShowSimpleMessageBox (SDL_MESSAGEBOX_INFORMATION, "Info", "Program is end", NULL);

#if USE_VIDEO_MODE == 1
    SDL_Quit();
#endif

    return 0;
}
