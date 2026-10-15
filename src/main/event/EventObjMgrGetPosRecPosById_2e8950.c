#include "types.h"

extern s32 DListGetHead_42ea60(s32);
extern s32 EventPosRecGetId_2e35d0(s32);
extern s32 EventPosRecGetPos_2e35b0(s32, void *);
extern s32 DListGetNext_42eb30(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    s32 m04;
    s32 m08;
    s32 m0C;
};

void EventObjMgrGetPosRecPosById_2e8950(s32 p0, struct Obj0 *p1, s32 p2)
{
    s32 r0;
    s32 l1;
    s32 r2;
    s32 r3;
    s32 r4;

    p1->m00 = 0;
    p1->m04 = 0;
    p1->m08 = 0;
    p1->m0C = 0;
    if (p2 >= 0) {
        r0 = DListGetHead_42ea60((p0 + 0x40));
        l1 = r0;
        while (l1 != 0) {
            r2 = EventPosRecGetId_2e35d0((l1 + 0x10));
            if (p2 == r2) {
                r3 = EventPosRecGetPos_2e35b0((l1 + 0x10), p1);
                return;
            }
            r4 = DListGetNext_42eb30(l1);
            l1 = r4;
        }
        return;
    }
}
