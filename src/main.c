/*
 * Program name: ELIF (a turkish female firstname, not python "else if" lol).
 * Author: kendrik.
 * Version: 1.2.
 * Repository: https://github.com/NoNameSpecified/ELIF.
 * Short Description: simple terminal based selection tool for windows.
 * License: modified MIT license (see license in repository, short: keep a link to the official repo and,
 *                                if you redistribute the code closed source, put it on splash screen).
 * First created: 25.02.2025.
 * Last modified: 09.03.2025.
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
#define VERSION         "1.2" // currently working on 1.2 to enhance .c and .py

/* NEW IN VERSION 1.1
 * added python message sender.
 * but it is not yet very versatile and limited to specific use case.
 */

/* NEW IN VERSION 1.2
 * bug fixes and enhancements, particularly for multiple selection.
 */

/* TODO:
 * -- maybe esc should close program/go back to splash screen and we use something else to return to main menu
 * -- select multiple options directly with space.
 * -- optimize code.
 * -- let user choose to go to sending screen directly from menu without choosing option.
 * -- improve aesthetics.
 * -- enhance python side.
 * -- create customization option on splash screen:
 *      start default / see or edit config / set custom config /
 */


#define DEFAULT_SLEEP_MS 400 // beware: too high will cause delays when pressing key in splash screen.

//
// Standard includes.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h> // only works on windows.
#include <windows.h> // only works on windows.

//
// Our own includes - general functions, colours, choices.
//

/// general functions moved to this header file.
#include "includes/general_functions.h"
/// colours are defined in that header, used throughout the code to make it more aesthetic.
#include "includes/define_colours.h"
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
    // we are going to need these for the selected visibility
    int is_selected = 0; int found_selected = 0;

    char key;

    // info: we print these things (i call it "prompt") outside the loop
    // because the loop will only redraw the options part to show highlighted.
    printf(BLACK "<enter> " BLUE "to select an option /" BLACK " <space> " BLUE "to select multiple (" RED "*" BLUE);
    printf(" shows already selected)\npress" BLACK " <q> " BLUE "or" BLACK " <esc> " BLUE "to go back to MAIN MENU\n\n" RESET);

    // for multiple selection
    printf(BLUE "Currently selected");
    for (int i = 0 ; i < selected_count ; i++) {
        // array is initialized with lots of "NULL". Only show actual content.
        // info: we use != NULL just in case, we don't really need it.
        // But: check for it needs to be before check for "NULL", else segmentation fault.
        if ( final_choice[i] != NULL && strcmp(final_choice[i], "NULL") != 0) {
            printf(BLUE " -" RED " %s", final_choice[i]);
            found_selected ++;
        }
    }
    // if nothing already in selection yet, say none.
    if (!found_selected){ printf( ": " RED "none" BLUE "."); }
    printf(RESET "\n\n");

    // print menu with highlight and currently selected.
    while (1){
        for (int i = 0 ; i < choices_count; i++){
            // default: current option that is being printed is not selected
            is_selected = 0;

            for (int j = 0 ; j < selected_count ; j++) {
                // if the option is in the final choices
                if (options[i] == final_choice[j]) {
                    // set selected to true
                    is_selected = 1;
                }
            }

            // print accordingly
            if (i == choice && is_selected) {
                print_selected_highlighted(options[i]);
            } else if (i == choice) { // i == choice und !is_selected
                print_highlighted(options[i]);
            } else if (is_selected) { // is_selected und i != choice
                print_selected(options[i]);
            } else {
                print_menu(options[i]);
            }

            printf("\n\n");
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
        } else if (key == '\r'){ // enter --> choose current option
            // but: don't choose something that is already selected
            int already_selected = 0;
            // only test if we have anything selected at all yet.
            if (found_selected) {
                for (int j = 0 ; j < selected_count ; j++) {
                    // if current option (string) == one of our final choices (string too).
                    if (strcmp(options[choice], final_choice[j]) == 0) {
                        // --> selected, stay in choosing menu.
                        already_selected = 1;
                        break; // break out of for loop.
                    }
                }
            }
            // if not already selected, go through ; if already_selected: continue (stay in menu).
            if (!already_selected) break;
        } else if (key == 'q' || key == 27) { // 27 is "esc".
            // leads us back to main menu // TODO -- maybe esc should do something else.
            return "main_menu";
        } else if (key == 32) { // "space" key
            // TODO -- select multiple options directly.
        }

        // loop if out of range
        if (choice < 0) { choice = choices_count - 1; }
        if (choice >= choices_count) { choice = 0; }

        // we just move up (from below) and rewrite, simpler than moving cursor from top and needing to calculate.
        move_cursor_up(choices_count * 2); // times 2 because we always have a clear line in between
    }
    return options[choice];
}


// info: functions print_choice_unselected and print_choice_selected in header file.

int draw_choice(char **final_choice){ // returns 0 for yes, 1 for add more and 2 for reset.

    clear_screen(); // - only need one at the beginning, else we just rewrite the core, not the outside.

    int choice = 0; // default could also be 1 to default send more options
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
    printf(BG_BLUE WHITE "\nyour final choice" RESET " ");
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
        // edit: i used move_cursor_precise before, but it is EVEN easier to just move the cursor up and rewrite !
        move_cursor_up(3); // move up 3 lines because we only have 3 options here.
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
    printf(RESET_DEFAULT);

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


// The FIRST MAIN PART of the code. This runs the whole select app and starts the menus etc.
void run_select_app(char **final_choice, const int max_choices) {
    int main_iteration = 0;
    int sending_choice; // initialise here, because value can change.

    while (1){
        // if reached max, inform user, go back.
        if (main_iteration >= max_choices){
            printf(MAGENTA "\n/!\\ maximum options reached (max: %i)\nPress to continue.", max_choices);
            getch(); // wait for (any) key to continue.
            // directly choose between sending or resetting completely.
            sending_choice = draw_choice(final_choice);
        } else { // else go usual way: choose an option, then choose to send / re-choose / reset.
            // first: get our selection
            final_choice[main_iteration] = start_selection(final_choice);
            // then: draw yes / no selection.
            sending_choice = draw_choice(final_choice);
        }

        if (sending_choice == 0){
            // printf("SENDING SENDING SENDING\n");
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

    // END OF SELECT APP
    clear_screen();
    printf(RESET);
}

// handles the "python" part aka the discord bot used to send the message with the options.
char *run_discord_handler(const int max_choices, char **final_choice) {
    // --> create formatted options for python script.
    const int max_len = max_choices * 100 + 1; // every option should be way less than 100 ; +1 for null terminator.
    char formatted_options[max_len];

    // need to init with \0 else it's a random value and that messes with our strncat().
    memset(formatted_options, '\0', sizeof(formatted_options));

    // create a formatted_options string to pass as command.
    // our format should be something like option 1;;option 2;;option 3 with stuff;; ...
    int options = 0;
    for (int i = 0 ; i < max_choices ; i++) {
        // if not NULL = if there is an option
        if (strcmp(final_choice[i], "NULL") != 0) {
            // add to the string
            strncat(formatted_options, final_choice[i], 100); // max 100, like above.
            strcat(formatted_options, ";;");
            options++;
        }
    }

    // if there is no option --> back to menu to choose.
    if (options == 0) {
        return "empty_choice";
    }

    /* start python processing. Script will
    *      (1) get config, set up bot,
    *      (2) format options and send message,
    *      (3) close and come back here   */

    char *path = ""; // in case the .py sits somewhere else. Then put = "C:\\Users\\...\\";
    char *file_name = "messenger_bot.py";
    char *py = "python ";

    // inform user we start sending process.
    printf(RESET_DEFAULT);
    reset_screen();
    printf("    \nsending options via discord...\n");

    // create the command to launch python script.
    char full_command[500];
    // we need to put formatted options in "quotation marks"
    // because else cmd reads special chars (like < or &) as commands
    sprintf(full_command, "%s\"%s%s\" \"%s\"", py, path, file_name, formatted_options);

    // printf("%s", full_command);

    // start python script with popen to read output from python ("print" in python will be sent here)
    FILE *python_process = popen(full_command, "r");
    // buffer to save output
    char buffer[500];

    if (python_process == NULL) {
        printf("    Error starting python process !");
        getchar();
    }

    // log - prints output from python for user info (and debugging if needed).
    while ( fgets(buffer, sizeof(buffer), python_process) != NULL ) {
        printf("%s\n", buffer);
    }

    // python process finished, close.
    pclose(python_process);
    // back to main().
    return "success";
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
    const int max_choices = 10; // max_choices = sizeof(options)/sizeof(options[0])
    char *final_choice[] = {"NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL"}; // array for multiple choices
    // for "return" value of python handler.
    char *python_return;

    // loop between menu and python handler
    while (1) {
        // SELECTION PART
        run_select_app(final_choice, max_choices);

        // PYTHON PART (sending msg over discord with bot)
        python_return = run_discord_handler(max_choices, final_choice);

        // if we empty_choice = choose something
        if (strcmp(python_return, "empty_choice") == 0) {
            printf("Error: no options chosen. Press to go back to main menu.\n");
        } else if (strcmp(python_return, "success") == 0) {
            // success = continue regular code
            break;
        } // no "else {}".
    }


    // END OF ELIF-PROGRAM

    // inform user
    printf("       <ENTER> to close.       ");
    getchar();

    return 0;
}
