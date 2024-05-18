
#include <Arduino.h>
#include <tgbot/tgbot.h>
#include <UniversalTelegramBot.h>

const String BOT_TOKEN = "7040368229:AAEoQZNvMDUzaCTZ177E7fhVettplMd-dII";

UniversalTelegramBot bot(BOT_TOKEN, "1712857373");

void handleNewMessages(int numNewMessages) {
  for (int i = 0; i < numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    String text = bot.messages[i].text;

    if (text == "/start") {
      String welcomeMessage = "Hi, my friend!\n\nPlease, select next action:";
      String keyboardJson = "[[\"Start\", \"/start\"], [\"Goodbye\", \"goodbay\"], [\"End\", \"end\"]]";
      bot.sendMessageWithInlineKeyboard(chat_id, welcomeMessage, "", keyboardJson);
    } else if (text == "/select_actions") {
      String message = "Please, select next action";
      String keyboardJson = "[[\"Start\", \"/start\"], [\"Goodbye\", \"goodbay\"], [\"End\", \"end\"]]";
      bot.sendMessageWithInlineKeyboard(chat_id, message, "", keyboardJson);
    } else if (text == "/start" || text == "goodbay") {
      bot.sendMessage(chat_id, "You clicked Start or Goodbye", "");
    } else if (text == "end") {
      bot.sendMessage(chat_id, "Goodbye!", "");
    } else {
      Serial.print("User wrote: ");
      Serial.println(text);
    }
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("Starting Telegram Bot...");
}

void loop() {
  int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

  while (numNewMessages) {
    handleNewMessages(numNewMessages);
    numNewMessages = bot.getUpdates(bot.last_message_received + 1);
  }
}

