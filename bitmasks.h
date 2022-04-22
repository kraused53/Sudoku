#ifndef BITMASKS_H
    #define BITMASKS_H

    // Bitmasks
    #define ORIGINAL_BITMASK 0x80   // 1000 0000 -> Used to isolate the original number flag
    #define ROW_SELECT 0x40         // 0100 0000 -> Used to highlight selected row
    #define COL_SELECT 0x20         // 0010 0000 -> Used to highlight selected col
    #define NUMBER_MASK 0x0F        // 0000 1111 -> Used to isolate the number currently stored in the cell

#endif