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
#ifndef ROWBITS_CONFIG_H
#define ROWBITS_CONFIG_H
#define ROWBITS_PROGRAM_ID "ZOWI_BASE_v2" //Makes App happy
// ### UNCOMMENT SENSORS YOU HAVE
#define ROWBITS_HAS_SPEAKER
#define ROWBITS_HAS_ULTRASOUND_SENSOR
//#define ROWBITS_HAS_BATTERY_SENSOR
//#define ROWBITS_HAS_NOISE_SENSOR
//#define ROWBITS_HAS_LED_DISPLAY
#define ROWBITS_HAS_BLUETOOTH
#define ROWBITS_HAS_SERIAL
// #######  MOTION TYPE ##############
// ### ONLY ONE MOTION ALLOWED
#define ROWBITS_MOTION_OTTO_BASE
//#define ROWBITS_MOTION_OTTO_ARMED
//#define ROWBITS_MOTION_KAME_QUAD
//#define ROWBITS_MOTION_KAME_QUAD_ARMED

#define PIN_SERVO1 2
#define PIN_SERVO2 3
#define PIN_SERVO3 4
#define PIN_SERVO4 5
#define PIN_SERVO5 6
#define PIN_SERVO6 7
#define PIN_SERVO7 -1
#define PIN_SERVO8 -1
#define PIN_SERVO9 -1
#define PIN_SERVO10 -1

#define PIN_Trigger 8
#define PIN_Echo    9

#define PIN_Buzzer  10

#define PIN_LED_SER  11
#define PIN_LED_CLK  13
#define PIN_LED_RLK  12

#define PIN_BT_RX  A0
#define PIN_BT_TX  A1

#define PIN_NoiseSensor A6
#define PIN_BATTERY A7

#define ROWBITS_DETECT_DISTANCE 15

#define BAT_MAX	4.2
#define BAT_MIN	3.25
#define BAT_ANA_REF 5
#define BAT_NUM_READ 10

// includes that should always be around
#include "motion/Rowbits_Motion.h"
#include "sound/Rowbits_Sounds.h"
#include "display/Rowbits_mouths.h"
#ifdef ROWBITS_HAS_ULTRASOUND_SENSOR
#include "sensor/UltraSonicSensor.h"
#endif
#ifdef ROWBITS_HAS_BATTERY_SENSOR
#include "sensor/BatteryReader.h"
#endif
#ifdef ROWBITS_HAS_SPEAKER
#include "sound/Rowbits_Speak.h"
#endif
#ifdef ROWBITS_HAS_NOISE_SENSOR
#include "sensor/NoiseSensor.h"
#endif
#ifdef ROWBITS_HAS_LED_DISPLAY
#include "display/LedMatrix.h"
#endif
// Communications
// BT has to come before serial to turn on software serial support.
// That is by undefining the serial command hardware only flag...
#define SERIALCOMMAND_HARDWAREONLY 1
#ifdef ROWBITS_HAS_BLUETOOTH
// serial command flags for saving space
#undef SERIALCOMMAND_HARDWAREONLY
#include "com/BTCom.h"
#endif
#ifdef ROWBITS_HAS_SERIAL
#include "com/SerialCom.h"
#endif
#define DEBUG_ROWBITS;
#define Gestures_CMD_Happy              0
#define Gestures_CMD_SuperHappy 	1
#define Gestures_CMD_Sad 		2
#define Gestures_CMD_Sleeping 	3
#define Gestures_CMD_Fart 		4
#define Gestures_CMD_Confused 	5
#define Gestures_CMD_Love 		6
#define Gestures_CMD_Angry 		7
#define Gestures_CMD_Fretful 	8
#define Gestures_CMD_Magic 		9
#define Gestures_CMD_Wave 		10
#define Gestures_CMD_Victory 	11
#define Gestures_CMD_Fail 		12

#define ROWBITS_ULTRASOUND_MAX   999;

#endif
