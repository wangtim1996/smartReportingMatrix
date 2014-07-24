/*
 * Show messages on an 8x8 led matrix,
 * scrolling from right to left.
 *
 * Uses FrequencyTimer2 library to
 * constantly run an interrupt routine
 * at a specified frequency. This
 * refreshes the display without the
 * main loop having to do anything.
 *
 */

#include <FrequencyTimer2.h>

#define SPACE { \
    {0, 0, 0, 0, 0, 0, 0, 0},  \
    {0, 0, 0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0, 0} \
}

#define H { \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {0, 1, 1, 1, 1, 1, 1, 0}, \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {0, 1, 0, 0, 0, 0, 1, 0}  \
}

#define E  { \
    {0, 1, 1, 1, 1, 1, 1, 0}, \
    {0, 1, 0, 0, 0, 0, 0, 0}, \
    {0, 1, 0, 0, 0, 0, 0, 0}, \
    {0, 1, 1, 1, 1, 1, 1, 0}, \
    {0, 1, 0, 0, 0, 0, 0, 0}, \
    {0, 1, 0, 0, 0, 0, 0, 0}, \
    {0, 1, 0, 0, 0, 0, 0, 0}, \
    {0, 1, 1, 1, 1, 1, 1, 0}  \
}

#define L { \
    {0, 1, 0, 0, 0, 0, 0, 0}, \
    {0, 1, 0, 0, 0, 0, 0, 0}, \
    {0, 1, 0, 0, 0, 0, 0, 0}, \
    {0, 1, 0, 0, 0, 0, 0, 0}, \
    {0, 1, 0, 0, 0, 0, 0, 0}, \
    {0, 1, 0, 0, 0, 0, 0, 0}, \
    {0, 1, 0, 0, 0, 0, 0, 0}, \
    {0, 1, 1, 1, 1, 1, 1, 0}  \
}

#define O { \
    {0, 0, 0, 1, 1, 0, 0, 0}, \
    {0, 0, 1, 0, 0, 1, 0, 0}, \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {0, 0, 1, 0, 0, 1, 0, 0}, \
    {0, 0, 0, 1, 1, 0, 0, 0}  \
}

#define W { \
    {1, 0, 0, 0, 0, 0, 1, 0}, \
    {1, 0, 0, 0, 0, 0, 1, 0}, \
    {1, 0, 0, 0, 0, 0, 1, 0}, \
    {1, 0, 0, 1, 0, 0, 1, 0}, \
    {1, 0, 0, 1, 0, 0, 1, 0}, \
    {1, 0, 0, 1, 0, 0, 1, 0}, \
    {0, 1, 0, 1, 0, 1, 0, 0}, \
    {0, 0, 1, 0, 1, 0, 0, 0}  \
}

#define R { \
    {0, 1, 1, 1, 1, 0, 0, 0}, \
    {0, 1, 0, 0, 0, 1, 0, 0}, \
    {0, 1, 0, 0, 0, 1, 0, 0}, \
    {0, 1, 0, 0, 0, 1, 0, 0}, \
    {0, 1, 1, 1, 1, 0, 0, 0}, \
    {0, 1, 0, 0, 1, 0, 0, 0}, \
    {0, 1, 0, 0, 0, 1, 0, 0}, \
    {0, 1, 0, 0, 0, 0, 1, 0}  \
}

#define D { \
    {0, 1, 1, 1, 1, 0, 0, 0}, \
    {0, 1, 0, 0, 0, 1, 0, 0}, \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {0, 1, 0, 0, 0, 1, 0, 0}, \
    {0, 1, 1, 1, 1, 0, 0, 0}  \
}

#define EXCLAIM { \
    {0, 0, 1, 1, 0, 0, 0, 0}, \
    {0, 1, 1, 1, 1, 0, 0, 0}, \
    {0, 1, 1, 1, 1, 0, 0, 0}, \
    {0, 1, 1, 1, 1, 0, 0, 0}, \
    {0, 0, 1, 1, 0, 0, 0, 0}, \
    {0, 0, 1, 1, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0, 0}, \
    {0, 0, 1, 1, 0, 0, 0, 0}  \
}
/*
#define SMILE { \
    {0, 0, 0, 0, 0, 0, 0, 0},  \
    {0, 0, 1, 0, 0, 1, 0, 0}, \
    {0, 0, 1, 0, 0, 1, 0, 0}, \
    {0, 0, 1, 0, 0, 1, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0, 0}, \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {0, 0, 1, 1, 1, 1, 0, 0} \
}
*/
#define SMILE { \
    {1, 0, 0, 0, 1, 0, 0, 1},  \
    {1, 1, 0, 0, 1, 0, 1, 0}, \
    {1, 1, 1, 0, 0, 0, 0, 0}, \
    {1, 1, 1, 1, 0, 0, 0, 0}, \
    {1, 1, 1, 1, 1, 0, 0, 0}, \
    {1, 1, 1, 1, 1, 1, 0, 0}, \
    {1, 1, 1, 1, 1, 1, 1, 0}, \
    {1, 1, 1, 1, 1, 1, 1, 1} \
}


byte col = 0;
byte leds[8][8];

// pin[xx] on led matrix connected to nn on Arduino (-1 is dummy to make array start at pos 1)
int pins[17]= {-1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 ,15 ,16 ,17};

// col[xx] of leds = pin yy on led matrix
int cols[8] = {pins[5], pins[10], pins[9], pins[3], pins[13], pins[4], pins[6], pins[7]};
//
// row[xx] of leds = pin yy on led matrix
int rows[8] = {pins[14], pins[11], pins[15], pins[12], pins[1], pins[16], pins[8], pins[2]};
/*
// col[xx] of leds = pin yy on led matrix
int cols[8] = {pins[2], pins[8], pins[16], pins[1], pins[11], pins[15], pins[12], pins[14]};
//
// row[xx] of leds = pin yy on led matrix
int rows[8] = {pins[7], pins[6], pins[4], pins[13], pins[3], pins[9], pins[10], pins[5]};
//**************** above is being used for "right side up"
// col[xx] of leds = pin yy on led matrix
int cols[8] = {pins[5], pins[10], pins[9], pins[3], pins[13], pins[4], pins[6], pins[7]};
//
// row[xx] of leds = pin yy on led matrix
int rows[8] = {pins[2], pins[8], pins[16], pins[1], pins[11], pins[15], pins[12], pins[14]};
*/
const int numPatterns = 15;
byte patterns[numPatterns][8][8] = {
  SMILE,SPACE,H,E,L,L,O,SPACE,W,O,R,L,D,EXCLAIM,SPACE
};

int pattern = 0;

void setup() {
  // sets the pins as output
  for (int i = 1; i <= 16; i++) {
    pinMode(pins[i], OUTPUT);
  }

  // set up cols and rows
  for (int i = 1; i <= 8; i++) {
    digitalWrite(cols[i - 1], LOW);
  }

  for (int i = 1; i <= 8; i++) {
    digitalWrite(rows[i - 1], LOW);
  }

  clearLeds();

  // Turn off toggling of pin 11
  FrequencyTimer2::disable();
  // Set refresh rate (interrupt timeout period)
  FrequencyTimer2::setPeriod(2000);
  // Set interrupt routine to be called
  FrequencyTimer2::setOnOverflow(display);

  setPattern(pattern);
}

void loop() {
    pattern = ++pattern % numPatterns;
    //slidePattern(pattern, 60);
}

void clearLeds() {
  // Clear display array
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      leds[i][j] = 0;
    }
  }
}

void setPattern(int pattern) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      leds[i][j] = patterns[pattern][j][i];//row column switch
    }
  }
}

void slidePattern(int pattern, int del) 
{
  for (int l = 0; l < 8; l++) //L
  {
    for (int i = 0; i < 8; i++) 
    {
      for (int j = 0; j < 7; j++) 
      {
        leds[j][i] = leds[j+1][i]; //#1
      }
    }
    for (int j = 0; j < 8; j++) 
    {
      leds[7][j] = patterns[pattern][j][0+l];//L // row column switch
    }
    delay(del);
  }
}

// Interrupt routine
void display() {
  digitalWrite(cols[col], HIGH);  // Turn whole previous column off
  col++;
  if (col == 8) {
    col = 0;
  }
  for (int row = 0; row < 8; row++) {
    if (leds[col][7 - row] == 1) {
        digitalWrite(rows[row], HIGH);  // Turn on this led
    }
    else {
      digitalWrite(rows[row], LOW); // Turn off this led
    }
  }
  digitalWrite(cols[col], LOW); // Turn whole column on at once (for equal lighting times)
}
