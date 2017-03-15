/*
 *  This sketch sends a message to a TCP server
 *
 */

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
//#include "TimeClient.h"

#define TIME_MSG_LEN  11   // time sync to PC is HEADER and unix time_t as ten ascii digits
#define TIME_HEADER  255   // Header tag for serial time sync message

ESP8266WiFiMulti WiFiMulti;

void setup() {
    Serial.begin(115200);
    delay(10);

    // We start by connecting to a WiFi network
    WiFiMulti.addAP("FiOS-9XH87", "shark8raw0743tutor");

    Serial.println();
    Serial.println();
    Serial.print("Wait for WiFi... ");

    while(WiFiMulti.run() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    delay(500);
}

// Use WiFiClient class to create TCP connections
    WiFiClient client;

void loop() {
    const uint16_t port = 9000;
    const char * host = "192.168.1.20"; // ip or dns

    
    
    Serial.print("connecting to ");
    Serial.println(host);

    

    if (!client.connect(host, port)) {
        Serial.println("connection failed");
        Serial.println("wait 5 sec...");
        delay(5000);
        return;
    }

    // This will send the request to the server
    client.print("Send this data to server");

    //getPCtime();   // try to get time sync from pc   
    //sendTime();

    //read back one line from server
    String line = client.readStringUntil('\r');
    client.println(line);

    Serial.println(line);
    
    if(line == "stop"){
      Serial.println("closing connection");
      client.stop();
    }
    
    Serial.println("wait 0.5 sec...");
    delay(500);
}

//void getPCtime(){
//   // if time available from serial port, sync the DateTime library
//  while(Serial.available() >=  TIME_MSG_LEN ){  // time message
//    if( Serial.read() == TIME_HEADER ) {        
//      time_t pctime = 0;
//      for(int i=0; i < TIME_MSG_LEN -1; i++){   
//        char c= Serial.read();          
//        if( c >= '0' && c <= '9')   
//          pctime = (10 * pctime) + (c - '0') ; // convert digits to a number            
//      }   
//      DateTime.sync(pctime);   // Sync DateTime clock to the time received on the serial port
//    }  
//  }
//}
//
//void sendTime(){
//  if(DateTime.available()) { // update clocks if time has been synced
//    //unsigned long prevtime = DateTime.now(); 
//    //while( prevtime == DateTime.now() )  // wait for the second to rollover
//      //;
//    DateTime.available(); //refresh the Date and time properties
//    //digitalClockDisplay( );   // update digital clock
//
//    // send our time to an app listening on the serial port
//    Serial.print( TIME_HEADER,BYTE); // this is the header for the current time
//    Serial.println(DateTime.now());      
//  } 
//}

