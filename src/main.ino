
#include <Arduino.h>
#include <BleGamepad.h>

BleGamepad bleGamepad(
  "BLEEP Controller",
  "DilithiumDev",
  100
);

const int PIN_UP = 4;
const int PIN_DOWN = 5;
const int PIN_LEFT = 6;
const int PIN_RIGHT = 7;

const int PIN_A = 1;
const int PIN_B = 2;
const int PIN_X = 42;
const int PIN_Y = 41;

const int PIN_START = 40;
const int PIN_SELECT = 15;

void setup()
{
    Serial.begin(115200);
    Serial.println("Starting BLE work!");

    pinMode(PIN_UP, INPUT_PULLUP);
    pinMode(PIN_DOWN, INPUT_PULLUP);
    pinMode(PIN_LEFT, INPUT_PULLUP);
    pinMode(PIN_RIGHT, INPUT_PULLUP);

    pinMode(PIN_A, INPUT_PULLUP);
    pinMode(PIN_B, INPUT_PULLUP);
    pinMode(PIN_X, INPUT_PULLUP);
    pinMode(PIN_Y, INPUT_PULLUP);

    pinMode(PIN_START, INPUT_PULLUP);
    pinMode(PIN_SELECT, INPUT_PULLUP);

    bleGamepad.begin();
}

void HandleButtonPress(int pin, int button)
{
  if (digitalRead(pin) == LOW)
    bleGamepad.press(button);
  else
    bleGamepad.release(button);
}

void HandleDPad()
{
    int hat = -1;

    bool up = (digitalRead(PIN_UP) == LOW);
    bool down = (digitalRead(PIN_DOWN) == LOW);
    bool left = (digitalRead(PIN_LEFT) == LOW);
    bool right = (digitalRead(PIN_RIGHT) == LOW);

    if (up && right) hat = HAT_UP_RIGHT;
    else if (right && down) hat = HAT_DOWN_RIGHT;
    else if (down && left) hat = HAT_DOWN_LEFT;
    else if (left && up) hat = HAT_UP_LEFT;
    else if (up) hat = HAT_UP;
    else if (right) hat = HAT_RIGHT;
    else if (down) hat = HAT_DOWN;
    else if (left) hat = HAT_LEFT;
    else hat = HAT_CENTERED;

    bleGamepad.setHat1(hat);
}

void loop()
{
    if (bleGamepad.isConnected())
    {        
        HandleDPad();

        HandleButtonPress(PIN_A, BUTTON_1);
        HandleButtonPress(PIN_B, BUTTON_2);
        HandleButtonPress(PIN_X, BUTTON_3);
        HandleButtonPress(PIN_Y, BUTTON_4);

        HandleButtonPress(PIN_START, BUTTON_8);
        HandleButtonPress(PIN_SELECT, BUTTON_7);
        
        delay(5);
    }   
}