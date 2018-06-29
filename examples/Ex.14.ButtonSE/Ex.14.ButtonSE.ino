/*
This is an example of the "DigitalSE" class of the MIDI_controller library.

Connect a push buttons to digital pins 2, 3 and 4. Connect the other pin of
the button to the ground, a pull-up resistor is not necessary, because the
internal one will be used.

These buttons will send SystemExclusive messages, which in this example will
control an Akai MPC Live - 'play', 'stop', and 'rewind'

Written by Simon Wood, 27/06/2018
https://github.com/tttapa/MIDI_controller
*/

#include <MIDI_Controller.h> // Include the library

// Create a new instance of the class 'DigitalSE', called 'button', on pin 2,
// that sends MCC messages, ie 'play'='F0 7F 7F 06 02 7F'
//
// https://en.wikipedia.org/wiki/MIDI_Machine_Control

DigitalSE play_button(2, 4, 0x7F, 0x7F, 0x06, 0x02, 0, 0, 0, 0, 0, 0);
DigitalSE stop_button(3, 4, 0x7F, 0x7F, 0x06, 0x01, 0, 0, 0, 0, 0, 0);
DigitalSE rewind_button(4, 10, 0x7F, 0x00, 0x06, 0x44, 0x06, 0x01, 0x00, 0x00, 0x00, 0x00);

// Double Check
const uint8_t velocity = 0b1111111;
const uint8_t C4 = 60;
Digital button(5, C4, 1, velocity);

void setup() {}

void loop() {
  // Refresh the button (check whether the button's state has changed since last time, if so, send it over MIDI)
  MIDI_Controller.refresh();
}
