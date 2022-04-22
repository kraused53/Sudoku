#include "GUI.h"

/* <-- nCurses window manager functions --> */

/*
 * This function takes a game board and a nCurses sub-window and
 *  generates an ASCII representation of a 9x9 Sudoku board.
 * 
 * Inputs:
 *  -> uint8_t *board:
 *      An array of 8-Bit integers that represent the current state of the sudoku board
 *  -> WINDOW *board_win:
 *      A pointer to the nCurses window containing the ASCII representation of the board
 * 
 * Outputs:
 *  -> None:
 *      This function updates the given window via pointers, and does not need to return anything
 */
void new_print_board(uint8_t *board, WINDOW *board_win)
{
    mvwprintw(board_win, 0, 0, "");
    for(uint8_t index = 0; index < 81; index++)
    {
        if(index != 0)
        {
            if(index % 27 == 0)
            {
                wprintw(board_win, "\n");
                for(uint8_t col_index = 0; col_index < 9; col_index++)
                {
                    if(board[col_index] & COL_SELECT)
                    {
                        wattron(board_win, COLOR_PAIR(4));
                        wprintw(board_win, "= ");
                        wattroff(board_win, COLOR_PAIR(4));
                    }else {
                        wprintw(board_win, "= ");
                    }

                    if((col_index == 2) || (col_index == 5))
                    {
                        wprintw(board_win, "= ");
                    }
                }
                wprintw(board_win, "\n");
            }else if((index % 9 == 0))
            {
                wprintw(board_win, "\n");
            }else if(index % 3 == 0)
            {
                if(board[index-1] & ROW_SELECT)
                {
                    wattron(board_win, COLOR_PAIR(4));
                    wprintw(board_win, "| ");
                    wattroff(board_win, COLOR_PAIR(4));
                }else {
                    wprintw(board_win, "| ");
                }

            }
        }

        if(board[index] != 0)
        {   
            if((board[index] & ROW_SELECT) || (board[index] & COL_SELECT))
            {
                if((board[index] & ROW_SELECT) && (board[index] & COL_SELECT))
                {
                    wattron(board_win, COLOR_PAIR(5));
                    if((board[index] & NUMBER_MASK) == 0)
                    {
                        wprintw(board_win, "  ");
                    }else {
                        wprintw(board_win, "%d ", (board[index] & NUMBER_MASK));
                    }
                    wattroff(board_win, COLOR_PAIR(5));
                }else {
                    wattron(board_win, COLOR_PAIR(4));
                    if((board[index] & NUMBER_MASK) == 0)
                    {
                        wprintw(board_win, "  ");
                    }else {
                        wprintw(board_win, "%d ", (board[index] & NUMBER_MASK));
                    }
                    wattroff(board_win, COLOR_PAIR(4));
                }
            }else if(board[index] & ORIGINAL_BITMASK) {
                wattron(board_win, COLOR_PAIR(3));
                wprintw(board_win, "%d ", (board[index] & NUMBER_MASK));
                wattroff(board_win, COLOR_PAIR(3));
            }

        }else {
            wprintw(board_win, "  ");
        }
    }

    wrefresh(board_win);
}


/*
 * This function takes set of initial contidions and returns a pointer to
 *  a nCurses window that meet the given specifications.
 * 
 * Inputs:
 *  -> int height:
 *      Define how many lines the windows height will span
 *  -> int width:
 *      Define how many columns the window will span
 *  -> int starty:
 *      Define the line in witch the top left corner of the window will be placed
 *  -> int startx:
 *      Define the column in witch the top left corner of the window will be placed
 * 
 * Outputs:
 *  -> WINDOW *create_new_window:
 *      This function returns a pointer to the window that it creates
 */
WINDOW *create_new_window(int height, int width, int starty, int startx)
{
    WINDOW *local_win;

    local_win = newwin(height, width, starty, startx);
    
    return local_win;
}


/*
 * This function prints the game controls across the bottom of the screen
 * 
 * Inputs:
 *  -> None
 * Outputs:
 *  -> None
 */
void display_game_controls()
{
    // Start printing in color
    attron(COLOR_PAIR(1));
    // Print exit statement
    mvprintw(20, 3, "(");
    // End color printing
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(2));
    printw("Q");
    attroff(COLOR_PAIR(2));

    attron(COLOR_PAIR(1));
    printw(")uit   (");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(2));
    printw("P");
    attroff(COLOR_PAIR(2));

    attron(COLOR_PAIR(1));
    printw(")lace   (");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(2));
    printw("R");
    attroff(COLOR_PAIR(2));

    attron(COLOR_PAIR(1));
    printw(")emove");
    attroff(COLOR_PAIR(1));
}

/*
 * This function clears the text from the message board
 *
 * Inputs:
 *  -> WINDOW *message_window:
 *      A pointer to thenCurses window containing game messages
 * Outputs:
 *  -> None
 */
void clear_message_window(WINDOW *message_window)
{
    mvwprintw(message_window, 1, 1, "                     ");
    mvwprintw(message_window, 2, 1, "                     ");
}