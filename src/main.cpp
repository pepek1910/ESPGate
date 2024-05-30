/*
   This source code of graphical user interface 
   has been generated automatically by RemoteXY editor.
   To compile this code using RemoteXY library 3.1.10 or later version 
   download by link http://remotexy.com/en/library/
   To connect using RemoteXY mobile app by link http://remotexy.com/en/download/                   
     - for ANDROID 4.13.11 or later version;
     - for iOS 1.10.3 or later version;  
*/
//tutorial from https://www.youtube.com/watch?v=SUQQn1RG_PY on Cloud (not working on WiFi)
//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// you can enable debug logging to Serial at 115200
//#define REMOTEXY__DEBUGLOG    

// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__ESP8266WIFI_LIB_CLOUD

#include <ESP8266WiFi.h>

// RemoteXY connection settings 
#define REMOTEXY_WIFI_SSID "HomeMadeWiFi"
#define REMOTEXY_WIFI_PASSWORD "12345678"
#define REMOTEXY_CLOUD_SERVER "cloud.remotexy.com"
#define REMOTEXY_CLOUD_PORT 6376
#define REMOTEXY_CLOUD_TOKEN "84a151390f640faeea458b3d956cce75"
#define REMOTEXY_ACCESS_PASSWORD "12345"
#include <RemoteXY.h>

#include<SoftwareSerial.h>
int message;
int last_message;

// RemoteXY GUI configuration  
#pragma pack(push, 1)  
uint8_t RemoteXY_CONF[] =   // 76 bytes
  { 255,3,0,4,0,69,0,17,0,0,0,31,1,106,200,1,1,5,0,2,
  7,9,44,22,0,2,26,36,28,79,78,0,79,70,70,0,4,45,94,14,
  36,0,2,26,10,22,37,21,21,48,4,26,31,79,78,0,31,79,70,70,
  0,70,66,37,18,18,16,26,37,0,65,67,11,18,18,112 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  uint8_t switch_01; // =1 if switch ON and =0 if OFF
  int8_t slider_01; // from 0 to 100
  uint8_t pushSwitch_02; // =1 if state is ON, else =0

    // output variables
  uint8_t led_02; // led state, =0 turn off
  uint8_t led_01_r; // =0..255 LED Red brightness
  uint8_t led_01_g; // =0..255 LED Green brightness
  uint8_t led_01_b; // =0..255 LED Green brightness

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0

} RemoteXY;   
#pragma pack(pop)
 
/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

#define PIN_SWITCH_01 D4

void setup() 
{
  RemoteXY_Init (); 
  Serial.begin(115200);
  pinMode (PIN_SWITCH_01, OUTPUT);

  //
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }
}

void loop() 
{ 
  RemoteXY_Handler ();
  digitalWrite(PIN_SWITCH_01, (RemoteXY.switch_01==0)?LOW:HIGH);
  if(RemoteXY.switch_01==1)
  {
    //Serial.println("Switch01 ON");
    message = 1;
  }
  if(RemoteXY.pushSwitch_02==1)
  {
    //Serial.println("pushSwitch_02 ON");
    message = 2;
    RemoteXY.led_02 = true;
  } 
  else{
    RemoteXY.led_02 = false;
  }
  if(RemoteXY.slider_01>0)
  {
    //Serial.print("slider_01 over");
    //Serial.println(RemoteXY.slider_01);  
    message = RemoteXY.slider_01;
    RemoteXY.led_01_r = (RemoteXY.slider_01);
    RemoteXY.led_01_g = (RemoteXY.slider_01);
    RemoteXY.led_01_b = (RemoteXY.slider_01);
  }
  if((message != 1) && (message !=2))
    message = 0;
  // TODO you loop code
  // use the RemoteXY structure for data transfer
  // do not call delay(), use instead RemoteXY_delay() 
  if(last_message != message)
  {
    Serial.print(message);
    last_message= message;
  }
}
//Code on UNO (Arduino IDE)
    /*
    String odebraneDane = ""; //Pusty ciąg odebranych danych
    
    void setup() {
    Serial.begin(115200); //Uruchomienie komunikacji
    }
    
    void loop() {
    if(Serial.available() > 0) { //Czy Arduino odebrało dane
        odebraneDane = Serial.readStringUntil('\n'); //Jeśli tak, to odczytaj je do znaku końca linii i zapisz w zmiennej odebraneDane
        //Serial.println("Witaj " + odebraneDane + "!"); //Wyświetl komunikat
    }
    if(odebraneDane == "1")
        Serial.println("Button 1 Pushed"); //Wyświetl komunikat
    else if(odebraneDane == "2")
        Serial.println("Button 2 Pushed"); //Wyświetl komunikat
    odebraneDane ="";
    }
    */