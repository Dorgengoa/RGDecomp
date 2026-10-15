#include "types.h"

/* Hub function, called from many already-merged src/ files.  Walks an
   intrusive list (next at +8) of "bucket" nodes; each bucket's +0 field is
   a tag object with two u16 tag fields (+0, +2) and a flags halfword at
   +0x1C.  arg1 is the u16 key to search for, arg3 gates whether the
   secondary tag (+2) is also compared, arg2 selects whether the found
   tag's flags bit0 is set or cleared. */

struct Tag291110 {
    u16 f0;
    u16 f2;
    u8 pad4[0x18];
    s16 f1C;
};

struct N291110 {
    struct Tag291110 *f0;
    u8 pad4[4];
    struct N291110 *f8;
};

struct Head291110 {
    struct N291110 *f0;
};

void UiSetWidgetsVisibleById_291110(struct Head291110 *head, s32 arg1, s32 arg2, s32 arg3)
{
    struct N291110 *cur;
    struct Tag291110 *found;
    struct Tag291110 *node;
    s32 mask;
    s32 tmp;

    cur = head->f0;
    mask = -2;
    arg1 = (u16)arg1;
    goto test;
body:
    node = cur->f0;
    if (node == 0) {
        return;
    }
    found = 0;
    if (node->f0 == arg1) {
        found = node;
    }
    if (arg3 != 0) {
        if (node->f2 != 0) {
            if (node->f2 == arg1) {
                found = node;
            }
        }
    }
    if (found != 0) {
        if (arg2 != 0) {
            tmp = found->f1C;
            tmp &= mask;
            found->f1C = (u16)tmp;
        } else {
            found->f1C |= 1;
        }
    }
    cur = cur->f8;
test:
    if (cur != 0) {
        goto body;
    }
}
