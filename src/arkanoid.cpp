#include "util.h"

#include "arkanoid.hpp"

void Arkanoid::game_loop () {
//    bool human_move = false;
//    char winner = '\0';
    SDL_Event event;

    bool done = false;

//    while (this->can_play ()) {
    while (!done) {
        while (SDL_PollEvent (&event)) {
            if (event.type == SDL_QUIT)
                //this->game.done = true;
                done = true;
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    //this->game.done = true;
                    done = true;
/*
            } else if (this->can_play ()) {
                human_move = this->check_mouse_click (event);
                this->Draw ();
                winner = this->check_winner ();
*/
            }
        }
/*
        if (human_move && this->can_play ()) {

            this->AI_move ();
            while (SDL_PollEvent (&event));

            // make it more realistic
            sleep (1);

            this->Draw ();
            winner = this->check_winner ();
            human_move = false;
        }
*/
    }

//    winner = '\0';
//    winner = this->check_winner ();
//    if (winner == '\0') {
//        printf ("Drawn game\n");
//    } else {
//        printf ("Winner: '%C'\n", winner);
//    }
}

