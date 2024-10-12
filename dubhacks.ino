#include <LiquidCrystal.h>
#include <Keypad.h>

#define BUFLEN 256

enum keynum : char {
  STAR = 10, POUND = 11, A = 12, B = 13, C = 14, D = 15
};

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
keynum hexaKeys[ROWS][COLS] = {
  {1,2,3,A},
  {4,5,6,B},
  {7,8,9,C},
  {STAR,0,POUND,D}
};
byte rowPins[ROWS] = {43, 41, 39, 37}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {40, 38, 36, 34}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

char buf[BUFLEN];

char stkchar;
uint8_t stklen;

/*
 * Flushes the keystroke stack, appending the created char to output
 * Does nothing if stack is empty
 */
void flushStack();

/*
 * Prints the buffer to the screen
 * Also prints the last char on the stack
 */
void printScreen();

/**
 * Adds a non-operator keypress
 */
void logPress(keynum k);

/**
 * Removes a character (either clears buffer or deletes char)
 */
void deleteChar();

/**
 * Clears the buffer and empties the stack
 */
void clearBuffer();

void setup(){
  Serial.begin(9600);
}
  
void loop(){
  keynum kp = waitForKey();
  switch (kp) {
    case A:
      break;
    case B:
      break;
    case C:
      clearBuffer();
      break;
    case D:
      break;
    case POUND:
      flushStack();
      break;
    case STAR:
      deleteChar();
      break;
    default:
      logPress(kp);
  }
  printScreen();
}