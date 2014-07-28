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

#define SPACE8x8 { \
    {0, 0, 0, 0, 0, 0, 0, 0},  \
    {0, 0, 0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0, 0} \
}

#define H8x8 { \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {0, 1, 1, 1, 1, 1, 1, 0}, \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {0, 1, 0, 0, 0, 0, 1, 0}  \
}

#define E8x8  { \
    {0, 1, 1, 1, 1, 1, 1, 0}, \
    {0, 1, 0, 0, 0, 0, 0, 0}, \
    {0, 1, 0, 0, 0, 0, 0, 0}, \
    {0, 1, 1, 1, 1, 1, 1, 0}, \
    {0, 1, 0, 0, 0, 0, 0, 0}, \
    {0, 1, 0, 0, 0, 0, 0, 0}, \
    {0, 1, 0, 0, 0, 0, 0, 0}, \
    {0, 1, 1, 1, 1, 1, 1, 0}  \
}

#define L8x8 { \
    {0, 1, 0, 0, 0, 0, 0, 0}, \
    {0, 1, 0, 0, 0, 0, 0, 0}, \
    {0, 1, 0, 0, 0, 0, 0, 0}, \
    {0, 1, 0, 0, 0, 0, 0, 0}, \
    {0, 1, 0, 0, 0, 0, 0, 0}, \
    {0, 1, 0, 0, 0, 0, 0, 0}, \
    {0, 1, 0, 0, 0, 0, 0, 0}, \
    {0, 1, 1, 1, 1, 1, 1, 0}  \
}

#define O8x8 { \
    {0, 0, 0, 1, 1, 0, 0, 0}, \
    {0, 0, 1, 0, 0, 1, 0, 0}, \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {0, 0, 1, 0, 0, 1, 0, 0}, \
    {0, 0, 0, 1, 1, 0, 0, 0}  \
}

#define W8x8 { \
    {1, 0, 0, 0, 0, 0, 1, 0}, \
    {1, 0, 0, 0, 0, 0, 1, 0}, \
    {1, 0, 0, 0, 0, 0, 1, 0}, \
    {1, 0, 0, 1, 0, 0, 1, 0}, \
    {1, 0, 0, 1, 0, 0, 1, 0}, \
    {1, 0, 0, 1, 0, 0, 1, 0}, \
    {0, 1, 0, 1, 0, 1, 0, 0}, \
    {0, 0, 1, 0, 1, 0, 0, 0}  \
}

#define R8x8 { \
    {0, 1, 1, 1, 1, 0, 0, 0}, \
    {0, 1, 0, 0, 0, 1, 0, 0}, \
    {0, 1, 0, 0, 0, 1, 0, 0}, \
    {0, 1, 0, 0, 0, 1, 0, 0}, \
    {0, 1, 1, 1, 1, 0, 0, 0}, \
    {0, 1, 0, 0, 1, 0, 0, 0}, \
    {0, 1, 0, 0, 0, 1, 0, 0}, \
    {0, 1, 0, 0, 0, 0, 1, 0}  \
}

#define D8x8 { \
    {0, 1, 1, 1, 1, 0, 0, 0}, \
    {0, 1, 0, 0, 0, 1, 0, 0}, \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {0, 1, 0, 0, 0, 1, 0, 0}, \
    {0, 1, 1, 1, 1, 0, 0, 0}  \
}

#define EXCLAIM8x8 { \
    {0, 0, 1, 1, 0, 0, 0, 0}, \
    {0, 1, 1, 1, 1, 0, 0, 0}, \
    {0, 1, 1, 1, 1, 0, 0, 0}, \
    {0, 1, 1, 1, 1, 0, 0, 0}, \
    {0, 0, 1, 1, 0, 0, 0, 0}, \
    {0, 0, 1, 1, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0, 0}, \
    {0, 0, 1, 1, 0, 0, 0, 0}  \
}

#define QUESTION8x8 { \
    {0, 0, 1, 1, 1, 1, 0, 0},  \
    {0, 1, 1, 0, 0, 1, 1, 0}, \
    {0, 1, 1, 0, 0, 1, 1, 0}, \
    {0, 0, 0, 0, 0, 1, 1, 0}, \
    {0, 0, 0, 1, 1, 1, 0, 0}, \
    {0, 0, 0, 1, 1, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 1, 1, 0, 0, 0} \
}

#define FULLSTOP8x8 { \
    {0, 0, 0, 0, 0, 0, 0, 0},  \
    {0, 0, 0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0, 0}, \
    {0, 1, 1, 0, 0, 0, 0, 0}, \
    {0, 1, 1, 0, 0, 0, 0, 0} \
}

#define SMILE8x8 { \
    {0, 0, 0, 0, 0, 0, 0, 0},  \
    {0, 0, 0, 0, 0, 0, 0, 0}, \
    {1, 1, 1, 1, 1, 1, 1, 1}, \
    {1, 0, 0, 0, 0, 0, 0, 1}, \
    {1, 0, 0, 0, 0, 0, 0, 1}, \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {0, 0, 1, 1, 1, 1, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0, 0} \
}

#define FROWN8x8 { \
    {0, 0, 0, 0, 0, 0, 0, 0},  \
    {0, 0, 0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 1, 0, 0, 0, 0}, \
    {0, 0, 1, 0, 1, 0, 0, 0}, \
    {0, 1, 0, 0, 0, 1, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0, 0} \
}


byte row = 0;//********** row col change
byte leds[8][8];

// pin[xx] on led matrix connected to nn on Arduino (-1 is dummy to make array start at pos 1)
int pins[17]= {-1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 ,15 ,16 ,17};

// col[xx] of leds = pin yy on led matrix
int cols[8] = {pins[2], pins[8], pins[16], pins[1], pins[12], pins[15], pins[11], pins[14]};
//
// row[xx] of leds = pin yy on led matrix
int rows[8] = {pins[7], pins[6], pins[4], pins[13], pins[3], pins[9], pins[10], pins[5]};
/*
// col[xx] of leds = pin yy on led matrix
int cols[8] = {pins[5], pins[10], pins[9], pins[3], pins[13], pins[4], pins[6], pins[7]};
//
// row[xx] of leds = pin yy on led matrix
int rows[8] = {pins[2], pins[8], pins[16], pins[1], pins[11], pins[15], pins[12], pins[14]};
*/
byte symbols[][8][8] = 
{
  SPACE8x8,SMILE8x8,FROWN8x8,EXCLAIM8x8,QUESTION8x8,FULLSTOP8x8,D8x8,E8x8,H8x8,L8x8,O8x8,R8x8,W8x8
};

enum symbolLib
{
  SPACE,SMILE,FROWN,EXCLAIM,QUESTION,FULLSTOP,D,E,H,L,O,R,W
};



byte patternHelloWorld [] =//start with space
{
  SPACE,H,E,L,L,O,SPACE,W,O,R,L,D,EXCLAIM
};


byte patternTest [] =//start with space
{
  SPACE,SMILE,E,L,L,FROWN,QUESTION,EXCLAIM
};

byte *patternCompendium[] =
{
  patternHelloWorld,patternTest
};

int symbol = 0;
int pattern = 0;
int sequence = 0;
bool slide = false;

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

  setSymbol(1);//smile
  
  
  Serial.begin(9600);

}

void loop() {
  
  while(Serial.available() > 0)
  {
    int input = Serial.parseInt();
    Serial.print("loop");
    Serial.println(input);
    
    //if (Serial.read() == '/n')
    {
      if(input == 1)
      {
        sequence = 0;
        slide = true;

      }
      else
      {
        if(input == 4)
        {
          sequence = 1;
          slide = true;
        }
        pattern = 0; //beginning of hello world
        
        
      }
      if(input == 2)
      {
        slide = false;
        setSymbol(1);
        Serial.println("set smile");
      }
      if(input == 3)
      {
        slide = false;
        setSymbol(2);
        Serial.println("set frown");
      }
      
      
    }
  }
  if(slide)
  {
    Serial.println(sizeof(&patternCompendium[0]));
    pattern = ++pattern;
    if(pattern > sizeof(patternCompendium[sequence]))//end of hello world!
    {
      pattern = 0;//beginning of hello world
    }
    slidePatternLeft(sequence, pattern, 60);  
  }
}

void clearLeds() {
  // Clear display array
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      leds[i][j] = 0;
    }
  }
}

void setSymbol(int symbol) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      leds[i][j] = symbols[symbol][i][j];
    }
  }
}

void slidePatternLeft(int sequence, int pattern, int del) {
  for (int l = 0; l < 8; l++) //L
  {
    for (int i = 0; i < 7; i++) 
    {
      for (int j = 0; j < 8; j++) 
      {
        leds[j][i] = leds[j][i+1]; //#1
      }
    }
    for (int j = 0; j < 8; j++) 
    {
      leds[j][7] = symbols[patternCompendium[sequence][pattern]][j][0 + l];//L
    }
    delay(del);
  }
}

void slidePatternUp(int pattern, int del)
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
      leds[7][j] = symbols[patternHelloWorld[pattern]][0+l][j];//L
    }
    delay(del);
  }
}  


// Interrupt routine
void display() {
  digitalWrite(rows[row], HIGH);
  //digitalWrite(cols[col], LOW);  // Turn whole previous column off
  row++;
  if (row == 8) {
    row = 0;
  }
  for (int col = 0; col < 8; col++) {
    if (leds[col][7 - row] == 1) {
        digitalWrite(cols[col], HIGH);
        //digitalWrite(rows[row], LOW);  // Turn on this led
    }
    else {
      digitalWrite(cols[col], LOW); // Turn off this led
    }
  }
  digitalWrite(rows[row], LOW); // Turn whole column on at once (for equal lighting times)
}
/* //old version
void display() {
  digitalWrite(cols[col], LOW);  // Turn whole previous column off
  col++;
  if (col == 8) {
    col = 0;
  }
  for (int row = 0; row < 8; row++) {
    if (leds[col][7 - row] == 1) {
        digitalWrite(rows[row], LOW);  // Turn on this led
    }
    else {
      digitalWrite(rows[row], HIGH); // Turn off this led
    }
  }
  digitalWrite(cols[col], HIGH); // Turn whole column on at once (for equal lighting times)
}
*/
