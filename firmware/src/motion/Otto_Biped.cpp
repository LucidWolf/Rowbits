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
#include "Otto_Biped.h"
void Otto_Biped::init(){
    servo_trim[0] = 0;
    servo_trim[1] = 0;
    servo_trim[2] = 0;
    servo_trim[3] = 0;
    servo_position[0] = 90;
    servo_position[1] = 90;
    servo_position[2] = 90;
    servo_position[3] = 90;
    attachServos();
}
void Otto_Biped::home(){ //Go to rest position only if necessary
    int homes[4]={90, 90, 90, 90}; //All the servos at rest position
    _moveServos(4,500,homes);   //Move the servos in half a second
    detachServos();
}
///////////////////////////////////////////////////////////////////
//-- ATTACH & DETACH FUNCTIONS ----------------------------------//
///////////////////////////////////////////////////////////////////
void Otto_Biped::attachServos(){
    servos[0].attach(PIN_SERVO1);
    servos[1].attach(PIN_SERVO2);
    servos[2].attach(PIN_SERVO3);
    servos[3].attach(PIN_SERVO4);
}

///////////////////////////////////////////////////////////////////
//-- PREDETERMINED MOTION SEQUENCES -----------------------------//
///////////////////////////////////////////////////////////////////

//---------------------------------------------------------
//-- Otto movement: Jump
//--  Parameters:
//--    steps: Number of steps
//--    T: Period
//---------------------------------------------------------
void Otto_Biped::jump(float steps, int T){

  int up[N_SERVOS]={90,90,150,30};
  _moveServos(N_SERVOS,T,up);
  int down[N_SERVOS]={90,90,90,90};
  _moveServos(N_SERVOS,T,down);
}

//---------------------------------------------------------
//-- Otto gait: Walking  (forward or backward)    
//--  Parameters:
//--    * steps:  Number of steps
//--    * T : Period
//--    * Dir: Direction: FORWARD / BACKWARD
//---------------------------------------------------------
void Otto_Biped::walk(float steps, int T, int dir){

  //-- Oscillator parameters for walking
  //-- Hip sevos are in phase
  //-- Feet servos are in phase
  //-- Hip and feet are 90 degrees out of phase
  //--      -90 : Walk forward
  //--       90 : Walk backward
  //-- Feet servos also have the same offset (for tiptoe a little bit)
  int A[N_SERVOS]= {30, 30, 20, 20};
  int O[N_SERVOS] = {0, 0, 4, -4};
  double phase_diff[N_SERVOS] = {0, 0, DEG2RAD(dir * -90), DEG2RAD(dir * -90)};

  //-- Let's oscillate the servos!
  _execute(N_SERVOS, A, O, T, phase_diff, steps);  
}
//---------------------------------------------------------
//-- Otto gait: Turning (left or right)
//--  Parameters:
//--   * Steps: Number of steps
//--   * T: Period
//--   * Dir: Direction: LEFT / RIGHT
//---------------------------------------------------------
void Otto_Biped::turn(float steps, int T, int dir){

  //-- Same coordination than for walking (see Otto::walk)
  //-- The Amplitudes of the hip's oscillators are not egual
  //-- When the right hip servo amplitude is higher, the steps taken by
  //--   the right leg are bigger than the left. So, the robot describes an 
  //--   left arc
  int A[N_SERVOS]= {30, 30, 20, 20};
  int O[N_SERVOS] = {0, 0, 4, -4};
  double phase_diff[N_SERVOS] = {0, 0, DEG2RAD(-90), DEG2RAD(-90)}; 
    
  if (dir == MOTION_LEFT) {  
    A[0] = 30; //-- Left hip servo
    A[1] = 10; //-- Right hip servo
  }
  else {
    A[0] = 10;
    A[1] = 30;
  }
    
  //-- Let's oscillate the servos!
  _execute(N_SERVOS, A, O, T, phase_diff, steps); 
}


//---------------------------------------------------------
//-- Otto gait: Lateral bend
//--  Parameters:
//--    steps: Number of bends
//--    T: Period of one bend
//--    dir: RIGHT=Right bend LEFT=Left bend
//---------------------------------------------------------
void Otto_Biped::bend (int steps, int T, int dir){

  //Parameters of all the movements. Default: Left bend
  int bend1[N_SERVOS]={90, 90, 62, 35}; 
  int bend2[N_SERVOS]={90, 90, 62, 105};
  int homes[N_SERVOS]={90, 90, 90, 90};

  //Time of one bend, constrained in order to avoid movements too fast.
  //T=max(T, 600);

  //Changes in the parameters if right direction is chosen 
  if(dir==-1)
  {
    bend1[2]=180-35;
    bend1[3]=180-60;  //Not 65. Otto is unbalanced
    bend2[2]=180-105;
    bend2[3]=180-60;
  }

  //Time of the bend movement. Fixed parameter to avoid falls
  int T2=800; 

  //Bend movement
  for (int i=0;i<steps;i++)
  {
    _moveServos(N_SERVOS, T2/2,bend1);
    _moveServos(N_SERVOS, T2/2,bend2);
    delay(T*0.8);
    _moveServos(N_SERVOS, 500,homes);
  }

}


//---------------------------------------------------------
//-- Otto gait: Shake a leg
//--  Parameters:
//--    steps: Number of shakes
//--    T: Period of one shake
//--    dir: RIGHT=Right leg LEFT=Left leg
//---------------------------------------------------------
void Otto_Biped::shakeLeg (int steps,int T,int dir){

  //This variable change the amount of shakes
  int numberLegMoves=2;

  //Parameters of all the movements. Default: Right leg
  int shake_leg1[N_SERVOS]={90, 90, 58, 35};   
  int shake_leg2[N_SERVOS]={90, 90, 58, 120};
  int shake_leg3[N_SERVOS]={90, 90, 58, 60};
  int homes[N_SERVOS]={90, 90, 90, 90};

  //Changes in the parameters if left leg is chosen
  if(dir==-1)      
  {
    shake_leg1[2]=180-35;
    shake_leg1[3]=180-58;
    shake_leg2[2]=180-120;
    shake_leg2[3]=180-58;
    shake_leg3[2]=180-60;
    shake_leg3[3]=180-58;
  }
  
  //Time of the bend movement. Fixed parameter to avoid falls
  int T2=1000;    
  //Time of one shake, constrained in order to avoid movements too fast.            
  T=T-T2;
  T=max(T,200*numberLegMoves);  

  for (int j=0; j<steps;j++)
  {
  //Bend movement
  _moveServos(N_SERVOS,T2/2,shake_leg1);
  _moveServos(N_SERVOS,T2/2,shake_leg2);
  
    //Shake movement
    for (int i=0;i<numberLegMoves;i++)
    {
    _moveServos(N_SERVOS,T/(2*numberLegMoves),shake_leg3);
    _moveServos(N_SERVOS,T/(2*numberLegMoves),shake_leg2);
    }
    _moveServos(N_SERVOS,500,homes); //Return to home position
  }
  
  delay(T);
}


//---------------------------------------------------------
//-- Otto movement: up & down
//--  Parameters:
//--    * steps: Number of jumps
//--    * T: Period
//--    * h: Jump height: SMALL / MEDIUM / BIG 
//--              (or a number in degrees 0 - 90)
//---------------------------------------------------------
void Otto_Biped::updown(float steps, int T, int h){

  //-- Both feet are 180 degrees out of phase
  //-- Feet amplitude and offset are the same
  //-- Initial phase for the right foot is -90, so that it starts
  //--   in one extreme position (not in the middle)
  int A[N_SERVOS]= {0, 0, h, h};
  int O[N_SERVOS] = {0, 0, h, -h};
  double phase_diff[N_SERVOS] = {0, 0, DEG2RAD(-90), DEG2RAD(90)};
  
  //-- Let's oscillate the servos!
  _execute(N_SERVOS,A, O, T, phase_diff, steps); 
}


//---------------------------------------------------------
//-- Otto movement: swinging side to side
//--  Parameters:
//--     steps: Number of steps
//--     T : Period
//--     h : Amount of swing (from 0 to 50 aprox)
//---------------------------------------------------------
void Otto_Biped::swing(float steps, int T, int h){

  //-- Both feets are in phase. The offset is half the amplitude
  //-- It causes the robot to swing from side to side
  int A[N_SERVOS]= {0, 0, h, h};
  int O[N_SERVOS] = {0, 0, h/2, -h/2};
  double phase_diff[N_SERVOS] = {0, 0, DEG2RAD(0), DEG2RAD(0)};
  
  //-- Let's oscillate the servos!
  _execute(N_SERVOS,A, O, T, phase_diff, steps); 
}


//---------------------------------------------------------
//-- Otto movement: swinging side to side without touching the floor with the heel
//--  Parameters:
//--     steps: Number of steps
//--     T : Period
//--     h : Amount of swing (from 0 to 50 aprox)
//---------------------------------------------------------
void Otto_Biped::tiptoeSwing(float steps, int T, int h){

  //-- Both feets are in phase. The offset is not half the amplitude in order to tiptoe
  //-- It causes the robot to swing from side to side
  int A[N_SERVOS]= {0, 0, h, h};
  int O[N_SERVOS] = {0, 0, h, -h};
  double phase_diff[N_SERVOS] = {0, 0, 0, 0};
  
  //-- Let's oscillate the servos!
  _execute(N_SERVOS,A, O, T, phase_diff, steps); 
}


//---------------------------------------------------------
//-- Otto gait: Jitter 
//--  Parameters:
//--    steps: Number of jitters
//--    T: Period of one jitter 
//--    h: height (Values between 5 - 25)   
//---------------------------------------------------------
void Otto_Biped::jitter(float steps, int T, int h){

  //-- Both feet are 180 degrees out of phase
  //-- Feet amplitude and offset are the same
  //-- Initial phase for the right foot is -90, so that it starts
  //--   in one extreme position (not in the middle)
  //-- h is constrained to avoid hit the feets
  h=min(25,h);
  int A[N_SERVOS]= {h, h, 0, 0};
  int O[N_SERVOS] = {0, 0, 0, 0};
  double phase_diff[N_SERVOS] = {DEG2RAD(-90), DEG2RAD(90), 0, 0};
  
  //-- Let's oscillate the servos!
  _execute(N_SERVOS,A, O, T, phase_diff, steps); 
}


//---------------------------------------------------------
//-- Otto gait: Ascending & turn (Jitter while up&down)
//--  Parameters:
//--    steps: Number of bends
//--    T: Period of one bend
//--    h: height (Values between 5 - 15) 
//---------------------------------------------------------
void Otto_Biped::ascendingTurn(float steps, int T, int h){

  //-- Both feet and legs are 180 degrees out of phase
  //-- Initial phase for the right foot is -90, so that it starts
  //--   in one extreme position (not in the middle)
  //-- h is constrained to avoid hit the feets
  h=min(13,h);
  int A[N_SERVOS]= {h, h, h, h};
  int O[N_SERVOS] = {0, 0, h+4, -h+4};
  double phase_diff[N_SERVOS] = {DEG2RAD(-90), DEG2RAD(90), DEG2RAD(-90), DEG2RAD(90)};
  
  //-- Let's oscillate the servos!
  _execute(N_SERVOS,A, O, T, phase_diff, steps); 
}


//---------------------------------------------------------
//-- Otto gait: Moonwalker. Otto moves like Michael Jackson
//--  Parameters:
//--    Steps: Number of steps
//--    T: Period
//--    h: Height. Typical valures between 15 and 40
//--    dir: Direction: LEFT / RIGHT
//---------------------------------------------------------
void Otto_Biped::moonwalker(float steps, int T, int h, int dir){

  //-- This motion is similar to that of the caterpillar robots: A travelling
  //-- wave moving from one side to another
  //-- The two Otto's feet are equivalent to a minimal configuration. It is known
  //-- that 2 servos can move like a worm if they are 120 degrees out of phase
  //-- In the example of Otto, the two feet are mirrored so that we have:
  //--    180 - 120 = 60 degrees. The actual phase difference given to the oscillators
  //--  is 60 degrees.
  //--  Both amplitudes are equal. The offset is half the amplitud plus a little bit of
  //-   offset so that the robot tiptoe lightly
 
  int A[N_SERVOS]= {0, 0, h, h};
  int O[N_SERVOS] = {0, 0, h/2+2, -h/2 -2};
  int phi = -dir * 90;
  double phase_diff[N_SERVOS] = {0, 0, DEG2RAD(phi), DEG2RAD(-60 * dir + phi)};
  
  //-- Let's oscillate the servos!
  _execute(N_SERVOS,A, O, T, phase_diff, steps); 
}


//----------------------------------------------------------
//-- Otto gait: Crusaito. A mixture between moonwalker and walk
//--   Parameters:
//--     steps: Number of steps
//--     T: Period
//--     h: height (Values between 20 - 50)
//--     dir:  Direction: LEFT / RIGHT
//-----------------------------------------------------------
void Otto_Biped::crusaito(float steps, int T, int h, int dir){

  int A[N_SERVOS]= {25, 25, h, h};
  int O[N_SERVOS] = {0, 0, h/2+ 4, -h/2 - 4};
  double phase_diff[N_SERVOS] = {90, 90, DEG2RAD(0), DEG2RAD(-60 * dir)};
  
  //-- Let's oscillate the servos!
  _execute(N_SERVOS,A, O, T, phase_diff, steps); 
}


//---------------------------------------------------------
//-- Otto gait: Flapping
//--  Parameters:
//--    steps: Number of steps
//--    T: Period
//--    h: height (Values between 10 - 30)
//--    dir: direction: FOREWARD, BACKWARD
//---------------------------------------------------------
void Otto_Biped::flapping(float steps, int T, int h, int dir){

  int A[N_SERVOS]= {12, 12, h, h};
  int O[N_SERVOS] = {0, 0, h - 10, -h + 10};
  double phase_diff[N_SERVOS] = {DEG2RAD(0), DEG2RAD(180), DEG2RAD(-90 * dir), DEG2RAD(90 * dir)};
  
  //-- Let's oscillate the servos!
  _execute(N_SERVOS,A, O, T, phase_diff, steps); 
}
///////////////////////////////////////////////////////////////////
//-- GESTURES ---------------------------------------------------//
///////////////////////////////////////////////////////////////////

void Otto_Biped::gestures_Happy(){
        Rowbits::_tone(note_E5,50,30);
        Rowbits::putMouth(smile);
        Rowbits::sing(S_happy_short);
        swing(1,800,20); 
        Rowbits::sing(S_happy_short);

        Rowbits::home();
        Rowbits::putMouth(happyOpen);

}
void Otto_Biped::gestures_SuperHappy(){
        Rowbits::putMouth(happyOpen);
        Rowbits::sing(S_happy);
        Rowbits::putMouth(happyClosed);
        tiptoeSwing(1,500,20);
        Rowbits::putMouth(happyOpen);
        Rowbits::sing(S_superHappy);
        Rowbits::putMouth(happyClosed);
        tiptoeSwing(1,500,20); 
        home();  
        Rowbits::putMouth(happyOpen);

}
void Otto_Biped::gestures_Sad(){
        int sadPos[4]=      {110, 70, 20, 160};
        Rowbits::putMouth(sad);
        _moveServos(4,700, sadPos);     
        Rowbits::bendTones(880, 830, 1.02, 20, 200);
        Rowbits::putMouth(sadClosed);
        Rowbits::bendTones(830, 790, 1.02, 20, 200);  
        Rowbits::putMouth(sadOpen);
        Rowbits::bendTones(790, 740, 1.02, 20, 200);
        Rowbits::putMouth(sadClosed);
        Rowbits::bendTones(740, 700, 1.02, 20, 200);
        Rowbits::putMouth(sadOpen);
        Rowbits::bendTones(700, 669, 1.02, 20, 200);
        Rowbits::putMouth(sad);
        delay(500);
        home();
        delay(300);
        Rowbits::putMouth(happyOpen);
}
void Otto_Biped::gestures_Sleeping(){
        int bedPos[4]=      {100, 80, 60, 120};
        _moveServos(4,700, bedPos);     

        for(int i=0; i<4;i++){
        Rowbits::putAnimationMouth(dreamMouth,0);
        Rowbits::bendTones (100, 200, 1.04, 10, 10);
        Rowbits::putAnimationMouth(dreamMouth,1);
        Rowbits::bendTones (200, 300, 1.04, 10, 10);  
        Rowbits::putAnimationMouth(dreamMouth,2);
        Rowbits::bendTones (300, 500, 1.04, 10, 10);   
        delay(500);
        Rowbits::putAnimationMouth(dreamMouth,1);
        Rowbits::bendTones (400, 250, 1.04, 10, 1); 
        Rowbits::putAnimationMouth(dreamMouth,0);
        Rowbits::bendTones (250, 100, 1.04, 10, 1); 
          delay(500);
        }
        
        Rowbits::putMouth(lineMouth);
        Rowbits::sing(S_cuddly);
        home();  
        Rowbits::putMouth(happyOpen);
}
void Otto_Biped::gestures_Fart(){
  int fartPos_1[4]=   {90, 90, 145, 122}; //rightBend
  int fartPos_2[4]=   {90, 90, 80, 122};
  int fartPos_3[4]=   {90, 90, 145, 80};
        _moveServos(4,500,fartPos_1);
        delay(300);     
        Rowbits::putMouth(lineMouth);
        Rowbits::sing(S_fart1);  
        Rowbits::putMouth(tongueOut);
        delay(250);
        _moveServos(4,500,fartPos_2);
        delay(300);
        Rowbits::putMouth(lineMouth);
        Rowbits::sing(S_fart2); 
        Rowbits::putMouth(tongueOut);
        delay(250);
        _moveServos(4,500,fartPos_3);
        delay(300);
        Rowbits::putMouth(lineMouth);
        Rowbits::sing(S_fart3);
        Rowbits::putMouth(tongueOut);    
        delay(300);

        home(); 
        delay(500); 
        Rowbits::putMouth(happyOpen);
}
void Otto_Biped::gestures_Confused(){
  int confusedPos[4]= {110, 70, 90, 90};
        _moveServos(4,300, confusedPos); 
        Rowbits::putMouth(confused);
        Rowbits::sing(S_confused);
        delay(500);

        home();  
        Rowbits::putMouth(happyOpen);

}
void Otto_Biped::gestures_Love(){
        Rowbits::putMouth(heart);
        Rowbits::sing(S_cuddly);
        crusaito(2,1500,15,1);

        home(); 
        Rowbits::sing(S_happy_short);  
        Rowbits::putMouth(happyOpen);

}
void Otto_Biped::gestures_Angry(){
  int angryPos[4]=    {90, 90, 70, 110};
  int headLeft[4]=    {110, 110, 90, 90};
  int headRight[4]=   {70, 70, 90, 90};
        _moveServos(4,300, angryPos); 
        Rowbits::putMouth(angry);

        Rowbits::_tone(note_A5,100,30);
        Rowbits::bendTones(note_A5, note_D6, 1.02, 7, 4);
        Rowbits::bendTones(note_D6, note_G6, 1.02, 10, 1);
        Rowbits::bendTones(note_G6, note_A5, 1.02, 10, 1);
        delay(15);
        Rowbits::bendTones(note_A5, note_E5, 1.02, 20, 4);
        delay(400);
        _moveServos(4,200, headLeft); 
        Rowbits::bendTones(note_A5, note_D6, 1.02, 20, 4);
        _moveServos(4,200, headRight); 
        Rowbits::bendTones(note_A5, note_E5, 1.02, 20, 4);

        home();  
        Rowbits::putMouth(happyOpen);
}
void Otto_Biped::gestures_Fretful(){
  int fretfulPos[4]=  {90, 90, 90, 110};
        Rowbits::putMouth(angry);
        Rowbits::bendTones(note_A5, note_D6, 1.02, 20, 4);
        Rowbits::bendTones(note_A5, note_E5, 1.02, 20, 4);
        delay(300);
        Rowbits::putMouth(lineMouth);

        for(int i=0; i<4; i++){
          _moveServos(4,100, fretfulPos);   
          home();
        }

        Rowbits::putMouth(angry);
        delay(500);

        home();  
        Rowbits::putMouth(happyOpen);

}
void Otto_Biped::gestures_Magic(){

        //Initial note frecuency = 400
        //Final note frecuency = 1000
        
        // Reproduce the animation four times
        for(int i = 0; i<4; i++){ 

          int noteM = 400; 

            for(int index = 0; index<6; index++){
              Rowbits::putAnimationMouth(adivinawi,index);
              Rowbits::bendTones(noteM, noteM+100, 1.04, 10, 10);    //400 -> 1000 
              noteM+=100;
            }

            Rowbits::clearMouth();
            Rowbits::bendTones(noteM-100, noteM+100, 1.04, 10, 10);  //900 -> 1100

            for(int index = 0; index<6; index++){
              Rowbits::putAnimationMouth(adivinawi,index);
              Rowbits::bendTones(noteM, noteM+100, 1.04, 10, 10);    //1000 -> 400 
              noteM-=100;
            }
        } 
 
        delay(300);
        Rowbits::putMouth(happyOpen);

}
void Otto_Biped::gestures_Wave(){
        
        // Reproduce the animation four times
        for(int i = 0; i<2; i++){ 

            int noteW = 500; 

            for(int index = 0; index<10; index++){
              Rowbits::putAnimationMouth(wave,index);
              Rowbits::bendTones(noteW, noteW+100, 1.02, 10, 10); 
              noteW+=101;
            }
            for(int index = 0; index<10; index++){
              Rowbits::putAnimationMouth(wave,index);
              Rowbits::bendTones(noteW, noteW+100, 1.02, 10, 10); 
              noteW+=101;
            }
            for(int index = 0; index<10; index++){
              Rowbits::putAnimationMouth(wave,index);
              Rowbits::bendTones(noteW, noteW-100, 1.02, 10, 10); 
              noteW-=101;
            }
            for(int index = 0; index<10; index++){
              Rowbits::putAnimationMouth(wave,index);
              Rowbits::bendTones(noteW, noteW-100, 1.02, 10, 10); 
              noteW-=101;
            }
        }    

        Rowbits::clearMouth();
        delay(100);
        Rowbits::putMouth(happyOpen);

}
void Otto_Biped::gestures_Victory(){
        
        Rowbits::putMouth(smallSurprise);
        //final pos   = {90,90,150,30}
        for (int i = 0; i < 60; ++i){
          int pos[]={90,90,90+i,90-i};  
          _moveServos(4,10,pos);
          Rowbits::_tone(1600+i*20,15,1);
        }

        Rowbits::putMouth(bigSurprise);
        //final pos   = {90,90,90,90}
        for (int i = 0; i < 60; ++i){
          int pos[]={90,90,150-i,30+i};  
          _moveServos(4,10,pos);
          Rowbits::_tone(2800+i*20,15,1);
        }

        Rowbits::putMouth(happyOpen);
        //SUPER HAPPY
        //-----
        tiptoeSwing(1,500,20);
        Rowbits::sing(S_superHappy);
        Rowbits::putMouth(happyClosed);
        tiptoeSwing(1,500,20); 
        //-----

        home();
        Rowbits::clearMouth();
        Rowbits::putMouth(happyOpen);

}
void Otto_Biped::gestures_Fail(){
    int bendPos_1[4]=   {90, 90, 70, 35};
    int bendPos_2[4]=   {90, 90, 55, 35};
    int bendPos_3[4]=   {90, 90, 42, 35};
    int bendPos_4[4]=   {90, 90, 34, 35};

        Rowbits::putMouth(sadOpen);
        _moveServos(4,300,bendPos_1);
        Rowbits::_tone(900,200,1);
        Rowbits::putMouth(sadClosed);
        _moveServos(4,300,bendPos_2);
        Rowbits::_tone(600,200,1);
        Rowbits::putMouth(confused);
        _moveServos(4,300,bendPos_3);
        Rowbits::_tone(300,200,1);
        _moveServos(4,300,bendPos_4);
        Rowbits::putMouth(xMouth);

        detachServos();
        Rowbits::_tone(150,2200,1);
        
        delay(600);
        Rowbits::clearMouth();
        Rowbits::putMouth(happyOpen);
        home();   
}
void Otto_Biped::gestures_Error(){
      Rowbits::putMouth(xMouth);
      Rowbits::sing(S_confused);
      delay(2000);
      Rowbits::clearMouth();
}
