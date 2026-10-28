/* rgp:protos */
#define RGP_SELF_McSaveSerialize_375c60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 strcpy(void *, void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xE6];
    s16 mE6;
    u8 pad0E8[0x406];
    s16 m4EE;
    u8 pad4F0[0xC];
    s16 m4FC;
    u8 pad4FE[0xE];
    s32 m50C;
    s32 m510;
};

s32 McSaveSerialize_375c60(struct Obj0 *p0)
{
    s32 vBC;
    s32 vB8;
    s32 v30[34] __attribute__((aligned(16)));
    s32 r0;
    s16 t0;
    s32 t1;
    s32 r1;
    s16 t2;
    s32 t3;
    s32 r2;
    s32 r4;
    s32 t4;

    r0 = ((s32)GetGameData_1fede0());
    if (r0 == 0) {
        return 0;
    }
    t0 = p0->m4FC;
    t1 = p0->m50C;
    r1 = SaveDataSerialize_3e6100(r0, t1, 0x20000, (t0 != 0));
    p0->m510 = r1;
    t2 = p0->m4EE;
    t3 = p0->m50C;
    r2 = ((s32)SlotRecordStore_3e52f0(r0, t2, t3, r1));
    if (r2 != 0) {
        SaveIconSysFormatTitle_3ee980(r2, v30, &vBC, &vB8);
        r4 = ((s32)strcpy((struct Obj0 *)((u8 *)p0 + 0x1A0), v30));
        t4 = vBC;
        p0->mE6 = t4;
    }
    return r2;
}
