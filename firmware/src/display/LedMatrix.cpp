/******************************************************************************
* Zowi LED Matrix Library
* 
* @version 20150710
* @author Raul de Pablos Martin
*         José Alberca Pita-Romero (Mouth's definitions)
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

#include "LedMatrix.h"

unsigned long LedMatrix::memory;


void LedMatrix::init() {
	memory = 0x00000000;
	pinMode(PIN_LED_SER, OUTPUT);
	pinMode(PIN_LED_CLK, OUTPUT);
	pinMode(PIN_LED_RLK, OUTPUT);
	digitalWrite(PIN_LED_SER, LOW);
	digitalWrite(PIN_LED_CLK, LOW);
	digitalWrite(PIN_LED_RLK, LOW);
	sendMemory();
}

void LedMatrix::writeFull(unsigned long value) {
	memory = value;
	sendMemory();
}

unsigned long LedMatrix::readFull(void) {
	return memory;
}

void LedMatrix::setLed(char row, char column) {
	if(row >= 1 && row <= ROWS && column >= 1 && column <= COLUMNS) {
		memory |= (1L << (MATRIX_LENGTH - (row-1)*COLUMNS - (column)));
		sendMemory();
	}
}

void LedMatrix::unsetLed(char row, char column) {
	if(row >= 1 && row <= ROWS && column >= 1 && column <= COLUMNS) {
		memory &= ~(1L << (MATRIX_LENGTH - (row-1)*COLUMNS - (column)));
		sendMemory();
	}
}

void LedMatrix::clearMatrix(void) {
	memory = 0x00000000;
	sendMemory();
}

void LedMatrix::setEntireMatrix(void) {
	memory = 0x3FFFFFFF;
	sendMemory();
}

void LedMatrix::sendMemory(void) {
	int i;
	
	for(i = 0; i < MATRIX_LENGTH; i++) {
		digitalWrite(PIN_LED_SER, 1L & (memory >> i));	
		// ## adjust this delay to match with 74HC595 timing
		asm volatile ("nop");
		asm volatile ("nop");
		asm volatile ("nop");
		digitalWrite(PIN_LED_CLK, 1);
		// ## adjust this delay to match with 74HC595 timing
		asm volatile ("nop");
		asm volatile ("nop");
		asm volatile ("nop");
		digitalWrite(PIN_LED_CLK, 0);	
	}
	
	digitalWrite(PIN_LED_RLK, 1);
	// ## adjust this delay to match with 74HC595 timing
	asm volatile ("nop");
	asm volatile ("nop");
	asm volatile ("nop");
	digitalWrite(PIN_LED_RLK, 0);	
}

