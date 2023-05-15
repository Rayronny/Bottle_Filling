#include <Keypad.h>
#include <ezOutput.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(A2, A1, 10, 11, 12, 13);

#define RELAY_PIN  A0 // the Arduino pin, which connects to the IN pin of relay
#define RELAY_PIN  A1 // the Arduino pin, which connects to the IN pin of relay
#define RELAY_PIN  A2 // the Arduino pin, which connects to the IN pin of relay
#define RELAY_PIN  A0 // the Arduino pin, which connects to the IN pin of relay
#define ROW_NUM    4  // four rows
#define COLUMN_NUM 4  // four columns
#define RELAY_ON_TIME 5000 // in milliseconds
int buzzer_pin=A3;

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte pin_rows[ROW_NUM] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );
ezOutput relay(RELAY_PIN);

const String password_1 = "1"; // change your password here
const String password_2 = "2";  // change your password here
const String password_3 = "3";   // change your password here
String input_password;

void setup() {
  Serial.begin(9600);
  input_password.reserve(32); // maximum password size is 32, change if needed
  relay.low();
    // set up the LCD's number of columns and rows:
  lcd.begin(16, 4);
  pinMode(buzzer_pin, OUTPUT); 

  // Clears the LCD screen
  lcd.clear();
      lcd.setCursor(0, 0);
    lcd.print(" SEMI AUTOMATIC");
    lcd.setCursor(0, 1);
    lcd.print(" BOTTLE FILLING");
        lcd.setCursor(0, 2);
    lcd.print("    MACHINE    ");
        lcd.setCursor(0, 3);
    lcd.print("    CUT HUB");
    delay(5000);
}

void loop() {
  key_1();
  key_2();
  key_3();
  }



void key_1()
{
  relay.loop(); // MUST call the loop() function first
  char key = keypad.getKey();

  if (key) {
    Serial.println(key);
    lcd.clear();
    lcd.setCursor(0, 1);
     lcd.println(key);

    if (key == '*') {
      input_password = ""; // reset the input password
    } else if (key == '#') {
      if (input_password == password_1 ) {
        Serial.println("The password is correct, turning ON pump");
            lcd.clear();
    lcd.setCursor(0, 0);
   lcd.println("The password is");
       lcd.setCursor(0,1 );
   lcd.println("correct, turning");
       lcd.setCursor(0, 2);
   lcd.println("ON relay");
        relay.low(); // set low before making a high pulse
        relay.pulse(RELAY_ON_TIME); // turn on relay in RELAY_ON_TIME duration and then turn off
        //delay(1000);
        digitalWrite(buzzer_pin,HIGH);
        delay(5000);
        digitalWrite(buzzer_pin,LOW);
      } else {
        Serial.println("The password is incorrect, try again");
      }

      input_password = ""; // reset the input password
    } else {
      input_password += key; // append new character to input password string
    }
  }
}



void key_2()

{
  relay.loop(); // MUST call the loop() function first
  char key = keypad.getKey();

  if (key) {
    Serial.println(key);

    if (key == '*') {
      input_password = ""; // reset the input password
    } else if (key == '#') {
      if (input_password == password_2 ) {
        Serial.println("The password is correct, turning ON relay");
        relay.low(); // set low before making a high pulse
        relay.pulse(RELAY_ON_TIME); // turn on relay in RELAY_ON_TIME duration and then turn off
      } else {
        Serial.println("The password is incorrect, try again");
      }

      input_password = ""; // reset the input password
    } else {
      input_password += key; // append new character to input password string
    }
  }
}


void key_3()

{
  relay.loop(); // MUST call the loop() function first
  char key = keypad.getKey();

  if (key) {
    Serial.println(key);

    if (key == '*') {
      input_password = ""; // reset the input password
    } else if (key == '#') {
      if (input_password == password_1 || input_password == password_2 || input_password == password_3) {
        Serial.println("The password is correct, turning ON relay");
        relay.low(); // set low before making a high pulse
        relay.pulse(RELAY_ON_TIME); // turn on relay in RELAY_ON_TIME duration and then turn off
      } else {
        Serial.println("The password is incorrect, try again");
      }

      input_password = ""; // reset the input password
    } else {
      input_password += key; // append new character to input password string
    }
  }
}
