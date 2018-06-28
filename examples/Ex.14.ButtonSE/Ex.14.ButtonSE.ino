/*
This is an example of the "DigitalSE" class of the MIDI_controller library.
Connect a push buttons to digital pins 2, 3 and 4. Connect the other pin of
the button to the ground, a pull-up resistor is not necessary, because the 
internal one will be used. 

Thess buttons will send SystemExclusive message, which in this exaple will
control an Akai MPC Live - 'play', 'stop', and 'rewind'

Written by Simon Wood, 27/06/2018
https://github.com/tttapa/MIDI_controller
*/

#include <MIDI_Controller.h> // Include the library

// Create a new instance of the class 'DigitalSE', called 'button', on pin 2, 
// that sends MIDI message 'F0 04 7F 7F 06 02 7F'

DigitalSE play_button(2, 4, 0x7F, 0x7F, 0x06, 0x02, 0, 0, 0, 0, 0, 0);
DigitalSE stop_button(3, 4, 0x7F, 0x7F, 0x06, 0x01, 0, 0, 0, 0, 0, 0);
DigitalSE rewind_button(4, 10, 0x7F, 0x00, 0x06, 0x44, 0x06, 0x01, 0x00, 0x00, 0x00, 0x00);

void setup() {}

void loop() {
  // Refresh the button (check whether the button's state has changed since last time, if so, send it over MIDI)
  MIDI_Controller.refresh();
}
