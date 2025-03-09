#ifndef GENERAL_FUNCTIONS_H
#define GENERAL_FUNCTIONS_H

#include "define_colours.h" // because we print with colours.

//
// Small, general functions. We use a lot of ANSI escape sequences.
//

static void hide_cursor() { printf("\033[?25l"); }
static void show_cursor() { printf("\033[?25h"); }
// deletes screen and sets cursor to top line but also resets color
static void clear_screen() { printf("\033[H\033[J"); printf(RESET); }
// simple delete and reset to default
static void reset_screen() { printf("\033[H\033[J"); printf(RESET_DEFAULT); }
// these functions arent always used, sometimes i just set specific colours in the code itself.
static void print_prompt(char *text){  printf(DARK_BLUE " %s \n\n" RESET, text);  }
static void print_menu(char *text){  printf(DARK_BLUE "    %s   " RESET, text);  }
static void print_highlighted(char *text){  printf(NEW_WHITE "  > %s < " RESET, text);  }
static void print_selected(char *text){  printf(RED "  *" DARK_BLUE " %s   " RESET, text);  }
static void print_selected_highlighted(char *text){  printf(RED "  *" NEW_WHITE " %s   " RESET, text);  }
static void print_magenta(char *text){  printf(MAGENTA " %s \n\n" RESET, text);  }
static void move_cursor_up(const int lines) { printf("\033[%iA", lines); } // moves cursor up X lines.
static void move_cursor_precise(const int row, const int col) {
    printf("\033[%d;%dH", row, col);  // moves cursor to position
    fflush(stdout); // print immediately.
}

// info: not used a lot, since it takes less processing to just rewrite.
static void clear_lines(const int from_row, const int to_row) {
    for (int i = from_row; i <= to_row; i++) {
        // info: \033[K deletes line from cursor, with 0H because we del whole line, so we set cursor to column 0.
        printf("\033[%d;0H\033[K", i); // move cursor to row X at col 0 + del line since 0 = complete line
    }
    fflush(stdout);
}

static void clear_line_precise(const int row, const int from_col) {
    printf("\033[%d;%dH\033[K", row, from_col); // move cursor and only delete line starting our column.
    fflush(stdout);
}

static int count_options(char *options[]){
    int count = 0;
    // we need arrays to end with NULL ! Exception is the array with already selected options which consists of "NULL", "NULL" anyway
    while (options[count] != NULL && strcmp(options[count], "NULL") != 0) {
        count ++;
    }
    return count;
}

// Calculate padding when we want to center according to the largest element.
static char *calculate_padding(const char *longest_string, const char *string_to_pad){
    // default padding that even the longest string must have.
    const int default_padding = 6; // so 3 spaces left, 3 right.
    // size_t is unsigned int but adapts to 32/64bit-CPU.
    size_t longest_string_len = strlen(longest_string) + default_padding;
    size_t string_to_pad_len = strlen(string_to_pad);

    // get a even number of char in length for both strings.
    if (longest_string_len % 2 != 0){ longest_string_len ++; }
    if (string_to_pad_len % 2 != 0){ string_to_pad_len ++; }

    const int padding = (longest_string_len - string_to_pad_len) / 2;
    char *padding_str = malloc(padding + 1); // + 1 for null-terminator \0.
    // memset to fill with our padding variable with spaces.
    memset(padding_str, ' ', padding);
    padding_str[padding] = '\0'; // null terminator.

    return padding_str;
}

// draw choice menu: print with padding, not highlighted
static void print_choice_unselected(char *padding, char *option){
    printf( NEW_WHITE " %s ", padding);
    printf(DARK_BLUE "%s" RESET, option);
    printf( NEW_WHITE " %s ", padding);
}
// draw choice menu: print with padding, highlighted
static void print_choice_selected(char *padding, char *option){
    printf( NEW_WHITE " >%s", padding);
    printf( NEW_WHITE "%s" RESET, option);
    printf( NEW_WHITE "%s< ", padding);
}

#endif //GENERAL_FUNCTIONS_H
