// Include necessary libraries
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <LedControl.h>
#include <Servo.h>

// Constant pin numbers
#define buzzerPin 2
#define echoPin 3
#define trigPin 4

#define DINPin 7
#define CLKPin 6
#define CSPin 5

#define ServoPin 11

// Variables
  // LCD display
LiquidCrystal_I2C lcd(0x27, 16, 2);
  // 8x8 dot matrix
LedControl lc = LedControl(DINPin, CLKPin, CSPin, 0);
  // Servo motor
Servo srv;

int maxRange = 50;
int minRange = 0;
long duration, distance;
long too_close_distance = 20;
String display_string;

//8x8 dot matrix figures
byte happy[8] = {0x7, 0xe, 0x1c, 0x18, 0x18, 0x1c, 0xe, 0x7};
byte sad[8] = {0x1c, 0xe, 0x7, 0x3, 0x3, 0x7, 0xe, 0x1c};
byte neutral[8] = {0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c};

void setup() {

  // initialize the LCD
	lcd.begin();
	lcd.backlight();

  // initialise Ultrasonic Sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // initialise buzzer
  pinMode(buzzerPin, OUTPUT);

  // initialise 8x8 led
  lc.shutdown(0, false);
  lc.setIntensity(0, 15);
  lc.clearDisplay(0);  

  // initialise Servo
  srv.attach(ServoPin);
  srv.write(180);

  Serial.begin(9600);
}

void loop() {

  // ULTRASONIC SENSOR
  int distance = dist_fnc(maxRange, minRange);

  if (distance >= maxRange || distance <= minRange){ //out of range
    if(display_string != "Hi, I am FunBin!"){
      display_string = "Hi, I am FunBin!";
      display_fnc(display_string);
      Serial.print(display_string);
      Serial.print("\n");
    }
    srv.write(180);

    printByte_fnc(neutral);

    delay(100);
    return;
  }
  else if (distance > too_close_distance) { //middle range
    ring_fnc(distance);

    if (display_string != "  COME CLOSER!  "){
      display_string = "  COME CLOSER!  ";
      display_fnc(display_string);
      Serial.print(display_string);
      Serial.print("\n");
    }
    srv.write(180);

    printByte_fnc(sad);
    //delay(1000);

  }
  else { //too close range
    ring_fnc(distance);
    if (display_string != "HAHAHA TOO CLOSE"){
      display_string = "HAHAHA TOO CLOSE";
      display_fnc(display_string);
      Serial.print(display_string);
      Serial.print("\n");
    }
    srv.write(0);
    
    printByte_fnc(happy);

  }

}

int dist_fnc(int maxRange, int minRange){

  //Make sure to clear the trig pulse.
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  //to generate the ultrasound wave need to set the tripPin on a HIGH state for 10microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW); //at this exact moment, ultrasound wave is generated

  duration = pulseIn(echoPin, HIGH);
  distance = duration*0.034/2;
  
  return distance;
}

int ring_fnc(int distance1){
  tone(buzzerPin, 900);
  delay(distance1*10);
  noTone(buzzerPin);
  delay(distance1*10);
}

void display_fnc(String display_string){
  lcd.setCursor(0,0); // First row first column
  lcd.clear();
  lcd.noBacklight(); 
  lcd.backlight(); 
  lcd.print(display_string); 
}

void printByte_fnc(byte character[]){
  int i = 0;
  for(i=0; i<8; i++){
    lc.setRow(0, i, character[i]);
  }
}
