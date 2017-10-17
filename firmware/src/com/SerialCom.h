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
#ifndef SERIALCOM_H
#define SERIALCOM_H
#include <WString.h>
#include "../Rowbits.h"
class SerialCommand;
class SerialCom {
public:
    SerialCom();
public:
    static void init();
    static void doit();
    static void debug(const __FlashStringHelper * s);
private:
    static SerialCommand SCmd;
    static void sendAck();
    static void sendFinalAck();
    static void requestRowbitConfig();
    static void receiveMovement();
    static void receiveStop();
    static void receiveLED();
    static void recieveBuzzer();
    static void receiveTrims();
    static void receiveServo();
    static void move(int moveId);
    static void receiveGesture();
    static void receiveSing();
    static void receiveName();
    static void requestName();
    static void requestDistance();
    static void requestBattery();
    static void requestProgramId();
    static void requestNoise();
    static void setupBluetooth();
};

#endif /* SERIALCOM_H */

