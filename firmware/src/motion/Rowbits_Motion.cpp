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
#include "Rowbits_Motion.h"

///////////////////////////////////////////////////////////////////
//-- ATTACH & DETACH FUNCTIONS ----------------------------------//
///////////////////////////////////////////////////////////////////

void Rowbits_Motion::detachServos(){
    for (int i = 0; i < N_SERVOS; i++) servos[i].detach();
}
///////////////////////////////////////////////////////////////////
//-- OSCILLATORS TRIMS ------------------------------------------//
///////////////////////////////////////////////////////////////////
void Rowbits_Motion::setTrim(int servoId, int trim) {
    servos[servoId].SetTrim(trim);
}


void Rowbits_Motion::saveTrimsOnEEPROM() {
  for (int i = 0; i < N_SERVOS; i++) EEPROM.write(i, servos[i].getTrim());
} 


///////////////////////////////////////////////////////////////////
//-- BASIC MOTION FUNCTIONS -------------------------------------//
///////////////////////////////////////////////////////////////////
void Rowbits_Motion::_moveServos(int lServo, int time, int  servo_target[]) {
  attachServos();
  if(time>10){
    for (int i = 0; i < lServo; i++) increment[i] = ((servo_target[i]) - servo_position[i]) / (time / 10.0);
    final_time =  millis() + time;

    for (int iteration = 1; millis() < final_time; iteration++) {
      partial_time = millis() + 10;
      for (int i = 0; i < lServo; i++) servos[i].SetPosition(servo_position[i] + (iteration * increment[i]));
      while (millis() < partial_time); //pause
    }
  }
  else{
    for (int i = 0; i < lServo; i++) servos[i].SetPosition(servo_target[i]);
  }
  for (int i = 0; i < lServo; i++) servo_position[i] = servo_target[i];
}


void Rowbits_Motion::_oscillateServos(int lServo, int A[], int O[], int T, double phase_diff[], float cycle=1.0f){

  for (int i=0; i < lServo; i++) {
    servos[i].SetO(O[i]);
    servos[i].SetA(A[i]);
    servos[i].SetT(T);
    servos[i].SetPh(phase_diff[i]);
  }
  double ref=millis();
   for (double x=ref; x<=T*cycle+ref; x=millis()){
     for (int i=0; i<4; i++){
        servos[i].refresh();
     }
  }
}


void Rowbits_Motion::_execute(int lServo, int A[4], int O[4], int T, double phase_diff[4], float steps = 1.0){
  attachServos();
  int cycles=(int)steps;    

  //-- Execute complete cycles
  if (cycles >= 1) 
    for(int i = 0; i < cycles; i++) 
      _oscillateServos(lServo,A,O, T, phase_diff);
      
  //-- Execute the final not complete cycle    
  _oscillateServos(lServo,A,O, T, phase_diff,(float)steps-cycles);
}
void Rowbits_Motion::move(int moveId, int T, int moveSize){
  switch (moveId) {
    case 0:
      home();
      break;
    case 1: //M 1 1000 
      walk(1,T,1);
      break;
    case 2: //M 2 1000 
      walk(1,T,-1);
      break;
    case 3: //M 3 1000 
      turn(1,T,1);
      break;
    case 4: //M 4 1000 
      turn(1,T,-1);
      break;
    case 5: //M 5 1000 30 
      updown(1,T,moveSize);
      break;
    case 6: //M 6 1000 30
      moonwalker(1,T,moveSize,1);
      break;
    case 7: //M 7 1000 30
      moonwalker(1,T,moveSize,-1);
      break;
    case 8: //M 8 1000 30
      swing(1,T,moveSize);
      break;
    case 9: //M 9 1000 30 
      crusaito(1,T,moveSize,1);
      break;
    case 10: //M 10 1000 30 
      crusaito(1,T,moveSize,-1);
      break;
    case 11: //M 11 1000 
      jump(1,T);
      break;
    case 12: //M 12 1000 30 
      flapping(1,T,moveSize,1);
      break;
    case 13: //M 13 1000 30
      flapping(1,T,moveSize,-1);
      break;
    case 14: //M 14 1000 20
      tiptoeSwing(1,T,moveSize);
      break;
    case 15: //M 15 500 
      bend(1,T,1);
      break;
    case 16: //M 16 500 
      bend(1,T,-1);
      break;
    case 17: //M 17 500 
      shakeLeg(1,T,1);
      break;
    case 18: //M 18 500 
      shakeLeg(1,T,-1);
      break;
    case 19: //M 19 500 20
      jitter(1,T,moveSize);
      break;
    case 20: //M 20 500 15
      ascendingTurn(1,T,moveSize);
      break;
    default:
        // Error make sounds and stuff
        
      break;
  }
}
void Rowbits_Motion::playGesture(int gesture, int moveSize){
    switch (gesture) {
      case 1: //H 1 
        gestures_Happy();
        break;
      case 2: //H 2 
        gestures_SuperHappy();
        break;
      case 3: //H 3 
        gestures_Sad();
        break;
      case 4: //H 4 
        gestures_Sleeping();
        break;
      case 5: //H 5  
        gestures_Fart();
        break;
      case 6: //H 6 
        gestures_Confused();
        break;
      case 7: //H 7 
        gestures_Love();
        break;
      case 8: //H 8 
        gestures_Angry();
        break;
      case 9: //H 9  
        gestures_Fretful();
        break;
      case 10: //H 10
        gestures_Magic();
        break;  
      case 11: //H 11
        gestures_Wave();
        break;   
      case 12: //H 12
        gestures_Victory();
        break; 
      case 13: //H 13
        gestures_Fail();
        break;         
      default:
        gestures_Error();
        break;
    }    
}

