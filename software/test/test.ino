#include "Keyboard.h"
#include "Mouse.h"
#include "pins.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

volatile int lastEncoded = 0;
volatile long encoderValue = 0;

int activeKeybindSet = 0;

void setup() {
  // Set up the serial monitor
  Serial.begin(9600);

  Mouse.begin();
  Keyboard.begin();

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
  pinMode(ROT_CLK, INPUT_PULLUP);

  Wire.begin();

  // Initialize the SSD1306 display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 initialization failed"));
    while (1); // Stop here if the display couldn't be initialized
  }
 attachInterrupt(digitalPinToInterrupt(ROT_A), updateEncoder, CHANGE);
attachInterrupt(digitalPinToInterrupt(ROT_B), updateEncoder, CHANGE);
  
  displayKeybinds();
}

void loop() {
  // change keybind set
  if (digitalRead(ROT_CLK) == LOW) {
    activeKeybindSet++;
    if (activeKeybindSet >= NUM_KEYBIND_SETS) {
      activeKeybindSet = 0;
    }
    displayKeybinds(); // Update the display with the new keybind set
    delay(200); // debounce
  }

  // Scan each column for button presses
  for (int col = 0; col < NUM_COLS; col++) {
    digitalWrite(COL_PINS[col], LOW);
    for (int row = 0; row < NUM_ROWS; row++) {
      if (digitalRead(ROW_PINS[row]) == LOW) {
        // Button is pressed
        Serial.print("Row ");
        Serial.print(row);
        Serial.print(" Col ");
        Serial.print(col);
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

  updateEncoder();

}

void executeShortcut(int row, int col) {
  const char* shortcutName = keybinds[activeKeybindSet][row][col];
  for (int i = 0; i < NUM_SHORTCUTS; i++) {
    if (strcmp(shortcutNames[i], shortcutName) == 0) {
      const char* shortcutCombo = shortcutCombos[i];
      int comboLength = 2; // Length of shortcutCombo, modify when adding longer shortcuts
      for (int j = 0; j < comboLength; j++) {
        Keyboard.press(shortcutCombo[j]);
        delay(10);
      }
      delay(200);
      Keyboard.releaseAll();
    }
  }
}

void displayKeybinds(){
  display.clearDisplay(); // Clear the display
  display.setRotation(2);
  display.setTextSize(1.5); // Set text size
  display.setTextColor(SSD1306_WHITE); // Set text color
  display.drawRect(2, 2, 100, 62, SSD1306_WHITE);
  display.drawCircle(114, 32, 9, SSD1306_WHITE);
  int cursorx = 5, cursory = 5;
  display.setCursor(cursorx, cursory); // Set cursor position

  // this it how this should work if i hadn't done the wiring while high off my ass 
  /*for (int col = 0; col < NUM_COLS; col++){
    for (int row = 0; row < NUM_ROWS; row++){
      display.setCursor(cursorx, cursory);
      display.print(keybinds[row][col]);
      cursory += 10;
    }
    cursorx = 50;
    cursory = 5;
  }*/

  for (int row = 0; row < NUM_ROWS; row++){
      display.setCursor(cursorx, cursory);
      display.print(keybinds[activeKeybindSet][row][1]);
      cursorx += 50;
      if (row==1){
        cursorx = 5;
        cursory += 15;
      }
  }
  cursorx = 5;
  cursory = 35;
  for (int row = 0; row < NUM_ROWS; row++){
    display.setCursor(cursorx, cursory);
    display.print(keybinds[activeKeybindSet][row][0]);
    cursorx += 50;
    if (row==1){
      cursorx = 5;
      cursory += 15;
    }
  }

  display.display();
}

void updateEncoder() {
  int MSB = digitalRead(ROT_A); // Most significant bit
  int LSB = digitalRead(ROT_B); // Least significant bit

  int encoded = (MSB << 1) | LSB;
  int sum = (lastEncoded << 2) | encoded;

  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) {
    encoderValue++;
    // Clockwise rotation
    Mouse.move(0, 0, -1); // Scroll up
    Serial.println("Scrolling up");
  } else if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) {
    encoderValue--;
    // Counterclockwise rotation
    Mouse.move(0, 0, 1); // Scroll down
    Serial.println("Scrolling down");
  }

  lastEncoded = encoded;
}

////////////////////   