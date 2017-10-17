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
#include "NoiseSensor.h"
void NoiseSensor::init(){
    //Set a random seed
    randomSeed(analogRead(A6));
    
}
void NoiseSensor::doit(){
    // check for voice stuff?
}


//---------------------------------------------------------
//-- Otto getNoise: return Otto's noise sensor measure
//---------------------------------------------------------
int NoiseSensor::getNoise(){

  int noiseLevel = 0;
  int noiseReadings = 0;
  int numReadings = 2;  

    noiseLevel = analogRead(PIN_NoiseSensor);

    for(int i=0; i<numReadings; i++){
        noiseReadings += analogRead(PIN_NoiseSensor);
        delay(4); // delay in between reads for stability
    }

    noiseLevel = noiseReadings / numReadings;

    return noiseLevel;
}

