#include "types.h"

extern s32 GetCharaResMgr_1fdb60(void);
extern s32 GetCharaDataMgr_1fdb70(void);
extern void * GetGameData_1fede0(void);
extern s32 ScriptGetInt_2490f0(s32);
extern void * CharaMgrPoolFindByDataId_3a8a70(s32, s32, s32, s32, s32, s32, s32);
extern s32 CharaResRequestPc_1f2c90(s32, s32, s32, s32, s32);
extern s32 CharaDataMgrUpdate_1ed9e0(s32);
extern s32 CharaResUpdateAllRecs_1f2e60(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern struct Obj0 * gEventContext;

struct Obj0;
struct Obj1;
struct Obj2;

struct Obj0 {
    s32 m00;
};

struct Obj1 {
    u8 pad000[0x14];
    s32 m14;
};

struct Obj2 {
    u8 pad000[0xC];
    s32 m0C;
};

s32 EvCmdCharaResRequest_243ed0(s32 p0)
{
    struct Obj0 * t0;
    s32 t1;
    s32 r0;
    s32 r1;
    struct Obj1 *r2;
    s32 r3;
    s32 t2;
    struct Obj2 *r4;
    s32 rv8;
    s32 t3;
    s32 r5;
    s32 r6;
    s32 r7;

    t0 = gEventContext;
    t1 = gEventContext->m00;
    r0 = GetCharaResMgr_1fdb60();
    r1 = GetCharaDataMgr_1fdb70();
    r2 = GetGameData_1fede0();
    r3 = ScriptGetInt_2490f0(p0);
    t2 = r2->m14;
    r4 = CharaMgrPoolFindByDataId_3a8a70(t2, r3, 1, 1, 0, 0, 0);
    rv8 = 1;
    if (r4 == 0) {
        rv8 = 0;
    } else {
        t3 = r4->m0C;
        r5 = CharaResRequestPc_1f2c90(r0, t1, t3, r3, 1);
        r6 = CharaDataMgrUpdate_1ed9e0(r1);
        r7 = CharaResUpdateAllRecs_1f2e60(r0, t1);
        rv8 = 1;
    }
    return rv8;
}
