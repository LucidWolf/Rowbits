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
#ifndef UltraSonicSensor_h
#define UltraSonicSensor_h
#include <Arduino.h>
#include "../Rowbits_config.h"


class UltraSonicSensor
{
public:
	static void init();
	static int read();

private:
	static const int _pinTrigger = PIN_Trigger;
	static const int _pinEcho = PIN_Echo;

};

#endif //US_h