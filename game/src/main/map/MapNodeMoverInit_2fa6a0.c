/* rgp:protos */
#define RGP_SELF_MapNodeMoverInit_2fa6a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void strcpy(void *, s32);
typedef rg_u128 u128;

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x34];
    s32 m34;
    s32 m38;
};

struct Obj1 {
    u8 pad000[0x20];
    s32 m20;
    s32 m24;
};

s32 MapNodeMoverInit_2fa6a0(struct Obj1 *p0, s32 p1, s32 p2, s32 p3)
{
    u128 v80[4];
    u128 v70;
    u128 v60;
    s32 r1;
    struct Obj0 *r2;

    MapNodeMoverClear_2fa7c0(p0);
    if (p1 >= 0) {
        if (p2 >= 0) {
            if (p3 != 0) goto ok;
        }
    }
    return 0;
ok:
    r1 = ((s32)GetMapMgr_201a90());
    r2 = MapFindObjInAreaById_1e44b0(r1, p2, p3);
    if (r2 == 0) {
        return 0;
    }
    NodeCalcWorldMatrixThunk_186130(r2, v80);
    r2->m34 = 0;
    r2->m38 = 0;
    MatToRotPos_1cade0(&v70, &v60, v80);
    NodeSetTranslation_1866b0(r2, &v60);
    NodeSetRotation_186620(r2, &v70);
    p0->m20 = p1;
    p0->m24 = p2;
    strcpy((struct Obj1 *)((u8 *)p0 + 0x28), p3);
    return 1;
}
