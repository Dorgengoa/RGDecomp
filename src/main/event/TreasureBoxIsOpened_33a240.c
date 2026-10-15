#include "types.h"

extern void * GetGameData_1fede0(void);
extern s32 StateFlag2Test_3cc860(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;
struct Obj2;

struct Obj0 {
    u8 pad000[0x68];
    struct Obj1 *m68;
};

struct Obj1 {
    u8 pad000[0x8];
    s16 m08;
};

struct Obj2 {
    u8 pad000[0x10];
    s32 m10;
};

s32 TreasureBoxIsOpened_33a240(struct Obj0 *p0)
{
    struct Obj1 * t0;
    s32 rv4;
    struct Obj2 *r0;
    s32 rv3;
    struct Obj1 * t1;
    s16 t2;
    s32 rv2;
    s32 t3;
    s32 r1;

    t0 = p0->m68;
    rv4 = rv3;
    if (t0 == 0) {
        rv4 = 0;
    } else {
        r0 = GetGameData_1fede0();
        rv3 = rv2;
        if (r0 == 0) {
            rv3 = 0;
        } else {
            t1 = p0->m68;
            t2 = p0->m68->m08;
            rv2 = (r1 & 0xFF);
            if (t2 < 0) {
                rv2 = 0;
            } else {
                t3 = r0->m10;
                r1 = StateFlag2Test_3cc860(t3, t2);
                rv2 = (r1 & 0xFF);
            }
            rv3 = rv2;
        }
        rv4 = rv3;
    }
    return rv4;
}
