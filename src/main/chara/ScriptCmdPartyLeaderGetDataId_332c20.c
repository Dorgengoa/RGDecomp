#include "types.h"

extern void * GetGameData_1fede0(void);
extern s32 CharaGetDataIdById_3a8a10(s32, s32);
extern s32 ScriptSlotStoreIntRef_3347f0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x14];
    s32 m14;
    struct Obj1 *m18;
};

struct Obj1 {
    u8 pad000[0x18E];
    s16 m18E;
};

s32 ScriptCmdPartyLeaderGetDataId_332c20(s32 p0, s32 p1)
{
    struct Obj0 *r0;
    s32 rv4;
    s32 rv3;
    struct Obj1 * t0;
    s16 t1;
    s32 t2;
    s32 r1;
    s32 r2;

    r0 = GetGameData_1fede0();
    rv4 = rv3;
    if (r0 == 0) {
        rv4 = 0;
    } else {
        rv3 = 1;
        if (p1 != 1) {
            rv3 = 0;
        } else {
            t0 = r0->m18;
            t1 = r0->m18->m18E;
            t2 = r0->m14;
            r1 = CharaGetDataIdById_3a8a10(t2, t1);
            r2 = ScriptSlotStoreIntRef_3347f0(p0, r1);
            rv3 = 1;
        }
        rv4 = rv3;
    }
    return rv4;
}
