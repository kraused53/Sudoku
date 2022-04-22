#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include "engine.h"
#include "GUI.h"

int main(int argc, char *argv[])
{
    /* <-- Check for correct input arguments --> */
    if(argc != 2)
    {
        if(argc > 2)
        {
            printf("Please provide a single board file.\n");
        }else {
            printf("Please provide a board file.\n");
        }
        return EXIT_FAILURE;
    }

    /* <-- Attempt to open and read given board file --> */
    // Createan empty file pointer
    FILE *input_file;

    // Attempt to open the given file to read
    input_file = fopen(argv[1], "r");

    // If there was an error, fopen() will return NULL
    if(input_file == NULL)
    {
        printf("There was an error when opening the given file\n");
        return EXIT_FAILURE;
    }

    /* <-- Check to see if the opened file is of a valid length --> */
    // Move file pointer to the end of the file
    fseek(input_file, 0, SEEK_END);

    // ftell with the file pointer at the end of the file will return the number of bytes in the file
    // A vaild game file will have exactly 89 bytes: 81 numbers and 8 '\n' characters
    if(ftell(input_file) != 89)
    {
        printf("The given file is not a valid game file.\n");
        return EXIT_FAILURE;
    }

    // Return the file pointer to the head of the file
    fseek(input_file, 0, SEEK_SET);

    /* <-- Attempt to load the given game file into program memory --> */
    // Create variables to store and track game board information
    // Allocate an array of 81 bytes to store game board information
    uint8_t *board = malloc(81*sizeof(uint8_t));

    // Check to make sure that the program was able to allocate the memory for the game board
    if(board == NULL)
    {
        printf("The system was not able to allocate the memory for the game board!\n");
        return EXIT_FAILURE;
    }

    // Create index variable to track progress when loading data from the now open file
    uint8_t index;
    // Create a variable to hold individual characters as they are read from the pen file
    char read_char;

    // Reset game board index
    index = 0;
    
    // Read the entirety of the file, one char at a time
    while((read_char = fgetc(input_file)) != EOF)
    {
        // Skip the 8 '\n' characters
        if(read_char != '\n')
        {
            // Make sure that the read char is a number
            if((read_char >= '0') && (read_char <= '9'))
            {
                // If the read character is a zero
                if(read_char == '0')
                {
                    // Store a zero into the game board and do not set it's ORIGINAL_MASK flag
                    board[index] = 0;
                }else {
                    // Store the given initial cell value in the game board memory
                    //      (read_char - '0') converts an ASCII number into the correct integer
                    //      value | ORIGINAL_BITMASK sets the origianal value flag for this number
                    board[index] = (read_char - '0') | ORIGINAL_BITMASK;
                }
            }else {
                printf("The given file contains invalid characters!\n");
                // Free all allocated memory
                fclose(input_file);
                free(board);
                // Exit the program
                return EXIT_FAILURE;
            }
            // Update the index variable
            index++;
        }
    }

    // Close the input file, we no longer need it
    fclose(input_file);

    /* <-- Create Game state flag, start nCurses GUI and enter game loop --> */
    // Game state flag [0 -> kepp playing, 1 -> game over/ended]
    uint8_t game_over = 0;
    // Variable to hold user input
    uint8_t user_input;

    // Start nCurses GUI
    initscr();
    // Enable color functionality
    start_color();
    // Disable line buffering to get user entry one char at a time
	raw();
    // Disable user input echo
    noecho();
    // Disable cursor
    curs_set(0);


    // Setup color pair: green text, black background
   	init_pair(1, COLOR_GREEN, COLOR_BLACK);     // Menu Text
    init_pair(2, COLOR_RED, COLOR_BLACK);       // Menu Text <Option characters>
    init_pair(3, COLOR_MAGENTA, COLOR_BLACK);   // Colors for initial number placements
    init_pair(4, COLOR_BLUE, COLOR_WHITE);      // Colors for row/col selection
    init_pair(5, COLOR_BLACK, COLOR_YELLOW);    // Colors for row & col selection

    display_game_controls();

    // Update display
    refresh();
    
    // Create game board window
    WINDOW *board_window = create_new_window(11, 23, 5, 5);
    new_print_board(board, board_window);
    wrefresh(board_window);

    // Create message window
    WINDOW *message_window = create_new_window(4, 23, 1, 4);
    wborder(message_window, '|', '|', '-', '-', '+', '+', '+', '+');
    mvwprintw(message_window, 1, 3, "Welcome to Sudoku!");
    mvwprintw(message_window, 2, 4, "Make a selection");
    wrefresh(message_window);

    mvprintw(0, 0, "");

    // Game loop
    while(!game_over)
    {
        user_input = getch();
        switch (user_input)
        {
            case 'q':
            case 'Q':
                clear_message_window(message_window);
                game_over = 1;
                break;
            case 'p':
            case 'P':
                place_piece(board, message_window, board_window);
                wrefresh(message_window);
                break;
            case 'r':
            case 'R':
                remove_piece(board, message_window, board_window);
                wrefresh(message_window);
                break;
                break;
            default:
                break;
        }

    }

    mvwprintw(message_window, 1, 2, "Thanks for playing!");
    mvwprintw(message_window, 2, 1, "Press any key to exit");
    wrefresh(message_window);

    getch();

    // Exit GUI
    endwin();
    printf("Done!\n\r");
    // De-allocate game board from memory
    free(board);
    return EXIT_SUCCESS;
}


