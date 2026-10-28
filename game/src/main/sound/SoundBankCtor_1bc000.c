/* rgp:protos */
#define RGP_SELF_SoundBankCtor_1bc000 1
#include "port/game_protos.h"
#line 1
#include "types.h"
u8 *SoundBankCtor_1bc000(u8 *p)
{
    u8 *q = p + 0x160;
    s16 v = -1;
    do { *(s16 *)q = v; q += 8; } while (q < p + 0x1E0);
    return p;
}
