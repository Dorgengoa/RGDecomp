#include "types.h"

extern s32 GetActionMgr_1fdb50(void);
extern s32 ActionMgrFindById_233b50(s32, s32);
extern s32 CharaGetActionTable_214cd0(s32);
extern s32 CharaGetActInfo_214cb0(s32);
extern s32 CharaActInfoGetTrail_2155b0(s32, s32);
extern void * ActCfgTableFindVertByName_222cd0(s32, s32);
extern s32 SwordTrailSetup_215a10(s32, s32, s32, f32, f32, f32, f32);
extern s32 SwordTrailSetEndRef_2159b0(s32, s32, s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;
struct Obj2;

struct Obj0 {
    u8 pad000[0xC];
    s32 m0C;
    s32 m10;
};

struct Obj1 {
    u8 pad000[0x4];
    s32 m04;
    s32 m08;
};

struct Obj2 {
    u8 pad000[0x4];
    s32 m04;
    s32 m08;
};

s32 CharaTrailSetup_22f380(struct Obj0 *p0, s32 p1, s32 p2, s32 p3, s32 p4, f32 fa0, f32 fa1, f32 fa2, f32 fa3)
{
    s32 r0;
    s32 r1;
    s32 r2;
    s32 rv13;
    s32 r3;
    s32 r4;
    s32 rv12;
    s32 t0;
    struct Obj1 *r5;
    s32 rv11;
    s32 t1;
    struct Obj2 *r6;
    s32 rv10;
    s32 r7;
    s32 t2;
    s32 t3;
    s32 r8;
    s32 t4;
    s32 t5;
    s32 r9;

    r0 = GetActionMgr_1fdb50();
    r1 = ActionMgrFindById_233b50(r0, p1);
    if (r1 == 0) {
        return 0;
    }
    r2 = CharaGetActionTable_214cd0(r1);
    if (r2 == 0) {
        rv13 = 0;
    } else {
        r3 = CharaGetActInfo_214cb0(r1);
        r4 = CharaActInfoGetTrail_2155b0(r3, p2);
        if (r4 == 0) {
            rv12 = 0;
        } else {
            t0 = p0->m0C;
            r5 = ActCfgTableFindVertByName_222cd0(r2, t0);
            if (r5 == 0) {
                rv11 = 0;
            } else {
                t1 = p0->m10;
                r6 = ActCfgTableFindVertByName_222cd0(r2, t1);
                rv10 = 1;
                if (r6 == 0) {
                    rv10 = 0;
                } else {
                    r7 = SwordTrailSetup_215a10(r4, p3, p4, fa0, fa1, fa2, fa3);
                    t2 = r5->m08;
                    t3 = r5->m04;
                    r8 = SwordTrailSetEndRef_2159b0(r4, 0, p1, t2, t3);
                    t4 = r6->m08;
                    t5 = r6->m04;
                    r9 = SwordTrailSetEndRef_2159b0(r4, 1, p1, t4, t5);
                    rv10 = 1;
                }
                rv11 = rv10;
            }
            rv12 = rv11;
        }
        rv13 = rv12;
    }
    return rv13;
}
