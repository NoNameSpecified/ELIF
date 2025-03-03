#ifndef DEFINE_COLOURS_H
#define DEFINE_COLOURS_H

// COLOURS, ANSI codes.

// font colours
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

// new colours that fit with sand-colour (180m) as background
#define DARK_BLUE "\033[38;5;17m"
#define DARK_GREEN "\033[38;5;22m"
#define NEW_BLACK "\033[38;5;236m"
#define NEW_WHITE "\033[38;5;15m"

// background colours
#define BG_RED    "\033[48;5;196m"
#define BG_GREEN  "\033[48;5;46m"
#define BG_BLUE   "\033[48;5;21m"

// style codes
#define BOLD      "\033[1m" // doesnt seem to work (on windows).
#define UNDERLINE "\033[4m"
#define BLINK     "\033[25m" // doesnt seem to work (on windows).

// resetting
#define RESET_STYLE "\033[0m" // we usually wanna keep background at least tho.
#define SANDFARBEN  "\033[48;5;180m"
#define RESET       "\033[48;5;180m\033[37m" // reset but keeps background colour and sets font to white.

#endif //DEFINE_COLOURS_H
