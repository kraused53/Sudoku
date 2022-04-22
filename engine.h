
#ifndef ENGINE_H
    #define ENGINE_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <stdint.h>
    #include <ncurses.h>

    #include "GUI.h"
    #include "bitmasks.h"

    // Function prototypes
    void print_board(uint8_t *board);
    uint8_t *place_piece(uint8_t *board, WINDOW *messages, WINDOW *game);
    uint8_t *remove_piece(uint8_t *board, WINDOW *messages, WINDOW *game);
#endif