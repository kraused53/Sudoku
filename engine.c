#include "engine.h"

// Print a given Sudoku board
void print_board(uint8_t *board)
{
    for(uint8_t index = 0; index < 81; index++)
    {
        if(index != 0)
        {
            if(index % 27 == 0)
            {
                printf("\n-------------------\n");
            }else if((index % 9 == 0))
            {
                printf("\n");
            }else if(index % 3 == 0)
            {
                printf("|");
            }
        }
        if((board[index] & NUMBER_MASK) != 0)
        {
            if(board[index] & ORIGINAL_BITMASK)
            {
                printf("\033[0;34m");
                printf("%d ", board[index] & NUMBER_MASK);
                printf("\033[0m");
            }else {
                printf("%d ", board[index] & NUMBER_MASK);
            }

        }else {
            printf("  ");
        }

    }

    printf("\n");
}

uint8_t *place_piece(uint8_t *board, WINDOW *messages, WINDOW *game)
{
    uint8_t valid, user_input, row, col, index;

    // Prompt for user row input
    clear_message_window(messages);
    mvwprintw(messages, 1, 2, "Place Number");
    mvwprintw(messages, 2, 4, "-> Select a row");
    wrefresh(messages);

    valid = 0;
    // Get user input
    while(!valid)
    {
        user_input = getch();
        if((user_input >= '1') && (user_input <= '9'))
        {
            valid = 1;
        }
    }

    row = user_input - '0' - 1;
    
    // Set the row select flag for the selected row
    for(index = 0; index < 9; index++)
    {
        board[9*row + index] |= ROW_SELECT;
    }

    new_print_board(board, game);

    // Prompt for user col input
    clear_message_window(messages);
    mvwprintw(messages, 1, 2, "Place Number");
    mvwprintw(messages, 2, 4, "-> Select a column");
    wrefresh(messages);
    
    valid = 0;
    // Get user input
    while(!valid)
    {
        user_input = getch();
        if((user_input >= '1') && (user_input <= '9'))
        {
            valid = 1;
        }
    }

    col = user_input - '0' - 1;
    
    // Set the row select flag for the selected row
    for(index = 0; index < 9; index++)
    {
        board[9*index + col] |= COL_SELECT;
    }

    new_print_board(board, game);

    // Prompt for user row input
    clear_message_window(messages);
    mvwprintw(messages, 1, 2, "Place Number");
    mvwprintw(messages, 2, 4, "-> Select a number");
    wrefresh(messages);
    
    valid = 0;
    // Get user input
    while(!valid)
    {
        user_input = getch();
        if((user_input >= '1') && (user_input <= '9'))
        {
            valid = 1;
        }
    }

    //num = user_input - '0';
    
    // Set the row select flag for the selected row
    for(index = 0; index < 81; index++)
    {
        board[index] &= ~(ROW_SELECT | COL_SELECT);
    }

    new_print_board(board, game);

    // Clear messages screen
    clear_message_window(messages);
    wrefresh(messages);

    return board;
}

uint8_t *remove_piece(uint8_t *board, WINDOW *messages, WINDOW *game)
{
    uint8_t valid, user_input, row, col, index;

    // Prompt for user row input
    clear_message_window(messages);
    mvwprintw(messages, 1, 2, "Place Number");
    mvwprintw(messages, 2, 4, "-> Select a row");
    wrefresh(messages);

    valid = 0;
    // Get user input
    while(!valid)
    {
        user_input = getch();
        if((user_input >= '1') && (user_input <= '9'))
        {
            valid = 1;
        }
    }

    row = user_input - '0' - 1;
    
    // Set the row select flag for the selected row
    for(index = 0; index < 9; index++)
    {
        board[9*row + index] |= ROW_SELECT;
    }

    new_print_board(board, game);

    // Prompt for user col input
    clear_message_window(messages);
    mvwprintw(messages, 1, 2, "Place Number");
    mvwprintw(messages, 2, 4, "-> Select a column");
    wrefresh(messages);
    
    valid = 0;
    // Get user input
    while(!valid)
    {
        user_input = getch();
        if((user_input >= '1') && (user_input <= '9'))
        {
            valid = 1;
        }
    }

    col = user_input - '0' - 1;
    
    // Set the row select flag for the selected row
    for(index = 0; index < 9; index++)
    {
        board[9*index + col] |= COL_SELECT;
    }

    new_print_board(board, game);

    // Prompt for user row input
    clear_message_window(messages);
    mvwprintw(messages, 1, 2, "Place Number");
    mvwprintw(messages, 2, 4, "-> Select a number");
    wrefresh(messages);
    
    valid = 0;
    // Get user input
    while(!valid)
    {
        user_input = getch();
        if((user_input >= '1') && (user_input <= '9'))
        {
            valid = 1;
        }
    }

    //num = user_input - '0';
    
    // Set the row select flag for the selected row
    for(index = 0; index < 81; index++)
    {
        board[index] &= ~(ROW_SELECT | COL_SELECT);
    }

    new_print_board(board, game);

    // Clear messages screen
    clear_message_window(messages);
    wrefresh(messages);

    return board;
}

