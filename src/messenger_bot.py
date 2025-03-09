import os.path
import sys
import json

from discord.ext.commands import Bot
import discord


class MessageSender:
    def __init__(self, bot):
        self.client = bot

        # token --> from discord developer portal ; ids from discord.
        # the server (guild) needs to be a server the bot has in common with the user so that he can dm him.
        self.default_config = {
            "token": "put_your_token_here",
            "guild": "guild_id",
            "user": "user_id"
        }

        # get config from json or put them in
        try:
            self.json_file = open("config.json","r")
            self.json_content = json.load(self.json_file)
            self.token = self.json_content["token"]
            self.guild_id = int(self.json_content["guild"])
            self.user_id = int(self.json_content["user"])
            # print(f"found Guild_id {self.guild_id} type {type(self.guild_id)}")
            # print(f"found User_id {self.user_id} type {type(self.user_id)}")
        except Exception as e:
            print("json ERROR, overwriting -- err --", e)
            # if not os.path.exists("config.json"): -- Exception should cover both cases, no file at all or incorrect content.
            config_file = open("config.json","w")
            config_file.write(json.dumps(self.default_config, indent=4, separators=(',', ': ')))
            config_file.close()

        # get passed options. sys.argv also automatically deals with the quotation marks around the commands.
        self.args = sys.argv[1:] # start at 1 because 0 is the path (python "C:\..." option1 option2).
        self.passed_options = " ".join(self.args).split(";;") # ;; is the delimitation from main program.
        # cut -1 because we also stop with ;;, which else would be seen as an arg aswell
        self.passed_options = self.passed_options[:-1]

    async def send_message(self):
        # print(f"Attempting to send message to user {self.user_id} in guild {self.guild_id}")

        # get guild, first try from cache, else API
        try:
            # tries to get guild from bot cache
            self.server = self.client.get_guild(self.guild_id)
            if self.server is None:
                # tries to get guild from discord API directly (takes longer)
                self.server = await self.client.fetch_guild(self.guild_id)
        except Exception as e:
            print(f"Error fetching guild, err code {e}")

        # get member
        self.member = self.server.get_member(self.user_id)
        if self.member is None:
            print(f"Error fetching member.")

        # inform user
        # print("    Fetched guild and user. Sending message...")

        """
        # create embed
        embed = discord.Embed(
            title = "Message from ELIF",
            # description = "",
            color = discord.Color.green()
        )
        i = 0
        for option in self.passed_options:
            i += 1
            embed.add_field(name = option, value = "", inline = False)

        # send the message
        msg = await self.member.send(embed = embed)
        """

        msg = "*Message from ELIF*\n"
        i = 0
        for option in self.passed_options:
            i += 1
            msg += f"{i}. " + option + "\n"

        await self.member.send(msg)

        print("    Message sent !")



# Set bot up
intents = discord.Intents.all()
client = Bot(command_prefix="+", intents=intents)  # init bot

# initiate json and variables etc.
MSG_SNDR = MessageSender(client)

@client.event
async def on_ready():
    # send message
    await MSG_SNDR.send_message()
    # close after sending, code should end.
    await client.close()

# token is from init in MSG_SNDR.
client.run(MSG_SNDR.token, log_handler=None) # no logs because we want to keep it pure for the user.

# end of script, back to main.c
