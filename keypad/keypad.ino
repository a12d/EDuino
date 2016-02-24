#include <Keyboard.h>

int RXLED = 17;
// define the different elite game modes
const int OPEN = 1;
const int PRIVATE = 2;
const int SOLO = 3;

// set the arduino pins for each key
const int KEY_1 = 5;
const int KEY_2 = 9;
const int KEY_3 = 15;
const int KEY_4 = 4;
const int KEY_5 = 8;
const int KEY_6 = 14;
const int KEY_7 = 3;
const int KEY_8 = 7;
const int KEY_9 = 16;
const int KEY_0 = 6;
const int KEY_STAR = 2;
const int KEY_HASH = 10;

// and the pin for the LED
const int BUSY_LED = 0;

// define the various E:D keys here
const char UISelect = ' ';
const char UINextTab = 'e';
const char OpenGalaxyMap = 'g';
const char TargetPanel = '1';
const char InterfacePanelDown = 's';
const char InterfacePanelUp = 'w';
const char InterfacePanelLeft = 'q';
const char InterfacePanelRight = 'e';
const char InterfacePanelPrevious = 'q';
const char InterfacePanelSelect = ' ';
const char UIPanelRight = 'd';
const char UIPanelLeft = 'a';
const char UIPanelUp = 'w';
const char UIPanelDown = 's';
const char UIPanelSelect = ' ';

const int spinning_ship_delay = 20000;
const int station_ident_delay = 5000;

// This is the mode that's used the first time around.
int game_mode = OPEN;

void setup() {
  pinMode(KEY_1, INPUT_PULLUP);
  pinMode(KEY_2, INPUT_PULLUP);
  pinMode(KEY_3, INPUT_PULLUP);
  pinMode(KEY_4, INPUT_PULLUP);
  pinMode(KEY_5, INPUT_PULLUP);
  pinMode(KEY_6, INPUT_PULLUP);
  pinMode(KEY_7, INPUT_PULLUP);
  pinMode(KEY_8, INPUT_PULLUP);
  pinMode(KEY_9, INPUT_PULLUP);
  pinMode(KEY_0, INPUT_PULLUP);
  pinMode(KEY_STAR, INPUT_PULLUP);
  pinMode(KEY_HASH, INPUT_PULLUP);

  pinMode(BUSY_LED, OUTPUT);
  
  Keyboard.begin();
}

void loop() {
  if (digitalRead(KEY_1) == LOW) {
    //Keyboard.write(KEY_ESC);
  }
  else if (digitalRead(KEY_2) == LOW) {
    //Keyboard.write(UIPanelUp);
  }
    else if (digitalRead(KEY_3) == LOW) {
    //Keyboard.write('3');
  }
    else if (digitalRead(KEY_4) == LOW) {
    //Keyboard.write(UIPanelLeft);
  }
    else if (digitalRead(KEY_5) == LOW) {
    //Keyboard.write(UIPanelSelect);
  }
    else if (digitalRead(KEY_6) == LOW) {
    //Keyboard.write(UIPanelRight);
  }
    else if (digitalRead(KEY_7) == LOW) {
    //Keyboard.write('7');
  }
    else if (digitalRead(KEY_8) == LOW) {
    //Keyboard.write(UIPanelDown);
  }
    else if (digitalRead(KEY_9) == LOW) {
    //Keyboard.write('9');
  }
    else if (digitalRead(KEY_0) == LOW) {
      digitalWrite(BUSY_LED, HIGH);
          digitalWrite(RXLED, HIGH);
    TXLED1;
      requestDocking();
  }
    else if (digitalRead(KEY_STAR) == LOW) {
      digitalWrite(BUSY_LED, HIGH);
          digitalWrite(RXLED, HIGH);
    TXLED1;
      refreshBBS();
  }
    else if (digitalRead(KEY_HASH) == LOW) {
      digitalWrite(BUSY_LED, HIGH);
          digitalWrite(RXLED, HIGH);
    TXLED1;
      updateMarketPrices();
  }
  delay(200);
  digitalWrite(BUSY_LED, LOW);
  digitalWrite(RXLED, LOW);
  TXLED0;
}

// Prints a given string one character at a time, with a delay between characters and a long press of the keys.
// the default key press duration was too low for elite.
void slowPrint(char* string, int keyPressTime = 100, int delayBetweenKeypress = 400)
{
  // This is how long the key should be pressed
  //const int keyPressTime = 100;
  // This is how long of a delay there should be between keypresses
  //const int delayBetweenKeypress = 200;  

  for (int index = 0; index < strlen(string); index++)
  {
    Keyboard.press(string[index]);
    delay(keyPressTime);
    Keyboard.releaseAll();

    delay(delayBetweenKeypress);
  }
}

void refreshBBS() {
    char highlightQuit[6] = {InterfacePanelDown, InterfacePanelDown, InterfacePanelDown, InterfacePanelDown, InterfacePanelDown};
    char selectYes[3] = {UIPanelRight, InterfacePanelSelect};
    char downThenSelect[3] = {InterfacePanelDown, InterfacePanelSelect};
    char highlightSolo[3] = {InterfacePanelDown, InterfacePanelDown};
    char selectString[2] = {InterfacePanelSelect};
    char selectBBS[5] = {InterfacePanelDown, InterfacePanelDown, InterfacePanelDown, InterfacePanelSelect};

  // Go to in game menu
  Keyboard.write(KEY_ESC);
  //Keyboard.print("KEY_ESC");
  delay(1000);
  // highlight quit to main menu

  slowPrint(highlightQuit);
  delay(1000);
  // select option
  slowPrint(selectString);
  delay(1000);
  // yes, we're sure
  slowPrint(selectYes);
  delay(3000);
  // "start"
  slowPrint(downThenSelect);
  //open/private/solo mode
  if (game_mode == OPEN){
    game_mode = PRIVATE;
  }
  else if (game_mode == PRIVATE){
    slowPrint(downThenSelect);
    game_mode = SOLO;
  }
  else if (game_mode == SOLO) {
    slowPrint(highlightSolo);
    game_mode = OPEN;
  }
  else
  {
    // open mode is the default
    game_mode = OPEN;
  }
  // select the mode (or the private group if it's mode 2) that's highlighted
  delay(500);
  slowPrint(selectString);
  // wait for the spinning ship...
  delay(spinning_ship_delay);
  // select starport services
  slowPrint(selectString);
  delay(station_ident_delay);
  // select BBS
  slowPrint(selectBBS);
}

void updateMarketPrices() {
  Keyboard.write(KEY_F7);
}

void requestDocking() {
   char dockingString[ ] = { TargetPanel, InterfacePanelRight, InterfacePanelRight, InterfacePanelSelect, InterfacePanelDown, InterfacePanelSelect, InterfacePanelPrevious, InterfacePanelPrevious, TargetPanel};
   slowPrint(dockingString,100,100);
}

// void targetNearestStation() {
// }

// void targetNextSystem() {
// }

