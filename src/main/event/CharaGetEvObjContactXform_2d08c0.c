#include "types.h"

extern s32 GetActionMgr_1fdb50(void);
extern s32 ActionMgrFindById_233b50(s32, s32);
extern void * CharaGetEvObjContact_214990(s32);
extern s32 GetEventObjMgr_2d1960(void);
extern s32 EventObjMgrFindObjByName_2e9920(s32, s32, s32);
extern s32 EvObjGetXform_2f9c90(s32);
extern s32 EventObjGetPos_2e7640(s32, s32);
extern s32 EventObjGetRot_2e7670(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    s16 m04;
};

s32 CharaGetEvObjContactXform_2d08c0(s32 p0, s32 p1, s32 p2)
{
    s32 r0;
    s32 r1;
    s32 rv9;
    struct Obj0 *r2;
    s32 r3;
    s16 t0;
    s32 t1;
    s32 r4;
    s32 rv8;
    s32 r5;
    s32 r6;
    s32 r7;

    r0 = GetActionMgr_1fdb50();
    r1 = ActionMgrFindById_233b50(r0, p0);
    rv9 = rv8;
    if (r1 == 0) {
        rv9 = 0;
    } else {
        r2 = CharaGetEvObjContact_214990(r1);
        r3 = GetEventObjMgr_2d1960();
        t0 = r2->m04;
        t1 = r2->m00;
        r4 = EventObjMgrFindObjByName_2e9920(r3, t1, t0);
        rv8 = 1;
        if (r4 == 0) {
            rv8 = 0;
        } else {
            r5 = EvObjGetXform_2f9c90(r4);
            r6 = EventObjGetPos_2e7640(r5, p1);
            r7 = EventObjGetRot_2e7670(r5, p2);
            rv8 = 1;
        }
        rv9 = rv8;
    }
    return rv9;
}
