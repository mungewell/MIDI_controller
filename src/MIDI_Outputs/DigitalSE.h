#ifndef DIGITALSE_h_
#define DIGITALSE_h_

#include "MIDI_Control_Element.h"
#include "../Settings/Settings.h"
#include "../ExtendedInputOutput/ExtendedInputOutput.h"

class DigitalSE : public MIDI_Control_Element
{
public:
  DigitalSE(pin_t pin, uint8_t count, uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4,
		  uint8_t byte5, uint8_t byte6, uint8_t byte7, uint8_t byte8, uint8_t byte9, uint8_t byte10); // Constructor
  ~DigitalSE();                                                              // Destructor
  void invert();                                                             // Invert the button state (send Note On event when released, Note Off when pressed)

private:
  void refresh(); // Check if the button state changed, and send a MIDI Note On or Off accordingly

  pin_t pin;
  uint8_t count, byte1, byte2, byte3, byte4, byte5, byte6, byte7, byte8, byte9, byte10;
  bool prevState = HIGH, buttonState = HIGH;
  unsigned long prevBounceTime = 0;

  bool invertState = false;

  const static unsigned long debounceTime = BUTTON_DEBOUNCE_TIME;

  const static int8_t falling = LOW - HIGH;
  const static int8_t rising = HIGH - LOW;
};

#endif
