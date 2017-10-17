/******************************************************************************
* Zowi LED Matrix Library
* 
* @version 20150710
* @author Raul de Pablos Martin
*		  José Alberca Pita-Romero (Mouth's definitions)
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
#ifndef __LEDMATRIX_H__
#define __LEDMATRIX_H__
#include "../Rowbits.h"
////////////////////////////
// Definitions            //
////////////////////////////
#define ROWS 5
#define COLUMNS 6
#define MATRIX_LENGTH ROWS*COLUMNS
class LedMatrix
{
public:
	// LedMatrix -- LedMatrix class constructor
	static void init();	
	// writeFull
	static void writeFull(unsigned long value);	
	// readFull
	static unsigned long readFull(void);	
	// setLed
	static void setLed(char row, char column);	
	// unsetLed
	static void unsetLed(char row, char column);	
	// readLed
	static bool readLed(char row, char column);	
	// clearMatrix
	static void clearMatrix(void);
	// setEntireMatrix
	static void setEntireMatrix(void);
private:	
    static unsigned long memory;
    static void sendMemory(void);

};

#endif // LEDMATRIX_H //
