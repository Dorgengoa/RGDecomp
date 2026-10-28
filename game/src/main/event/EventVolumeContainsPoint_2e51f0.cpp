/* rgp:protos */
#line 1
#include "types.h"

typedef struct Vec3 {
    f32 x;
    f32 y;
    f32 z;
} Vec3;

typedef struct Obj {
    u8 pad0[0x34];
    f32 x34;
    f32 x38;
    f32 x3C;
} Obj;


extern "C" {
f32 VecLengthSqXZ_1cb450(Vec3 *, void *);
f32 VecLengthSq_1cb470(Vec3 *, void *);
void EventVolumeWorldToLocal_2e5060(Obj *, Vec3 *, s32);
s32 EventVolumeGetClipMode_2e56e0(Obj *);
s32 EventVolumeGetShape_2e56f0(Obj *);
}

static inline u8 inRange(f32 *v, f32 *lim) {
    f32 a;
    if (*v < 0.0f) {
        a = -*v;
    } else {
        a = *v;
    }
    return a <= *lim;
}

extern "C" u8 EventVolumeContainsPoint_2e51f0(Obj *self, s32 arg1, f32 pad) {
    Vec3 e __attribute__((aligned(16)));
    __attribute__((aligned(16))) unsigned char rgp_blk1[(0x0 + sizeof(Vec3)) + (0x10)];
    u8 *p;
    u32 n;
    u8 r;
    u8 res;

    EventVolumeWorldToLocal_2e5060(self, &(*(Vec3 *)(rgp_blk1 + 0x0)), arg1);
    switch (EventVolumeGetClipMode_2e56e0(self)) {
    case 0:
        break;
    case 0x10:
        (*(Vec3 *)(rgp_blk1 + 0x0)).y = 0.0f;
        break;
    case 0x20:
        if ((*(Vec3 *)(rgp_blk1 + 0x0)).y < 0.0f) {
            return 0;
        }
        break;
    case 0x30:
        if (!((*(Vec3 *)(rgp_blk1 + 0x0)).y <= 0.0f)) {
            return 0;
        }
        break;
    default:
        return 0;
    }
    p = (u8 *)&e;
    n = 0xC;
    if (p != 0) {
        do {
            *p = 0;
            n--;
            p++;
        } while (n != 0);
    }
    e.x = self->x34 + pad;
    e.y = self->x38 + pad;
    e.z = self->x3C + pad;
    switch (EventVolumeGetShape_2e56f0(self)) {
    case 1:
        (*(Vec3 *)(rgp_blk1 + 0x0)).z /= e.z;
        (*(Vec3 *)(rgp_blk1 + 0x0)).x /= e.x;
        (*(Vec3 *)(rgp_blk1 + 0x0)).y /= e.y;
        return VecLengthSq_1cb470(&(*(Vec3 *)(rgp_blk1 + 0x0)), 0) <= 1.0f;
    case 2:
        (*(Vec3 *)(rgp_blk1 + 0x0)).z /= e.z;
        (*(Vec3 *)(rgp_blk1 + 0x0)).x /= e.x;
        r = VecLengthSqXZ_1cb450(&(*(Vec3 *)(rgp_blk1 + 0x0)), 0) <= 1.0f;
        if (r) {
            r = inRange(&(*(Vec3 *)(rgp_blk1 + 0x0)).y, &e.y);
        }
        return r;
    case 3:
        r = inRange(&(*(Vec3 *)(rgp_blk1 + 0x0)).x, &e.x);
        if (r) {
            r = inRange(&(*(Vec3 *)(rgp_blk1 + 0x0)).y, &e.y);
        }
        res = r;
        if (r) {
            res = inRange(&(*(Vec3 *)(rgp_blk1 + 0x0)).z, &e.z);
        }
        return res;
    }
    return 0;
}
