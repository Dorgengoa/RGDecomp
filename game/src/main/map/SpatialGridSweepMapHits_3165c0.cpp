/* rgp:protos */
#line 1
#include "types.h"

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec003165C0;

typedef struct {
    u8 pad0[0x20];
    f32 unk20;
    s32 unk24;
    f32 unk28;
    f32 unk2C;
} Item003165C0;

class Obj003165C0 {
public:
    u8 pad0[0xB0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    void vf(Item003165C0 * a0, s32 a1) { VCM(void, (void *, Item003165C0 *, s32), 0x20, a0, a1); }
};

struct Ref003165C0 {
    Obj003165C0 **p;
    bool Valid() const { return p != 0; }
    bool Invalid() const { return !Valid(); }
    Obj003165C0 *Get() const { return p ? *p : 0; }
};

struct Node003165C0 {
    Ref003165C0 ref;
    Item003165C0 *item;
    Node003165C0 *next;
};

struct Ent003165C0 {
    Node003165C0 *head;
};

struct Scene003165C0 {
    u8 pad0[4];
    u8 heap[0x7C];
    s32 count;
    u8 pad84[0xC];
    Ent003165C0 **ents;
};

extern "C" {
u8 *ConstructNewArray_100710(void *, s32, s32, s32, s32);
void *MemStackNew_14e1b0(s32, void *);
s32 CollSphereSweepNearest_1c8880(void *, void *, u8 *, s32, s32, Item003165C0 *, Vec003165C0 *, f32 *, f32);
s32 CollRaycastNearestHit_1c8ad0(void *, void *, u8 *, s32, s32, Item003165C0 *, Vec003165C0 *, f32 *);
f32 CollRayTriTest_1c8ce0(u8 *, u8 *, u8 *, Item003165C0 *, Vec003165C0 *);
void VecSub_1cbd00(Vec003165C0 *, void *, Item003165C0 *);
s32 CollTriIsWaterMaybe_1ce5c0(u8 *);
s32 MapEvCollectCollPolysMaybe_1ff270(u8 *, s32, void *, s32);
void SpatialGridSweepMapHits_3165c0(Scene003165C0 *self, s32 idx);
}

void SpatialGridSweepMapHits_3165c0(Scene003165C0 *self, s32 idx) {
    u8 *arr;
    s32 i;
    Ent003165C0 *e;
    s32 cnt;
    Node003165C0 *node;
    Item003165C0 *item;
    f32 t;
    s32 flags;
    Vec003165C0 vec __attribute__((aligned(16)));
    u8 *p;
    s32 j;
    f32 d;
    s32 r;

    if (self->ents == 0) {
        return;
    }
    arr = ConstructNewArray_100710(MemStackNew_14e1b0(idx * 0x60 + 0x10, self->heap), 0, 0, 0x60, idx);
    for (i = 0; i < self->count; i++) {
        e = self->ents[i];
        if (e == 0) {
            continue;
        }
        cnt = MapEvCollectCollPolysMaybe_1ff270(arr, idx, (u8 *)e + 0x10, -1);
        for (node = e->head; node != 0; node = node->next) {
            item = node->item;
            t = 1.0f;
            flags = 0;
            VecSub_1cbd00(&vec, (u8 *)item + 0x10, item);
            if (item->unk20 <= 0.0f) {
                r = CollRaycastNearestHit_1c8ad0((u8 *)item + 0x30, (u8 *)item + 0x40, arr, cnt, 0x104C, item, &vec, &t);
            } else {
                r = CollSphereSweepNearest_1c8880((u8 *)item + 0x30, (u8 *)item + 0x40, arr, cnt, 0x104C, item, &vec, &t, item->unk20);
            }
            if (r >= 0) {
                flags |= 1;
                item->unk2C = t;
            } else {
                item->unk2C = 1.0f;
            }
            if (item->unk24 & 8) {
                item->unk28 = item->unk2C;
                if (vec.y < 0.0f) {
                    p = arr;
                    for (j = 0; j < cnt; j++, p += 0x60) {
                        if (CollTriIsWaterMaybe_1ce5c0(p) != 0) {
                            d = CollRayTriTest_1c8ce0(p, p + 0x10, p + 0x20, item, &vec);
                            if (d >= item->unk28) {
                                item->unk28 = d;
                                flags |= 4;
                            }
                        }
                    }
                }
            }
            if (flags != 0) {
                if (!node->ref.Invalid()) {
                    node->ref.Get()->vf(item, flags);
                }
            }
        }
    }
}
