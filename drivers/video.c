#include "video.h"
#include <stdint.h>

#define VIDEO_ADRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLORS 80
#define WHITE_ON_BLACK 0x0f

int get_cursor_offset();
void set_cursor_offset(int offset);
int print_char(char c, int col, int row, char attr);
int get_offset(int col, int row);
int get_offset_row(int offset);
int get_offset_col(int offset);

// Kernel API
void kprint_at(char *message, int col, int row) {
    int offset;
    if (col >= 0 && row >= 0) {
        offset = get_offset(col, row);
    } else {
        offset = get_cursor_offset();
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }
    int i = 0;
    while (message[i] != 0) {
        offset = print_char(message[i++], col, row, WHITE_ON_BLACK);
        /* Compute row/col for next iteration */
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }
}

void kprint(char *message) {
    kprint_at(message, -1, -1);
}

void kprint_backspace() {
    int offset = get_cursor_offset() - 2;  // Move back by 2 bytes (char + attribute)
    int row = get_offset_row(offset);
    int col = get_offset_col(offset);
    print_char(' ', col, row, WHITE_ON_BLACK);
    set_cursor_offset(offset);
}

void cls() {
    int screen_size = MAX_ROWS * MAX_COLORS;
    int i;
    char *screen =(char*) VIDEO_ADRESS;

    for (i = 0; i < screen_size; i++) {
        screen[i*2] = ' ';
        screen[i*2+1] = WHITE_ON_BLACK;
    }
    
}