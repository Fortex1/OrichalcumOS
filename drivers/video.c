#include "video.h"
#include <stdint.h>

int get_cursor_offset();
void set_cursor_offset(int offset);
int print_char(char c, int col, int row, char attr);
int get_offset(int col, int row);
int get_offset_row(int offset);
int get_offset_col(int offset);

// Kernel API
void kprint_at(char *message, int col, int row){
    int offset;
    if (col >= 0 && row >= 0){
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
    int offset = get_cursor_offset() - 1;
    int row = get_offset_row(offset);
    int col = get_offset_col(offset);
    print_char(' ', col, row, WHITE_ON_BLACK);
    set_cursor_offset(offset);
}
