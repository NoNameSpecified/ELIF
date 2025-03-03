/*
 * Program name: ELIF (a turkish female firstname, not python "else if" lol).
 * Author: kendrik.
 * Version: 0.3.
 * Repository: https://github.com/NoNameSpecified/ELIF.
 * Short Description: simple terminal based selection tool for windows.
 * License: modified MIT license (see license in repository, short: keep a link to the official repo and,
 *                                if you redistribute the code closed source, put it on splash screen).
 * First created: 25.02.2025.
 * Last modified: 03.03.2025.
 *
 * Long Description:
 *  The goal is to let the user choose one or multiple options from (currently) pre-defined options.
 *  After the selection, the aim is to send the information to another person you want to communicate
 *  that with. The simplest approach currently seems to go through a python script with a discord bot
 *  that sends it to the user via discord. In the long term, the goal would be to offer other ways to
 *  communicate the information and make the program work on multiple platforms, not just windows.
 *
 * Feel free to fork and modify the code but please keep this info intact.
 */


/// meta info of the code used in splash screen. You can change it if you change the program
/// but please include the original author and a link to the original repo on splash screen.
#define PGM_NAME        "ELIF" // turkish female firstname, not python "else if" lol.
#define DEV             "kendrik"
#define ORIGINAL_REPO   "https://github.com/NoNameSpecified/ELIF"
#define VERSION         "0.3"

/* TODO:
 * -- maybe esc should close program/go back to splash screen and we use something else to return to main menu
 * -- select multiple options directly with space.
 * -- optimize code.
 * -- create python script with discord bot implementation to send message.
 * -- don't let "none" be enough to send.
 * -- don't let the user choose the same option multiple times at once.
 * -- change the "selected" info when you brows the menu.
 * -- improve aesthetics.
 */


#define DEFAULT_SLEEP_MS 400 // beware: too high will cause delays when pressing key in splash screen.

//
// Standard includes.
//

#include <stdio.h>
#include <string.h>
#include <conio.h> // only works on windows.
#include <windows.h> // only works on windows.

//
// Our own includes - general functions, colours, choices.
//

/// general functions moved to this header file.
#include "general_functions.h"
/// colours are defined in that header, used throughout the code to make it more aesthetic.
#include "define_colours.h"
/// this header file will include the options arrays. They all need to end with NULL !
#include "menu_options.h"

// currently only working in windows. Other OS maybe later.
#ifndef _WIN32
#error "[ERR] this program requires windows specific headers and can only run on windows. Please contact dev for help."
#endif


//
// Start of code.
//

// the draw function for menu selection.
char *draw_selected(char **options, char **final_choice){ // returns a string (the option).
    clear_screen();
    int choice = 0;

    const int choices_count = count_options(options); // all option arrays need to end with NULL for this function.
    const int selected_count = count_options(final_choice);
    int found_selected = 0;
    // to know from what position from we rewrite.
    int last_prompt_line = 0;
    // we don't actually need lines printed if we just overwrite and don't clear_lines(from row, to row) + overwrite.
    // Keeping it in case.
    int lines_printed = 0;
    char key;

    // info: we print these things (i call it "prompt") outside the loop
    // because the loop will only redraw the options part to show highlighted.
    printf(BLACK "<enter> " BLUE "to select an option /" BLACK " <space> " BLUE "to select multiple (" RED "*" BLUE);
    printf(" shows selected)\npress" BLACK " <q> " BLUE "or" BLACK " <esc> " BLUE "to go back to MAIN MENU\n\n" RESET);

    lines_printed += 3; // 3 * "\n" in line above.
    last_prompt_line += 3; // update this separately.

    // for multiple selection
    printf(BLUE "Currently selected: ");
    for (int i = 0 ; i < selected_count ; i++) {
        // array is initialized with lots of "NULL". Only show actual content.
        // info: we use != NULL just in case, we don't really need it.
        // But: check for it needs to be before check for "NULL", else segmentation fault.
        if ( final_choice[i] != NULL && strcmp(final_choice[i], "NULL") != 0) {
            printf(BLUE " -" RED " %s", final_choice[i]);
            found_selected ++; // found_selected = 1 would be enough.
        }
    }
    // if nothing already in selection yet, say none.
    if (found_selected == 0){ printf(RED "none" BLUE "."); }
    printf(RESET "\n\n");

    lines_printed += 2; last_prompt_line += 2;

    while (1){
        // clear_screen(); --> we just overwrite.

        // print menu with highlight for currently selected.
        for (int i = 0 ; i < choices_count; i++){
            if (i == choice){
                print_selected(options[i]);
            } else {
                print_menu(options[i]);
            }

            // info for already selected
            for (int ii = 0 ; ii < selected_count - 1; ii++) {
                if (strcmp(options[i], final_choice[ii]) == 0) {
                    printf(RED " [selected] " RESET);
                    break;
                }
            }

            printf("\n\n");
            // we need this to know how many lines to rewrite
            lines_printed += 3; // 1x for the actual content line and 2x for the \n\n
        }

        key = getch(); // waiting for key(board)

        // special key like arrows.
        if (key == -32 || key == 224) {
            key = getch();
            if (key == 77 ||key == 80){ // arrow right / down
                choice ++;
            } else if (key == 75 || key == 72){ // arrow left / up
                choice --;
            }
        // other cases
        } else if (key == '\r'){ // enter
            break;
        } else if (key == 'q' || key == 27) { // 27 is "esc".
            // leads us back to main menu // TODO -- maybe esc should do something else.
            return "main_menu";
        } else if (key == 32) { // "space" key
            // TODO -- select multiple options directly.
        }

        // loop if out of range
        if (choice < 0) { choice = choices_count - 1; }
        if (choice >= choices_count) { choice = 0; }

        // info: we don't need to clear lines and rewrite, we can just overwrite.
        move_cursor_precise(last_prompt_line + 1 , 0);
    }

    return options[choice];
}


// info: functions print_choice_unselected and print_choice_selected in header file.

int draw_choice(char **final_choice){ // returns 0 for yes, 1 for add more and 2 for reset.

    clear_screen(); // - only need one at the beginning, else we just rewrite the core, not the outside.

    int choice = 1; // default ist send more options
    int choices_count = 3; // just defining this myself here, because this would be easy to change if we need to.
    char *options[] = {"yes send !", "add more options" , "noo, go back pls (reset)"};

    char *padding_0 = calculate_padding(options[2], options[0]);
    char *padding_1 = calculate_padding(options[2], options[1]);
    char *padding_2 = calculate_padding(options[2], options[2]);
    // we will need to free() them all at the end of this.

    const int selected_count = count_options(final_choice);

    char key;

    // new colours.
    printf(BLUE "\n\nDo you want to send this selection ? press" BLACK " <q> " BLUE "or" BLACK " <esc> ");
    printf(BLUE "to go back to MAIN MENU\n\n" );
    // print the choices we already have (can be none or multiple).
    printf(BG_BLUE WHITE "\nyour final choice:" RESET " ");
    for (int i = 0 ; i < selected_count ; i++) {
        if (strcmp(final_choice[i], "NULL") != 0) {printf(BLUE "- " RED "%s " RESET, final_choice[i]);}
    }
    printf("\n\n");

    while (1){
        // clear_screen(); -> now using rewriting specific lines instead.

        for (int i = 0; i < choices_count; i++) {
            char *padding_set = (i == 0) ? padding_0 : (i == 1) ? padding_1 : padding_2;

            // option highlighted (selected)
            if (i == choice) {
                print_choice_selected(padding_set, options[i]);
                printf("\n");
            }
            // option not highlighted
            else {
                print_choice_unselected(padding_set, options[i]);
                printf("\n");
        }}

        key = getch(); // waiting for key(board), returning ascii values.

        // if "special key" like arrows
        if (key == -32 || key == 224) {
            key = getch();
            if (key == 77 ||key == 80){ // arrow right / down
                choice ++;
            } else if (key == 75 || key == 72){ // arrow left / up
                choice --;
            }
        // other cases.
        } else if (key == '\r'){ // enter
            break;
        } else if (key == 'q' || key == 27) { // 27 is "esc".
            free(padding_0); free(padding_1); free(padding_2);
            padding_0 = NULL; padding_1 = NULL; padding_2 = NULL;
            return 1; // so back to main menu and reset choices.
        }

        // loop if out of range
        if (choice < 0) { choice = choices_count - 1; }
        if (choice >= choices_count) { choice = 0; }


        // Redraw screen (without clearing the whole screen) !

        // options start at row 8 ("yes send !") and stop row 10 ("noo, go back pls").
        move_cursor_precise(8, 0);
    }

    // we used malloc() above, so we need to free the space now.
    // also set to NULL in case theres multiple free() tried on same variable.
    free(padding_0); free(padding_1); free(padding_2);
    padding_0 = NULL; padding_1 = NULL; padding_2 = NULL;

    return choice;
}

/// char* get_new_menu(char *menu_selection){} --> moved to define_colours header file (specific function, not in general header file).


// navigate in menu
char *start_selection(char **final_choice){

    char **selected_menu = global_choices;
    char *iteration_final_choice;

    while (1){

        // show main menu

        char *menu_selection = draw_selected(selected_menu, final_choice);

        if (strcmp(menu_selection, "main_menu") == 0){
            selected_menu = global_choices;
        } else {
            // get_new_menu is from our colour header file.
            selected_menu = get_new_menu(menu_selection);
        }

        if (selected_menu == NULL){
            iteration_final_choice = menu_selection;
            break;
        }
    }

    return iteration_final_choice;
}


void splash_screen() {
    const int start_row = 9;
    const int start_col_top = 25;
    const int start_col_bot = start_col_top + 2;

    move_cursor_precise(start_row, start_col_top);

    // print welcome message with info on the code.
    printf( WHITE "Welcome to  " CYAN PGM_NAME WHITE " v." RED " %s" WHITE " by " CYAN "%s\n", VERSION, DEV);

    move_cursor_precise(start_row+1, start_col_bot);
    // as a variable to calculate length
    char welcome_prompt[] = "press to start";
    printf(YELLOW BLINK "%s", welcome_prompt);
    printf(RESET_STYLE);

    // convert to int because we will never go above int (strlen() returns size_t, can cause problems, raises warning).
    const int welcome_prompt_len = (int)(start_col_bot + strlen(welcome_prompt)); // sizeof counts \0, strlen not.

    int stop = 0; char *colour;
    while (!stop) {

        // moving this above so we dont sleep after breaking out of for loop.
        // clear and then redraw the points
        clear_line_precise(start_row + 1, welcome_prompt_len); // + 1 because we have "welcome" and then "press to start" lines.
        Sleep(DEFAULT_SLEEP_MS);

        for (int i = 0; i < 3; i++){
            // make the dots the colour of french flag (except its cyan but that's for visibility).
            switch (i) {
                case 0: colour = CYAN ; break;
                case 1: colour = WHITE ; break;
                case 2: colour = RED ; break;
                default: colour = YELLOW; break;
            }
            printf("%s.", colour);
            fflush(stdout); // print the dot immediately
            Sleep(DEFAULT_SLEEP_MS); // 500ms. Sleep is from windows.h.

            if (kbhit()) { // khbit is from conio.h, doesn't wait for input, just reacts, if there is one.
                getch(); // prevent key from staying in buffer and being a first key in menu.
                stop = 1;
                break;
            }
        }
    }
    // return to main and show menu.
}


int main(){

    // we don't need a cursor, we show highlighted stuff ourselves.
    hide_cursor();

    // welcome screen with press to start.
    splash_screen();

    // Sandfarben-background
    // RESET includes bg-colour and changes font-colour to white.
    printf(RESET);
    // final options can be one or multiple.
    // for now, we will put max_choices to 10, should be more than enough.
    int max_choices = 10;
    char *final_choice[] = {"NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL"}; // array for multiple choices
    int main_iteration = 0;

    while (1){

        if (main_iteration >= max_choices - 1){
            printf("maximum options reached (max: %i)\n", max_choices);
        }

        // first: get our selection
        final_choice[main_iteration] = start_selection(final_choice);

        // then: draw yes / no selection.
        int sending_choice = draw_choice(final_choice);

        if (sending_choice == 0){
            printf("SENDING SENDING SENDING\n");
            break;
        } else if (sending_choice == 1) {
            // when "add more options"
            ; // just to clarify ; not actually needed, array handled in function directly. Just pass.
        } else if (sending_choice == 2){
            // when "no, reset".
            for (int i = 0; i < max_choices - 1 ; i++) {
                final_choice[i] = "NULL";
            }
            main_iteration = 0; // continue jumps, so no = -1 needed.
            continue;
        }

        main_iteration ++;
    }

    // end of code, end of menu. In later versions we want to communicate this to a python bot script, so we can
    // communicate the choice to the other person. Easiest option for now.
    clear_screen();
    printf(BLACK "\n\nended successfully\n\n");
    getchar();
    return 0;

}
