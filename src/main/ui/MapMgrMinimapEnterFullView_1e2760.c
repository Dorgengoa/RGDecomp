#include "types.h"

extern void * GetGameData_1fede0(void);
extern s32 GetActionMgr_1fdb50(void);
extern void GetMapMgr_201a90(void);
extern s32 ActionMgrFindById_233b50(s32, s32);
extern s32 CharaGetPos_2388a0(s32, void *);
extern s32 GetMinimapMgr_201a70(void);
extern s32 MinimapMgrSetCenterPos_321910(s32, void *);
extern s32 MinimapSetFullView_1d9ca0(void *);
typedef unsigned __int128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;
struct Obj2;

struct Obj0 {
    u8 pad000[0x18];
    struct Obj1 *m18;
};

struct Obj1 {
    u8 pad000[0x18E];
    s16 m18E;
};

struct Obj2 {
    u8 pad000[0x60];
    s32 m60;
    u8 pad064[0x223C];
    s32 m22A0;
    s32 m22A4;
    s32 m22A8;
    s32 m22AC;
};

void MapMgrMinimapEnterFullView_1e2760(struct Obj2 *p0)
{
    u128 v40;
    struct Obj0 *r0;
    s32 r1;
    struct Obj1 * t0;
    s16 t1;
    s32 r3;
    s32 rv7;
    s32 r4;
    s32 r5;
    s32 r6;
    struct Obj2 * l9;
    s32 l8;
    s32 r10;
    s32 t2;

    r0 = (struct Obj0 *)GetGameData_1fede0();
    r1 = GetActionMgr_1fdb50();
    GetMapMgr_201a90();
    t0 = r0->m18;
    t1 = r0->m18->m18E;
    r3 = ActionMgrFindById_233b50(r1, t1);
    rv7 = r3;
    if (r3 != 0) {
        r4 = CharaGetPos_2388a0(r3, &v40);
        r5 = GetMinimapMgr_201a70();
        r6 = MinimapMgrSetCenterPos_321910(r5, &v40);
        rv7 = r6;
    }
    l9 = (struct Obj2 *)((u8 *)p0 + 0x1928);
    l8 = 0;
    do {
        r10 = MinimapSetFullView_1d9ca0(l9);
        l8 = (l8 + 1);
        l9 = (struct Obj2 *)((u8 *)l9 + 0x1CC);
    } while (l8 < 4);
    p0->m22A0 = 0;
    p0->m22A4 = 0;
    p0->m22A8 = 0;
    p0->m22AC = 0x3F800000;
    t2 = p0->m60;
    p0->m60 = (t2 | 4);
}
