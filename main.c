#include <ncurses.h>
#include <string.h>

#include "pong.h"

void draw_paddle(paddle* paddle)
{
    for (int i = 0; i < PADDLE_HEIGHT; i++) {
        move(paddle->y + i, paddle->x);
        printw("#");
    }
}

void draw_ball(game* game, ball* ball)
{
    if (ball->x < 0 || ball->x >= game->window_width) {
        return;
    }
    move(ball->y, ball->x);
    printw("@");
}

void draw(game* game)
{
    clear();
    draw_paddle(game->paddle1);
    draw_paddle(game->paddle2);
    draw_ball(game, game->ball);

    move(0, ((int) game->window_width / 2) - 8);
    attron(A_UNDERLINE);
    printw("SCORE: %02d -- %02d", game->score1, game->score2);
    attroff(A_UNDERLINE);
    refresh();
}

int main()
{
    int ch;
    bool quit = false;

    game game;
    paddle paddle1;
    paddle paddle2;
    ball ball;
    game.paddle1 = &paddle1;
    game.paddle2 = &paddle2;
    game.ball = &ball;
    
    initscr();
    curs_set(0);
    raw();
    noecho();
    halfdelay(1);

    getmaxyx(stdscr, game.window_height, game.window_width);
    init(&game);

    while (!quit) {
        tick(&game);
        draw(&game);
        // todo: get user input (halfdelay?)
        ch = getch();
        switch (ch) {
            case 'q':
            case 'Q':
                quit = true;
                break;
            case 'a':
            case 'A':
                move_paddle(&game, game.paddle1, -1);
                break;
            case 'z':
            case 'Z':
                move_paddle(&game, game.paddle1, 1);
                break;
            case '\'':
            case '"':
                move_paddle(&game, game.paddle2, -1);
                break;
            case '/':
            case '?':
                move_paddle(&game, game.paddle2, 1);
                break;
        }
    }

    endwin();

    return 0;
}
