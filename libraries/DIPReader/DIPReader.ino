/*
  DigitalReadSerial
 Reads a digital input on pin 2, prints the result to the serial monitor

 This example code is in the public domain.
 */

// setup the input pins. they are arrange in terms of creating a 1 bit number 0000, 0001, 00010, 0011, 010
int io4 = 2;
int io3 = 3;
int io2 = 4;
int io1 = 5;

//set delay time
int loopDelay=1;
//integer equivalent of byte
int loopCount=0;

String myByte="";
int intByte=0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(io4, INPUT_PULLUP);
  pinMode(io3, INPUT_PULLUP);
  pinMode(io2, INPUT_PULLUP);
  pinMode(io1, INPUT_PULLUP);

  //delay for stability
  delay(5);

  // read the input pin:
  int read4 = digitalRead(io4);
  int read3 = digitalRead(io3);
  int read2 = digitalRead(io2);
  int read1 = digitalRead(io1);
  myByte=String(read1)+String(read2)+String(read3)+String(read4);
  // create integer equivalent of byte
  intByte=read4+2*read3+4*read2+8*read1;
  loopDelay=getDelay(intByte);
}

// the loop routine runs over and over again forever:
void loop() {
	loopCount+=1;
	if(loopCount==loopDelay){
		Serial.print(intByte);
		Serial.print(" ");
		Serial.println(myByte);
		loopCount=0;	
	}

	delay(1000);        // delay in between reads for stability
}

int getDelay(int d){
	int thisdelay=0;
	switch (d) {
      case 0 :
        //1 sec read t
        thisdelay=1;
        break;
      case 1 :
        //10 sec read ti
        thisdelay=10;
        break;
      case 2:
        //30 sec read ti
        thisdelay=30;
        break;
      case 3:
        //1 minu
        thisdelay=60;
        break;
      case 4:
        //2 minut
        thisdelay=120;
        break;
      case 5:
        //5 minute read tim
        thisdelay=300;
        break;
      case 6:
        //10 minute readtim
        thisdelay=600;
        break;
      case 7:
        //15 minute read tim
        thisdelay=900;
        break;
      case 8:
        //20 min read time
        thisdelay=1200;
        break;
      case 9:
        //30 min read time
        thisdelay=1800;
        break;
      case 10:
        //60 min read time
        thisdelay=3600;
        break;
      case 11:
        // 2 hr  read time
        thisdelay=7200;
        break;
      case 12:
        // 4 hr  read time

        thisdelay=14400;
        break;
      case 13:
        // 6 hr  read time

        thisdelay=21600;
        break;
      default:
        // do a one minute read   
        thisdelay=60000;
        break;
    }
    return thisdelay;
}
