#include <LiquidCrystal.h>
#include <Keypad.h>

#define BUFLEN 256
#define LCD_COLS 16
#define LCD_ROWS 2

enum keynum : char {
  STAR = 10, POUND = 11, A = 12, B = 13, C = 14, D = 15, ZERO = 16
};

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
keynum hexaKeys[ROWS][COLS] = {
  {STAR,ZERO,POUND,D}
  {7,8,9,C},
  {4,5,6,B},
  {1,2,3,A},
};
byte rowPins[ROWS] = {43, 41, 39, 37}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {42, 40, 38, 36}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

char buf[BUFLEN];
char* bufend = buf;

keynum stkchr;
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
  lcd.begin(LCD_COLS, LCD_ROWS, LCD_5x8DOTS);
  lcd.blink();
}
  
void loop(){
  keynum kp = customKeypad.waitForKey();
  //Serial.println("<<<<<<<<<<<<< Read keynum >>>>>>>>>>>>");
  //Serial.println(kp);
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
  if (stklen == 0) return;
  char c = getstkchr();
  if (bufend - buf < BUFLEN) {
    *bufend++ = c;
    *bufend = 0;
  }
  stklen = 0;
  return;
}

void printScreen() {
  lcd.clear();
  
  // Number chars to print determines cursor loc. Print up to
  // LCD_COLS - 1 chars from buf.
  char* toPrint = max(bufend - LCD_COLS + 1, buf);
  int toPrintLen = strlen(toPrint);
  
  Serial.println("<<<<<<<<<<<<< To Print >>>>>>>>>>>>");
  Serial.println(toPrint);

  // Allow space for all of toPrint plus the nextChar
  lcd.setCursor(LCD_COLS - 1 - toPrintLen, 0);
  lcd.print(toPrint);

  // Print placement character
  lcd.setCursor(LCD_COLS - 1, 0);
  
  char nextChar = getstkchr();
  lcd.print(nextChar);

  Serial.println("<<<<<<<<<<<<< Next Char >>>>>>>>>>>>");
  Serial.println(nextChar);
}

void logPress(keynum k) {
  // push key onto the stack
  if (stklen && stkchr != k) {
    flushStack();
  }
  stkchr = k;
  stklen++;
  
  // check if stack is full
  if (stkchr == ZERO || (stklen == 3 && !(stkchr == 7 || stkchr == 9)) || stklen == 4) {
    // stack full
    flushStack();
  }
}

void deleteChar() {
  if (bufend == buf) return;

  bufend--;
  *bufend = 0;
}

void clearBuffer() {
  buf[0] = 0;
  bufend = buf;
  stklen = 0;
}

char getstkchr() {
  Serial.println("<<<<<<<<<<<<< stack len >>>>>>>>>>>>");
  Serial.println(stklen);
  Serial.println("<<<<<<<<<<<<< stack chr >>>>>>>>>>>>");
  Serial.println(stkchr);

  if (stklen == 0  || stkchr == ZERO) {
    return ' ';
  }

  // stklen <= 3
  // stkchr <= 9 && stkchr > 0
  switch (stklen) {
    case 1:
      switch (stkchr) {
        case 2: return 'a';
        case 3: return 'd';
        case 4: return 'g';
        case 5: return 'j';
        case 6: return 'm';
        case 7: return 'p';
        case 8: return 't';
        case 9: return 'w';
      }
      break;
    case 2:
      switch (stkchr) {
        case 2: return 'b';
        case 3: return 'e';
        case 4: return 'h';
        case 5: return 'k';
        case 6: return 'n';
        case 7: return 'q';
        case 8: return 'u';
        case 9: return 'x';
      }
      break;
    case 3:
      switch (stkchr) {
        case 2: return 'c';
        case 3: return 'f';
        case 4: return 'i';
        case 5: return 'l';
        case 6: return 'o';
        case 7: return 'r';
        case 8: return 'v';
        case 9: return 'y';
      }
      break;
    case 4:
      if (stkchr == 7) return 's';
      if (stkchr == 9) return 'z';
      break;
  }
  Serial.println("Failure: invalid stack char");
  Serial.print("stkchr: "); Serial.println(stkchr);
  Serial.print("stklen: "); Serial.println(stklen);
  delay(1000);
  exit(0);
}
