#include "types.h"

typedef struct { f32 x, y, z, w; } V4;
typedef struct { f32 x, y, z; } V3;

typedef struct {
    u8 pad0[4];
    s32 *list;
    s16 count;
    u8 padA[2];
    V3 b[4];
} Obj;

extern void VecMin_1cb590(V4 *, V4 *, V4 *);
extern void VecMax_1cb5b0(V4 *, V4 *, V4 *);
extern void MapBlockCalcBounds_1dfd40(s32, V4 *, V4 *);
extern void MapBlockGetBoxBounds_1dfe50(s32, V4 *, V4 *);
extern const f32 D_0047D1EC __attribute__((section(".sdata")));
extern const f32 D_0047D1F0 __attribute__((section(".sdata")));
extern f32 D_0047E330;
extern f32 D_0047E334;
extern f32 D_0047E338;
extern f32 D_0047E33C;
extern f32 D_0047E340;
extern f32 D_0047E344;
extern f32 D_0047E348;
extern f32 D_0047E34C;
extern f32 D_0047E350;
extern f32 D_0047E354;
extern f32 D_0047E358;
extern f32 D_0047E35C;
extern f32 D_0047E360;
extern f32 D_0047E364;
extern f32 D_0047E368;
extern f32 D_0047E36C;

void MapPartTableCalcBounds_1de210(Obj *arg0) {
    V4 v0;
    V4 v1;
    V4 v2;
    V4 v3;
    V4 lo;
    V4 hi;
    s32 *p;
    s32 i;
    f32 hi_;
    f32 lo_;

    hi_ = D_0047D1F0;
    lo_ = D_0047D1EC;
    arg0->b[0].x = hi_;
    arg0->b[0].y = hi_;
    arg0->b[0].z = hi_;
    arg0->b[1].x = lo_;
    arg0->b[1].y = lo_;
    arg0->b[1].z = lo_;
    arg0->b[2].x = hi_;
    arg0->b[2].y = hi_;
    arg0->b[2].z = hi_;
    arg0->b[3].x = lo_;
    arg0->b[3].y = lo_;
    arg0->b[3].z = lo_;
    if (arg0->list == NULL || arg0->count <= 0) {
        return;
    }
    { f32 *p0_ = (f32 *)&v0; p0_[0] = D_0047E330; p0_[1] = D_0047E334; p0_[2] = D_0047E338; p0_[3] = D_0047E33C; }
    v0.x = arg0->b[0].x;
    v0.y = arg0->b[0].y;
    v0.z = arg0->b[0].z;
    { f32 *p1_ = (f32 *)&v1; p1_[0] = D_0047E340; p1_[1] = D_0047E344; p1_[2] = D_0047E348; p1_[3] = D_0047E34C; }
    v1.x = arg0->b[1].x;
    v1.y = arg0->b[1].y;
    v1.z = arg0->b[1].z;
    { f32 *p2_ = (f32 *)&v2; p2_[0] = D_0047E350; p2_[1] = D_0047E354; p2_[2] = D_0047E358; p2_[3] = D_0047E35C; }
    v2.x = arg0->b[2].x;
    v2.y = arg0->b[2].y;
    v2.z = arg0->b[2].z;
    { f32 *p3_ = (f32 *)&v3; p3_[0] = D_0047E360; p3_[1] = D_0047E364; p3_[2] = D_0047E368; p3_[3] = D_0047E36C; }
    v3.x = arg0->b[3].x;
    v3.y = arg0->b[3].y;
    v3.z = arg0->b[3].z;
    p = *(s32 * volatile *)((u8 *)arg0 + 4);
    for (i = 0; i < arg0->count; i++, p++) {
        MapBlockGetBoxBounds_1dfe50(*p, &lo, &hi);
        VecMax_1cb5b0(&v0, &v0, &lo);
        VecMin_1cb590(&v1, &v1, &hi);
        MapBlockCalcBounds_1dfd40(*p, &lo, &hi);
        VecMax_1cb5b0(&v2, &v2, &lo);
        VecMin_1cb590(&v3, &v3, &hi);
    }
    arg0->b[0].x = v0.x;
    arg0->b[0].y = v0.y;
    arg0->b[0].z = v0.z;
    arg0->b[1].x = v1.x;
    arg0->b[1].y = v1.y;
    arg0->b[1].z = v1.z;
    arg0->b[2].x = v2.x;
    arg0->b[2].y = v2.y;
    arg0->b[2].z = v2.z;
    arg0->b[3].x = v3.x;
    arg0->b[3].y = v3.y;
    arg0->b[3].z = v3.z;
}
