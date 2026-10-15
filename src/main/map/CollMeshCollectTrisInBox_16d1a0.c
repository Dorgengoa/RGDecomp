#include "types.h"
#include "vec.h"

typedef struct {
    Vec4 min;
    Vec4 max;
} Box;

typedef struct {
    s32 a;
    s32 b;
    u8 pad[8];
    Box box;
    s32 n;
} Req;

typedef struct {
    u8 pad0[0x10];
    Vec4 v10;
    Vec4 v20;
    u8 pad30[0x20];
    s32 n50;
    s32 p54;
    s32 *p58;
} Obj;

s32 CollMeshGatherFacesInBox_16cd90(Obj *, s32, s32, s32, s32, Box *, s32);
s32 CollMeshQuadTreeCollectTris_16cfe0(Obj *, s32, Req *, s32);

s32 CollMeshCollectTrisInBox_16d1a0(Obj *arg0, s32 arg1, s32 arg2, Box *arg3, s32 arg4) {
    Req req;
    s32 *p;

    if (arg0->p54 == 0 || arg0->n50 <= 0) {
        return 0;
    }
    if (arg4 <= 0) {
        return 0;
    }
    if (!(arg3->max.x <= arg0->v10.x)) {
        return 0;
    }
    if (!(arg3->max.y <= arg0->v10.y)) {
        return 0;
    }
    if (!(arg3->max.z <= arg0->v10.z)) {
        return 0;
    }
    if (arg3->min.x < arg0->v20.x) {
        return 0;
    }
    if (arg3->min.y < arg0->v20.y) {
        return 0;
    }
    if (arg3->min.z < arg0->v20.z) {
        return 0;
    }
    p = arg0->p58;
    if (p == NULL) {
        return CollMeshGatherFacesInBox_16cd90(arg0, arg0->p54, arg0->n50, arg1, arg2, arg3, arg4);
    }
    req.a = arg1;
    req.b = arg2;
    req.box.min = arg3->min;
    req.box.max = arg3->max;
    req.n = arg4;
    return CollMeshQuadTreeCollectTris_16cfe0(arg0, *p, &req, 1);
}
