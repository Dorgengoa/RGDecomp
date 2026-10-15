#include "types.h"
#include "vec.h"

typedef struct Rec003163f0 {
    void *a;
    s32 b;
    struct Rec003163f0 *next;
} Rec003163f0;

typedef struct Node003163f0 {
    Rec003163f0 *head;
    s32 pad4[3];
    u128 lo;
    u128 hi;
} Node003163f0;


extern "C" void VecScale_13be00(Vec4 *, Vec4 *, f32);
extern "C" void VecAdd_13be20(Vec4 *, u128 *, u128 *);
extern "C" void BBoxUnion_13dea0(void *, u128 *);
extern "C" void VecMin_13df90(Vec4 *, Vec4 *, void *);
extern "C" void VecMax_13dfe0(Vec4 *, Vec4 *, void *);
extern "C" void VecSubInPlace_13e050(Vec4 *, void *);
extern "C" s32 AabbOverlap_13e0e0(u128 *, u128 *, void *, void *);
extern "C" void *MemStackNew_14e230(s32, void *);
extern "C" void JdgGridNodeGetBounds_3171f0(s32, u128 *);

extern "C" Rec003163f0 *SpatialGridInsert_3163f0(u8 *arg0, s32 arg1)
{
    Node003163f0 *grid;
    u128 sp70;
    bool created;
    s32 x;
    s32 y;
    u128 sp60;
    f32 f2;
    Node003163f0 *node;
    Vec4 sp50;
    Node003163f0 **cell;
    Rec003163f0 *rec;
    JdgGridNodeGetBounds_3171f0(arg1, &sp60);
    if (AabbOverlap_13e0e0(&sp60, &sp70, arg0 + 0x60, arg0 + 0x70) == 0) {
        return 0;
    }
    VecAdd_13be20(&sp50, &sp60, &sp70);
    VecScale_13be00(&sp50, &sp50, 0.5f);
    VecMax_13dfe0(&sp50, &sp50, arg0 + 0x70);
    VecMin_13df90(&sp50, &sp50, arg0 + 0x60);
    VecSubInPlace_13e050(&sp50, arg0 + 0x70);
    f2 = *(f32 *)(arg0 + 0x8C);
    x = (s32)(sp50.x / f2);
    y = (s32)(sp50.z / f2);
    if (x < 0) {
        x = 0;
    }
    if (x >= *(s32 *)(arg0 + 0x84)) {
        x = *(s32 *)(arg0 + 0x84) - 1;
    }
    if (y < 0) {
        y = 0;
    }
    if (y >= *(s32 *)(arg0 + 0x88)) {
        y = *(s32 *)(arg0 + 0x88) - 1;
    }
    cell = &(*(Node003163f0 ***)(arg0 + 0x90))[x + y * *(s32 *)(arg0 + 0x84)];
    created = false;
    if (*cell == 0) {
        node = (Node003163f0 *)MemStackNew_14e230(0x30, arg0 + 4);
        if (node != 0) {
            node->head = 0;
        }
        *cell = node;
        created = true;
    }
    grid = *cell;
    if (grid != 0) {
        if ((rec = (Rec003163f0 *)MemStackNew_14e230(0xC, arg0 + 4)) != 0) {
            rec->a = 0;
            rec->b = 0;
            rec->next = 0;
        }
        if (rec != 0) {
            rec->next = grid->head;
            grid->head = rec;
        }
        if (created) {
            grid = *cell;
            grid->lo = sp60;
            grid->hi = sp70;
        } else {
            BBoxUnion_13dea0(&(*cell)->lo, &sp60);
        }
        return rec;
    }
    return 0;
}
