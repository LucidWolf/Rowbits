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
#ifndef ROWBITS_SPEAK_H
#define ROWBITS_SPEAK_H
#include "../Rowbits.h"
class Rowbits_Speak {
public:
    Rowbits_Speak();
    static void _tone (float noteFrequency, long noteDuration, int silentDuration);
    static void bendTones (float initFrequency, float finalFrequency, float prop, long noteDuration, int silentDuration);
    static void sing(int songName);
private:

};

#endif /* ROWBITS_SPEAK_H */

