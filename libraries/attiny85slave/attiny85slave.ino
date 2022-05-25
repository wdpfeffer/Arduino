
#include <TinyWireM.h>

char state = '0';
char oldState = '0';
unsigned long endMillis = 0;

void receiveEvent(int howMany)
{
  state = TinyWireM.receive();
}

void setup()
{
  pinMode(3, OUTPUT );
  TinyWireM.begin(13);                
  TinyWireM.(receiveEvent);
}

void loop()
{
  TinyWireM.endTransmission();
  
  if (oldState != state) {
    switch(state) {
      case '1':
        endMillis = millis() + 2000;
        break;
      case '2':
        endMillis = millis() + 3000;
        break;
      case '3':
        endMillis = millis() + 5000;
        break;
      case '4':
        endMillis = millis() + 10000;
        break;
      default:
        endMillis = 0;
    }
    oldState = state;
  }

  if(endMillis <= millis()) {
    digitalWrite(3, HIGH);
  } else {
    digitalWrite(3, LOW);
  }
}
