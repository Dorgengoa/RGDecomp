#include "types.h"

extern s32 GetMapMgr_201a90(void);
extern s32 MapFindObjInAreaById_1e44b0(s32, s32, void *);
extern void NodeGetTranslation_186650(s32, void *);
extern void NodeGetRotation_1865e0(s32, void *);
extern void VecAdd_1cbdc0(void *, void *, void *);
extern void VecWrapAngle_1cbe90(void *, void *);
extern void NodeSetTranslation_1866b0(s32, void *);
extern void NodeSetRotation_186620(s32, void *);
typedef unsigned __int128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x24];
    s32 m24;
    u8 pad028[0x20];
    s32 m48;
};

void MapNodeMoveStep_2fa4a0(struct Obj0 *p0)
{
    u128 v40;
    u128 v30;
    s32 t0;
    s32 r0;
    s32 t1;
    s32 r1;

    t0 = p0->m48;
    p0->m48 = (t0 + -1);
    if ((t0 + -1) >= 0) {
        r0 = GetMapMgr_201a90();
        t1 = p0->m24;
        r1 = MapFindObjInAreaById_1e44b0(r0, t1, (struct Obj0 *)((u8 *)p0 + 0x28));
        if (r1 == 0) {
            p0->m48 = -1;
        } else {
            NodeGetTranslation_186650(r1, &v40);
            NodeGetRotation_1865e0(r1, &v30);
            VecAdd_1cbdc0(&v40, &v40, p0);
            VecAdd_1cbdc0(&v30, &v30, (struct Obj0 *)((u8 *)p0 + 0x10));
            VecWrapAngle_1cbe90(&v30, &v30);
            NodeSetTranslation_1866b0(r1, &v40);
            NodeSetRotation_186620(r1, &v30);
        }
        return;
    }
}
