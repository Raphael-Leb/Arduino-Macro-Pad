#include <BleKeyboard.h>
//#include <BleMouse.h>
#include "pins.h"

BleKeyboard bleKeyboard;
//BleMouse bleMouse;

int lastState = 0;
int currentState = 0;

void setup() {
  // Set up the serial monitor
  Serial.begin(9600);

  bleKeyboard.begin();
  //bleMouse.begin();
  // Set up the row pins as inputs with pull-up resistors
  for (int i = 0; i < NUM_ROWS; i++) {
    pinMode(ROW_PINS[i], INPUT_PULLUP);
  }
  // Set up the column pins as outputs
  for (int i = 0; i < NUM_COLS; i++) {
    pinMode(COL_PINS[i], OUTPUT);
  }

  pinMode(ROT_A, INPUT_PULLUP);
  pinMode(ROT_B, INPUT_PULLUP);

}

void loop() {
  // Read the current state of the rotary encoder
  currentState = digitalRead(ROT_A);

  // Scan each column for button presses
  for (int col = 0; col < NUM_COLS; col++) {
    digitalWrite(COL_PINS[col], LOW);
    for (int row = 0; row < NUM_ROWS; row++) {
      if (digitalRead(ROW_PINS[row]) == LOW) {
        // Button is pressed
        Serial.print("Button ");
        Serial.print(row * NUM_COLS + col);
        Serial.println(" pressed");

        executeShortcut(row, col);

        delay(200); // debounce
      }
      else {
        Serial.println("nothing");
      }
    }
    digitalWrite(COL_PINS[col], HIGH);
  }
    // Check if there's a change in the state of the rotary encoder
  /*if (currentState != lastState) {
    if (digitalRead(ROT_B) != currentState) {
      // Clockwise rotation
      bleMouse.move(0, 0, 1); // Scroll up
      Serial.println("scrolling up");
    } else {
      // Counterclockwise rotation
      bleMouse.move(0, 0, -1); // Scroll down
      Serial.println("scrolling down");
    }
    delay(100); // Delay to debounce the rotary encoder
  }

  lastState = currentState;*/

}

void executeShortcut(int row, int col) {
  const char* shortcutName = keybinds[row][col];
  for (int i = 0; i < NUM_SHORTCUTS; i++) {
    if (strcmp(shortcutNames[i], shortcutName) == 0) {
      const char* shortcutCombo = shortcutCombos[i];
      int comboLength = sizeof(shortcutCombo) / sizeof(shortcutCombo[0]);
      for (int j = 0; j < comboLength; j++) {
        bleKeyboard.press(shortcutCombo[j]);
      }
      delay(200);
      bleKeyboard.releaseAll();
    }
  }
}

