#include "types.h"

extern s32 SlotGetInt_15f720(s32);
extern s32 strlen(s32);
extern s32 BytesToQwords_18a6c0(s32);
extern s32 MemStackAllocQw_14d950(s32, s32);
extern void strcpy(s32, s32);
extern s32 MapFuncEffectIdStub_1896d0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00481250;
extern s32 D_0048125C;
extern struct Obj1 * D_004812DC;

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x60];
    s32 m60;
};

struct Obj1 {
    u8 pad000[0x40];
    s32 m40;
    u8 pad044[0x20];
    s32 m64;
};

s32 MapCfgFuncEffectName_18a600(s32 p0)
{
    struct Obj1 * t0;
    s32 r0;
    s32 rv8;
    s32 r1;
    s32 r2;
    s32 t1;
    s32 r3;
    struct Obj0 *rv5;
    struct Obj1 * t2;
    struct Obj1 * t3;
    s32 t4;
    s32 r6;
    struct Obj1 * rv7;
    struct Obj1 * t5;
    struct Obj1 * t6;

    t0 = D_004812DC;
    if (t0 == 0) {
        return 0;
    }
    r0 = SlotGetInt_15f720(p0);
    rv8 = 1;
    if (r0 == 0) {
        rv8 = 0;
    } else {
        r1 = strlen(r0);
        r2 = BytesToQwords_18a6c0((r1 + 1));
        t1 = D_0048125C;
        r3 = MemStackAllocQw_14d950(t1, r2);
        if (r3 != 0) {
            strcpy(r3, r0);
            t2 = D_004812DC;
            rv5 = (struct Obj0 *)t2;
        } else {
            t3 = D_004812DC;
            rv5 = (struct Obj0 *)t3;
        }
        rv5->m60 = r3;
        t4 = D_00481250;
        r6 = MapFuncEffectIdStub_1896d0(t4, r3);
        if (r6 >= 0) {
            t5 = D_004812DC;
            D_004812DC->m64 = r6;
            rv7 = (struct Obj1 *)r6;
        } else {
            t6 = D_004812DC;
            D_004812DC->m40 = 0;
            rv7 = (struct Obj1 *)t6;
        }
        rv8 = 1;
    }
    return rv8;
}
