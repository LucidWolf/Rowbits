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
#include "UltraSonicSensor.h"
void UltraSonicSensor::init(){
    pinMode(_pinTrigger, OUTPUT); // Sets the trigPin as an Output
    pinMode(_pinEcho, INPUT); // Sets the echoPin as an Input  
}

int UltraSonicSensor::read()
{
    digitalWrite(_pinTrigger, LOW);
    delayMicroseconds(2);
    digitalWrite(_pinTrigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(_pinTrigger, LOW);
    long microseconds = pulseIn(_pinEcho,HIGH,40000); // 0.040000 sec
    long distance = microseconds/29/2;
    if (distance == 0){
      distance = ROWBITS_ULTRASOUND_MAX;
    }
    return distance;
}