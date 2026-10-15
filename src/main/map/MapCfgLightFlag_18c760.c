#include "types.h"

typedef struct E8W { u8 b[8]; } E8W;

extern void * ListNodeGetData_18a370(s32);
extern s32 VariantGetInt_15f780(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00481254;

struct Obj0;

struct Obj0 {
    u8 pad000[0x128];
    s32 m128;
    s32 m12C;
};

s32 MapCfgLightFlag_18c760(s32 p0)
{
    s32 t0;
    struct Obj0 *r0;
    s32 rv3;
    s32 r1;
    s32 r2;
    E8W *q;

    q = (E8W *)p0;
    t0 = D_00481254;
    if (t0 == 0) {
        return 0;
    }
    r0 = ListNodeGetData_18a370(t0);
    rv3 = 1;
    if (r0 == 0) {
        rv3 = 0;
    } else {
        r1 = VariantGetInt_15f780((s32)q++);
        r0->m128 = r1;
        r2 = VariantGetInt_15f780((s32)q);
        r0->m12C = r2;
        rv3 = 1;
    }
    return rv3;
}
