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
#ifndef Rowbits_h
#define Rowbits_h
#include <EEPROM.h>
// does all the include linking based on options specified in config file
#include "Rowbits_config.h"

class Otto_Biped;
class Rowbits_Motion;
class LedMatrix;
class Rowbits
{
  public:
    //-- Important Handles all setup routines.
    // Should be called from setup() in ino file
    static void init();  
    static void doit();  
    static void debug(const __FlashStringHelper * s);
    // movement commands
    static void home();
    static void move(int moveId, int T, int moveSize);
    static void setTrim(int servoId, int trim);
    static void setTrims(int trims[], int n);
    static void saveTrimsOnEEPROM();
    static void _moveServos(int lServo, int time, int  servo_target[]);
    //-- Sensors functions
    static int getDistance(); //US sensor
    static bool obstacleDetector(); //US sensor
    
    static int getNoise();      //Noise Sensor

    //-- Battery
    static double getBatteryLevel();
    static double getBatteryVoltage();
    
    //-- Mouth & Animations
    static void putMouth(unsigned long int mouth, bool predefined = true);
    static void putAnimationMouth(unsigned long int anim, int index);
    static void clearMouth();

    //-- Sounds
    static void _tone (float noteFrequency, long noteDuration, int silentDuration);
    static void bendTones (float initFrequency, float finalFrequency, float prop, long noteDuration, int silentDuration);
    static void sing(int songName);

    //-- Gestures
    static void playGesture(int gesture);
    static void playGesture(int gesture, int moveSize);
    static unsigned long int getMouthShape(int number);
    static unsigned long int getAnimShape(int anim, int index);

 
    static const char name_fir='#'; //First name
    static const char name_fac='$'; //Factory name
  private:

    // pointer since there can be multiples types wish it were static but required too much repeats
    // if you dont have a motion that is a sad little robot :(
#ifdef ROWBITS_MOTION_OTTO_BASE
    static Otto_Biped motion;
#endif
#ifdef ROWBITS_MOTION_OTTO_ARMED
    static Rowbits_Armed motion;
#endif
    
// moved to static procedures so no longer need variables
// Saving memory is handled by #includes
// These are here so you can copy them if you need them
/**
#ifdef ROWBITS_HAS_LED_DISPLAY
    LedMatrix;
#endif
#ifdef ROWBITS_HAS_ULTRASOUND_SENSOR
    UltraSonicSensor; 
#endif
#ifdef ROWBITS_HAS_BATTERY_SENSOR
    BatteryReader;
#endif
#ifdef ROWBITS_HAS_NOISE_SENSOR
    NoiseSensor; 
#endif
#ifdef ROWBITS_HAS_SPEAKER
    Rowbits_Speak;
#endif
#ifdef ROWBITS_HAS_BLUETOOTH
    BTCom;
#endif
#ifdef ROWBITS_HAS_SERIAL
    SerialCom;
#endif
*/
};

#endif


