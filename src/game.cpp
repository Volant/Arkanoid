#include "util.h"

int main() {
    if (SDL_Init (SDL_INIT_VIDEO) < 0) {
        printf("Error while initializing SDL: %sn",SDL_GetError());
        exit(1);
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 6);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);

    if (SDL_SetVideoMode (SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_OPENGL) == NULL) { // |SDL_FULLSCREEN
        printf("Error while setting up video mode: %sn", SDL_GetError());
        exit(1);
    }

    glClearColor(0, 0, 0, 0);
    glClearDepth(1.0f);
     
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
     
    glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 1, -1);
     
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_TEXTURE_2D);
    glLoadIdentity();

//    TicTacToe.game_loop ();

    SDL_Quit();

    return 0;
}
