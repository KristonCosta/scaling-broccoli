#include <Keyboard.h>
#include <elapsedMillis.h>

#define KEY_LAYER 0x00
#define KEY_NULL 0x00
#define KEY_SPACE 0x20
#define KEY_COMMA 0x2C
#define KEY_FORWARD_SLASH 0x2F
#define KEY_PERIOD 0x2E
#define KEY_DASH 0x2D
#define KEY_EQUALS 0x3D
#define KEY_QUOTE 0x27
#define KEY_SEMICOLON 0x3B
#define KEY_LEFT_BRACKET 0x5B
#define KEY_RIGHT_BRACKET 0x5D

#define KEY_A 0x61
#define KEY_B 0x62
#define KEY_C 0x63
#define KEY_D 0x64
#define KEY_E 0x65
#define KEY_F 0x66
#define KEY_G 0x67
#define KEY_H 0x68
#define KEY_I 0x69
#define KEY_J 0x6A
#define KEY_K 0x6B
#define KEY_L 0x6C
#define KEY_M 0x6D
#define KEY_N 0x6E
#define KEY_O 0x6F
#define KEY_P 0x70
#define KEY_Q 0x71
#define KEY_R 0x72
#define KEY_S 0x73
#define KEY_T 0x74
#define KEY_U 0x75
#define KEY_V 0x76
#define KEY_W 0x77
#define KEY_X 0x78
#define KEY_Y 0x79
#define KEY_Z 0x7A

#define KEY_0 0x30
#define KEY_1 0x31
#define KEY_2 0x32
#define KEY_3 0x33
#define KEY_4 0x34
#define KEY_5 0x35
#define KEY_6 0x36
#define KEY_7 0x37
#define KEY_8 0x38
#define KEY_9 0x39 

uint8_t layer1[4][12] = {{KEY_ESC, KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T, KEY_Y, KEY_U, KEY_I, KEY_O, KEY_P, KEY_BACKSPACE},
                         {KEY_TAB, KEY_A, KEY_S, KEY_D, KEY_F, KEY_G, KEY_H, KEY_J, KEY_K, KEY_L, KEY_SEMICOLON, KEY_QUOTE},
                         {KEY_LEFT_SHIFT, KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B, KEY_N, KEY_M, KEY_COMMA, KEY_PERIOD, KEY_FORWARD_SLASH, KEY_RETURN},
                         {KEY_LEFT_CTRL, KEY_LEFT_ALT, KEY_HOME, KEY_END, KEY_LAYER, KEY_SPACE, KEY_SPACE, KEY_LAYER, KEY_LEFT_BRACKET, KEY_RIGHT_BRACKET, KEY_DASH, KEY_EQUALS}};

uint8_t layer2[4][12] = {{KEY_ESC, KEY_1,KEY_2,KEY_3,KEY_4,KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0,KEY_BACKSPACE},
                         {KEY_TAB, KEY_A, KEY_S, KEY_D, KEY_F, KEY_G, KEY_H, KEY_J, KEY_UP_ARROW, KEY_L, KEY_SEMICOLON, KEY_QUOTE},
                         {KEY_LEFT_SHIFT, KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B, KEY_N, KEY_LEFT_ARROW, KEY_DOWN_ARROW, KEY_RIGHT_ARROW, KEY_FORWARD_SLASH, KEY_RETURN},
                         {KEY_LEFT_CTRL, KEY_LEFT_ALT, KEY_HOME, KEY_END, KEY_LAYER, KEY_SPACE, KEY_SPACE, KEY_LAYER, KEY_LEFT_BRACKET, KEY_RIGHT_BRACKET, KEY_DASH, KEY_EQUALS}};

uint8_t layer3[4][12] = {{KEY_ESC, KEY_F1,KEY_F2,KEY_F3,KEY_F4,KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10,KEY_BACKSPACE},
                         {KEY_TAB, KEY_A, KEY_S, KEY_D, KEY_F, KEY_G, KEY_H, KEY_J, KEY_UP_ARROW, KEY_L, KEY_SEMICOLON, KEY_QUOTE},
                         {KEY_LEFT_SHIFT, KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B, KEY_N, KEY_LEFT_ARROW, KEY_DOWN_ARROW, KEY_RIGHT_ARROW, KEY_FORWARD_SLASH, KEY_RETURN},
                         {KEY_LEFT_CTRL, KEY_LEFT_ALT, KEY_HOME, KEY_END, KEY_LAYER, KEY_SPACE, KEY_SPACE, KEY_LAYER, KEY_LEFT_BRACKET, KEY_RIGHT_BRACKET, KEY_DASH, KEY_EQUALS}};

uint8_t layer4[4][12] = {{KEY_ESC, KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T, KEY_Y, KEY_U, KEY_I, KEY_O, KEY_P, KEY_BACKSPACE},
                         {KEY_TAB, KEY_A, KEY_S, KEY_D, KEY_F, KEY_G, KEY_H, KEY_J, KEY_UP_ARROW, KEY_L, KEY_SEMICOLON, KEY_QUOTE},
                         {KEY_LEFT_SHIFT, KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B, KEY_N, KEY_LEFT_ARROW, KEY_DOWN_ARROW, KEY_RIGHT_ARROW, KEY_FORWARD_SLASH, KEY_RETURN},
                         {KEY_LEFT_CTRL, KEY_LEFT_ALT, KEY_HOME, KEY_END, KEY_LAYER, KEY_SPACE, KEY_SPACE, KEY_LAYER, KEY_LEFT_BRACKET, KEY_RIGHT_BRACKET, KEY_DASH, KEY_EQUALS}};
           
                   //      {KEY_ESC,KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_DELETE},
                        
uint8_t (*currentLayer)[12];

bool function1Pressed = false;
bool function2Pressed = false;
bool functionLock = false;

elapsedMillis lockTimer;
unsigned int lockDelay = 500;

bool pressed[4][12] = {{false, false, false, false, false, false, false, false, false, false, false, false},
                      {false, false, false, false, false, false, false, false, false, false, false, false},
                      {false, false, false, false, false, false, false, false, false, false, false, false},
                      {false, false, false, false, false, false, false, false, false, false, false, false}};

int columnList[12] = { 6, 7, 8, 9, 10, 11, 12, 13, A0, A1, A2, A3 };
int rowList[4] = { 2, 3, 4, 5 };

void setup() {
  // put your setup code here, to run once:
  for (int thisPin = 0; thisPin < 4; thisPin++) {
      pinMode(rowList[thisPin], INPUT);
  }
  
  for (int thisPin = 0; thisPin < 12; thisPin++) {
    pinMode(columnList[thisPin], OUTPUT); 
  }
  Keyboard.begin();
  currentLayer = layer1;
}

void clearPresses() {
  Keyboard.releaseAll();
  for (int i = 0; i < 12; i++){
    for (int j = 0; j < 4; j++){
      pressed[j][i] = false;
    }
  }
}

void loop() {

  int buttonState;
  int f1State; 
  int f2State;

  digitalWrite(13,HIGH);
  f1State = digitalRead(5);
  digitalWrite(13,LOW);

  digitalWrite(10,HIGH);
  f2State = digitalRead(5);
  digitalWrite(10,LOW);

  if ((f2State == HIGH) && (f1State == HIGH)){
    if (!functionLock) {
      clearPresses();
      functionLock = true;
      lockTimer = 0;
      currentLayer = layer4;
    }
  }

  if (!((f2State == HIGH) && (f1State == HIGH))){
    if ((f1State == HIGH) or (f2State == HIGH)) {
      if (functionLock && (lockTimer > lockDelay)) {
        lockTimer = 0;
        clearPresses();
        functionLock = false;
        currentLayer = layer1;
      }
    }
  }

  if ((f2State == HIGH) && !(f1State == HIGH)){
    if (!functionLock) {
      if (!function2Pressed) {
        clearPresses();
        function2Pressed = true;
        currentLayer = layer3;
      }
    }
  }

  if (!(f2State == HIGH) && (f1State == HIGH)){
    if (!functionLock) {
      if (!function1Pressed) {
        clearPresses();
        function1Pressed = true;
        currentLayer = layer2;
      }
    }
  }
  if (!(f2State == HIGH) && !(f1State == HIGH)){
    if (!functionLock) {
      if (function1Pressed or function2Pressed) {
        clearPresses();
        function1Pressed = false;
        function2Pressed = false;
        currentLayer = layer1;
      }
    }
  } 
  for (int colPin = 0; colPin < 12; colPin++){
    digitalWrite(columnList[colPin], HIGH);
    for (int rowPin = 0; rowPin < 4; rowPin++) {
      buttonState = digitalRead(rowList[rowPin]);   
      if (buttonState == HIGH){
   //     Keyboard.print(String(rowPin) + "  :  " + String(colPin) + "\n");
        if (!(pressed[rowPin][colPin])){
          Keyboard.press(currentLayer[rowPin][colPin]);
          pressed[rowPin][colPin] = true;
        }
      } else if (pressed[rowPin][colPin]) {
        Keyboard.release(currentLayer[rowPin][colPin]);
        pressed[rowPin][colPin] = false;
      }
    }
    digitalWrite(columnList[colPin], LOW);
  }
}
