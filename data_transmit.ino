#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define ldr 8

String duration = "";

void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  
  pinMode(ldr, INPUT_PULLUP);
  
  lcd.clear();
  lcd.print("LiFi Project");
  delay(2000);
  
  lcd.clear();
  lcd.print("Send any message");
  lcd.setCursor(0, 1);
  lcd.print("from LiFi App..");
}

void loop() {
  int val = digitalRead(ldr);
  
  // Detects the start bit (when light goes low/0)
  if (val == 0) {
    delay(100); // Small buffer to settle on the bit
    
    while (true) {
      int current_bit = digitalRead(ldr);
      
      // If we see a 1, it means the pulse stream for this specific message has concluded
      if (current_bit == 1) {
        
        // Evaluate the accumulated string BEFORE clearing it
        if (duration == "00") { // Adjusted to match standard app bit length sequences
          Serial.println("Received message: hi");
          lcd.clear();
          lcd.print("hi");
        }
        else if (duration == "000") {
          Serial.println("Received message: hello");
          lcd.clear();
          lcd.print("hello");
        }
        else if (duration == "0000") {
          Serial.println("Received message: how are you?");
          lcd.clear();
          lcd.print("how are you?");
        }
        else if (duration == "00000") {
          Serial.println("Received message: I am fine");
          lcd.clear();
          lcd.print("I am fine");
        }
        else if (duration == "000000") {
          Serial.println("Received message: ok");
          lcd.clear();
          lcd.print("ok");
        }
        else if (duration == "0000000") {
          Serial.println("Received message: good morning");
          lcd.clear();
          lcd.print("good morning");
        }
        else if (duration == "00000000") {
          Serial.println("Received message: good afternoon");
          lcd.clear();
          lcd.print("good afternoon");
        }
        else if (duration == "000000000") {
          Serial.println("Received message: good evening");
          lcd.clear();
          lcd.print("good evening");
        }
        else if (duration == "0000000000") {
          Serial.println("Received message: thank you");
          lcd.clear();
          lcd.print("thank you");
        }
        else if (duration == "00000000000") {
          Serial.println("Received message: sorry");
          lcd.clear();
          lcd.print("sorry");
        }
        
        // Reset the tracker string and exit the listening loop
        duration = ""; 
        break;
      } 
      else {
        // If the bit is still 0, accumulate it
        duration += "0";
      }
      
      // This delay MUST match the millisecond transmit speed configured in your mobile LiFi App
      delay(200); 
    }
  }
}