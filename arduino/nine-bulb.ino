/*
  9 Bulb - A twitter client in 9 bulbs
  by Grant Gibson, created August 2011
  Updated to INO format May 2013
*/

int k = 10;  // for incoming serial data
int pinMap[] = {9, 10, 11, 8, 5, 12, 7, 6, 13}; // logically map the physical pins to left-to-right reading order
int letter_matrix[70][9] = {
  0,0,0,0,0,0,0,0,0, // space
  0,1,0,0,1,0,0,1,0, // !
  0,0,0,0,0,0,0,0,0, // " - set to space
  1,0,1,1,0,1,1,0,1, // #
  0,1,1,0,1,0,1,1,0, // $
  0,0,0,0,1,0,0,0,0, // % - not implemented (middle dot)
  0,0,0,0,1,0,0,0,0, // & - not implemented
  0,1,0,0,1,0,0,0,0, // '
  0,1,0,1,0,0,0,1,0, // (
  0,1,0,0,0,1,0,1,0, // )
  0,1,0,1,0,1,0,1,0, // *
  0,1,0,1,1,1,0,1,0, // +
  0,0,0,0,1,0,1,0,0, // ,
  0,0,0,1,1,1,0,0,0, // -
  0,0,0,0,0,0,0,1,0, // .
  0,0,1,0,1,0,1,0,0, // /
  1,1,1,1,0,1,1,1,1, // 0
  1,1,0,0,1,0,1,1,1, // 1
  1,1,0,0,1,0,0,1,1, // 2
  1,1,1,0,1,1,1,1,1, // 3
  1,0,1,1,1,1,0,0,1, // 4
  0,1,1,0,1,0,1,1,0, // 5
  1,0,0,1,1,1,1,1,1, // 6
  1,1,1,0,0,1,0,0,1, // 7
  0,1,1,1,1,1,1,1,1, // 8
  1,1,1,1,1,1,0,0,1, // 9
  0,1,0,0,0,0,0,1,0, // :
  0,1,0,0,1,0,1,0,0, // ;
  0,0,1,0,1,0,0,0,1, // <
  1,1,1,0,0,0,1,1,1, // =
  1,0,0,0,1,0,1,0,0, // >
  1,1,1,0,1,1,0,1,0, // ?
  0,1,1,1,0,1,0,1,1, // @
  0,1,0,1,1,1,1,0,1, // a
  1,1,0,1,1,1,1,1,1, // b
  1,1,1,1,0,0,1,1,1, // c
  1,1,0,1,0,1,1,1,0, // d
  1,1,1,1,1,0,1,1,1, // e
  1,1,1,1,1,0,1,0,0, // f
  1,1,0,1,0,1,1,1,1, // g
  1,0,1,1,1,1,1,0,1, // h
  1,1,1,0,1,0,1,1,1, // i
  0,0,1,1,0,1,1,1,1, // j
  1,0,1,1,1,0,1,0,1, // k
  1,0,0,1,0,0,1,1,1, // l
  1,1,1,1,1,1,1,0,1, // m
  1,1,1,1,0,1,1,0,1, // n
  1,1,1,1,0,1,1,1,1, // o
  1,1,1,1,1,1,1,0,0, // p
  1,1,1,1,1,1,0,0,1, // q
  1,1,1,1,1,0,1,0,1, // r
  0,1,1,0,1,0,1,1,0, // s
  1,1,1,0,1,0,0,1,0, // t
  1,0,1,1,0,1,1,1,1, // u
  1,0,1,1,0,1,0,1,0, // v
  1,0,1,1,1,1,1,1,1, // w
  1,0,1,0,1,0,1,0,1, // x
  1,0,1,0,1,0,0,1,0, // y
  1,1,0,0,1,0,0,1,1, // z
  1,1,0,1,0,0,1,1,0, // [
  1,0,0,0,1,0,0,0,1, // \
  0,1,1,0,0,1,0,1,1, // ]
  0,1,0,1,0,1,0,0,0, // ^
  0,0,0,0,0,0,1,1,1, // _
  1,0,0,0,1,0,0,0,0, // `
  0,0,1,1,1,0,0,0,1, // {
  0,1,0,0,1,0,0,1,0, // |
  1,0,0,0,1,1,1,0,0, // }
  1,0,1,0,1,0,0,0,0, // ~
};


void setup() {    
  Serial.begin(9600);
  pinMode(2, INPUT); 
  digitalWrite(2, HIGH);
  
  pinMode(5, OUTPUT); 
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);  
  pinMode(13, OUTPUT);    
}

void loop() {
  int buttonValue = digitalRead(2);
  if(buttonValue == 1) {
    modeOne();
  } else {
    modeTwo();
  }
}

void modeOne() {
  // Colour cycles all except middle if outstanding messages
  for(int i=0; i<9; i++) {
    digitalWrite(pinMap[i], HIGH);
  }
  delay(100);       
  if (Serial.available() > 0) {
    digitalWrite(pinMap[0], LOW);
    digitalWrite(pinMap[2], LOW);
    digitalWrite(pinMap[4], LOW);
    digitalWrite(pinMap[6], LOW);
    digitalWrite(pinMap[8], LOW);
  }
}

void modeTwo() {
  int i;
  // Blank the display first
  for(i=0;i<9;i++) {
    digitalWrite(pinMap[i], LOW); 
  }
  delay(100);
  
  if (Serial.available() > 0) {
    int ki = Serial.read();
    Serial.println(ki);
    if(ki == 124) {
      // Pipe separator
      doFlourish();
      k = 0;
    } else if ((ki>=97) && (ki<=122)) {
      // Lowercase alpha, so take away 64
      k = ki - 64; 
    } else if ((ki>=32) && (ki<=126)) {
      // Other displayable ascii char, so take away 32
      k = ki - 32;
    } else {
      // Non-displayable character, so set to space
      k = 0;
    }
  } else {
     k = 0;
  }
  for(i=0;i<9;i++) {
    if(letter_matrix[k][i] == 0) {
      digitalWrite(pinMap[i], LOW); 
    } else {
      digitalWrite(pinMap[i], HIGH); 
    }
  }
  delay(750);
}

void doFlourish() {
  digitalWrite(pinMap[0], HIGH); 
  digitalWrite(pinMap[3], HIGH); 
  digitalWrite(pinMap[6], HIGH); 
  delay(100);
  digitalWrite(pinMap[1], HIGH); 
  digitalWrite(pinMap[4], HIGH); 
  digitalWrite(pinMap[7], HIGH); 
  delay(100);
  digitalWrite(pinMap[2], HIGH); 
  digitalWrite(pinMap[5], HIGH); 
  digitalWrite(pinMap[8], HIGH); 
  delay(100);
  digitalWrite(pinMap[0], LOW); 
  digitalWrite(pinMap[3], LOW); 
  digitalWrite(pinMap[6], LOW);
  delay(100);
  digitalWrite(pinMap[1], LOW); 
  digitalWrite(pinMap[4], LOW); 
  digitalWrite(pinMap[7], LOW);
  delay(100);
  digitalWrite(pinMap[2], LOW); 
  digitalWrite(pinMap[5], LOW); 
  digitalWrite(pinMap[8], LOW);
}
