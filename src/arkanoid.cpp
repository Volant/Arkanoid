#include "util.h"

#include "arkanoid.hpp"

void Arkanoid::draw_level (unsigned level_num) {

    // Draw bricks
    std::map < unsigned, Image > sprites = conf->sprites();
    for (unsigned i = 0; i < conf->lines_count(level_num); i++) {
        for (unsigned j = 0; j < conf->lines(level_num)[i].length(); j++) {
            unsigned sprite_num = conf->lines(level_num)[i][j] - 0x30;
            if (sprite_num == 1) {
                sprites[sprite_num - 1].draw_image (j * 36, i * 12);
            }
        }
    }

    // Draw ball
    sprites[1].draw_image (200, 150);

    conf->bat()->image()->draw_image (conf->bat()->x(), conf->bat()->y());
}

void Arkanoid::game_loop () {
//    bool human_move = false;
//    char winner = '\0';
    SDL_Event event;

    bool done = false;

    while (!done) {
        while (SDL_PollEvent (&event)) {
            if (event.type == SDL_QUIT)
                //this->game.done = true;
                done = true;
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    //this->game.done = true;
                    done = true;
                if (event.key.keysym.sym == SDLK_LEFT)
                    conf->bat()->move_left();
                if (event.key.keysym.sym == SDLK_RIGHT)
                    conf->bat()->move_right();
/*
            } else if (this->can_play ()) {
                human_move = this->check_mouse_click (event);
                this->Draw ();
                winner = this->check_winner ();
*/
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        draw_level (0);

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

#if USE_VIDEO_MODE == 1
        SDL_GL_SwapWindow(sdlWindow);
#endif

    }

//    winner = '\0';
//    winner = this->check_winner ();
//    if (winner == '\0') {
//        printf ("Drawn game\n");
//    } else {
//        printf ("Winner: '%C'\n", winner);
//    }
}

Arkanoid::Arkanoid (SDL_Window *sdlWindow) {
    current_level = 1;
    conf = new Config();

    this->sdlWindow = sdlWindow;
};

Arkanoid::~Arkanoid () {
    delete conf;
};
