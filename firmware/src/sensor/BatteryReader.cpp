/******************************************************************************
* Zowi Battery Reader Library
* 
* @version 20150831
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
#include "BatteryReader.h"

double BatteryReader::readBatVoltage(void) {    
	double readed = (double)(analogRead(PIN_BATTERY)*BAT_ANA_REF)/1024;
	if(readed > BAT_MAX) return BAT_MAX;
	else return readed;
}

double BatteryReader::readBatPercent(void) {
	double value = (BAT_SLOPE*readBatVoltage()) - BAT_OFFSET;
	if(value < 0) return 0;
	else return value;
}

