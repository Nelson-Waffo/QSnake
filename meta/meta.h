#ifndef META_H
#define META_H

#include "enums/position.h"
#include <QString>

// meta data for the game
struct LVMeta{
    // initial game speed
    static const int initial_game_speed = 280;
    // dimensions of the game widget which contains the game
    // cell size
    static const int cell = 20; // 20 px
    // dimensions for the game display and game widget: display game
    static const int display_width = 800;  // 800 px
    static const int display_height = 800; // 800 px
    // dimensions for the game info view widget
    static const int info_width = 200; // 200 px
    static const int info_height = 800; // 800 px
    // speed of the game
    static int speed;
    // initial position of the snake
    static const Position iniPosition = Position::Right;
    // range for poisonous candy
    static const int range = 3; // 3
    // score change
    static const int scoring = 2; // 2
    static const int start_score = 2; // 2
    // consumption sound
    static QString sweet_sound;
    static QString poison_sound;
    // height of the snake
    static const int snake_min_height = 2; // 2
    // single shot timer
    static const int single_shot = 2000; // 2 seconds
    // duration of the game
    static const int game_duration = 300; // 5 minutes
    // duration of a second
    static const int second = 1000; // 1 second
    // max point to win the game
    static const int max_points = 60; // 60 points
    static const int collision_timer = 50; // 50 ms
    static const int speed_increment = 20; // 10
};

#endif // META_H

/**
  collision timer // snake controller
  time timer // game view
  snake timer // python
  game loop timer // game view
  */
