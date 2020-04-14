#include <RTClib.h>
#include <Wire.h>

RTC_DS3231 rtc;

int hourPin = 5;   // Digital Pin 5 to Panel Voltmeter (Hours)
int minutePin = 6; // Digital Pin 4 to Panel VOltmeter (Minutes)
int hourBut = 3;   //   Digital Pin 3 to Tactile button (other side to ground)
int minuteBut = 2; // Digital Pin 2 to Tactile button (other side to ground)
int hourAnalogUnit = 23;  // Number of analog units per hour for your dial (1-12)
int minAnalogUnit = 4;   // Number of analog units per minute for your dial
int hourButPrevValue = HIGH;
int minButPrevValue = HIGH;
int minButValue;
int hourButValue;

DateTime now;
DateTime newtime;  // For Time Adjustment

void setup() {
   delay(3000);
  
   pinMode(hourPin, OUTPUT);
   pinMode(minutePin, OUTPUT); 
   pinMode(hourBut, INPUT);
   pinMode(minuteBut, INPUT);

   
   Serial.begin(9600); 
   Serial.println("Starting");
   
   
   delay(3000);
   Serial.println("Initializing RTC");
   if (! rtc.begin()) {
    Serial.println("RTC Not Initialized");
    while(1);
   }
   
   digitalWrite(LED_BUILTIN, HIGH);
   
   if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
   }
}

void loop() {

  // CHeck for button presses
  minButValue = digitalRead(minuteBut);
  if (minButValue != minButPrevValue) {
    if (minButValue == LOW) {   // Button Pushed
        now = rtc.now();
        newtime = DateTime(now.unixtime()+60L);
        rtc.adjust(newtime);
    } 
    minButPrevValue = minButValue;
  }
  
  hourButValue = digitalRead(hourBut);
  if (hourButValue != hourButPrevValue) {
    if (hourButValue == LOW) { // Button Pushed
        now = rtc.now();
        newtime = DateTime(now.unixtime()+3600L); 
        rtc.adjust(newtime);
    }
    hourButPrevValue = hourButValue;
  }

  now = rtc.now();
 
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
    
  // Convert Time to Voltage
  // Each "Segment" of time is about 85 units of PWM
  int hour;
  int hourPWM;
  int minutePWM;
  
  if (now.hour() > 12) {
     hour = now.hour() - 12;  // Correct for 12 hour time
  } else if (now.hour() == 0) {
     hour = 12;               // Midnight is considered 0
  } else {
     hour = now.hour();
  }

  hourPWM = (hour - 1) * hourAnalogUnit;
  minutePWM = now.minute() * minAnalogUnit;

  Serial.print("HourPWM: ");
  Serial.print(hourPWM);
  Serial.print("  MinutePWM: ");
  Serial.print(minutePWM);
  Serial.print("\n");

  // Update the clock display
  analogWrite(hourPin, hourPWM);
  analogWrite(minutePin, minutePWM);
   
  
}
