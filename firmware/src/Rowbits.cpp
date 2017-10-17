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

// See Rowbits.h for Pin setup from linked config file
#include "Rowbits.h"
///////////////////////////////////////////////////////////////////
//-- Define variables -------------------------------//
///////////////////////////////////////////////////////////////////
const char Rowbits::name_fir; //First name
#ifdef ROWBITS_MOTION_OTTO_BASE
Otto_Biped Rowbits::motion;
#endif
#ifdef ROWBITS_MOTION_OTTO_ARMED
    static Rowbits_Armed motion;
#endif

///////////////////////////////////////////////////////////////////
//-- Build Rowbits -------------------------------//
///////////////////////////////////////////////////////////////////
void Rowbits::init(){
#ifdef ROWBITS_HAS_SERIAL
    SerialCom::init();
#endif    
#ifdef ROWBITS_HAS_BLUETOOTH
    BTCom::init();
#endif    
#ifdef ROWBITS_HAS_LED_DISPLAY
    LedMatrix::init();
#endif
#ifdef ROWBITS_HAS_MOTION
    motion.init();
#endif
#ifdef ROWBITS_HAS_ULTRASOUND_SENSOR
    UltraSonicSensor::init();
#endif
    //Otto wake up!
    sing(S_connection);
    home();
    // give it time to home
    delay(50);

  //If Otto's name is '&' (factory name) means that is the first time this program is executed.
  //This first time, Otto mustn't do anything. Just born at the factory!
  //5 = EEPROM address that contains first name character
  if (EEPROM.read(5)==name_fac){ 

    EEPROM.put(5, name_fir); //From now, the name is '#'
    EEPROM.put(6, '\0'); 
    putMouth(culito);
  }  
#ifdef ROWBITS_HAS_SERIAL
    debug(F("Finished Setup"));
#endif    

}
///////////////////////////////////////////////////////////////////
//-- Run Rowbits -------------------------------//
///////////////////////////////////////////////////////////////////
void Rowbits::doit(){
#ifdef ROWBITS_HAS_SERIAL
    SerialCom::doit();
#endif    
#ifdef ROWBITS_HAS_BLUETOOTH
    BTCom::doit();
#endif    
} 
void Rowbits::debug(const __FlashStringHelper * s){
#ifdef ROWBITS_HAS_SERIAL
    SerialCom::debug(s);
#endif        
}
///////////////////////////////////////////////////////////////////
//-- HOME = Otto at rest position -------------------------------//
///////////////////////////////////////////////////////////////////
void Rowbits::home(){
#ifdef ROWBITS_HAS_MOTION
    motion.home();
#endif
    
}
//-- Function to execute the right movement according the movement command received.

void Rowbits::move(int moveId, int T, int moveSize){
#ifdef ROWBITS_HAS_MOTION
    motion.move(moveId, T, moveSize);
#endif
    
}
void Rowbits::playGesture(int gesture){
    playGesture(gesture, MOTION_MEDIUM);
}
void Rowbits::playGesture(int gesture, int moveSize){
#ifdef ROWBITS_HAS_MOTION
    motion.playGesture(gesture, moveSize);
#endif    
}
void Rowbits::setTrim(int servoId, int trim){
#ifdef ROWBITS_HAS_MOTION
    motion.setTrim(servoId, trim);
#endif    
}
void Rowbits::setTrims(int trims[], int n){
#ifdef ROWBITS_HAS_MOTION
    for (int i = 0; i < n; i++) {
        motion.setTrim(i, trims[i]);
    }
#endif    
}
void Rowbits::saveTrimsOnEEPROM(){
#ifdef ROWBITS_HAS_MOTION
    motion.saveTrimsOnEEPROM();
#endif    
}
void Rowbits::_moveServos(int lServo, int time, int  servo_target[]){
#ifdef ROWBITS_HAS_MOTION
    motion._moveServos(lServo, time, servo_target);
#endif    
}
///////////////////////////////////////////////////////////////////
//-- SENSORS FUNCTIONS  -----------------------------------------//
///////////////////////////////////////////////////////////////////

//---------------------------------------------------------
//-- Otto getDistance: return Otto's ultrasonic sensor measure
//---------------------------------------------------------
int Rowbits::getDistance(){
#ifdef ROWBITS_HAS_ULTRASOUND_SENSOR
    return UltraSonicSensor::read(); 
#else
    return ROWBITS_ULTRASOUND_MAX
#endif

}
//-- Function to read distance sensor & to actualize obstacleDetected variable
bool Rowbits::obstacleDetector(){
    return (getDistance() < ROWBITS_DETECT_DISTANCE);
}

//---------------------------------------------------------
//-- Otto getNoise: return Otto's noise sensor measure
//---------------------------------------------------------
int Rowbits::getNoise(){
#ifdef ROWBITS_HAS_NOISE_SENSOR
    return NoiseSensor::getNoise();
#else
    return 0;
#endif
    
}


//---------------------------------------------------------
//-- Otto getBatteryLevel: return battery voltage percent
//---------------------------------------------------------
double Rowbits::getBatteryLevel(){
#ifdef ROWBITS_HAS_BATTERY_SENSOR
  //The first read of the batery is often a wrong reading, so we will discard this value. 
    double batteryLevel = BatteryReader::readBatPercent();
    
    double batteryReadings = 0;
    for(int i=0; i< BAT_NUM_READ; i++){
        batteryReadings += BatteryReader::readBatPercent();
        delay(1); // delay in between reads for stability
    }
    batteryLevel = batteryReadings / BAT_NUM_READ;
    return batteryLevel;
#else
    return 1.0;
#endif
}

double Rowbits::getBatteryVoltage(){
#ifdef ROWBITS_HAS_BATTERY_SENSOR
  //The first read of the battery is often a wrong reading, so we will discard this value. 
    double batteryLevel = BatteryReader::readBatVoltage();
    double batteryReadings = 0;
    for(int i=0; i<BAT_NUM_READ; i++){
        batteryReadings += BatteryReader::readBatVoltage();
        delay(1); // delay in between reads for stability
    }
    batteryLevel = batteryReadings /BAT_NUM_READ;
    return batteryLevel;
#else
    return BAT_MAX;
#endif
}

///////////////////////////////////////////////////////////////////
//-- MOUTHS & ANIMATIONS ----------------------------------------//
///////////////////////////////////////////////////////////////////

unsigned long int Rowbits::getMouthShape(int number){
  unsigned long int types []={zero_code,one_code,two_code,three_code,four_code,five_code,six_code,seven_code,eight_code,
  nine_code,smile_code,happyOpen_code,happyClosed_code,heart_code,bigSurprise_code,smallSurprise_code,tongueOut_code,
  vamp1_code,vamp2_code,lineMouth_code,confused_code,diagonal_code,sad_code,sadOpen_code,sadClosed_code,
  okMouth_code, xMouth_code,interrogation_code,thunder_code,culito_code,angry_code};
  return types[number];
}


unsigned long int Rowbits::getAnimShape(int anim, int index){

  unsigned long int littleUuh_code[]={
     0b00000000000000001100001100000000,
     0b00000000000000000110000110000000,
     0b00000000000000000011000011000000,
     0b00000000000000000110000110000000,
     0b00000000000000001100001100000000,
     0b00000000000000011000011000000000,
     0b00000000000000110000110000000000,
     0b00000000000000011000011000000000  
  };

  unsigned long int dreamMouth_code[]={
     0b00000000000000000000110000110000,
     0b00000000000000010000101000010000,  
     0b00000000011000100100100100011000,
     0b00000000000000010000101000010000           
  };

  unsigned long int adivinawi_code[]={
     0b00100001000000000000000000100001,
     0b00010010100001000000100001010010,
     0b00001100010010100001010010001100,
     0b00000000001100010010001100000000,
     0b00000000000000001100000000000000,
     0b00000000000000000000000000000000
  };

  unsigned long int wave_code[]={
     0b00001100010010100001000000000000,
     0b00000110001001010000100000000000,
     0b00000011000100001000010000100000,
     0b00000001000010000100001000110000,
     0b00000000000001000010100100011000,
     0b00000000000000100001010010001100,
     0b00000000100000010000001001000110,
     0b00100000010000001000000100000011,
     0b00110000001000000100000010000001,
     0b00011000100100000010000001000000    
  };

  switch  (anim){

    case littleUuh:
        return littleUuh_code[index];
        break;
    case dreamMouth:
        return dreamMouth_code[index];
        break;
    case adivinawi:
        return adivinawi_code[index];
        break;
    case wave:
        return wave_code[index];
        break;    
  }  
  return littleUuh_code[index];
}
void Rowbits::putAnimationMouth(unsigned long int aniMouth, int index){
#ifdef ROWBITS_HAS_LED_DISPLAY
    LedMatrix::writeFull(getAnimShape(aniMouth,index));
#endif
}
void Rowbits::putMouth(unsigned long int mouth, bool predefined){
#ifdef ROWBITS_HAS_LED_DISPLAY
  if (predefined){
    LedMatrix::writeFull(getMouthShape(mouth));
  }
  else{
    LedMatrix::writeFull(mouth);
  }
#endif
}
void Rowbits::clearMouth(){
#ifdef ROWBITS_HAS_LED_DISPLAY
    LedMatrix::clearMatrix();
#endif
}
///////////////////////////////////////////////////////////////////
//-- SOUNDS -----------------------------------------------------//
///////////////////////////////////////////////////////////////////
void Rowbits::_tone (float noteFrequency, long noteDuration, int silentDuration){
#ifdef ROWBITS_HAS_SPEAKER    
      Rowbits_Speak::_tone(noteFrequency, noteDuration, silentDuration);
#endif
}
void Rowbits::bendTones (float initFrequency, float finalFrequency, float prop, long noteDuration, int silentDuration){
#ifdef ROWBITS_HAS_SPEAKER    
      Rowbits_Speak::bendTones (initFrequency, finalFrequency, prop, noteDuration, silentDuration);
#endif
}
void Rowbits::sing(int songName){
#ifdef ROWBITS_HAS_SPEAKER    
      Rowbits_Speak::sing(songName);
#endif
}




