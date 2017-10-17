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
#ifndef ROWBITS_MOTION_H
#define ROWBITS_MOTION_H

#define ROWBITS_HAS_MOTION
#define MOTION_FORWARD     1
#define MOTION_BACKWARD    -1
#define MOTION_LEFT        1
#define MOTION_RIGHT       -1
#define MOTION_SMALL       5
#define MOTION_MEDIUM      15
#define MOTION_BIG         30
#include "../Rowbits.h"
#ifdef ROWBITS_MOTION_OTTO_BASE
// Define number of servos for Motion.h
// Then link Motion and Gesture file at end of include
#define N_SERVOS 4
#endif
#ifdef ROWBITS_MOTION_OTTO_ARMED
#define N_SERVOS 6
#endif
#include "Oscillator.h"
class Rowbits_Motion {
protected:
    // used to run the methods
    Oscillator servos[N_SERVOS];
    int servo_pins[N_SERVOS];
    int servo_trim[N_SERVOS];
    int servo_position[N_SERVOS];
    
    unsigned long final_time;
    unsigned long partial_time;
    float increment[N_SERVOS];
    
public:
    //-- Attach & detach functions
    void detachServos();

    //-- Oscillator Trims
    void setTrim(int servoId, int trim);
    void saveTrimsOnEEPROM();

    //-- Predetermined Motion Functions
    void _moveServos(int lServo, int time, int  servo_target[]);
    void _oscillateServos(int l_Servos, int A[], int O[], int T, double phase_diff[], float cycle);
    void _execute(int lServo, int A[], int O[], int T, double phase_diff[], float steps);
    void move(int moveId, int T, int moveSize);
    void playGesture(int gesture, int moveSize);

    //char* getGestures(void);
    //int getGesturesLength(void); 
    
   // char* getMovements(void);
    //int getMovementsLength(void); 
    
    //-- Predetermined Motion Functions defined in extended classes
    virtual void init()=0;
    virtual void home()=0;
    virtual void attachServos()=0;
    virtual void jump(float steps=1, int T = 2000)=0;
    virtual void walk(float steps=4, int T=1000, int dir = MOTION_FORWARD)=0;
    virtual void turn(float steps=4, int T=2000, int dir = MOTION_LEFT)=0;
    virtual void bend (int steps=1, int T=1400, int dir=MOTION_LEFT)=0;
    virtual void shakeLeg (int steps=1, int T = 2000, int dir=MOTION_RIGHT)=0;
    virtual void updown(float steps=1, int T=1000, int h = 20)=0;
    virtual void swing(float steps=1, int T=1000, int h=20)=0;
    virtual void tiptoeSwing(float steps=1, int T=900, int h=20)=0;
    virtual void jitter(float steps=1, int T=500, int h=20)=0;
    virtual void ascendingTurn(float steps=1, int T=900, int h=20)=0;
    virtual void moonwalker(float steps=1, int T=900, int h=20, int dir=MOTION_LEFT)=0;
    virtual void crusaito(float steps=1, int T=900, int h=20, int dir=MOTION_FORWARD)=0;
    virtual void flapping(float steps=1, int T=1000, int h=20, int dir=MOTION_FORWARD)=0;
    
    virtual void gestures_Happy()=0;
    virtual void gestures_SuperHappy()=0;
    virtual void gestures_Sad()=0;
    virtual void gestures_Sleeping()=0;
    virtual void gestures_Fart()=0;
    virtual void gestures_Confused()=0;
    virtual void gestures_Love()=0;
    virtual void gestures_Angry()=0;
    virtual void gestures_Fretful()=0;
    virtual void gestures_Magic()=0;
    virtual void gestures_Wave()=0;
    virtual void gestures_Victory()=0;
    virtual void gestures_Fail()=0;    
    virtual void gestures_Error()=0;    
};
#ifdef ROWBITS_MOTION_OTTO_BASE
// Then link Motion and Gesture file
#include "motion/Otto_Biped.h"
#endif
#ifdef ROWBITS_MOTION_OTTO_ARMED
#include "motion/Rowbits_Biped_Armed.h"
#endif

#endif /* ROWBITS_MOTION_H */

