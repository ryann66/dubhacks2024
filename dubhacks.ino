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

#define MAX_LEN 3
#define MAX_KEYNUM 9
char charsOfKeynumLens[MAX_LEN][MAX_KEYNUM] = {{'a', 'b', 'c'}, {'d', 'e', 'f'}}

//initialize an instance of class NewKeypad
Keypad customKeypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

char buf[BUFLEN];

keynum stkchar;
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

/**
 * Gets the char that the current stack represents
 * returns ' ' if the stack is empty
 */
char getstkchr();

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

void flushStack() {

}

void logPress(keynum k) {
  // push key onto the stack
  if (stklen && stkchar != k) {
    flushStack();
  }
  stkchar = k;
  stklen++;
  
  // check if stack is full
  if (stkchar == 0 || (stklen == 3 && (stkchr == 7 || stkchr == 9)) || stklen == 4) {
    // stack full
    flushStack();
  }
}

void deleteChar() {

}

void clearBuffer() {
  buf[0] = 0;
  stklen = 0;
}

char getstkchr() {
  if (stklen == 0  || stkchr == 0) {
    return ' ';
  }
  if (stklen == 4) {
    if (stkchr == 7) return 's';
    if (stkchr == 9) return 'z';
    // assert unreachable
  }

  // stklen <= 3
  uint8_t chr = stkchr - 1;
  uint8_t len = stklen - 1;

}
