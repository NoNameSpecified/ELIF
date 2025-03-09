![splash_screen](https://github.com/user-attachments/assets/8ac08913-4b6a-4f1d-9c5b-00bd94d1a02c)

# **ELIF** v1.2
### For questions: ask me on Discord at *<kendrik2.0>*
Code is still in development. Only works on windows10 or above. Have fun if you wanna try / modify it :)

## Official repo:   
https://github.com/NoNameSpecified/ELIF  
You're free to do anything with the code, but please leave a link to the original repo (see license for more info).

### - short description:
simple terminal based selection tool for windows. Choose "dialog options" to send to someone through discord bot api.
Elif is a turkish female firstname and not related to python.

### - long description: 
The goal is to let the user choose one or multiple options from (currently) pre-defined options.
After the selection, the aim is to send the information to another person you want to communicate that with.
The simplest approach currently seems to go through a python script with a discord bot that sends it to the user via discord.
In the long term, the goal would be to offer other ways to communicate the information and make the program
work on multiple platforms, not just windows.


## - Install & Use:
1. Create a Discord Application for your bot (see https://youtu.be/b61kcgfOm_4, https://discord.com/developers/applications).
2. In the Discord Dev Portal, in the "Bot" tab of your application, enable presence intent, server members intent, message content intent.
3. Invite the bot to a server where the user you want to communicate with is also a member (else the bot can't dm him).
4. Download the code from the repo in src/ (for releases see info below). Compile main.c
6. Install python3 if you dont have it (choose "add to path" to make "python" callable in cmd).
7. Install discord.py with pip (in your cmd: "pip install discord.py")
8. Edit config.json and add your bot-token, the guild_id of the server (see above) and the user_id of the user you want to communicate with.
9. Start elif :)

-> Customize the menu_options.h to create your own menu, then compile main.c

additional info: you don't have to install the whole repo files in src/, you can also download a published release which has a pre-compiled .exe - https://github.com/NoNameSpecified/ELIF/tags - (you will still need to have python and discord.py installed). A mid-term goal would be to make the user able to create menus directly from the program but currently you need to customize menu_options.h.


### new in version 1.1
- added python message sender, but not yet very versatile and limited to specific use case.

### new in version 1.2
- fixed: multiple selection max_count and printing bug.
- fixed: "none" being enough to send, now requires selection.
- fixed: showing multiple selection (with "*" on left side and highlighting differently).
- fixed: already selected cannot be selected multiple times.
- fixed: menu options now don't risk to be recognized as cmd commands.

### TODOs in v1.2.
- maybe esc should close program/go back to splash screen and we use something else to return to main menu
- select multiple options directly with space.
- optimize code.
- let user choose to go to sending screen directly from menu without choosing option.
- improve aesthetics.
- enhance python side.
- create customization option on splash screen:
     start default / see or edit config / set custom config /
- make the menu_options customizable directly in the terminal program.


![splash_screen](https://github.com/user-attachments/assets/8ac08913-4b6a-4f1d-9c5b-00bd94d1a02c)

![menu_screen](https://github.com/user-attachments/assets/2538a7bc-e49e-4e1d-ad25-495c6c4914cb)

![sending_screen](https://github.com/user-attachments/assets/9c328a5e-d469-4519-821e-05b2ec6ebb70)

![sent_screen](https://github.com/user-attachments/assets/208ef0e1-fc43-4741-9870-8751edb56f1a)

