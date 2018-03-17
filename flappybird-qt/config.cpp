#include "./config.h"

int config::CYCLE = 10;

int config::FPS = 30;

int config::GAME_WIDTH = 480;
int config::GAME_HEIGHT = 720;

int config::PIPE_GAP = 158;
int config::PIPE_WIDTH = 64;
int config::PIPE_FIRST_X = 400;
int config::PIPE_BETWEEN = 270;
int config::PIPE_GAP_MIN_HEIGHT = 100;
int config::PIPE_GAP_MAX_HEIGHT = 400;

int config::LAND_HEIGHT = 120;
int config::SKY_HEIGHT = GAME_HEIGHT - LAND_HEIGHT;
int config::MAX_OVERFLOW_HEIGHT = 20;

int config::BIRD_SPEED = 2;
int config::BIRD_SIZE_HEIGHT = 42;
int config::BIRD_X_OFFSET = (int) (0.45 * GAME_WIDTH);
int config::BIRD_INIT_HEIGHT = (GAME_HEIGHT - LAND_HEIGHT) >> 1;
int config::BIRD_CLICK_UP_V = -45;

int config::PLAYING_SCORE_Y = 100;

QString config::TITLE = "Flappy Bird";

double config::G = 9.8;

bool config::RUSH = false;
