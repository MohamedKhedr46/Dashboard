#include <UTFTGLUE.h>  //use GLUE class and constructor
UTFTGLUE myGLCD(0, A2, A1, A3, A4, A0);


const int HALLSEN_A = 18;

volatile long encoderValue = 0;

int interval = 1000;
long previousMillis = 0;
long currentMillis = 0;

int rpm = 0;
boolean measureRpm = false;

float Analog;
float Sum;
float Average;

float Analog1;
float Sum1;
float Average1;

float Analog2;
float Sum2;
int Average2; 


void EncoderInit() {
  // Attach interrupt at hall sensor A on each rising signal
  attachInterrupt(digitalPinToInterrupt(HALLSEN_A), updateEncoder, RISING);
}


void updateEncoder() {
  // Add encoderValue by 1, each time it detects rising signal
  // from hall sensor A
  encoderValue++;
}

void setup() {

Serial.begin(9600);
  myGLCD.InitLCD();
  myGLCD.fillScreen(VGA_BLACK);

  myGLCD.drawFastHLine(0, 155, 480, VGA_WHITE);
  myGLCD.drawFastVLine(280, 0, 320, VGA_WHITE);

  //analogReference(INTERNAL1V1);

  EncoderInit();  //Initialize the module
  encoderValue = 0;
  previousMillis = millis();
}

void loop() {

  //int speed = map(analogRead(A8), 0, 1023, 0, 199);

  currentMillis = millis();
  if (currentMillis - previousMillis > interval) {

    encoderValue = encoderValue / 6;

    rpm = ((encoderValue / (float)interval) * 60000.0);

    int speed = rpm * 0.0933;

    if(speed > 99)
    {
      speed = 0;
    }

    myGLCD.setColor(VGA_WHITE);
    myGLCD.setTextSize(14);
    myGLCD.printNumI(speed, 30, 40);
    //myGLCD.print("00",30, 40);
    myGLCD.setTextSize(3);
    myGLCD.print("km/h", 200, 117);

    encoderValue = 0;
    previousMillis = currentMillis;
  }



Sum = 0;        //Initialize/reset

//Take 1000 readings, find min, max, and average.  This loop takes about 100ms.
for (int i = 0; i < 500; i++)
{
  Analog = map(analogRead(A11),530,910,48,58);

  Sum = Sum + Analog;   //Sum for averaging
        
}

Average = (Sum/500);

//Serial.println(analogRead(A11));
  myGLCD.setColor(VGA_WHITE);
  myGLCD.setTextSize(6);
  //myGLCD.print("00", 330, 180);
  myGLCD.printNumI(Average,330, 180);
  myGLCD.setTextSize(5);
  myGLCD.print("V", 420, 185);

  myGLCD.setColor(VGA_WHITE);
  myGLCD.setTextSize(3);
  myGLCD.print("Range", 15, 200);
  myGLCD.setTextSize(5);
  //myGLCD.printNumI(speed, 120, 190);
  myGLCD.print("68", 120, 190);
  myGLCD.setTextSize(3);
  myGLCD.print("km", 220, 204);



  myGLCD.setColor(VGA_WHITE);
  myGLCD.setTextSize(3);
  myGLCD.print("ODO", 15, 280);
  myGLCD.setTextSize(4);
  //myGLCD.printNumI(speed,80, 275);
  //myGLCD.print("0000", 80, 275);
  myGLCD.print("0002", 80, 275);
  myGLCD.setTextSize(3);
  myGLCD.print("km", 190, 280);


Sum1 = 0;        //Initialize/reset

//Take 1000 readings, find min, max, and average.  This loop takes about 100ms.
for (int i = 0; i < 500; i++)
{
  Analog1 = map(analogRead(A11),0,670,0,100);

  Sum1 = Sum1 + Analog1;   //Sum for averaging
        
}

Average1 = (Sum1/500);

if(Average1 < 1)
{
  Average1 = 0;
}


  myGLCD.setColor(VGA_WHITE);
  myGLCD.setTextSize(3);
  myGLCD.print("SOC", 290, 130);
  myGLCD.setTextSize(8);
  myGLCD.printNumI(Average1,350, 65);
  //myGLCD.print("00", 350, 65);
  myGLCD.setTextSize(5);
  myGLCD.print("%", 450, 85);



  myGLCD.setColor(VGA_BLACK);
  myGLCD.setTextSize(6);
  myGLCD.printNumI(Average2,310, 250);


Sum2 = 0; 
Average2 = 0;       //Initialize/reset

//Take 1000 readings, find min, max, and average.  This loop takes about 100ms.
for (int i = 0; i < 50; i++)
{
  Analog2 = map(analogRead(A6),10,1023,0,200);
  //Serial.println(Analog2);


  Sum2 = Sum2 + Analog2;   //Sum for averaging
        
}

Average2 = (Sum2/50);


Serial.println(analogRead(A6));

if(Average2 < 0)
{
  Average2 = 0;
}
if(Average2 > 200)
{
  Average2 = 200;
}


 // Analog2 = map(analogRead(A6),0,400,1,200);
   
  myGLCD.setColor(VGA_WHITE);
  myGLCD.setTextSize(6);
  //myGLCD.print("000", 310, 250);
  myGLCD.printNumI(Average2,310, 250);
  myGLCD.setTextSize(5);
  myGLCD.print("A", 430, 255);


//Average2 = 0;       //Initialize/reset




  if (digitalRead(44) == HIGH) {

    myGLCD.setColor(VGA_GREEN);
    myGLCD.setTextSize(6);
    myGLCD.print("-->", 360, 10);
  } else if (digitalRead(48) == HIGH) {
    myGLCD.setColor(VGA_GREEN);
    myGLCD.setTextSize(6);
    myGLCD.print("<--", 360, 10);
  } else {
    myGLCD.setColor(VGA_BLACK);
    myGLCD.setTextSize(6);
    myGLCD.print("-->", 360, 10);
    myGLCD.setColor(VGA_BLACK);
    myGLCD.setTextSize(6);
    myGLCD.print("<--", 360, 10);
  }
}
