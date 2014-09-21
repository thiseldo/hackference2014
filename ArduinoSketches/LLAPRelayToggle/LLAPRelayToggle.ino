// Quick hack to toggle relay wirelessly.
#include "LLAPSerial.h"	// include the library
#define DEVICE_ID "DD"

// IOpins used by relays
#define RELAYA 3
#define RELAYB 5

void setup() {
  // initialise serial:
  Serial.begin(115200);
  
  pinMode(8, OUTPUT);    // initialize pin 8 to control the radio
  digitalWrite(8, HIGH); // select the radio
  // Set output pins
  pinMode(RELAYA, OUTPUT);
  digitalWrite(RELAYA, LOW);
  pinMode(RELAYB, OUTPUT);
  digitalWrite(RELAYB, LOW);

  // Initialise the LLAPSerial library
  LLAP.init(DEVICE_ID);
}

int relayA = LOW;
int relayB = LOW;
void loop() {

  if (LLAP.bMsgReceived) {
    if( LLAP.sMessage.equalsIgnoreCase( "RELAYATOG") ) {
      LLAP.sendMessage("RELAYATOG");
      digitalWrite(RELAYA, HIGH );
      delay(100);
      digitalWrite(RELAYA, LOW );
    }

    if( LLAP.sMessage.equalsIgnoreCase( "RELAYBTOG") ) {
      LLAP.sendMessage("RELAYBTOG");
      digitalWrite(RELAYB, relayA );
      delay(100);
      digitalWrite(RELAYB, LOW );
    }

    LLAP.bMsgReceived = false;	// if we do not clear the message flag then message processing will be blocked
  }

}


