/******************************************************************************
* Zowi Battery Reader Library
* 
* @version 20150824
* @author Raul de Pablos Martin
*
******************************************************************************/
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
#ifndef __BATTERYREADER_H__
#define __BATTERYREADER_H__

#include <Arduino.h>
#include <pins_arduino.h>
#include "../Rowbits_config.h"
////////////////////////////
// Definitions            //
////////////////////////////
#define BAT_SLOPE	100/(BAT_MAX - BAT_MIN)
#define BAT_OFFSET	(100*BAT_MIN)/(BAT_MAX - BAT_MIN)

class BatteryReader
{
public:
    // readBatPercent
    static double readBatVoltage(void);	
    // readBatPercent
    static double readBatPercent(void);
};
#endif // BATREADER_H //
