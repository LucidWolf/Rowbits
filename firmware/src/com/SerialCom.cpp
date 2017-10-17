//----------------------------------------------------------------
//-- Zowi basic firmware v2 adapted to RowBits for BitBloq
//-- (c) BQ. Released under a GPL licencse
//-- 04 December 2015
//-- Authors:  Anita de Prado: ana.deprado@bq.com
//--           Jose Alberca:   jose.alberca@bq.com
//--           Javier Isabel:  javier.isabel@bq.com
//--           Juan Gonzalez (obijuan): juan.gonzalez@bq.com
//--           Irene Sanz : irene.sanz@bq.com
//-- RowBits:  Aaron Harris (LucidWolf) lucidwolf <https://github.com/LucidWolf>
//-----------------------------------------------------------------
#include "SerialCom.h"
SerialCommand SerialCom::SCmd;
extern HardwareSerial Serial;
void SerialCom::init(){
    //Serial communication initialization
    Serial.begin(115200); 
    //Setup callbacks for SerialCommand commands 
    SCmd.addCommand("A", setupBluetooth);
    SCmd.addCommand("B", requestBattery);
    SCmd.addCommand("C", receiveTrims);     //  sendAck & sendFinalAck
    SCmd.addCommand("D", requestDistance);
    SCmd.addCommand("E", requestName);
    SCmd.addCommand("G", receiveServo);     //  sendAck & sendFinalAck
    SCmd.addCommand("H", receiveGesture);   //  sendAck & sendFinalAck
    SCmd.addCommand("I", requestProgramId);
    SCmd.addCommand("K", receiveSing);      //  sendAck & sendFinalAck
    SCmd.addCommand("L", receiveLED);       //  sendAck & sendFinalAck
    SCmd.addCommand("M", receiveMovement);  //  sendAck & sendFinalAck
    SCmd.addCommand("N", requestNoise);
    SCmd.addCommand("R", receiveName);      //  sendAck & sendFinalAck
    SCmd.addCommand("S", receiveStop);      //  sendAck & sendFinalAck
    SCmd.addCommand("T", recieveBuzzer);    //  sendAck & sendFinalAck
    SCmd.addCommand("Z", requestRowbitConfig); //  sendAck & sendFinalAck
    SCmd.addDefaultHandler(receiveStop);
    
}
void SerialCom::debug(const __FlashStringHelper * s){
#ifdef DEBUG_ROWBITS
    if(Serial.available()){
        Serial.println(s);
    }
#endif    
    
}
void SerialCom::doit(){
    if(Serial.available()){
    //If Otto is moving yet
        SCmd.readSerial();   
    }
}
///////////////////////////////////////////////////////////////////
//-- Functions --------------------------------------------------//
///////////////////////////////////////////////////////////////////
//-- Function to send Ack comand (A)
void SerialCom::sendAck(){
  Serial.print(F("&&"));
  Serial.print(F("A"));
  Serial.println(F("%%"));
  Serial.flush();
}
//-- Function to send final Ack comand (F)
void SerialCom::sendFinalAck(){
  delay(30);
  Serial.print(F("&&"));
  Serial.print(F("F"));
  Serial.println(F("%%"));
  Serial.flush();
}
//-- Function to receive Stop command.
void SerialCom::setupBluetooth(){
    BTCom::setup();
}
//-- Function to receive Stop command.
void SerialCom::requestRowbitConfig(){
    
}
//-- Function to receive Stop command.
void SerialCom::receiveStop(){
    sendAck();
    Rowbits::home();
    sendFinalAck();

}


//-- Function to receive LED commands
void SerialCom::receiveLED(){  

    //sendAck & stop if necessary
    sendAck();
    Rowbits::home();

    //Examples of receiveLED Bluetooth commands
    //L 000000001000010100100011000000000
    //L 001111111111111111111111111111111 (todos los LED encendidos)
    unsigned long int matrix;
    char *arg;
    char *endstr;
    arg=SCmd.next();
    //Serial.println (arg);
    if (arg != NULL) {
      matrix=strtoul(arg,&endstr,2);    // Converts a char string to unsigned long integer
      Rowbits::putMouth(matrix,false);
    }else{
      Rowbits::putMouth(xMouth);
      delay(2000);
      Rowbits::clearMouth();
    }

    sendFinalAck();

}
//-- Function to receive buzzer commands
void SerialCom::recieveBuzzer(){
  
    //sendAck & stop if necessary
    sendAck();
    Rowbits::home(); 

    bool error = false; 
    int frec;
    int duration; 
    char *arg; 
    
    arg = SCmd.next(); 
    if (arg != NULL) { frec=atoi(arg); }    // Converts a char string to an integer   
    else {error=true;}
    
    arg = SCmd.next(); 
    if (arg != NULL) { duration=atoi(arg); } // Converts a char string to an integer  
    else {error=true;}

    if(error==true){

      Rowbits::putMouth(xMouth);
      delay(2000);
      Rowbits::clearMouth();

    }else{ 

      Rowbits::_tone(frec, duration, 1);   
    }

    sendFinalAck();

}


//-- Function to receive TRims commands
void SerialCom::receiveTrims(){  

    //sendAck & stop if necessary
    sendAck();
    Rowbits::home(); 

    int trims [N_SERVOS];
    
    //Definition of Servo Bluetooth command
    //C trim_YL trim_YR trim_RL trim_RR
    //Examples of receiveTrims Bluetooth commands
    //C 20 0 -8 3
    bool stop = false;
    int i = 0;
    char *arg;
    while(!stop){
        arg=SCmd.next();
        if (arg != NULL) {
            trims[i] = atoi(arg);
            i++;
        }else{
            stop = true;
        }
    }
    //Save it on EEPROM
    Rowbits::setTrims(trims, i);
    Rowbits::saveTrimsOnEEPROM(); 
    sendFinalAck();
}


//-- Function to receive Servo commands
void SerialCom::receiveServo(){  

    sendAck(); 
    int moveId = 30;

    //Definition of Servo Bluetooth command
    //G  servo_YL servo_YR servo_RL servo_RR 
    //Example of receiveServo Bluetooth commands
    //G 90 85 96 78 
    bool error = false;
    char *arg;
    int servo_YL,servo_YR,servo_RL,servo_RR;

    arg=SCmd.next();
    if (arg != NULL) { servo_YL=atoi(arg); }    // Converts a char string to an integer   
    else {error=true;}

    arg = SCmd.next(); 
    if (arg != NULL) { servo_YR=atoi(arg); }    // Converts a char string to an integer  
    else {error=true;}

    arg = SCmd.next(); 
    if (arg != NULL) { servo_RL=atoi(arg); }    // Converts a char string to an integer  
    else {error=true;}

    arg = SCmd.next(); 
    if (arg != NULL) { servo_RR=atoi(arg); }    // Converts a char string to an integer  
    else {error=true;}
    
    if(error==true){

      Rowbits::putMouth(xMouth);
      delay(2000);
      Rowbits::clearMouth();

    }else{ //Update Servo:

      int servoPos[4]={servo_YL, servo_YR, servo_RL, servo_RR}; 
      Rowbits::_moveServos(4, 200, servoPos);   //Move 200ms
      
    }

    sendFinalAck();

}


//-- Function to receive movement commands
void SerialCom::receiveMovement(){
    int T=1000;              //Initial duration of movement
    int moveId=0;            //Number of movement
    int moveSize=15;         //Associated with the height of some movements

    sendAck();

    //Definition of Movement Bluetooth commands
    //M  MoveID  T   MoveSize  
    
    char *arg; 
    arg = SCmd.next(); 
    if (arg != NULL) {
        moveId=atoi(arg);
    }
    else{
      Rowbits::putMouth(xMouth);
      delay(2000);
      Rowbits::clearMouth();
      moveId=0; //stop
    }
    
    arg = SCmd.next(); 
    if (arg != NULL) {T=atoi(arg);}
    else{
      T=1000;
    }

    arg = SCmd.next(); 
    if (arg != NULL) {moveSize=atoi(arg);}
    else{
      moveSize =15;
    }
    Rowbits::move(moveId,T,moveSize);
    sendFinalAck();
}
//-- Function to receive gesture commands
void SerialCom::receiveGesture(){

    //sendAck & stop if necessary
    sendAck();
    Rowbits::home(); 

    //Definition of Gesture Bluetooth commands
    //H  GestureID  
    int gesture = 0;
    char *arg; 
    arg = SCmd.next(); 
    if (arg != NULL) {
        gesture=atoi(arg);
    }
    else{
      Rowbits::putMouth(xMouth);
      Rowbits::sing(S_confused);
      delay(2000);
      Rowbits::clearMouth();
    }
    Rowbits::playGesture(gesture);

    sendFinalAck();
}

//-- Function to receive sing commands
void SerialCom::receiveSing(){

    //sendAck & stop if necessary
    sendAck();
    Rowbits::home(); 

    //Definition of Sing Bluetooth commands
    //K  SingID    
    int sing = 0;
    char *arg; 
    arg = SCmd.next(); 
    if (arg != NULL) {sing=atoi(arg);}
    else 
    {
      Rowbits::putMouth(xMouth);
      delay(2000);
      Rowbits::clearMouth();
    }

    switch (sing) {
      case 1: //K 1 
        Rowbits::sing(S_connection);
        break;
      case 2: //K 2 
        Rowbits::sing(S_disconnection);
        break;
      case 3: //K 3 
        Rowbits::sing(S_surprise);
        break;
      case 4: //K 4 
        Rowbits::sing(S_OhOoh);
        break;
      case 5: //K 5  
        Rowbits::sing(S_OhOoh2);
        break;
      case 6: //K 6 
        Rowbits::sing(S_cuddly);
        break;
      case 7: //K 7 
        Rowbits::sing(S_sleeping);
        break;
      case 8: //K 8 
        Rowbits::sing(S_happy);
        break;
      case 9: //K 9  
        Rowbits::sing(S_superHappy);
        break;
      case 10: //K 10
        Rowbits::sing(S_happy_short);
        break;  
      case 11: //K 11
        Rowbits::sing(S_sad);
        break;   
      case 12: //K 12
        Rowbits::sing(S_confused);
        break; 
      case 13: //K 13
        Rowbits::sing(S_fart1);
        break;
      case 14: //K 14
        Rowbits::sing(S_fart2);
        break;
      case 15: //K 15
        Rowbits::sing(S_fart3);
        break;    
      case 16: //K 16
        Rowbits::sing(S_mode1);
        break; 
      case 17: //K 17
        Rowbits::sing(S_mode2);
        break; 
      case 18: //K 18
        Rowbits::sing(S_mode3);
        break;   
      case 19: //K 19
        Rowbits::sing(S_buttonPushed);
        break;                      
      default:
        break;
    }

    sendFinalAck();
}
//-- Function to receive Name command
void SerialCom::receiveName(){

    //sendAck & stop if necessary
    sendAck();
    Rowbits::home(); 

    char newOttoName[11] = "";  //Variable to store data read from Serial.
    int eeAddress = 5;          //Location we want the data to be in EEPROM.
    char *arg; 
    arg = SCmd.next(); 
    
    if (arg != NULL) {

      //Complete newOttoName char string
      int k = 0;
      while((*arg) && (k<11)){ 
          newOttoName[k]=*arg++;
          k++;
      }
      
      EEPROM.put(eeAddress, newOttoName); 
    }
    else 
    {
      Rowbits::putMouth(xMouth);
      delay(2000);
      Rowbits::clearMouth();
    }

    sendFinalAck();

}
//-- Function to send Otto's name
void SerialCom::requestName(){

    Rowbits::home(); //stop if necessary

    char actualOttoName[11]= "";  //Variable to store data read from EEPROM.
    int eeAddress = 5;            //EEPROM address to start reading from

    //Get the float data from the EEPROM at position 'eeAddress'
    EEPROM.get(eeAddress, actualOttoName);

    Serial.print(F("&&"));
    Serial.print(F("E "));
    Serial.print(actualOttoName);
    Serial.println(F("%%"));
    Serial.flush();
}


//-- Function to send ultrasonic sensor measure (distance in "cm")
void SerialCom::requestDistance(){

    Rowbits::home();  //stop if necessary  

    int distance = Rowbits::getDistance();
    Serial.print(F("&&"));
    Serial.print(F("D "));
    Serial.print(distance);
    Serial.println(F("%%"));
    Serial.flush();
}

//-- Function to send battery voltage percent
void SerialCom::requestBattery(){

    Rowbits::home();  //stop if necessary

    //The first read of the batery is often a wrong reading, so we will discard this value. 
    double batteryLevel = Rowbits::getBatteryLevel();

    Serial.print(F("&&"));
    Serial.print(F("B "));
    Serial.print(batteryLevel);
    Serial.println(F("%%"));
    Serial.flush();
}


//-- Function to send program ID
void SerialCom::requestProgramId(){

    Rowbits::home();   //stop if necessary

    Serial.print(F("&&"));
    Serial.print(F("I "));
    Serial.print(F(ROWBITS_PROGRAM_ID));
    Serial.println(F("%%"));
    Serial.flush();
}
//-- Function to send noise sensor measure
void SerialCom::requestNoise(){

    Rowbits::home();  //stop if necessary

    int microphone= Rowbits::getNoise(); //analogRead(PIN_NoiseSensor);
    Serial.print(F("&&"));
    Serial.print(F("N "));
    Serial.print(microphone);
    Serial.println(F("%%"));
    Serial.flush();
}
