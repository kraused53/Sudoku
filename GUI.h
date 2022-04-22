#ifndef GUI_H
    #define GUI_H

    #include <ncurses.h>

    #include "engine.h"
    #include "bitmasks.h"

    WINDOW *create_new_window(int height, int width, int starty, int startx);
    void new_print_board(uint8_t *board, WINDOW *board_win);
    void display_game_controls();
    void clear_message_window(WINDOW *message_window);

#endif