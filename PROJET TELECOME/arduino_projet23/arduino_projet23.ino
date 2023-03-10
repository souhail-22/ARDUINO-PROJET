#include <MFRC522.h>

#include <Servo.h>
Servo s1;


/////new add /////////////
#include <SoftwareSerial.h>



////////////////////////////
#include <SPI.h>
#include <HardwareSerial.h>
SoftwareSerial  Serial2(2,3);
//HardwareSerial  Serial2(3);
SoftwareSerial hc05(0, 1);
MFRC522 rfid(10,9);
//////////////////////////////////variable  mot de pass et id valid pour rfid //////////
String my_id ="6A A9 2A B4";
String localValue = "ABCD123";
////////////////////////////////////////////////////////////////////////////////////////
void setup() {

  ////////////////////////////
  Serial2.begin(9600);
  ////////////////////////////
    s1.attach(5);
    hc05.begin(9600); 
    Serial.begin(9600);
    SPI.begin();
    rfid.PCD_Init();

}
int cp=0;
int ccp=0;
void loop() {
  ///////////////////test 555//////////
  if (Serial2.available() > 0) {
    String message = Serial2.readString();
   valid();
    Serial.println(message);
  }

/////////////////////// code module hc05 blueuthoot /////////
 if (hc05.available() > 0) {
    String receivedValue = hc05.readString();

    if (receivedValue == localValue) {
      Serial.println("Valid");
       valid();
    } else {
      Serial.println("Error");
        err();
    }
  }
//////////////////////////////////////////////////////////////////


    
////////////////// code RFID /////////////////

if(card_detected()){
 if(my_id==Card_id()){
   Serial.println("Carte valider");
     valid();
  //  tone(8,1200,200);
  //  delay(3330);
  //  tone(8,1200,200);
   //cp=0;
 }else{
       err();   
     //  cp++;
  //  Serial.println("Carte non valider");
  // Serial.println(Card_id());
  //  tone(8,1300,800);
  // if(cp==3){
  //    tone(8,1100,4000);
  //   cp=0;
  // }
   }
}
////////////////////////////////////////////
}
//////////////////////////// fonction de RFID //////////////////////////
 bool card_detected(){
   if(!rfid.PICC_IsNewCardPresent())
   return false;

   if(!rfid.PICC_ReadCardSerial())
   return false;
   return true; 
 }

String Card_id(){
  String id;
for(byte i=0; i<4;i++){
 id+= String(rfid.uid.uidByte[i],HEX);
if(i<3) id+=' ';
}
id.toUpperCase();
rfid.PICC_HaltA();
rfid.PCD_StopCrypto1();
return id;

}

////////////////////////////////////////////////////////////////////////////////

 void err(){
  ccp++;
        tone(8,1300,800);
        if(ccp==3){

          Serial.println("VOUS AVER ECHOUER 3 FOIS ");
        tone(8,1100,4000);
        ccp=0;
         } 
 }


 void valid(){
   tone(8,1200,200);
   s1.write(90);
   delay(7000);
   s1.write(0);
           //delay(3330);
           //tone(8,1200,200);
             ccp=0;
 }
