/* rgp:protos */
#define RGP_SELF_CameraResetParams_3090a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;
struct Obj2;

struct Obj0 {
    u8 pad000[0xC];
    struct Obj1 *m0C;
};

struct Obj1 {
    u8 pad000[0x1A];
    s16 m1A;
};

struct Obj2 {
    u8 pad000[0x2E1];
    u8 m2E1;
};

void CameraResetParams_3090a0(struct Obj2 *p0)
{
    struct Obj0 *r1;
    struct Obj1 * t0;
    s16 t1;
    s32 r2;

    CameraSetDefaultParams_309260(p0);
    r1 = GetGameData_1fede0();
    t0 = r1->m0C;
    t1 = r1->m0C->m1A;
    r2 = (CameraSetPresetParams_309100((struct Obj2 *)((u8 *)p0 + 0x15C), (t1 & 1)), (s32)0);
    CameraSetClampEaseDivMaybe_161e10(2.0f);
    p0->m2E1 = 0;
}
