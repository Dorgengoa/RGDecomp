/* rgp:protos */
#define RGP_SELF_EquipSlotClearGauge_3a0030 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern struct Obj1 * D_00483748;

struct Obj0;
struct Obj1;
struct Obj2;

struct Obj0 {
    u8 pad000[0x4];
    s32 m04;
    u8 pad008[0x8];
    s32 m10;
};

struct Obj1 {
    u8 pad000[0x20];
    struct Obj2 *m20;
};

struct Obj2 {
    u8 pad000[0x24C];
    u8 m24C;
};

s32 EquipSlotClearGauge_3a0030(struct Obj0 *p0)
{
    s32 rv1;
    s32 rv0;

    if (p0->m04 == 0) {
        rv1 = 0;
    } else {
        rv0 = 1;
        if ((D_00483748->m20->m24C & 1) == 0) {
            rv0 = 0;
        } else {
            p0->m10 = 0;
            rv0 = 1;
        }
        rv1 = rv0;
    }
    return rv1;
}
