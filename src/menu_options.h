#ifndef DEMO_MENU_OPTIONS_H
#define DEMO_MENU_OPTIONS_H

// you must always end the array with NULL ! Else the count_options function won't work.
// please excuse the unoriginal names, their goal is just to show how it functions.
// add as many options / menus as you want :)

static char *global_choices[] = {"sample menu (1)", "my other menu (2)", "yet another menu (3)", "menu 4", NULL}; // NULL to show End

static char *menu_1[] = {
    "--> example submenu 1",
    "--> example submenu 2",
    "m1 option 3",
    "m1 option 4",
    "m1 option 5",
    "m1 option 6",
    "m1 option 7",
    "m1 option 8",
    NULL
};

static char *submenu_1[] = {
    "subm1 option 1",
    "subm1 option 2",
    "subm1 option 3",
    "subm1 option 4",
    "subm1 option 5",
    NULL
};

static char *submenu_2[] = {
    "subm2 option 1",
    "subm2 option 2",
    "subm2 option 3",
    "subm2 option 4",
    NULL
};

static char *menu_2[] = {
    "m2 option 1",
    "m2 option 2",
    "m2 option 3",
    "m2 option 4",
    NULL
};

static char *menu_3[] = {
    "m3 option 1",
    "m3 option 2",
    "m3 option 3",
    "m3 option 4",
    NULL
};

static char *menu_4[] = {
    "m4 option 1",
    "m4 option 2",
    NULL
};


char **get_new_menu(char *menu_selection){

    // MAIN MENU

    if (strcmp(menu_selection, global_choices[0]) == 0) {
        // i. e. when in the "main menu" you chose the first option which is menu 1
        return menu_1;

    } else if (strcmp(menu_selection, global_choices[1]) == 0) {
        // menu 2
        return menu_2;
    } else if (strcmp(menu_selection, global_choices[2]) == 0) {
        // menu 3
        return menu_3;
    } else if (strcmp(menu_selection, global_choices[3]) == 0) {
        // menu 4
        return menu_4;

        // Submenus for menu 1.

    } else if (strcmp(menu_selection, menu_1[0]) == 0) {
        // submenu 1
        return submenu_1;
    } else if (strcmp(menu_selection, menu_1[1]) == 0) {
        // submenu 2
        return submenu_2;
    }

    else {
        // Default: NULL, which is handled in main.c as back to main menu
        return NULL;
    }

}


#endif //DEMO_MENU_OPTIONS_H
