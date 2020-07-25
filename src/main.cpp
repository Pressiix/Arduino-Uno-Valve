/***** Author by Watcharaphon Piamphuetna *****/
/** Watcharapon.piam@gmail.com **/
#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#define RELAY_PIN1 13
#define RELAY_PIN2 12

const char *check_relay_status = "";

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN1, OUTPUT);
  pinMode(RELAY_PIN2, OUTPUT);    //If arduino board start, Relay will turn off
  delay(8000);
  check_relay_status = "4";
  Serial.println("ED4."); 
}

void loop() {    
  if (Serial.available()) {
     String msg = Serial.readStringUntil('.');  //read serial messege character until '.'(dot)
     /****Depend on WIFI connection*****/
         if(check_relay_status){ 
              if(digitalRead(RELAY_PIN1)&& !digitalRead(RELAY_PIN2)){  
                if(check_relay_status != "1"){  //if relay1 status = OFF and if relay2 status = OFF
                  check_relay_status = "1";   //set relay1 status = ON and relay2 status = OFF
                    Serial.println("OP1.");  
                }
              }

              if(!digitalRead(RELAY_PIN1)&& digitalRead(RELAY_PIN2)){  
                if(check_relay_status != "2"){  //if relay1 status = OFF and if relay2 status = OFF
                  check_relay_status = "2";   //set relay1 status = ON and relay2 status = OFF
                   Serial.println("OP2.");   
                }
              }

              if(digitalRead(RELAY_PIN1)&& digitalRead(RELAY_PIN2)){  
                if(check_relay_status != "3"){  //if relay1 status = OFF and if relay2 status = OFF
                  check_relay_status = "3";   //set relay1 status = ON and relay2 status = OFF
                    Serial.println("ED3.");  
                }
              }

              if(!digitalRead(RELAY_PIN1)&& !digitalRead(RELAY_PIN2)){  
                if(check_relay_status != "4"){  //if relay1 status = OFF and if relay2 status = OFF
                  check_relay_status = "4";   //set relay1 status = ON and relay2 status = OFF
                     Serial.println("ED4.");
                } 
              }
                
         }
         if(msg == "lost"){
            digitalWrite(RELAY_PIN1,LOW);
            digitalWrite(RELAY_PIN2,LOW);     //If you lost WIFI connection, Relay will turn off
            if(!digitalRead(RELAY_PIN1) && !digitalRead(RELAY_PIN2)){      //if relay turn off now
                check_relay_status = "4";     
                Serial.println("ED4.");             
              }
         }
         if(msg == "connect"){
          if(!digitalRead(RELAY_PIN1) && !digitalRead(RELAY_PIN2)){      //if relay turn off now
                check_relay_status = "4";     
                Serial.println("ED4.");             
              }
         }
     /******************************************/
        if(msg == "ON1" || msg == "ON2" || msg == "ONALL" || msg == "OFFALL"){      //If your command is ON or OFF 
          
            if(msg == "ON1"){                    //If your command is ON
              digitalWrite(RELAY_PIN1,HIGH);
              digitalWrite(RELAY_PIN2,LOW);         //Relay will turn on
            }
            if(msg == "ON2"){                   //If your command is OFF
              digitalWrite(RELAY_PIN1,LOW);
              digitalWrite(RELAY_PIN2,HIGH);      //Relay will turn off
            }
            if(msg == "ONALL"){                    //If your command is ON
              digitalWrite(RELAY_PIN1,HIGH);
              digitalWrite(RELAY_PIN2,HIGH);         //Relay will turn on
            }
            if(msg == "OFFALL"){                   //If your command is OFF
              digitalWrite(RELAY_PIN1,LOW);
              digitalWrite(RELAY_PIN2,LOW);    //Relay will turn off
              if(check_relay_status == "4"){
                Serial.println("ED4."); 
              }
            }
       }
   }
}