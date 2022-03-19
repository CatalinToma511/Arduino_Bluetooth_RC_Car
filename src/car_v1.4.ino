#include<Servo.h>
#include<SoftwareSerial.h>

#define TurningBPS 0.65 //turn indicators beats per sec
#define SteeringCenter 90
#define SteeringRight 0
#define SteeringLeft 180
#define LeftMotorsCoef 0.8

#define BT_TX 0
#define BT_RX 1
#define BTStatePin A5

#define EnA 11
#define EnB 3
#define IN1 A1
#define IN2 A2
#define IN3 A3
#define IN4 A4

#define SteeringPin A0
#define WinchPin 4

#define UnderglowPin 2
#define RevLightPin   8
#define BrakeLightPin 5
#define ThirdBrakePin 10
#define LTPin 9
#define RTPin 7
#define DRLPin 12
#define BeamPin 6
#define RoofLightsPin 13

//SoftwareSerial hc05(BT_TX, BT_RX); //BT_TX is RX for Arduino and vice-versa
Servo steering, winch;
String rasp;
char last_direction;
bool lastDirectionFront = 1;
bool j = 0, k = 0;
bool inDrive = 1;
unsigned long time_now = 0, time_old = 0, brake_time = 0, max_speed = 0, num_j = 0, last_print = 0;
bool rev = 0;
bool brake = 0;
bool lt = 0, rt = 0;
bool aprins = 0;
int beam = 0;
bool bt_connected = 0;
bool underglow = 0;
bool tank_mode = 0;
bool winch_mode = 0;
int winch_position = 0;

void setup() {
  TCCR2B = TCCR2B & B11111000 | B00000111; // for PWM frequency of 30.64 Hz 3&11
  pinMode(BTStatePin, INPUT);
  pinMode(EnA, OUTPUT);
  pinMode(EnB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(UnderglowPin, OUTPUT);
  pinMode(RevLightPin, OUTPUT);
  pinMode(BrakeLightPin, OUTPUT);
  pinMode(ThirdBrakePin, OUTPUT);
  pinMode(RoofLightsPin, OUTPUT);
  pinMode(LTPin, OUTPUT);
  pinMode(RTPin, OUTPUT);
  pinMode(DRLPin, OUTPUT);
  pinMode(BeamPin, OUTPUT);
  Serial.begin(9600);
  Serial.setTimeout(5);
  //hc05.begin(9600);
  //hc05.setTimeout(50);
  
  steering.attach(SteeringPin);
  steering.write(SteeringCenter);

  updateLights();
}

void loop() {
  bt_connected = digitalRead(BTStatePin);
  if(bt_connected)
  {
    if(Serial.available())
    {
      rasp = Serial.readString();
      //Serial.println(rasp);
      updateCommands(rasp);
    }
    Serial.print("D");
    Serial.println(winch_mode);
    Serial.print("T");
    Serial.println(tank_mode);
    updateLights();
    
  }
  else
  {
    unconnected();
  }
}
