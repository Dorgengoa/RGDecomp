/* rgp:protos */
#define RGP_SELF_InsectCageMenuGetCursorInvItem_38f550 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00483310;
extern u8 D_004E94E0[];

struct Obj0;
struct Obj1;
struct Obj2;

struct Obj0 {
    u8 pad000[0x10];
    s16 m10;
    s16 m12;
};

struct Obj1 {
    u8 pad000[0x18];
    s32 m18;
};

struct Obj2 {
    s32 m00;
};

s32 InsectCageMenuGetCursorInvItem_38f550(struct Obj2 *p0)
{
    struct Obj0 *r0;
    s32 t0;
    struct Obj1 *r1;
    s16 t1;
    s16 t2;
    s32 t3;
    s32 r2;

    r0 = UiEntryListFindDataByTag_28ec30(D_004E94E0, 0x7534);
    t0 = D_00483310;
    r1 = GetGameData_1fede0();
    t1 = r0->m10;
    t2 = r0->m12;
    t3 = r1->m18;
    r2 = ((s32)InvFindByCategoryIndex_3c86e0(t3, 0, t0, t1, t2, 0));
    p0->m00 = r2;
    return r2;
}
