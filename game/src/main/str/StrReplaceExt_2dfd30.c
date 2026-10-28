/* rgp:protos */
#define RGP_SELF_StrReplaceExt_2dfd30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 strlen(s32);
extern void strcpy(s32, s32);
extern void Sprintf_1343b8(s32, void *, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00461778[];

struct Obj0;

struct Obj0 {
    s8 m00;
};

void StrReplaceExt_2dfd30(s32 p0, s32 p1, s32 p2)
{
    s32 r0;
    s32 l1;
    struct Obj0 *l2;
    s8 t0;

    r0 = strlen(p1);
    l2 = (struct Obj0 *)(p1 + r0);
    l1 = 0;
    while (l1 < r0) {
        t0 = l2->m00;
        if (t0 == 0x2E) {
            l2->m00 = 0;
            break;
        }
        l2 = (struct Obj0 *)((u8 *)l2 + -1);
        l1 = (l1 + 1);
    }
    if (p2 == 0) {
        strcpy(p0, p1);
        return;
    }
    Sprintf_1343b8(p0, D_00461778, p1, p2);
}
