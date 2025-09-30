#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD address (0x27 or 0x3F usually)
LiquidCrystal_I2C lcd(0x27, 16, 2);

String message1 = "AEGIS GUARD";  // Top line
String message2 = "SHIELD ENABLED!"; // Final message with glitch
// Sequence of messages to show before final
String preMessages[] = {
  "ANALOG EMERGENCY",
  "AND",
  "GAS INTEGRATED",
  "SAFETY GUARD"
};
int numPreMessages = sizeof(preMessages)/sizeof(preMessages[0]);

void setup() {
  // Initialize LCD
  Wire.begin(21, 22);   // ESP32 default SDA=21, SCL=22
  lcd.init();
  lcd.backlight();
  lcd.clear();

  int lcdColumns = 16;
  int msgLength = message1.length();

  // --- Scroll first message ---
  for (int pos = lcdColumns; pos >= -msgLength; pos--) {
    lcd.clear();
    if (pos >= 0) {
      lcd.setCursor(pos, 0);
    } else {
      lcd.setCursor(0, 0);
    }
    lcd.print(message1);
    delay(200); // adjust speed
  }

  // Fix first message on top line
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(message1);

  // --- Display pre-messages one by one on second line ---
  for (int i = 0; i < numPreMessages; i++) {
    lcd.setCursor(0, 1);
    lcd.print(preMessages[i]);
    delay(1000);               // display for 1 second
    lcd.setCursor(0, 1);
    lcd.print("                "); // clear second line
    delay(200);                // small gap between messages
  }

  // --- Glitch effect for final message ---
  for (int i = 0; i < 6; i++) {  
    lcd.setCursor(0, 1);
    if (i % 2 == 0) {
      lcd.print(message2.substring(0,16)); // glitch text
    } else {
      lcd.print("                "); // clear row
    }
    delay(150);
  }

  // Show final stable message
  lcd.setCursor(0, 1);
  lcd.print(message2.substring(0, 16)); // only first 16 chars fit
}

void loop() {
  // nothing - messages stay until power off
}
