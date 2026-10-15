#include "types.h"

extern s32 LoaderUnitHasUserBuf_1ce250(void *);
extern s32 MemStackHeapFree_14dcb0(s32, s32);
extern s32 LoaderUnitReset_1ce370(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x88];
    s32 m88;
};

s32 LoaderUnitFree_1ce300(struct Obj0 *p0, s32 p1)
{
    s32 t0;
    s32 rv4;
    s32 r1;
    s32 rv3;
    s32 t1;
    s32 r2;
    s32 r5;

    if (p1 != 0) {
        t0 = p0->m88;
        rv4 = t0;
        if (t0 != 0) {
            r1 = LoaderUnitHasUserBuf_1ce250(p0);
            rv3 = r1;
            if (r1 == 0) {
                t1 = p0->m88;
                r2 = MemStackHeapFree_14dcb0(p1, t1);
                rv3 = r2;
            }
            rv4 = rv3;
        }
    }
    r5 = LoaderUnitReset_1ce370(p0);
    return r5;
}
