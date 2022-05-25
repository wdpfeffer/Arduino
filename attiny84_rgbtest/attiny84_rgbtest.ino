
int redPin = 6;     // Red RGB pin -> D0
int greenPin = 5;   // Green RGB pin -> D1
int bluePin = 3;    // Blue RGB pin -> D2
int powerPin=9;     // Pin for Controlling power
int count = 0;      // Used for counting
int ppv = 0;        // power pin value;
bool up = true;     // direction for counting.


int treeBlueCount = 0;
int treeRedCount = 0;
int treeGreenCount = 0;
int smBlueCount = 255;
int smRedCount = 255;
int smGreenCount = 255;
int i=10;


void setup() {
  Serial.begin(9600);
  pinMode(redPin,OUTPUT);
  pinMode(bluePin,OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(powerPin, OUTPUT);
  
}

void loop() {
  // RGB LED COMMON ANODE
  ppv = count/1000.0*230+25;
  // write the snowman routine first
  //if (smRedCount >=244) && (smBlueCount >= 255) && (smGreenCount ==255){
  //    
  //}
  Serial.println(ppv);
  analogWrite(powerPin,ppv);
  analogWrite(redPin,0);
  analogWrite(greenPin,51);
  analogWrite(bluePin,26);

  if ((count<1000) && (count >-1)){
    if (up){
      count++;
    }else{
      count--;
    }
  }else{
    if (up){
      up=false;
      count+=-1;
    }else{
      up=true;
      count+=1;
    }
  }
}
