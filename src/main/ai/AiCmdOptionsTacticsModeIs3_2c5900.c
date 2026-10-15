#include "types.h"

extern void * GetGameData_1fede0(void);
extern s32 ScriptSlotStoreIntRef_2cc900(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0xC];
    struct Obj1 *m0C;
};

struct Obj1 {
    u8 pad000[0x24];
    s16 m24;
};

s32 AiCmdOptionsTacticsModeIs3_2c5900(s32 p0)
{
    struct Obj0 *r0;
    s16 t1;
    s32 r1;

    r0 = GetGameData_1fede0();
    t1 = r0->m0C->m24;
    r1 = ScriptSlotStoreIntRef_2cc900(p0, (t1 == 3));
    return 1;
}
