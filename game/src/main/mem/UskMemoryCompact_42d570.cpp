/* rgp:protos */
#line 1
#include "types.h"

typedef struct Item Item;
typedef struct Sub {
    Item *next;
    s32 flags;
    s32 val;
} Sub;
struct Item {
    u8 pad0[0x10];
    Sub sub;
};

typedef struct Obj {
    u8 pad0[0x40];
    s32 x40;
} Obj;

extern "C" {
s32 UskMemoryCompactToEndMaybe_42d040(Obj *, bool);
s32 UskMemoryCompactToStartMaybe_42d310(Obj *, bool);
Item * DListGetHead_42ea60(void *);
Item *DListGetNext_42eb30(Item *);
}

extern "C" s32 UskMemoryCompact_42d570(Obj *o)
{
    Item *it;
    bool a;
    bool b;
    bool force;
    bool c1;
    bool c2;
    s32 sum;
    s32 v;

    if (o->x40 & 2) {
        return 0;
    }
    if (o->x40 & 1) {
        return 0;
    }
    o->x40 |= 1;
    it = DListGetHead_42ea60((void *)o);
    a = false;
    b = false;
    for (; it != NULL; it = DListGetNext_42eb30(it)) {
        {
            Sub *sb = &it->sub;
            if (!(sb->flags & 2) || sb->val == 0) {
                continue;
            }
        }
        if (it->sub.flags & 1) {
            b = true;
        } else {
            a = true;
        }
        if (a && b) {
            break;
        }
    }
    force = it == NULL;
    c1 = true;
    c2 = c1;
    sum = 0;
again:
    for (;;) {
        if (!c1) {
            break;
        }
        v = UskMemoryCompactToStartMaybe_42d310(o, force);
        sum += v;
        c1 = v > 0;
        if (!c2) {
            break;
        }
        v = UskMemoryCompactToEndMaybe_42d040(o, force);
        sum += v;
        c2 = v > 0;
    }
    if (!force) {
        force = true;
        c1 = force;
        c2 = force;
        goto again;
    }
    o->x40 &= ~1;
    return sum > 0;
}
