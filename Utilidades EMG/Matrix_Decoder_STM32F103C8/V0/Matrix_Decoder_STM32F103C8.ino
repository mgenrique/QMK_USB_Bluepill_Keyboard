/* Copyright 2020 Frank Adams
   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at
       http://www.apache.org/licenses/LICENSE-2.0
   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
// It will determine how a laptop keyboard matrix is wired using a Teensy LC on an FPC daughterboard.
// Open an editor on a computer and load or create a file that lists every key
// on the laptop keyboard that will be tested. Connect the FPC cable of the test keyboard 
// to the Teensy/FPC board. Connect a USB cable from the Teensy to the computer.
// Wait 20 seconds for the computer to see the Teensy as a keyboard. If numbers are reported on the screen
// before any keys are pressed, these pin numbers are shorted together and must be fixed. 
// Press each key one by one on the test keyboard as listed on the editor screen. When a key 
// is pressed on the test keyboard, the program detects which two pins on the FPC connector 
// were connected. Those two pin numbers are sent over USB (separated by a TAB) and displayed 
// on the editor. After sending the numbers, a DOWN ARROW is sent over USB to prepare for
// the next key. Once all keys on the test keyboard have been pressed, the file in
// the editor can be saved to create a row-column matrix.
//
// If your keyboard has diodes, you must pay attention to the order of the two pins that are reported by the Teensy. The code performs 
// a bottom up test first, followed by a top down test so that one of the two tests will forward bias the diode. 
// The first pin reported over USB is the cathode side and the second pin is the anode side. The diode direction must be taken into 
// account when programming the TMK or Teensyduino keyboard routine.
//
// Revision History
// Rev 1.00 - Nov 18, 2018 - Original Release
// Rev 1.1 - April 19, 2020 - Use min_pin in bottom up loop 
//
// Load an array with the Teensy LC I/O numbers that correspond to FPC pins 1 thru 26.
//int con_pin[] = {23, 0, 22, 1, 24, 2, 21, 3, 25, 4, 20, 5, 19, 6, 18, 7, 17, 8, 16, 9, 15, 10, 14, 11, 26, 12}; // I/O 13 is for the LED
//EMG, definciones d epin para bluepill. Saltamos los pines PA11, PA12 (usb) Y PA13,PA14 (Serial wire Debug), a idea me salto tambien el PA15, PC13 que es el LED
int con_pin[] = {PB12, PB13, PB14, PB15, PA8, PA9, PA10, PB3, PB4, PB5, PB6, PB7, PB8, PB9, PC14, PC15, PA0, PA1, PA2, PA3, PA4, PA5, PA6, PA7, PB0, PB1};
#include "Keyboard.h"

//
// Define maximum and minimum pin numbers that will be tested. 
//
int max_pin = 26; // the keyboard fpc connector pin count 
int min_pin = 1; // the first pin to be tested on the FPC connector (usually pin 1)
//

//
// Function to set a pin as an input with a pullup so it's high unless grounded by a key press
void go_z(int pin)
{
  pinMode(pin, INPUT_PULLUP);
  digitalWrite(pin, HIGH);
}

// Function to set a pin as an output and drive it to a logic low (0 volts)
void go_0(int pin)
{
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
}





// --------------------------------------------------Setup-----------------------------------
void setup() {
    // initialize control over the keyboard:
  Keyboard.begin();
  pinMode(PC13, OUTPUT);
  digitalWrite(PC13, LOW); 
  delay(5000);
  digitalWrite(PC13, HIGH);
  
  //Serial.begin(9600);
  //Serial.println("Iniciado");
  Keyboard.println("Iniciado: ");
  for (int k = 0; k < max_pin; k++) {  // loop thru all connector pins 
    go_z(con_pin[k]); // set each pin as an input with a pullup
  }

}
//
int blink_count = 0; // loop counter
boolean blinky = LOW; // Blink LED state
// -------------------------------------------Main Loop--------------------------------------
// 
void loop() {  
//
// ***********Bottom up Test************ 
//
  for (int i=min_pin-1; i<max_pin-1; i++) {   // outer loop pin (min_pin-1 is typically = 0)
    go_0(con_pin[i]); // make the outer loop pin an output and send this pin low
    for (int j=i+1; j<max_pin; j++) {   // inner loop pin
      delayMicroseconds(10); // give time to let the signals settle out
      if (!digitalRead(con_pin[j])) {  // check for connection between inner and outer pins
        Keyboard.print("Bottom up Test: ");
        Keyboard.print(i+1,DEC);
        Keyboard.print("   ;    ");
        Keyboard.println(j+1,DEC);
        //usb_num(i); // send outer loop pin number over usb
        //usb_num(j); // send inner loop pin number over usb
        //down_arrow(); // send a down arrow over usb
        while(!digitalRead(con_pin[j])) {  // wait until key is released 
           ;     // if 2 pins are shorted, the code will hang here waiting for their release                                          
        }                                                  
      }
    }
  go_z(con_pin[i]); // return the outer loop pin to float with pullup        
  }
//
// *********Top down Test***********
//
  for (int p=max_pin-1; p>min_pin-1; p--) {   // outer loop pin
    go_0(con_pin[p]); // make the outer loop pin an output and send this pin low
    for (int r=p-1; r>=min_pin-1; r--) {   // inner loop pin
      delayMicroseconds(10); // give time to let the signals settle out
      if (!digitalRead(con_pin[r])) {  // check for connection between inner and outer pins
        Keyboard.print("Top down Test: ");
        Keyboard.print(p+1,DEC);
        Keyboard.print("   ;    ");
        Keyboard.println(r+1,DEC);        
        //usb_num(p); // send outer loop pin number over usb
        //usb_num(r); // send inner loop pin number over usb
        //down_arrow(); // send a down arrow over usb
        while(!digitalRead(con_pin[r])) {  // wait until key is released 
           ;                                               
        }                                                  
      }
    }
  go_z(con_pin[p]); // return the outer loop pin to float with pullup
  }
//
// Blink the LED to show the Teensy is alive
//
  if (blink_count == 0x0a) {  
    pinMode(PC13, OUTPUT);
    digitalWrite(PC13, blinky);
    blinky = !blinky;
    Serial.println(blinky,DEC);
    blink_count = 0;
  }
  else {
    blink_count++;
  }
delay(25);  // overall keyboard scan rate is about 30 milliseconds
//
}
