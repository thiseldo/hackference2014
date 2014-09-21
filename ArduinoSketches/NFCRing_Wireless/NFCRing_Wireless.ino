// Report NFC Ring

// SM130 - seek continuosly for tags and print type and id to serial port
// Marc Boon <http://www.marcboon.com>
// April 2009

// Controls a SonMicro SM130/mini RFID reader or RFIDuino by I2C
// Arduino analog input 4 is I2C SDA (SM130/mini pin 10/6)
// Arduino analog input 5 is I2C SCL (SM130/mini pin 9/5)
// Arduino digital input 4 is DREADY (SM130/mini pin 21/18)
// Arduino digital output 3 is RESET (SM130/mini pin 18/14)

// Following two includes are required for SM130
#include <Wire.h>
#include <SM130.h>

#define SRFPIN 8

// Create SM130 instance for RFIDuino
SM130 RFIDuino;


void setup()
{
  pinMode( SRFPIN, OUTPUT);
  digitalWrite( SRFPIN, HIGH );
  // Start I2C bus master (required)
  Wire.begin();

  // Using the serial port is optional
  Serial.begin(115200);

  // Reset RFIDuino, this will also configure IO pins DREADY and RESET
  RFIDuino.reset();
  delay(50);
  RFIDuino.getFirmwareVersion();

  // Start SEEK mode
  RFIDuino.seekTag();
}

void loop()
{
  // Tag detected?
  if(RFIDuino.available())
  {
    // Print the tag's serial number
    RFIDuino.getTagName();
    Serial.print("r");
    Serial.println(RFIDuino.getTagString());
    delay(2000);
    // Start new SEEK
    RFIDuino.seekTag();
  }
}

