//BUTTON BOX
//Use with Teensy 4.0

#include <Bounce2.h>
#include <Encoder.h>

#define NUMSWITCHES 3
#define NUMENCODERS 5
#define NUMBUTTONS 9

int joystickKey = 0;
int buttonKey = 0;

// Switches //
byte switchesPins[NUMSWITCHES] = {0, 1, 2};
Bounce switches[NUMSWITCHES] = {Bounce(), Bounce(), Bounce()};

void setupSwitches() {
  for (int i = 0; i < NUMSWITCHES; i++) {
    switches[i].attach(switchesPins[i]);
    switches[i].interval(20);
    pinMode(switchesPins[i], INPUT_PULLUP);
  }
}


void updateSwitches() {
  for (int i = 0; i < NUMSWITCHES; i++) {
    switches[i].update();
  }
  for (int i = 0; i < NUMSWITCHES; i++) {
    joystickKey = i + 1;
    if (switches[i].fallingEdge()) {
      Joystick.button(joystickKey, 1);
    }
    if (switches[i].risingEdge()) {
      Joystick.button(joystickKey, 0);
    }
  }
}


// Buttons //
byte buttonsPins[NUMBUTTONS] = {3, 4, 8, 11, 5, 6, 7, 23, 10};
Bounce buttons[NUMBUTTONS] = {Bounce(), Bounce(), Bounce(), Bounce(), Bounce(), Bounce(), Bounce(), Bounce(), Bounce()};

void setupButtons() {
  for (int i = 0; i < NUMBUTTONS; i++) {
    buttons[i].attach(buttonsPins[i]);
    buttons[i].interval(10);
    pinMode(buttonsPins[i], INPUT_PULLUP);
  }
}

void updateButtons() {
  for (int i = 0; i < NUMBUTTONS; i++) {
    buttons[i].update();
  }
  for (int i = 0; i < NUMBUTTONS; i++) {
    buttonKey = i + 4;
    if (buttons[i].fallingEdge()) {
      Joystick.button(buttonKey, 1);
    }
    if (buttons[i].risingEdge()) {
      Joystick.button(buttonKey, 0);
    }
  }
}


// Encoders //
Encoder encoder[NUMENCODERS] = {Encoder(13, 14), Encoder(15, 16), Encoder(17, 18), Encoder(12, 20), Encoder(21, 22)};
int encoderButton[NUMENCODERS][5] = {{13, 14}, {15, 16}, {17, 18}, {19, 20}, {21, 22}};
int encoderVal[NUMENCODERS] = {9999, -9999};
long encoderValue = -9999;

void updateEncoders() {
  for (int i = 0; i < NUMENCODERS; i++) {
    encoderValue = encoder[i].read();
    if (encoderValue == encoderVal[i]) {
      Joystick.button(encoderButton[i][0], 0);
      Joystick.button(encoderButton[i][1], 0);
      delay(10);
    }
    else if (encoderValue > encoderVal[i]) {
      Joystick.button(encoderButton[i][0], 1);
      delay(20);
    }
    else {
      Joystick.button(encoderButton[i][1], 1);
      delay(20);
    }
    encoderVal[i] = encoderValue;
  }
}


String DEVICE_NAME = String("Button Box");


void setup() {
  Joystick.hat(-1);
  setupSwitches();
  setupButtons();
}

void loop() {
  updateButtons();
  updateSwitches();
  updateEncoders();
}
