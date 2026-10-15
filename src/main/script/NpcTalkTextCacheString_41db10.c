#include "types.h"

extern s32 StrCacheAdd_3eff80(s32, s32, s32, s32, s32);

struct Obj0;
struct Obj1;
struct Obj2;
struct Obj3;

struct Obj0 {
    u8 pad000[0x4];
    s32 m04;
    u8 pad008[0x10];
    struct Obj2 *m18;
    struct Obj1 *m1C;
    s32 m20;
    s32 m24;
};

struct Obj1 {
    s32 m00;
};

struct Obj2 {
    s16 m00;
    u8 pad002[0xE];
    struct Obj3 *m10;
};

struct Obj3 {
    s16 m00;
};

s32 NpcTalkTextCacheString_41db10(struct Obj0 *p0, s32 p1)
{
    struct Obj1 *t0;
    struct Obj2 *t1;
    struct Obj3 *t2;
    s32 v;
    s32 r5;

    if (p1 == 0) {
        p0->m24 = 0;
        return 0;
    }
    t0 = p0->m1C;
    if (t0 == 0) {
        return 0;
    }
    t1 = p0->m18;
    v = t0->m00;
    if (t1 != 0) {
        t2 = t1->m10;
        if (t2 != 0) {
            if (t2->m00 == 0xA) {
                v = t1->m00;
            }
        }
    }
    r5 = StrCacheAdd_3eff80(p0->m04, 2, v, p0->m20, p1);
    if (r5 == 0) {
        return 0;
    }
    p0->m24 = r5;
    return 1;
}
