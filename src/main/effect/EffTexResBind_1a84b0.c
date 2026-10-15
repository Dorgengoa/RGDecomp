#include "types.h"

extern void * GetDrawCtx_15de80(void);
extern s32 NameTableRegisterImArchiveFwd_1594c0(s32, s32, s32, s32);
extern s32 TexAnimeTableLoadFromImg_159340(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x4];
    s32 m04;
    s32 m08;
    s32 m0C;
};

struct Obj1 {
    u8 pad000[0x3BA0];
    s32 m3BA0;
};

void EffTexResBind_1a84b0(struct Obj0 *p0, s32 p1, s32 p2, s32 p3)
{
    struct Obj1 *r0;
    s32 t0;
    s32 t1;
    s32 r1;
    s32 rv3;
    s32 rv4;
    s32 t2;
    s32 r2;

    if (p1 != 0) {
        p0->m08 = p1;
        r0 = GetDrawCtx_15de80();
        t0 = r0->m3BA0;
        t1 = p0->m08;
        r1 = NameTableRegisterImArchiveFwd_1594c0(t0, t1, p2, 0);
        p0->m04 = p2;
        rv3 = r1;
        rv4 = 0;
        if (p3 != 0) {
            t2 = p0->m08;
            r2 = TexAnimeTableLoadFromImg_159340(t0, t2, p3);
            p0->m0C = r2;
            rv3 = r2;
            rv4 = p3;
        } else {
            p0->m0C = 0;
            rv3 = r1;
            rv4 = 0;
        }
        return;
    }
}
