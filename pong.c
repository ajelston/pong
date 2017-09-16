#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include <ncurses.h>

#include "pong.h"

int random_velo(int max) 
{
    int velo = (rand() % (max * 2)) - max;
    if (velo == 0) {
        if (rand() % 2) {
            velo = 1;
        } else {
            velo = -1;
        }
    }
    return velo;
}

void reset(game* game) {
    int mid_width = game->window_width / 2;
    int mid_height = game->window_height / 2;

    game->ball->x = mid_width;
    game->ball->y = mid_height;
    game->ball->x_velo = random_velo(3);
    game->ball->y_velo = random_velo(2);
    game->paddle1->x = 0;
    game->paddle1->y = mid_height;
    game->paddle2->x = game->window_width - 1;
    game->paddle2->y = mid_height;
}

void init(game* game)
{
    assert(game->paddle1 != NULL);
    assert(game->paddle2 != NULL);
    assert(game->ball != NULL);
    game->score1 = 0;
    game->score2 = 0;
    srand(time(NULL));
    reset(game);
}

void reverse(int* velo) 
{
    *velo = -(*velo);
}

/**
 * Return true if the current velocity and position of the
 * ball would mean that it would pass through the paddle
 * on the next update.
 */
bool intersect(game* game, paddle* paddle)
{
    ball* ball = game->ball;
    // If the ball is travelling away from the paddle, then 
    // it won't intercept.
    if (ball->x <= paddle->x && ball->x_velo < 0) {
        return false;
    }
    if (ball->x >= paddle->x && ball->x_velo > 0) {
        return false;
    }
    // Need to find the ball's y position when it's x would match
    // the paddle.
    int delta_y = (int) round(ball->y_velo / ball->x_velo);
    int y_at_paddle = ball->y + delta_y;
    int next_x = ball->x + ball->x_velo;

    return ((ball->x_velo < 0 && next_x <= paddle->x) 
            || (ball->x_velo > 0 && next_x >= paddle->x)) 
        && y_at_paddle >= paddle->y 
        && y_at_paddle < (paddle->y + PADDLE_HEIGHT);
}

void tick(game* game) 
{
    if (game->ball->x < 0) {
       game->score2++;
       reset(game);
    }
    if (game->ball->x >= game->window_width) {
        game->score1++;
        reset(game);
    }
    if (game->ball->y <= 1) {
        reverse(&(game->ball->y_velo));
    }
    if (game->ball->y >= game->window_height - 1) {
        reverse(&(game->ball->y_velo));
    }
    if (intersect(game, game->paddle1)) {
        reverse(&(game->ball->x_velo));
    }
    if (intersect(game, game->paddle2)) {
        reverse(&(game->ball->x_velo));
    }
    game->ball->x += game->ball->x_velo;
    game->ball->y += game->ball->y_velo;
}

void move_paddle(game* game, paddle* paddle, int delta_y)
{
    int next_y = paddle->y + delta_y;
    if (next_y <= 0 || next_y >= game->window_height - 1) {
        return;
    }
    paddle->y = next_y;
}
