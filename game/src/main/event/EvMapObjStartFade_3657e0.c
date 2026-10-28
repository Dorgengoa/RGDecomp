/* rgp:protos */
#define RGP_SELF_EvMapObjStartFade_3657e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
extern s32 strcpy(void *, void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00462E68[];
extern f32 D_0047D2AC;

struct Obj0;

struct Obj0 {
    u8 pad000[0xD0];
    s32 mD0;
    u8 pad0D4[0x22C];
    s16 m300;
    s16 m302;
    u8 pad304[0x1C];
    f32 m320;
};

s32 EvMapObjStartFade_3657e0(struct Obj0 *p0)
{
    s32 t0;
    s32 rv3;
    s32 r0;
    s32 rv2;
    f32 t1;
    s32 r1;

    t0 = p0->mD0;
    rv3 = rv2;
    if ((t0 & 0x2000000) == 0) {
        rv3 = 0;
    } else {
        r0 = ((short)EvMapObjGetMode_366b80(p0));
        rv2 = 1;
        if (r0 != 2) {
            rv2 = 0;
        } else {
            t1 = D_0047D2AC;
            p0->m320 = t1;
            r1 = ((s32)strcpy((struct Obj0 *)((u8 *)p0 + 0x304), D_00462E68));
            p0->m300 = 3;
            p0->m302 = 0;
            rv2 = 1;
        }
        rv3 = rv2;
    }
    return rv3;
}
