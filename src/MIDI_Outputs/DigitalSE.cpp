#include "DigitalSE.h"
#include "MIDI_Controller.h"

using namespace ExtIO;

DigitalSE::DigitalSE(pin_t pin, uint8_t count, uint8_t byte1, uint8_t byte2, uint8_t byte3 ,uint8_t byte4,
		  uint8_t byte5, uint8_t byte6, uint8_t byte7, uint8_t byte8, uint8_t byte9, uint8_t byte10) // Constructor
{
  ExtIO::pinMode(pin, INPUT_PULLUP); // Enable the internal pull-up resistor on the pin with the button/switch
  this->pin = pin;
  this->count = count;
  this->byte1 = byte1;
  this->byte2 = byte2;
  this->byte3 = byte3;
  this->byte4 = byte4;
  this->byte5 = byte5;
  this->byte6 = byte6;
  this->byte7 = byte7;
  this->byte8 = byte8;
  this->byte9 = byte9;
  this->byte10 = byte10;
}

DigitalSE::~DigitalSE() // Destructor
{
  ExtIO::pinMode(pin, INPUT); // make it a normal input again, without the internal pullup resistor.
}

void DigitalSE::invert() // Invert the button state (send Note On event when released, Note Off when pressed)
{
  invertState = true;
}

void DigitalSE::refresh() // Check if the button state changed, and send a MIDI Note On or Off accordingly
{
  bool state = ExtIO::digitalRead(pin) ^ invertState; // read the button state and invert it if "invert" is true

  if (millis() - prevBounceTime > debounceTime)
  {
    int8_t stateChange = state - buttonState;

    if (stateChange == falling)
    { // Button is pushed
      buttonState = state;
      if (count > 0 && count < 11)
      {
	uint8_t data[11];

        data[0] = SysExStart;
        data[1] = byte1 & 0x7f;
        data[2] = byte2 & 0x7f;
        data[3] = byte3 & 0x7f;
        data[4] = byte4 & 0x7f;
        data[5] = byte5 & 0x7f;
        data[6] = byte6 & 0x7f;
        data[7] = byte7 & 0x7f;
        data[8] = byte8 & 0x7f;
        data[9] = byte8 & 0x7f;
        data[10] = byte10 & 0x7f;

        data[count + 1] = SysExEnd;
        MIDI_Controller.MIDI()->write(data, count + 2);
      }
    }
  }
  if (state != prevState)
  {
    prevBounceTime = millis();
    prevState = state;
  }
}
