/* rgp:protos */
#define RGP_SELF_ObjMgrInit_3bc2d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_004659C8;
extern s32 D_004659D0;

struct Obj0;

struct Obj0 {
    u8 pad000[0x10];
    s32 m10;
};

u8 ObjMgrInit_3bc2d0(struct Obj0 *p0, s32 p1)
{
    s32 r1;
    s32 rv6;
    s32 r3;
    s32 t0;
    s32 t1;
    s32 t2;
    u8 r4;

    if (p1 == 0) {
        return 0;
    }
    ObjMgrResetFields_3bc390(p0);
    r1 = ((s32)MemStackNew_14e130(0x2C, p1));
    if (r1 != 0) {
        PoolCtor_36b0c0(r1);
        p0->m10 = r1;
    } else {
        p0->m10 = r1;
    }
    if (r1 == 0) {
        return 0;
    }
    {
        r3 = ObjMaxClassSize_3bed60();
        t0 = p0->m10;
        t1 = D_004659C8;
        t2 = D_004659D0;
        r4 = PoolInit_36ae50(t0, p1, r3, t1, t2);
        ObjMgrGroupLetterSlotsReset_3bc270(p0);
        return r4;
    }
}
