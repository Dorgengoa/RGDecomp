#include "types.h"

extern s32 AreaBoxGetBoundsThunk_1e97b0(void *);
extern s32 MapBlockGetBoxArray1_1dfec0(void *);
extern s32 MapBlockGetBoxCount1_1dfeb0(void *);
extern void AreaBoxGetBounds_1e97b0(s32, void *, void *);
extern void VecMax_1cb5b0(void *, void *, void *);
extern void VecMin_1cb590(void *, void *, void *);
typedef unsigned __int128 u128;

extern f32 D_0047D1EC;
extern f32 D_0047D1F0;

struct Obj0;
struct Obj1;
struct Obj2;

struct Obj0 {
    u8 pad000[0x2C];
    s32 m2C;
};

struct Obj1 {
    f32 m00;
    f32 m04;
    f32 m08;
    s32 m0C;
};

struct Obj2 {
    f32 m00;
    f32 m04;
    f32 m08;
    s32 m0C;
};

void MapBlockCalcBounds_1dfd40(struct Obj0 *p0, struct Obj1 *p1, struct Obj2 *p2)
{
    u128 v70;
    u128 v60;
    s32 t0;
    s32 rv1;
    s32 r0;
    f32 t1;
    f32 t2;
    s32 r2;
    s32 rv9;
    s32 r3;
    s32 l4;
    s32 l5;

    t0 = p0->m2C;
    rv1 = 0x3F800000;
    if ((t0 & 0x100) != 0) {
        r0 = AreaBoxGetBoundsThunk_1e97b0((struct Obj0 *)((u8 *)p0 + 0x74));
        rv1 = r0;
    } else {
        t1 = D_0047D1F0;
        t2 = D_0047D1EC;
        p1->m00 = t1;
        p1->m04 = t1;
        p1->m08 = t1;
        p1->m0C = 0x3F800000;
        p2->m00 = t2;
        p2->m04 = t2;
        p2->m08 = t2;
        p2->m0C = 0x3F800000;
        rv1 = 0x3F800000;
    }
    r2 = MapBlockGetBoxArray1_1dfec0(p0);
    rv9 = r2;
    if (r2 != 0) {
        r3 = MapBlockGetBoxCount1_1dfeb0(p0);
        if (r3 > 0) {
            l4 = r2;
            l5 = 0;
            while (l5 < r3) {
                AreaBoxGetBounds_1e97b0(l4, &v70, &v60);
                VecMax_1cb5b0(p1, p1, &v70);
                VecMin_1cb590(p2, p2, &v60);
                l5 = (l5 + 1);
                l4 = (l4 + 0x4C);
            }
        }
        rv9 = r3;
    }
}
