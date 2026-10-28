/* rgp:protos */
#define RGP_SELF_GameRecFindFreeInsectRecSlot_3ce0d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Slot {
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 6;
    u8 pad001[0x84B];
} Slot;

typedef struct Obj {
    u8   pad000[0x1ADC];
    Slot s[3];
} Obj;

s32 GameRecFindFreeInsectRecSlot_3ce0d0(Obj *o)
{
    Slot *p;
    s32 i;

    p = o->s;
    for (i = 0; i < 3; i++, p++) {
        if (p->b0 == 0) {
            return i;
        }
    }
    p = o->s;
    for (i = 0; i < 3; i++, p++) {
        if (p->b1 != 0) {
            return i;
        }
    }
    return -1;
}
