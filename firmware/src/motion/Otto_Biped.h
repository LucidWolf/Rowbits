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
#ifndef OTTO_BIPED_H
#define OTTO_BIPED_H
#include "../Rowbits.h"

/*
                --------------- 
               |     O   O     |
               |---------------|
               |               |
                ----------------    
      YR S2==>     ||     ||    <== YL S1
                   ||     ||
      RR S4==>   -----   ------  <== RL S3
                |-----   ------|
*/

class Otto_Biped : public Rowbits_Motion{
public:
    // major access
    using Rowbits_Motion::move;
    using Rowbits_Motion::playGesture;
    using Rowbits_Motion::detachServos;
    using Rowbits_Motion::setTrim;
    using Rowbits_Motion::saveTrimsOnEEPROM;
    // <>< make protected?
    using Rowbits_Motion::_moveServos;
    using Rowbits_Motion::_oscillateServos;
    using Rowbits_Motion::_execute;
    
    void init();
    void attachServos();
    //-- Predetermined Motion Functions
    void home();
    void jump(float steps=1, int T = 2000);
    void walk(float steps=4, int T=1000, int dir = MOTION_FORWARD);
    void turn(float steps=4, int T=2000, int dir = MOTION_LEFT);
    void bend (int steps=1, int T=1400, int dir=MOTION_LEFT);
    void shakeLeg (int steps=1, int T = 2000, int dir=MOTION_RIGHT);
    void updown(float steps=1, int T=1000, int h = 20);
    void swing(float steps=1, int T=1000, int h=20);
    void tiptoeSwing(float steps=1, int T=900, int h=20);
    void jitter(float steps=1, int T=500, int h=20);
    void ascendingTurn(float steps=1, int T=900, int h=20);
    void moonwalker(float steps=1, int T=900, int h=20, int dir=MOTION_LEFT);
    void crusaito(float steps=1, int T=900, int h=20, int dir=MOTION_FORWARD);
    void flapping(float steps=1, int T=1000, int h=20, int dir=MOTION_FORWARD);
    void gestures_Happy();
    void gestures_SuperHappy();
    void gestures_Sad();
    void gestures_Sleeping();
    void gestures_Fart();
    void gestures_Confused();
    void gestures_Love();
    void gestures_Angry();
    void gestures_Fretful();
    void gestures_Magic();
    void gestures_Wave();
    void gestures_Victory();
    void gestures_Fail();    
    void gestures_Error();    
};

#endif /* OTTO_BIPED_H */

