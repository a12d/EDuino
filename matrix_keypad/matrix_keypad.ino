#include <HashMap.h>
#include <SD.h>

#include <Keypad.h>
#include <Key.h>

#include <Keyboard.h>

int RXLED = 17;
// define the different elite game modes
const int OPEN_MODE = 1;
const int PRIVATE_MODE = 2;
const int SOLO_MODE = 3;

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
int game_mode = OPEN_MODE;

// matrix keypad pins
const int COL_1 = 2;
const int COL_2 = 3;
const int COL_3 = 4;
const int COL_4 = 5;
const int ROW_1 = 6;
const int ROW_2 = 7;
const int ROW_3 = 8;
const int ROW_4 = 9;

const byte rows = 4;
const byte cols = 4;

char keys[rows][cols] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[rows] = {ROW_1, ROW_2, ROW_3, ROW_4}; //connect to the row pinouts of the keypad
byte colPins[cols] = {COL_1, COL_2, COL_3, COL_4}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols );

void setup() {
  pinMode(BUSY_LED, OUTPUT);
  
  Keyboard.begin();
}

void loop() {
  char key = keypad.getKey();

  if (key != NO_KEY)
  {
    Keyboard.write(key);
  }
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
  delay(4000);
  // "start"
  slowPrint(downThenSelect);
  delay(1000);
  //open/private/solo mode
  if (game_mode == OPEN_MODE){
    game_mode = PRIVATE_MODE;
  }
  else if (game_mode == PRIVATE_MODE){
    slowPrint(downThenSelect);
    game_mode = SOLO_MODE;
  }
  else if (game_mode == SOLO_MODE) {
    slowPrint(highlightSolo);
    game_mode = OPEN_MODE;
  }
  else
  {
    // open mode is the default
    game_mode = OPEN_MODE;
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
   char dockingString[ ] = {TargetPanel, InterfacePanelRight, InterfacePanelRight, InterfacePanelSelect, InterfacePanelDown, InterfacePanelSelect, InterfacePanelPrevious, InterfacePanelPrevious, TargetPanel};
   slowPrint(dockingString, 100, 100);
}

void acceptMission() {
    char missionString[ ] = {InterfacePanelSelect, UIPanelRight, InterfacePanelSelect};
    slowPrint(missionString);
}

void completeMission() {
    char missionString[ ] = {InterfacePanelSelect, UIPanelRight, InterfacePanelSelect};
    char selectString[2] = {InterfacePanelSelect};
    slowPrint(missionString);
    delay(1500);
    slowPrint(selectString);
}
// void targetNearestStation() {
// }

// void targetNextSystem() {
// }

