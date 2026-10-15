#include "types.h"

extern void * GetGameData_1fede0(void);
extern s32 RecordGetBlobSize_430430(s32);
extern s32 RecordGetBlobData_430170(s32);
extern void SaveFilePatchInsectTeams_3e4ad0(void *, s32, s32, s32, s32);
extern void memcpy(s32, s32, s32);
extern s32 SlotRecordStore_3e52f0(void *, s32, s32, s32);
extern void SaveIconSysFormatTitle_3ee980(s32, void *, void *, void *);
extern void strcpy(void *, void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00483188;
extern s32 D_0048318C;

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x24];
    s32 m24;
};

struct Obj1 {
    u8 pad000[0xE6];
    s16 mE6;
    u8 pad0E8[0x406];
    s16 m4EE;
    u8 pad4F0[0x1C];
    s32 m50C;
    s32 m510;
};

s32 SaveDataBuildWriteBuffer_375b80(struct Obj1 *p0)
{
    s32 vCC;
    s32 vC8;
    s32 v40[34];
    struct Obj0 *r0;
    s32 t0;
    s32 r1;
    s32 t1;
    s32 r2;
    s32 t2;
    s32 t3;
    s32 t4;
    s32 t5;
    s32 t6;
    s32 t7;
    s16 t8;
    s32 t9;
    s32 r5;
    s32 t10;

    r0 = GetGameData_1fede0();
    if (r0 == 0) {
        return 0;
    }
    t0 = r0->m24;
    r1 = RecordGetBlobSize_430430(t0);
    t1 = r0->m24;
    r2 = RecordGetBlobData_430170(t1);
    t2 = D_00483188;
    t3 = D_0048318C;
    SaveFilePatchInsectTeams_3e4ad0(r0, r2, r1, t2, t3);
    t4 = *(volatile s32 *)&p0->m50C;
    t5 = *(volatile s32 *)&D_00483188;
    t6 = *(volatile s32 *)&D_0048318C;
    memcpy(t4, t5, t6);
    t7 = D_0048318C;
    p0->m510 = t7;
    t8 = p0->m4EE;
    t9 = p0->m50C;
    r5 = SlotRecordStore_3e52f0(r0, t8, t9, t7);
    if (r5 != 0) {
        SaveIconSysFormatTitle_3ee980(r5, v40, &vCC, &vC8);
        strcpy((struct Obj1 *)((u8 *)p0 + 0x1A0), v40);
        t10 = vCC;
        p0->mE6 = t10;
    }
    return r5;
}
