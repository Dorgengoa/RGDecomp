#include "types.h"

extern void * ResGroupListCurElem_42a5d0(void);
extern s32 SlotGetInt_15f720(s32);
extern s32 strncpy(void *, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x13];
    u8 m13;
};

s32 ResGroupCmdSetName_42b3f0(s32 p0)
{
    struct Obj0 *r0;
    s32 r1;
    s32 r2;

    r0 = ResGroupListCurElem_42a5d0();
    if (r0 == 0) {
        return 1;
    }
    r1 = SlotGetInt_15f720(p0);
    r2 = strncpy((struct Obj0 *)((u8 *)r0 + 4), r1, 0xF);
    r0->m13 = 0;
    return 1;
}
