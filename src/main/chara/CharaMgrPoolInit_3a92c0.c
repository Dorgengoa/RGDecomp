#include "types.h"

extern void CharaMgrPoolReset_3a9370(void *);
extern s32 MemStackNew_14e130(s32, s32);
extern void PoolCtor_36b0c0(s32);
extern s32 CharaMaxClassSize_3afba0(void);
extern s32 PoolInit_36ae50(s32, s32, s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern const s32 D_004659B8;
extern const s32 D_004659C0;

struct Obj0;

struct Obj0 {
    u8 pad000[0x8];
    s32 m08;
};

s32 CharaMgrPoolInit_3a92c0(struct Obj0 *p0, s32 p1)
{
    s32 rv6;
    s32 r1;
    s32 rv5;
    s32 r3;
    s32 t0;
    s32 t1;
    s32 t2;
    s32 r4;

    rv6 = rv5;
    if (p1 == 0) {
        rv6 = 0;
    } else {
        CharaMgrPoolReset_3a9370(p0);
        r1 = MemStackNew_14e130(0x2C, p1);
        if (r1 != 0) {
            PoolCtor_36b0c0(r1);
            p0->m08 = r1;
        } else {
            p0->m08 = r1;
        }
        rv5 = (r4 & 0xFF);
        if (r1 == 0) {
            rv5 = 0;
        } else {
            r3 = CharaMaxClassSize_3afba0();
            t0 = p0->m08;
            t1 = D_004659B8;
            t2 = D_004659C0;
            r4 = PoolInit_36ae50(t0, p1, r3, t1, t2);
            rv5 = (r4 & 0xFF);
        }
        rv6 = rv5;
    }
    return rv6;
}
