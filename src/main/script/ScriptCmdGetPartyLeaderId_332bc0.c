#include "types.h"

extern void * GetGameData_1fede0(void);
extern s32 ScriptSlotStoreIntRef_3347f0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x18];
    struct Obj1 *m18;
};

struct Obj1 {
    u8 pad000[0x18E];
    s16 m18E;
};

s32 ScriptCmdGetPartyLeaderId_332bc0(s32 p0, s32 p1)
{
    struct Obj0 *r0;
    s32 rv3;
    s32 rv2;
    struct Obj1 * t0;
    s16 t1;
    s32 r1;

    r0 = GetGameData_1fede0();
    rv3 = rv2;
    if (r0 == 0) {
        rv3 = 0;
    } else {
        rv2 = 1;
        if (p1 != 1) {
            rv2 = 0;
        } else {
            t0 = r0->m18;
            t1 = r0->m18->m18E;
            r1 = ScriptSlotStoreIntRef_3347f0(p0, t1);
            rv2 = 1;
        }
        rv3 = rv2;
    }
    return rv3;
}
