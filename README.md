# **ELIF** v0.3
### For questions: ask me on Discord at *<kendrik2.0>*
Code is still in development. Only works on windows10 or above. Have fun if you wanna try / modify it :)

## Official repo:   
https://github.com/NoNameSpecified/ELIF  
You're free to do anything with the code, but please leave a link to the original repo (see license for more info).

### - short description:
simple terminal based selection tool for windows.
Elif is a turkish female firstname and not related to python.

### - long description: 
The goal is to let the user choose one or multiple options from (currently) pre-defined options.
After the selection, the aim is to send the information to another person you want to communicate that with.
The simplest approach currently seems to go through a python script with a discord bot that sends it to the user via discord.
In the long term, the goal would be to offer other ways to communicate the information and make the program
work on multiple platforms, not just windows.


## setup:
You can simply compile the .c file and try it out.
You should however take a look at menu_options.h and customize your menus.

## TODOs
- maybe esc should close program/go back to splash screen and we use something else to return to main menu
- select multiple options directly with space.
- optimize code.
- create python script with discord bot implementation to send message.
- don't let "none" be enough to send.
- don't let the user choose the same option multiple times at once.
- change the "selected" info when you brows the menu.
- improve aesthetics.
