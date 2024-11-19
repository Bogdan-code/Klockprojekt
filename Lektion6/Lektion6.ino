#include "U8glib.h"
#include <RTClib.h>
#include <Wire.h>
#include "Servo.h"



U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);


// unsigned long myTime;
#define DS3231_I2C_ADDR             0x68
#define DS3231_TEMPERATURE_ADDR     0x11
Servo myservo;

#define servoPin 9

DateTime now;

RTC_DS3231 rtc;
char t[32];
byte control_reg, temperature_lsb;
char temperature_msb;


void setup() {
  for(int i= 4; i <= 6; i++){
    pinMode(i, OUTPUT);
  }
  pinMode(A1, INPUT);
  Serial.begin(9600);
  Serial.begin(9600);
  Wire.begin();
  rtc.begin();
  rtc.adjust(DateTime(F(__DATE__),F(__TIME__)));
  //rtc.adjust(DateTime(2019, 1, 21, 5, 0, 0));

  myservo.attach(servoPin);
  myservo.write(0);

}

void loop() {
  now = rtc.now();
  

  int temp = map(getTemp(), 18, 26, 0,10); //Maps the getTemp() functions output (0-10)
  oledWrite(getTime(), getTemp());
  servoWrite(getTemp());
  Serial.println(getTemp());

  delay(1000);



  

}


/*
* This function reads the temperature output from the ds3231 module
*Parameters: Void
*Returns: temprature as float
*/
float getTemp(){ //getTemp function, when called returns the current Temperature(float)
  return rtc.getTemperature();
}

// void alarm(){
//   for (int i=4; i<= 6; i++) {
//   digitalWrite(i, HIGH);
//   delay(100);
//   digitalWrite(i, LOW);
//   }
//   for (int i=6; i>= 4; i--) {
//   digitalWrite(i, HIGH);
//   delay(100);
//   digitalWrite(i, LOW);
// }
// }


/*
* This function takes a string and a float and draws them on the oled display(Time and Temp)
*Parameters: - time: String to write to display, temp: float to write to display as temp
*Returns: void
*/
void oledWrite(String time, float temp){//When called with and inputted with time and a temp, writes the values on oled
  String temp_str = String(temp,2);
  u8g.firstPage();
  do {
    u8g.setFont(u8g_font_unifont);
    u8g.drawStr(10, 20, time.c_str());
    u8g.drawStr(10, 40, "Temp: ");
    u8g.drawStr(50, 40, temp_str.c_str());

  } while (u8g.nextPage());
}

/*
*This function reads time from an ds3231 module and package the time as a String
*Parameters: Void
*Returns: time in hh:mm:ss as String
*/

String getTime(){ 
  DateTime now = rtc.now();
  // sprintf(t, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());  
  return ("Time: " +  String(now.hour()) + ":" + String(now.minute()) +  ":" +  String(now.second()));
}



/*
* takes a temprature value and maps it to corresppnding degree on a servo
*Parameters: - value: temprature
*Returns: void
*/
void servoWrite(float value){
  int servo_temp = map(value, 17, 27, 0, 179);
  Serial.println(servo_temp);
  myservo.write(servo_temp);

}
