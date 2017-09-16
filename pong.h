#ifndef PONG_H
#define PONG_H

#define PADDLE_WIDTH 1
#define PADDLE_HEIGHT 3

#define BALL_WIDTH 1
#define BALL_HEIGHT 1

typedef struct paddle {
    int x;
    int y;
} paddle;

typedef struct ball {
    int x;
    int y;
    int x_velo;
    int y_velo;
} ball;

typedef struct game {
    paddle* paddle1;
    paddle* paddle2;
    ball* ball;
    int score1;
    int score2;
    int window_width;
    int window_height;
} game;

void init(game* game);
void tick(game* game);
void move_paddle(game* game, paddle* paddle, int delta_y);
bool intersect(game*, paddle*);

#endif
